#!/usr/bin/env python

from ROOT import TFile

dataset_e = 'evVarFriend_SingleElectron_Run2016H_PromptReco_v3.root'
dataset_m = 'evVarFriend_SingleMuon_Run2016H_PromptReco_v3.root'

f_e = TFile.Open(dataset_e)
t_e = f_e.Get('sf/t')
f_m = TFile.Open(dataset_m)
t_m = f_m.Get('sf/t')

isData = True

cutflow_e = [0]*7
cutflow_m = [0]*7

evts1 = []
evts2 = []

for idx in range(0, 2):
    if idx == 0:
        tree = t_e
        cutflow = cutflow_e
    else:
        tree = t_m
        cutflow = cutflow_m

    for event in tree:

        cutflow[0] += 1
        if event.nLep != 1:
            continue
        if event.Lep_pt <= 25.:
            continue
        cutflow[1] += 1
        if event.nVeto != 0:
            continue
        cutflow[2] += 1
        if event.Selected != 1:
            continue
        cutflow[3] += 1
        if not (not isData or (isData and (event.HLT_EleHT350 or event.HLT_EleHT400 or event.HLT_Ele105 or event.HLT_MuHT400 or event.HLT_MuHT350))):
            continue
        cutflow[4] += 1
        if (not isData or (isData and ((event.PD_SingleEle and event.nEl==1) or (event.PD_SingleMu and event.nMu==1)))):
            cutflow[5] += 1
            evts1 += [float(str(event.Run)+str(event.Event))]
        if (not isData or ((event.PD_SingleEle and (event.HLT_EleHT350 or event.HLT_EleHT400 or event.HLT_Ele105)) or (event.PD_SingleMu and (event.HLT_MuHT400 or event.HLT_MuHT350) and not ((event.HLT_EleHT350 or event.HLT_EleHT400 or event.HLT_Ele105))))):
            cutflow[6] += 1
            evts2 += [float(str(event.Run)+str(event.Event))]

print cutflow_e
print cutflow_m
print [x + y for x, y in zip(cutflow_e, cutflow_m)]

print len(evts1)
print len(evts2)

diff = set(evts2).difference(evts1)
print diff

for idx in range(0, 2):
    if idx == 0:
        tree = t_e
        cutflow = cutflow_e
    else:
        tree = t_m
        cutflow = cutflow_m

    for event in tree:
        if (float(str(event.Run)+str(event.Event))) in diff:
            print 'Run:', event.Run
            print 'Event:', event.Event
            print 'HLT_EleHT350:', event.HLT_EleHT350
            print 'HLT_EleHT400:', event.HLT_EleHT400
            print 'HLT_Ele105:', event.HLT_Ele105
            print 'HLT_MuHT400:',event.HLT_MuHT400
            print 'HLT_MuHT350:',event.HLT_MuHT350
            print 'PD_SingleEle:',event.PD_SingleEle
            print 'PD_SingleMu:',event.PD_SingleMu
            print 'nMu:', event.nMu
            print 'nEl:', event.nEl
