#!/bin/bash

pandoc "$1" \
    -f markdown \
    -t latex \
    --pdf-engine=xelatex  \
    -H latexheader.tex \
    --highlight-style=tango.theme \
    --wrap auto \
    -s \
    -o "$2" \

#    --listings -H listings-setup.tex \
