# Numbat documentation:

## Software requirements:
 - mkdocs (www.mkdocs.org)
 - pandoc (www.pandoc.org)
 - pdflatex (requires a TeX distribution)

## Extensions:

### figureAltCaption:
To get captions in mkdocs, we use the Python Markdown extension
figureAltCaption (https://github.com/jdittrich/figureAltCaption).
This needs to be installed manually by copying the figureAltCaption.py file
to the appropriate site-packages directory.

This can be found by starting python (make sure it is the correct executable used
by mkdocs for systems with multiple python installations) and typing:

import site; site-getsitepackages()

at the Python prompt. The second directory listed in the one where you should copy
figureAltCaption.py. You can check that it worked by using

import figureAltCaption

from the Python prompt.

### pandoc-fignos:
To get figure labels and references, we use the pandoc-fignos extension (https://github.com/tomduck/pandoc-fignos).
Installation instructions are provided on the project site.

## Source files:

The Numbat documentation is written in markdown and is located in the
numbat/documentation/docs directory in the master branch. Each page is a
separate markdown file.

To allow the online documentation navigation to be built, the mkdocs.yml
file in the numbat/documentation directory must be edited to include the
name of the new page.

## Building the online documentation for local preview:

To build a local version for testing:
From the numbat/documentation directory, run

    ./build_and_preview_documentation.sh

and preview the documentation in a web browser (using the provided address).

## Building the pdf documentation for local preview:

To build a pdf from the markdown documentation, from the numbat/documentation directory
run

    ./build_pdf_documentation.sh

This Bash script uses pandoc to convert each of the markdown documents to LaTeX format,
assembles them into a LaTeX template and runs pdflatex to generate a pdf file. The pdf
version of the documentation is moved to the numbat/documentation directory and linked to
by the online documentation.


## Building and deploying the documentation:

To build and deploy the documentation to GitHub.com:
From the numbat/documentation directory, run

    ./build_and_deploy_documentation.sh

which builds all the documentation, transfers it the gh-pages branch,
and pushes it to GitHub. Once this has run, the updated documentation should
be available at http://cpgr.github.io/numbat
