#!/bin/bash 

drawPlotOnly=0 # 1 if output file exists, 0 for drawing the first time
i=-1 #-1 for all events, otherwise pickup event number

root -l -q -b runDrawHist.C'('$i','$drawPlotOnly')'
