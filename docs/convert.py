#!/usr/bin/env python2

# Convert MOOSE markdown documents to LaTeX using pandoc and some
# custom elements. Pypandoc calls pandoc to do the bulk of the
# conversion from markdown to LaTeX. There are a few elements
# in MOOSE markdown that are not converted by pandoc that this
# script converts.
#
# Requirements:
# pypandoc (github.com/bebraw/pypandoc)
# pandoc (pandoc.org)
#
# Chris Green, 2018
# chris.green@csiro.au

import pypandoc
import re
import os
import argparse
parser = argparse.ArgumentParser()

def main():
    # Command line arguments
    parser.add_argument("--file", "-f", type=str, required=True, help = "Markdown file to be converted to LaTeX")
    args = parser.parse_args()

    # Read the MOOSE markdown file and convert it to LaTeX using pypandoc
    input = args.file
    base = os.path.splitext(input)[0]

    contents = pypandoc.convert_file(input, 'latex', extra_args=['--wrap=preserve'])

    # Split the converted contents of the file into seperate lines
    contents = contents.splitlines()

    # Empty list for updated contents
    modified = []

    line_iter = iter(contents)

    # We define an alert environment in the LaTeX template used to replace !alert
    # Similarly, replace !listing with the LaTeX version !lstinputlisting
    for line in line_iter:
        if line.startswith('!alert note'):
            text = processAlert(line, line_iter)
            modified.extend(text)

        elif line.startswith('!listing'):
            text = processListing(line)
            modified.extend(text)

        elif line.startswith('!media'):
            text = processMedia(line, line_iter)
            modified.extend(text)

        elif line.startswith('!bibtex'):
            pass

        else:
            modified.append(line)

    # Process any strong characters, replacing +word+ with \textbf{word}
    new_modifed = []
    line_iter = iter(modified)
    for line in line_iter:
        if ("+" in line):
            line = processStrong(line)
            new_modifed.append(line)
        else:
            new_modifed.append(line)

    modified = new_modifed

    # Process any figure links, converting them to LaTex
    new_modifed = []
    line_iter = iter(modified)
    for line in line_iter:
        if ("{[}" in line):
            line = processFigureLink(line)
            new_modifed.append(line)
        else:
            new_modifed.append(line)

    modified = new_modifed

    # Process any equation links, converting them to LaTex
    new_modifed = []
    line_iter = iter(modified)
    for line in line_iter:
        if ("{[}" in line):
            line = processEquationLink(line)
            new_modifed.append(line)
        else:
            new_modifed.append(line)

    modified = new_modifed

    # Process any {[} and {]} characters from auto links, removing them
    new_modifed = []
    line_iter = iter(modified)
    for line in line_iter:
        if ("{[}" in line):
            line = processAutoLink(line)
            new_modifed.append(line)
        else:
            new_modifed.append(line)

    modified = new_modifed

    # Process any citet commands
    new_modifed = []
    line_iter = iter(modified)
    for line in line_iter:
        if ("citet" in line):
            line = processCitet(line)
            new_modifed.append(line)
        else:
            new_modifed.append(line)

    modified = new_modifed

    # Process any citep commands
    new_modifed = []
    line_iter = iter(modified)
    for line in line_iter:
        if ("citep" in line):
            line = processCitep(line)
            new_modifed.append(line)
        else:
            new_modifed.append(line)

    modified = new_modifed

    # Write output to output.tex
    output = os.path.split(base)[1]
    output = "report/" + output + ".tex"
    file = open(output, 'w')

    for item in modified:
        file.write(item)
        file.write("\n")

    file.close()

# Function to replace !alert commands with the alert environment
def processAlert(line, line_iter):
    '''Wraps text in !alert with \begin{alert}...\end{alert} and returns it as a list'''
    text = []

    text.append(line.replace('!alert note', "\\begin{alert}\n"))

    alert = True
    while alert:
        try:
            line = next(line_iter)
        except StopIteration:
            text.append("\\end{alert}")
            alert = False
        else:
            if (len(line.strip())==0):
                text.append("\\end{alert}\n")
                alert = False
            else:
                text.append(line)

    return text

# Function to replace !media commands with the figure environment
def processMedia(line, line_iter):
    '''Wraps text in !media with \begin{figure}...\end{figure} and returns it as a list'''
    text = []

    text.append("\\begin{figure}[ht]")
    text.append("\\begin{center}")

    # Default is to have !media filename
    filename = line.split()[1]
    text.append("\\includegraphics{../content/" + filename + "}")

    # If the line has only !media filename, then look at the next lines to get
    # caption and label
    # TODO: should also handle case where it as all one line
    if (len(line.split()) == 2):
        media = True
        while media:
            try:
                line = next(line_iter)
            except StopIteration:
                media = False
            else:
                if (len(line.strip())==0):
                    media = False
                else:
                    if line.startswith("caption"):
                        caption = line.split('=',1)[1]
                        text.append("\\caption{" + caption + "}")

                    if line.startswith("id"):
                        id = line.split('=',1)[1]
                        text.append("\\label{" + id + "}")
    else:
        print("!media elements should be formatted as:\n!media filename\n    caption=caption\n    id=id")

    text.append("\\end{center}")
    text.append("\\end{figure}\n")
    return text

# Function to replace !lsiting with LaTeX lstinputlisting
def processListing(line):
    '''Convert !listing with LaTeX lstinputlisting'''
    text = []

    # This should have the one of the three forllowing forms:
    # !listing file
    # !listing file block=name
    # !listing file start=start end=end
    words = line.split()
    # Filename (note: pandoc converts underscores in filename with \_)
    filename = "../" + words[1].replace("\_", "_")

    block_found = False

    if (len(words) == 2):
        # Don't do anything
        pass

    elif (len(words) == 3):
        # block keyword
        block = "[" + words[2].split("=")[1] + "]"

        # Once we have the filename and the block keyword, we have to
        # find the line number of the start and end of the block. The
        # line number of the start is the line where the block is, and
        # the line number at the end is the next line where a [] is present
        with open(filename) as file:
            for num, line in enumerate(file, 1):
                if block in line:
                    block_found = True
                    block_start = num
                if block_found and line.startswith('[]'):
                    block_end = num
                    break

        file.close()

    elif (len(words) == 4):
        # start/end keywords
        start = "[" + words[2].split("=")[1] + "]"
        end =  "[" + words[3].split("=")[1] + "]"

        # Once we have the filename and the start/end keywords, we have to
        # find the line number of the start and end of the block. The
        # line number of the start is the line where the start block is, and
        # the line number at the end is the line where the end block begins
        with open(filename) as file:
            for num, line in enumerate(file, 1):
                if start in line:
                    block_found = True
                    block_start = num
                if block_found and end in line:
                    # Block end is the line before end is found
                    block_end = num - 1

        file.close()

    else:
        print("No heading found for "), line

    if (len(words) == 2):
        text.append("\\lstinputlisting{../" + filename + "}")

    if (block_found):
        # Now we can add the lstinputlisting command
        text.append("\\lstinputlisting[firstline=" + str(block_start) + ", lastline=" + str(block_end) +"]{../" + filename + "}")

    return text

# Function to replace strong markdown with \textbf
def processStrong(line):
    '''Replace +word+ with \textbf{word}'''
    result = re.sub(r'\+(.[a-z,A-Z]+)\+', r'\\textbf{\1}', line)

    return result

# Function that simply removes any automatic links from the markdown
def processAutoLink(line):
    '''Removes {[} and {]} characters'''
    result = re.sub(r'{\[}(.[a-z,A-Z].*?){\]}', r'\1', line)

    return result

# Process figure links that are of the form: {[}fig:label{]}
def processFigureLink(line):
    '''Convert figure links to \ref{}'''
    result = re.sub(r'{\[}(fig:.*?){\]}', r'Figure \\ref{\1}', line)

    return result

# Process equation links that are of the form: {[}eq:label{]}
def processEquationLink(line):
    '''Convert equation links to \ref{}'''
    result = re.sub(r'{\[}(eq:.*?){\]}', r'Eq. (\\ref{\1})', line)

    return result

# Process citations that are of the form: citet:label or citep:label
def processCitet(line):
    '''Convert citet:label to LaTeX citation \citet'''
    result = re.sub(r'citet:(.*?)[\.\,\s]', r'\\citet{\1} ', line)

    return result

def processCitep(line):
    '''Convert citep:label to LaTeX citation \citep'''
    result = re.sub(r'citep:(.*?)[\.\,\s]', r'\\citep{\1} ', line)

    return result


if __name__ == "__main__":
    main()
