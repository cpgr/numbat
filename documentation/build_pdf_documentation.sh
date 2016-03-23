#!/bin/bash

# Script to convert the markdown documentation to LaTeX, and then build a pdf
# document using pdflatex.
#
# Markdown to LaTeX conversion uses pandoc (pandoc.org).
#
# Currently, all markdown files are in ./docs/
# All generated LaTeX files will be placed in ./latex/
#
# Chris Green, 2016
# chris.green@csiro.au

# First, clean the .tex files and associated files in the latex directory
rm latex/*.tex latex/numbat.aux latex/numbat.log latex/numbat.toc latex/numbat.out docs/numbat.pdf

# Then, create the main numbat.tex file using the template numbat_layout.tex
cp latex/template/numbat_layout.tex latex/numbat.tex
sed -i '' '$d' latex/numbat.tex

# Extract all of the markdown files used in the online documentation by looking
# at the mkdocs.yml file and extracting all filenames. This gives an ordered list
# of markdown files. Then use pandoc to convert each file to LaTeX.

for line in `grep -e md mkdocs.yml | cut -d ":" -f 2- | grep -v download`
do
  filenameonly=${line##*/}
  filenameonly=${filenameonly%.*}
  filename=${line%.*}

  echo "Converting $filename.md"
  pandoc --filter pandoc-fignos -o latex/$filenameonly.tex docs/$filename.md

# Now add each LaTeX file as an input in the main LaTeX file
echo "\clearpage" >> latex/numbat.tex
echo "\input{$filenameonly.tex}" >> latex/numbat.tex
done

# Finally, insert \end{document} at the end of the main LaTeX file
echo "" >> latex/numbat.tex
echo "\end{document}" >> latex/numbat.tex

# Make some styling changes to the resulting LaTeX documentation
# First, change the image location and add a width=\pagewidth to size the images
sed -i '' 's|\includegraphics{images|\includegraphics[width=\\textwidth]{../docs/images|g' latex/*.tex

# Also, the \\ in each align environment should be replaced with \\ for correct LaTeX equation numbering
sed -i '' 's|\\\\|\\|g' latex/*.tex

# Add a \begin{shaded} ... \end{shaded} around the verbatim environment
sed -i '' 's|\begin{verbatim}|\begin{shaded}\
\\begin{verbatim}|g' latex/*.tex
sed -i '' 's|\end{verbatim}|\end{verbatim}\
\\end{shaded}|g' latex/*.tex

# Insert the git version hash and date into the LaTeX file
gvh=`git log -1 --format="%h"`
gvd=`git log -1 --format="%ad" --date=short`

# Change the date from YYYY-MM-DD to DD/MM/YYYY
gvdyear=${gvd:0:4}
gvdmonth=${gvd:5:2}
gvdday=${gvd:8:2}

sed -i '' "s|git-version-hash|$gvh|" latex/numbat.tex
sed -i '' "s|git-version-date|$gvdday/$gvdmonth/$gvdyear|" latex/numbat.tex
sed -i '' "s|git-version-hash|$gvh|" latex/index.tex
sed -i '' "s|git-version-date|$gvdday/$gvdmonth/$gvdyear|" latex/index.tex

# Now run pdflatex to make the pdf version
cd latex
pdflatex numbat.tex
pdflatex numbat.tex

# Move the pdf file to the docs directory for linking to the website
mv numbat.pdf ../docs
