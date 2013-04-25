import json, sys, argparse

def csvtojson(f):
    f = open(f, 'r') # open file specified by the first argument to the function

    lines = f.readlines() # read raw data into list
    csv = []
    for line in lines:
        csv.append(line.replace('"', '').replace('\n', '').split(';')) # read lines of CSV into 2 x (number of tags) list ignoring quotes and newlines and spliting at semicolons

    l = []
    for tag in csv[0]: # take only the tags that contain more than a single digit
        if '.' not in tag or 'auto' in tag or 'foul' in tag:
            l.append(tag)
    dic = {'tags': l} # assign tags to the list of important tags

    data = {} # create data dictionary to be indexed by team number and list of teams for which lists have already been created
    teams = []
    
    for match in [x + 1 for x in range(len(csv)-1)]: # loop through for every line of data
        d = {}
        i = 0
        while i < len(csv[0]): # loop through the tags and assign tags to their values
            while '.' in csv[0][i] and 'auto' not in csv[0][i] and 'foul' not in csv[0][i]: # just keep going if the tag contains a '.'
                i += 1
            if i >= len(csv[0]): # make sure we haven't overshot the lenth of the list before trying to access it
                break
            d[csv[0][i]] = csv[match][i] # set key for tag to its value
            i += 1
        if d['teamnumber'] not in teams: # add a list of match data for a team if none exists
            data[d['teamnumber']] = []
            teams.append(d['teamnumber']) # store the teamnumber so that we know a list exists
        data[d['teamnumber']].append(d) # and add the data to the list

    dic['data'] = data # add dictionary to data tag in the main one
        

    return dic # convert dictionary to JSON

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--file")
    args = parser.parse_args()

    print csvtojson(args.file) # run function with command line argument

