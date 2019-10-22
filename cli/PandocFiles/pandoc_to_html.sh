#!/bin/bash

pandoc "$1" \
    -f markdown \
    -t html \
    --katex  \
    --css pandoc.css \
    --highlight-style=tango.theme \
    -s \
    -o "$2"
