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

# Modify the markdown files using pandoc-fignos to hardcode the Figure labels.
# Extract all of the markdown files used in the online documentation by looking
# at the mkdocs.yml file and extracting all filenames. This gives an ordered list
# of markdown files.

for line in `grep -e md mkdocs.yml | cut -d ":" -f 2- | grep -v download`
do
  filenameonly=${line##*/}
  filenameonly=${filenameonly%.*}
  filename=${line%.*}

  # If the file contains a figure reference, use pandoc-fignos to hardcode the figure
  # refence so that mkdocs renders them correctly when making the html site.
  if grep -lq '#fig:' docs/$filename.md; then
    # Make a temporary copy of the file
    cp docs/$filename.md docs/$filename.bak

    # Use pandoc-fignos to hardcode the figure numbers in the markdown
    pandoc --filter pandoc-fignos -o docs/$filename.tmp.md docs/$filename.md

    # Now move the hardcoded file to the original file so that mkdocs buids the
    # hardcoded version
    mv docs/$filename.tmp.md docs/$filename.md
  fi
done

# Then, use mkdocs to build the online documentation and automatically deploy it
mkdocs gh-deploy --clean

# Now that mkdocs has built the site with the hardcoded Figure labels, replace the
# original markdown so that git doesn't think that it has been updated
for file in docs/*.bak
do
  mv "$file" "${file%.bak}.md"
done

# Finally, undo the changes in the index.md file
mv docs/tmpindex.md docs/index.md
