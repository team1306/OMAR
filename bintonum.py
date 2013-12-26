import os

f = open("report.dat", 'r') # open report in binary (filled in/not filled in)
lines = f.readlines() # read all lines
f.close() # close file
# the first line is always the list of tags or, in excel, the column headers
tags = lines[0].rstrip('\n').split(';') # strip the first tag line of newline characters and split into a list at each semicolon

# initialize the variables we'll need to append to
newtags = ['filename']
page = {} # will contain tag names and values for each line in file
pages = []
for p in [x.split(';') for x in lines[1:]]: # for each list representing every line after the first tag line
    page['filename'] = p[0]
    i = 1 # initialize the incrementor. I didn't use for here since i needs to be incremented conditionally inside the loop
    while i < len(tags): # while i is still less than the length of the list of subtags
        if len(tags[i].split('.')) == 3: # if the current tag represents a multidigit number, it will have exactly 2 periods
            page[tags[i].split('.')[0]] = 0 # set the value of the tag equal to zero
            tag = tags[i].split('.')[0] # set the current tag name
            if tag not in newtags: # if we haven't seen this tag before, append it to newtags
                newtags.append(tag)

            # walk through the subtags as long as they're still part of the current tag, adding their corresponding value if they were filled in
            while i < len(tags) and tags[i].split('.')[0] == tag: # iterate through each subtag until either we reach the end of the line or the subtag is no longer part of the tag we're reading
                coef = tags[i].split('.')[1] # read the coefficient of the current subtag
                while i < len(tags) and tags[i].split('.')[0] == tag and tags[i].split('.')[1] == coef: # iterate through each subtag until we reach the end of the line or the coefficient changes
                    if p[i] == '1': # if the bubble was filled
                        page[tag] += int(coef)*int(tags[i].split('.')[2]) # add to the value the coefficient times the value of the subtag
                    i += 1 # increment the variable
                i += 1 # increment the variable
            if i < len(tags) and len(tags[i].split('.')) != 3: # if we are not yet at the end of the line and the next tag is not a multidigit number, backtrack one since the last iteration of the previous while loop will have run "i += 1" twice in a row on its last iteration
                i -= 1

        elif len(tags[i].split('.')) == 2: # otherwise, if the subtag refers to a single digit number
            page[tags[i].split('.')[0]] = 0 # set the value of the tag equal to zero
            tag = tags[i].split('.')[0] # set the current tag name
            if tag not in newtags: # if we haven't seen this tag before, append it to newtags
                newtags.append(tag)
            while i < len(tags) and tags[i].split('.')[0] == tag: # iterate through each subtag until either we reach the end of the line or the subtag is no longer part of the tag we're reading
                if p[i] == '1': # if the bubble was filled
                    page[tags[i].split('.')[0]] += int(tags[i].split('.')[1]) # add to the value the value represented by the subtag
                i += 1 # increment the variable

        elif len(tags[i].split('.')) == 4: # otherwise, if the subtag refers to a multipule choice bubble
            tag = tags[i].split('.')[0] # set the current tag name
            if tag not in newtags: # if we haven't seen this tag before, append it to newtags
                newtags.append(tag)
            page[tags[i].split('.')[0]] = tags[i].split('.')[3] # set the value of the tag to the default value in case none of the bubbles were filled
            while i < len(tags) and tags[i].split('.')[0] == tag: # iterate through each subtag until either we reach the end of the line or the subtag is no longer part of the multipule choice we're reading
                if p[i] == '1': # if this bubble is filled in
                    page[tags[i].split('.')[0]] = tags[i].split('.')[3] # set the value of the tag to this new value, overriding the default one
                i += 1 # increment the variable
    pages.append(page) # append page to pages so that we can repeat the process on the next line
    page = {} # empty page

if os.path.isfile("report.csv"): # if report.csv exists
    n = False # set new to false
    f = open("report.csv", 'a') # open the file for appending the data instead of overwriting the current data
else: # otherwise
    n = True # set new to true
    f = open("report.csv", 'w') # open the file for first time writing

s = "" # initialize string that will be written to the file
if n: # if the file is new
    for i in newtags: # add all the tag names
        s += i + ";" # each followed by a semicolon
    s += '\n' # and then terminated by a newline character
for i in range(len(pages)): # for every line of data
    for x in newtags: # for every tag value
        s += str(pages[i][x]) + ";" # append the tag value followed by a semicolon
    s += '\n' # terminated by a newline character
f.write(s) # write string to the file. Append if there was already data there, straight write if not
f.close() # close file
