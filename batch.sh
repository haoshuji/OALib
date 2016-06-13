#!/bin/bash

bin=/home/shuji/Dropbox/share\(hoi-shuji\)/SOAL/SOAL-ICDM16-code/

DATA_DIR=/home/shuji/data/SOAL/

OUTPUT_DIR=${bin}results/11Jun/

for DATA in 'SUSY.b' 'HIGGS.b'  #'covtype.scale.b'
do
	${bin}struct/SOAL -s ${bin}setting.txt -i ${DATA_DIR} -d ${DATA} -o ${OUTPUT_DIR} #> ${SOAL}/${OUTPUT_DIR}/${DIRNAME}.lo
done
# 'a8a.b' 'magic04.b' l 'aloi.b' 'covtype.b' 'ijcnn1.b' 'kddcup99.b' 'letter.b' 'optdigits.b' 'satimage.b' 'spambase.b' 'w8a.b'
# 'webspam.b' 'url.b' 
# 'aloi.b' 'covtype.b' 'ijcnn1.b' 'kddcup99.b' 'letter.b' 'optdigits.b' 'satimage.b' 'spambase.b'
