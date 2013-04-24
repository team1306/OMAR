f = open("report.csv", 'r')
lines = f.readlines()
f.close()
tags = lines[0].rstrip('\n').split(';')

newtags = []
page = {}
pages = []
for p in [x.split(';') for x in lines[1:]]:
    i = 1
    while i < len(tags):
        if len(tags[i].split('.')) == 3: # multidigit number
            page[tags[i].split('.')[0]] = 0
            tag = tags[i].split('.')[0]
            if tag not in newtags:
                newtags.append(tag)
            while i < len(tags) and tags[i].split('.')[0] == tag:
                coef = tags[i].split('.')[1]
                while i < len(tags) and tags[i].split('.')[0] == tag and tags[i].split('.')[1] == coef:
                    if p[i] == '1':
                        page[tag] += int(coef)*int(tags[i].split('.')[2])
                    i += 1
                i += 1
            if i < len(tags) and len(tags[i].split('.')) != 3:
                i -= 1
        elif len(tags[i].split('.')) == 2:
            page[tags[i].split('.')[0]] = 0
            tag = tags[i].split('.')[0]
            if tag not in newtags:
                newtags.append(tag)
            while i < len(tags) and tags[i].split('.')[0] == tag:
                if p[i] == '1':
                    page[tags[i].split('.')[0]] += int(tags[i].split('.')[1])
                i += 1
        elif len(tags[i].split('.')) == 4:
            tag = tags[i].split('.')[0]
            if tag not in newtags:
                newtags.append(tag)
            while i < len(tags) and tags[i].split('.')[0] == tag:
                if p[i] == '1':
                    page[tags[i].split('.')[0]] = tags[i].split('.')[3]
                i += 1
    pages.append(page)
    page = {}

f = open("report.csv", 'w')
s = ""
for i in newtags:
    s += i + ";"
s += '\n'
for i in range(len(pages)):
    for x in newtags:
        s += str(pages[i][x]) + ";"
    s += '\n'
f.write(s)
f.close()
