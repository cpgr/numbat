#!/bin/bash

# Script to convert the markdown documentation to HTML and PDF versions, and then
# deploy the documentation to GitHub pages.
#
# Chris Green, 2016
# chris.green@csiro.au

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

perl -pi -e "s|git-version-hash|$gvh|" docs/index.md
perl -pi -e "s|git-version-date|$gvdday/$gvdmonth/$gvdyear|" docs/index.md

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
    cp docs/$filename.md docs/$filename.bak.md

    # Use pandoc-fignos to hardcode the figure numbers in the markdown
    pandoc --filter pandoc-fignos --wrap=none -o docs/$filename.tmp.md docs/$filename.md

    # Strip out any leftover figure labels {#fig:id} that may have been left behind
    perl -pi -e 's|{#fig:.*}||g' docs/$filename.tmp.md
    # Now move the hardcoded file to the original file so that mkdocs buids the
    # hardcoded version
    mv docs/$filename.tmp.md docs/$filename.md
  fi
done
