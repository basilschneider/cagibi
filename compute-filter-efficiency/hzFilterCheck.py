#!/usr/bin/env python

# python hzFilter.py SOURCE.LHE TARGET.LHE

import sys

#Open this LHE file
file = open(sys.argv[1])
outputfile = open(sys.argv[2], "w")

#Read file into memory
lines = file.readlines()

#Variables to store counts of events
HZEvents = 0
HHEvents = 0
ZZEvents = 0
ZEvents = 0
HEvents = 0
NEvents = 0

newevent = 1
linenumber = 0 #Keep track of line number in an event
indicator = 0 #To skip header of LHE file

#Start looping over lines in LHE file
for l in lines:

    if l.find("<event>")>=0 and NEvents==0:
        indicator = 1
    if indicator == 0 and NEvents==0:
        outputfile.write(l)
        print "Skipped", l,
        continue

    #Start new event
    if l.find("<event>")>=0:
        NEvents = NEvents + 1
        print "Found event ", NEvents
        newevent = 1
        numberZ = 0 #number of Zs found in event
        numberH = 0 #number of Hs found in event
        linenumber = -2 #variable to store line number in event
        n2linenumbers = [] #list to store line numbers of n2s
        eventinfo = [] #store event listing

#    if NEvents==5278:
#        print "Event: ", l

    if newevent==1:
        linenumber = linenumber + 1
        temp = l.split()#split line wrt whitespace
        eventinfo.append(l)

    if linenumber==0: #Skip the first line in an event
        print "Hellooooooo", l
        continue

#        print temp[0]
    if temp[0]=='1000023':
        n2linenumbers.append(linenumber)
        print "Appending line number for 1000023", n2linenumbers

#        if temp[0]=='23' and n2linenumbers.index(int(temp[2]))>=0: #Z and mother in n2linenumbers
#        if temp[0]=='23' and int(temp[2]) in n2linenumbers: #Z and mother in n2linenumbers
#            print "Found Z coming from 1000023"
#            numberZ = numberZ + 1

    if temp[0]=='23':
            print "Found Z coming from line number", temp[2]
            if int(temp[2]) in n2linenumbers:
                numberZ = numberZ + 1 #Found Z coming from 1000023

    if temp[0]=='25':
        if int(temp[2]) in n2linenumbers:
            print "Found H coming from line number", temp[2]
            numberH = numberH + 1 #Found H coming from 1000023
#Ignore status for now
#            if temp[1]!='3' and temp[1]!='2':
#                print "Z doesn't have status 3"
#                sys.exit(1)
#        elif temp[0]=='25' and n2linenumbers.index(int(temp[2]))>=0: #H and mother in n2linenumbers
#        elif temp[0]=='25' and int(temp[2]) in n2linenumbers: #H and mother in n2linenumbers
#            print "Found H coming from 1000023"
#            numberH = numberH + 1
#Ignore status for now
#            if temp[1]!='3' and temp[1]!='2':
#                print "H doesn't have status 3"
#                sys.exit(1)

    if l.find("</event>")>=0:
        print "Event ended: Z and H content: ", numberZ, numberH
        newevent = 0
        if len(n2linenumbers)!=2:
            print "n2linenumbers size: ", len(n2linenumbers)
            sys.exit(1)
        if numberZ==1 and numberH==1:
            HZEvents = HZEvents + 1
            outputfile.writelines(eventinfo)
        elif numberZ==2 and numberH==0:
            ZZEvents = ZZEvents + 1
        elif numberZ==0 and numberH==2:
            HHEvents = HHEvents + 1
        elif numberZ==1 and numberH==0:
            ZEvents = ZEvents + 1
        elif numberZ==0 and numberH==1:
            HEvents = HEvents + 1
        else:
            print "Oops! Error in number of Zs and Hs"
            sys.exit(1)

outputfile.close()

print "HZEvents: ", HZEvents
print "ZZEvents: ", ZZEvents
print "HHEvents: ", HHEvents
print "ZEvents: ", ZEvents
print "HEvents: ", HEvents
print "NEvents: ", NEvents
