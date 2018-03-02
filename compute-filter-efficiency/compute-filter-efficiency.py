#!/usr/bin/env python

from sys import argv
from itertools import dropwhile, ifilterfalse

lhefiles = argv[1:]

leptons = [-11, 11, -13, 13, -15, 15]
evts_tot = 0
evts_2lep = 0

for lhefile in lhefiles:
    with open(lhefile, 'r') as f:

        # Remove header lines
        f = dropwhile(lambda l: not l.strip()=='<event>', f)

        # Filter out comments
        f = ifilterfalse(lambda l: l.startswith('#'), f)

        for line in f:

            # Strip newline characters
            line = line.strip()

            # End of file
            if line == '</LesHouchesEvents>':
                continue

            # Start of new event
            if line == '<event>':
                # Reset variables
                emptyEvent = False
                ctr = 0
                continue

            # End of event
            if line == '</event>':
                # If event was empty, don't do anything
                if emptyEvent:
                    continue
                evts_tot += 1
                if ctr >= 2:
                    evts_2lep += 1
                continue

            # Skip event data
            if len(line.split()) == 6:
                if int(line.split()[0]) == 0:
                    emptyEvent = True
                continue

            # Get particle ID
            pid = int(line.split()[0])

            if pid in leptons:
                ctr += 1

print '{}/{} = {}'.format(evts_2lep, evts_tot, float(evts_2lep)/evts_tot)
