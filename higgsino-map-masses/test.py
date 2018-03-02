#!/usr/bin/env python

from higgsino_map_masses import *

print 'Test 1, should be (100, 300):'
print higgsino_map_masses([92.8, 109.7, 304.6, 663.5, 101.1, 663.5])
print 'Test 2, should be (180, 800):'
print higgsino_map_masses([183.4, 189.7, 796.4, 1706.5, 186.5, 1706.5])
print 'Test 3, should raise ValueError:'
print higgsino_map_masses([99.8, 109.7, 304.6, 663.5, 101.1, 663.5])
