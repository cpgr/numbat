#!/bin/bash

# Script to convert the markdown documentation to LaTeX and then a pdf
#
# Chris Green, 2018
# chris.green@csiro.au

# First, clean the .tex files and associated files in the latex directory, and the previous
# pdf version
cd report
rm -f numbat.aux numbat.log numbat.lof numbat.lot numbat.toc numbat.out numbat.pdf *.tex
cd ../

# Convert all of the markdown files needed by the Numbat LaTeX template
echo "Converting markdown to LaTeX"
./convert.py -f content/introduction.md
./convert.py -f content/governing_equations.md
./convert.py -f content/getting_started.md
./convert.py -f content/implementation.md
./convert.py -f content/input_file_syntax.md
./convert.py -f content/running_numbat.md
./convert.py -f content/example2D.md
./convert.py -f content/example3D.md
./convert.py -f content/contributing.md

# Then build the pdf document using the template
cd report
cp template/numbat.tex ./

pdflatex -interaction=batchmode numbat.tex
bibtex numbat
pdflatex -interaction=batchmode numbat.tex
pdflatex -interaction=batchmode numbat.tex

cd ..
echo "Finished building PDF manual"
