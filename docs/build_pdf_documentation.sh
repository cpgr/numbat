#!/bin/bash

# Script to convert the markdown documentation to HTML, and then
# deploy the documentation to GitHub pages.
#
# Chris Green, 2017
# chris.green@csiro.au

# Build the MooseDocs site
print "Building site with MooseDocs"
./moosedocs.py build

# Then, use ghp-import to move the site to the gh-pages branch, and deploy it to GitHub
# The git hash
gvh=`git log -1 --format="%h"`

print "Deploying site to gh-pages"
ghp-import -m"Deploy $gvh documentation" -p ../site
