#!/bin/bash

# Script to convert the markdown documentation to HTML and PDF versions, and then
# deploy the documentation to GitHub pages.
#
# Chris Green, 2016
# chris.green@csiro.au

# Create the cross-references in the documentation
./build_crossref_documentation.sh

# Then, use mkdocs to build the online documentation and automatically deploy it
mkdocs serve

# Now that mkdocs has built the site with the hardcoded Figure labels, replace the
# original markdown so that git doesn't think that it has been updated
for file in docs/*.bak.md
do
  mv "$file" "${file%.bak.md}.md"
done

# Finally, undo the changes in the index.md file
mv docs/tmpindex.md docs/index.md
