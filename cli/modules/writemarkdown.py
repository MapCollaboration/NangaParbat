import modules.bcolours as bcolours
from modules.bcolours import *

##############################################
# Write in Markdown with python
##############################################

# ---------------------------------- Tables ------------------------------------

# Translation dictionaries for table alignment
left_rule = {'<': ':', '^': ':', '>': '-'}
right_rule = {'<': '-', '^': ':', '>': ':'}

def evaluate_field(record, field_spec):
    """
    Evaluate a field of a record using the type of the field_spec as a guide.
    """
    if type(field_spec) is int:
        return str(record[field_spec])
    elif type(field_spec) is str:
        return str(getattr(record, field_spec))
    else:
        return str(field_spec(record))

def table(file, records, headings, fields = None, alignment = None):
    """
    Generate a Markdown table from records.

    file    -- File where the table will be printed. Any object with a 'write'
               method that takes a single string parameter.
    records -- List of tuples. Rows will be generated from this. Each row must be a tuple.
               Example:
               data = [('Alabama', 'AL', '1819', 'Montgomery', '1846', 155.4, False, 205764),
                    ('Alaska', 'AK', '1959', 'Juneau', '1906', 2716.7, False, 31275),
                    ('Arizona', 'AZ', '1912', 'Phoenix', '1889',474.9, True, 1445632),
                    ('Arkansas', 'AR', '1836', 'Little Rock', '1821', 116.2, True,
                     193524)]
    headings -- List of column headings.
                Example:
                headings = ['State', 'Abrev.', 'Capital', 'Capital since', 'Population',
                        'Largest Population?']
    fields    [optional] -- List of fields for each row.  Each entry may be an
              integer, string or a function.  If the entry is an integer, it is assumed
              to be an index of each record.  If the entry is a string, it is assumed
              to be a field of each record.  If the entry is a function, it is called
              with the record and its return value is taken as the value of the field.

              [optional]: if the list of fields to use is not specified, all the elements
              given in 'records' are put into the table.
    alignment [optional] -- List of pairs alignment characters.  The first of the pair
              specifies the alignment of the header, (Doxygen won't respect this, but
              it might look good, the second specifies the alignment of the cells in
              the column.
              [optional]: if the alignment is not specified, all elements will be centered.

              Possible alignment characters are:
              '<' = Left align (default for cells)
              '>' = Right align
              '^' = Center (default for column headings)
              Example:
              align = [('^', '<'), ('^', '^'), ('^', '<'), ('^', '^'), ('^', '>'),
                 ('^','^')]
    """
    # Set fields to use among the data given in 'records'
    if fields != None:
        fields_to_use = fields
    else:
        fields_to_use = []
        for c in range (0,len(headings)):
            fields_to_use.append(c)

    num_columns = len(fields_to_use)
    assert len(headings) == num_columns

    # Compute the table cell data
    columns = [[] for i in range(num_columns)]
    for record in records:
        for i, field in enumerate(fields_to_use):
            columns[i].append(evaluate_field(record, field))

    # Fill out any missing alignment characters.
    extended_align = alignment if alignment != None else []
    if len(extended_align) > num_columns:
        extended_align = extended_align[0:num_columns]
    elif len(extended_align) < num_columns:
        for c in range (0,len(headings)):
            extended_align.append(('^', '^'))

    heading_align, cell_align = [x for x in zip(*extended_align)]

    # Set element widths
    field_widths = [len(max(column, key=len)) if len(column) > 0 else 0
                    for column in columns]
    heading_widths = [max(len(head), 3) for head in headings]
    column_widths = [max(x) for x in zip(field_widths, heading_widths)]

    _ = ' | '.join(['{:' + a + str(w) + '}'
                    for a, w in zip(heading_align, column_widths)])
    heading_template = '| ' + _ + ' |'
    _ = ' | '.join(['{:' + a + str(w) + '}'
                    for a, w in zip(cell_align, column_widths)])
    row_template = '| ' + _ + ' |'

    _ = ' | '.join([left_rule[a] + '-'*(w-2) + right_rule[a]
                    for a, w in zip(cell_align, column_widths)])
    ruling = '| ' + _ + ' |'

    # Write table
    # add new line at the start of the table
    file.write('\n')

    file.write(heading_template.format(*headings).rstrip() + '\n')
    file.write(ruling.rstrip() + '\n')
    for row in zip(*columns):
        file.write(row_template.format(*row).rstrip() + '\n')

    # add new line at the end of the table
    file.write('\n')

# ----------------------------------- Text -------------------------------------

def mdtitle(file, level, text):
    """
    Print taxt as markdown title onto a file

    file  -- file where the output is printed. Any object with a 'write'
             method that takes a single string parameter.
    level -- Integer that specifies the number of # in front of the text (in
             markdown is the level of the title). From 1 (main title) to 5
             (lowest order and smallest title).
    text  -- text to print. It must be a string.

    """
    # Check that 'level' is an integer
    try:
        int(level)
    except:
        print(bcolours.FAIL + "TypeError: 'level' must be an integer" + bcolours.ENDC)

    # Set number of #
    hash = ""
    for s in range(level):
        hash += "#"

    # Write
    file.write(hash + " " + text + '\n')
    file.write('\n')

def mdincludefig(file, figpath, title = None):
    """
    Include figure from local path into Markdown file
    file  --  file where the output is printed. Any object with a 'write'
              method that takes a single string parameter.
    figpath --  name of the relative path of the file of the figure to include. The
                path is relative to where the file 'file' is.
    title --  [optional] name of the plot in markdown. It is also what is shown
              if you hover your mouse over the image in the markdown file. If not
              given is the same as the path of the image.
              It must be a string.
    """

    # Check that 'title' is a string, if not try to convert it.
    if type(title) is not str:
        print(bcolours.WARNING + "TypeError: the title of the image must be a string." + bcolours.ENDC)
        print(bcolours.WARNING + "Trying to convert it to a string." + bcolours.ENDC)
        title = str(title)

    if title == "None":
       title = figpath

    file.write("\n")
    file.write("![" + title + "](" + figpath +  " \""  + title + "\"" + ")" + "\n")
    file.write("\n")
