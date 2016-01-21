#!/bin/bash

# Script to convert the markdown documentation to HTML and PDF versions, and then
# deploy the documentation to GitHub pages.
#
# Chris Green, 2016
# chris.green@csiro.au

# First, build the pdf documentation
./build_pdf_documentation.sh

# Then, use mkdocs to build the online documentation and automatically deploy it
mkdocs gh-deploy --clean
