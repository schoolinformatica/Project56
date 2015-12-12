import re

string = "324FDFSZ'dsfsd ,  sdf"

regex = re.compile('[^a-zA-Z]')
#First parameter is the replacement, second parameter is your input string
regex.sub('', string)

print (string)
#Out: 'abdE'