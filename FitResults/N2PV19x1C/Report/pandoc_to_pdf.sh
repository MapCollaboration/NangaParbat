#!/bin/bash

pandoc "$1" \
    -f markdown \
    -t latex \
    --filter ./tablefilter.py \
    --pdf-engine=xelatex  \
    -V geometry:margin=1in \
    -H latexheader.tex \
    --highlight-style=tango.theme \
    --wrap auto \
    -s \
    -o "$2" \

#    --listings -H listings-setup.tex \
