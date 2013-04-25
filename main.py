import numpy
import csvtojson, ranking, argparse

# parse the tags to get the name of the input file and the respective climbing and shooting weights
parser = argparse.ArgumentParser()
parser.add_argument("-f", "--file", default="./report.csv")
parser.add_argument("-s", "--shooter", type=float, help="shooter weighting factor", default=1)
parser.add_argument("-c", "--climber", type=float, help="climber weighting factor", default=1)

args = parser.parse_args()

# print the resulting ranking
r = numpy.array(ranking.rank(csvtojson.csvtojson(args.file), args.climber, args.shooter))

s = ''
for x in r[:,0][::-1]:
    s += str(x) + '\n'
f = open("rankings", "w")
f.write(s)
