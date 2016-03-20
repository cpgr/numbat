#!/bin/bash

# Script to convert the markdown documentation to HTML and PDF versions, and then
# deploy the documentation to GitHub pages.
#
# Chris Green, 2016
# chris.green@csiro.au

# First, build the pdf documentation
./build_pdf_documentation.sh

# Insert the git version hash and date into the index.md file. First, make a copy
# to undo the changes with after building the documentation, so that git doesn't know that
# index.md has been changed
cp docs/index.md docs/tmpindex.md
gvh=`git log -1 --format="%h"`
gvd=`git log -1 --format="%ad" --date=short`

# Change the date from YYYY-MM-DD to DD/MM/YYYY
gvdyear=${gvd:0:4}
gvdmonth=${gvd:5:2}
gvdday=${gvd:8:2}

sed -i '' "s|git-version-hash|$gvh|" docs/index.md
sed -i '' "s|git-version-date|$gvdday/$gvdmonth/$gvdyear|" docs/index.md

# Then, use mkdocs to build the online documentation and automatically deploy it
mkdocs gh-deploy --clean

# Finally, undo the changes in the index.md file
mv docs/tmpindex.md docs/index.md
