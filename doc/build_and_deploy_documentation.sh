#!/bin/bash

# Script to convert the markdown documentation to HTML, and then
# deploy the documentation to GitHub pages.
#
# Chris Green, 2018
# chris.green@csiro.au

# Build the MooseDocs site
echo "Building site with MooseDocs"
./moosedocs.py build --clean --destination ../site

# Build the pdf documentation and move it to the site directory
./build_pdf_documentation.sh
mkdir ../site/pdf
mv report/numbat.pdf ../site/pdf/numbat.pdf

# The git hash
gvh=`git log -1 --format="%h"`

# Then, use ghp-import to move the site to the gh-pages branch, and deploy it to GitHub
# ghp-import can be installed using `pip install ghp-import`. For details, see
# https://github.com/davisp/ghp-import
echo "Deploying site to gh-pages"
ghp-import -m"Deploy $gvh documentation" -p ../site
