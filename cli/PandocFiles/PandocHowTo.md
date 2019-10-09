# Pandoc
To get __pandoc__:

  <https://pandoc.org/installing.html>

How to use pandoc from terminal to convert files.

## From .md to html
I created a script to convert a ``markdown`` file to an ``html`` using pandoc, ``pandoc_to_html.sh``

```bash {cmd=false}
bash pandoc_to_html.sh file.md file.html
```

The script was made starting from the basic line and then adding useful options as described below.

The basic line to convert a ``markdown`` file to an ``html`` is:

```bash {cmd=false}
pandoc file.md -f markdown -t html -s -o file.html
```

This line says: convert the file ``file.md``, which is in ``markdown``, to an ``html`` output called ``file.html``.
Such output is ``standalone`` (``-s`` or ``--standalone``), which means that is interpreted as a complete file by itself and so __pandoc__ includes all the headers necessary for opening that output in the desired format. It's necessary to include the ``-s`` option because otherwise __pandoc__ by default produces pieces of code and does not include the headers necessary to open the output in the desired format.

It's also possible to write:

```bash {cmd=false}
pandoc file.md -s -o file.html
```
as if you don't write explicitly the format of the input/output,  pandoc guesses the format from the extension of the files.

The ``html`` (or ``html5``) file goes to a new line only if in the ``markdown`` there is a blank line between two lines. Otherwise, if in the ``markdown`` file one goes to a new line but there is no emply line between the two paragraphs, the ``html`` file will write the two paragraphs on the same line. This is also true for the lines that follow a block of code or a title.

There are several useful additions that can be made to the simple line above (most of them have a general validity, not only for converting a file to ``html``).

### Markdown format

If the ``markdown`` file contans _emoji_, instead of ``-f markdown``, write ``-f markdown+emoji`` to render the _emoji_ in the output file.
If the markdown file is written in GitHub Flavored Markdown, it's  ``-f gfm``

### Latex formula

Use ``--katex`` to render __latex__ formulas (also ``--mathjax`` works, but renders the formulas slightly worse in my opinion).

### Syntax highlighting

It's possible to costumize the syntax highlighting in the code blocks: for the _tango_ style, for example, write ``--highlight-style tango``. You can get the other possible syles from the pandoc manual <https://pandoc.org/MANUAL.html> or from  <https://www.garrickadenbuie.com/blog/pandoc-syntax-highlighting-examples/> or simply running

```bash {cmd=true}
pandoc --list-highlight-styles
```
You can also customize the style itself. To do that, print the pandoc theme by typing:

 ```bash {cmd=true}
 pandoc --print-highlight-style=pygments > pygments.theme
 ```
Then edit the ``theme`` file as you wish and include it in the pandoc output using ``--highlight-style=pygments.theme``.
Costumizing the themes, I created ``tango.theme`` and ``kate.theme``.

### Customize css

I found online, at <https://gist.github.com/killercup/5917178>, a ``css`` file to make ``html`` files look better, and I included it  ``--css pandoc.css`` after having slightly modified it to have less margin in the ``html``.


## From .md to .tex

At the moment I found that __latex__ can't render _emoji_, so it's best if the file.md to convert doesn't have any.

```bash {cmd=true}
pandoc file.md -f markdown -t latex -s -o file.tex
```

You can also specify which latex compiler you want to use: for example, for __xelatex__

```bash {cmd=true}
pandoc --pdf-engine=xelatex file.md -f markdown -t latex -s -o file.latex
```

If you accidentally run the wrong name or an invalid name for the ``--pdf-engine``, __pandoc__ will suggest you the possibile choices.

## From .md to PDFs
Pandoc always goes through __latex__ to produce a pdf.

At the moment I found that __latex__ can't render _emoji_, so it's best if the file.md to convert doesn't have any.

I created a script to convert ``markdown`` files (GitHub Flavored Markdown files, to be more specific) to ``pdf``.
The script is ``pandoc_to_pdf.sh`` and to run it use:

```bash {cmd=false}
bash pandoc_to_pdf.sh file.md file.pdf
```
The basic pandoc line to convert an ``.md`` file to ``.pdf`` is:

```bash {cmd=true}
pandoc file.md -f markdown -t latex -s -o file.pdf
```
You can also specify which latex compiler you want to use: for example, for __xelatex__

```bash {cmd=true}
pandoc --pdf-engine=xelatex file.md -f markdown -t latex -s -o file.pdf
```
You may want to use __xelatex__ as a pdf engine because some features work best (or work only) when using that and not __pdflatex__.
If you accidentally run the wrong name or an invalid name for the ``--pdf-engine``, __pandoc__ will suggest you the possibile choices.

### Wrap lines

In order to make the __code lines__ to wrap __inside the codeblocks__ and not be cut off in the pdf, I wrote a __latex__ header, ``latexheader.tex``, and included it in the script with ``-H latexheader.tex``.

Another possibility to do the same thing is to include ``--listings -H listings-setup.tex``, but the ``--listing`` option is not compatible with ``--highlight-style``, so the code blocks in the pdf will not be highlighted.

In order to make the __text lines__ to wrap include ``--wrap auto`` (or ``none`` or the other option that can be found in the pandoc manual).

### Syntax highlighting

Works in the same way as explained in the ``html`` section.

### Latex settings

There are also these useful options to add to the command line if needed:

```bash {cmd=true}
-V header-includes:'\setmainfont[BoldFont = Font-Bold.otf, ItalicFont = Font-Italic.otf, BoldItalicFont = Font-BoldItalic.otf]{Font-Regular.otf}'
```

to change the font and:

```bash {cmd=true}
-V header-includes:'\usepackage{}'
--include-in-header=fontoptions.tex
```

where ``fontoptions.tex`` is some needed .tex file.


__If you have emoji in your file__ the best chance to obtain a pdf is to follow two steps (do not use the script):

- convert the markdown to latex (.tex) with ``markdown+emoji``
- open the .tex file and compile it manually with __xelatex__

In this way the emoji simply won't show on the pdf, but the rest will be in pdf latex format.

#### From .md to html to .pdf

There is also another way to get a pdf, through html:

```bash {cmd=true}
pandoc file.md -f markdown -t html -s -o file.pdf --katex
```

or

```bash {cmd=true}
pandoc file.md -f markdown -t html5 -s -o file.pdf --katex
```

but I've found it to be worse than the latex option.

## Other info

__Pandoc__ also runs in __atom__, and to export and convert files directly from __atom__ you can set the preferences of the atom package _markdown_preview_enhanced_.

In general, there is the possibility to create files to use as filter, the ``.lua`` files.
For example, I created the ``emoji.lua`` file that converts string emoji (emoji in markdown style, between the two double dots, :example:) to the relative emoji image. The file can be applied as an option to the command line, ``--lua-filter=emoji.lua``.
