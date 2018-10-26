#!/bin/bash
setup="betaHigh-snrLow"
folderObs="/data/sls/scratch/fgrondin/experiments/gccphat/obs/$setup/"
folderResults="/data/sls/scratch/fgrondin/experiments/gccphat/results/$setup/"
#bash batch.sh "$folderObs*.bin" $folderResults ../bin/gccphat m 1
#bash batch.sh "$folderObs*.bin" $folderResults ../bin/gccphat f 1
#bash batch.sh "$folderObs*.bin" $folderResults ../bin/gccphat f 2
#bash batch.sh "$folderObs*.bin" $folderResults ../bin/gccphat f 4
#bash batch.sh "$folderObs*.bin" $folderResults ../bin/gccphat f 8
#bash batch.sh "$folderObs*.bin" $folderResults ../bin/gccphat f 16
#bash batch.sh "$folderObs*.bin" $folderResults ../bin/gccphat f 32
#bash batch.sh "$folderObs*.bin" $folderResults ../bin/gccphat q 1
#bash batch.sh "$folderObs*.bin" $folderResults ../bin/gccphat q 2
#bash batch.sh "$folderObs*.bin" $folderResults ../bin/gccphat q 4
#bash batch.sh "$folderObs*.bin" $folderResults ../bin/gccphat q 8
#bash batch.sh "$folderObs*.bin" $folderResults ../bin/gccphat q 16
#bash batch.sh "$folderObs*.bin" $folderResults ../bin/gccphat q 32
bash batch.sh "$folderObs*.bin" $folderResults ../bin/gccphat s 1
