import json
import argparse


def rank(dictionary, climberWeight, shooterWeight):
    dictionarylength = (len(dictionary["data"]))

    x = 0
    temporary = [] #add up a teams points per round here temporarily
    teampoints = [] #a big list with all teams and their average points
    for team in dictionary["data"]:
        for rnd in dictionary["data"][str(team)]:
            # rip all raw values from json and multiply by the scores
            if rnd["climbingpts"][2:] != '':
                climberTotal = int(rnd["climbingpts"][2:])*climberWeight
            else:
                climberTotal = 0
        
            
            highPoints = int(rnd["telehighgoals"])*3
            medPoints = int(rnd["telemedgoals"])*2
            lowPoints = int(rnd["telelowgoals"])
            
            highPointsAuto = int(rnd["autohighgoals.1"])*6
            medPointsAuto = int(rnd["automedgoals.1"])*5
            lowPointsAuto = int(rnd["autolowgoals.1"])*4      
            
            shooterTotal = (highPoints+medPoints+lowPoints+highPointsAuto+medPointsAuto+lowPointsAuto)*shooterWeight
            temporary.append(climberTotal+shooterTotal)
        # add up team points
        teampoints.append([int(team), sum(temporary)/len(temporary)])
        temporary = []
        # sort the teams based on cumulative score
        teampoints.sort(key=lambda x: x[1]) #this does the sorting

    return teampoints

if __name__ == "__main__":
    # tag parser for arguments normally passed to the function by main file
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--file")
    parser.add_argument("-s", "--shooter", type=float, help="shooter weighting factor", default=1)
    parser.add_argument("-c", "--climber", type=float, help="climber weighting factor", default=1)
    args = parser.parse_args()
    
    # parse file specified by argument -f
    jsonFile = args.file
    climberWeight = args.climber
    shooterWeight = args.shooter
    
    jsonFileLines = open(jsonFile)
    lines = jsonFileLines.readlines()
    jsonFileLines.close()
    
    s = ""
    for line in lines:
        s += line.strip("\n")
        
    print s
    dictionary = (json.loads(s)) #this is the dictionary
    # print the ranked teams
    print rank(dictionary, climberWeight, shooterWeight)
