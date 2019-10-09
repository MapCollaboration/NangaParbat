#!/bin/bash

pandoc "$1" \
    -f markdown \
    -t html \
    --katex  \
    --css ../PandocFiles/pandoc.css \
    --highlight-style=../PandocFiles/tango.theme \
    -s \
    -o "$2"
