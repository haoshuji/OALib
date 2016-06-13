
# coding: utf-8

# In[60]:

import numpy as np
import re
import matplotlib.pyplot as plt
import os.path
import shutil
# from matplotlib.font_manager import FontProperties

# loc = 'D:/Dropbox/share(peilin-shuji)/OALAR/figures/'
# output ='D:/Dropbox/share(peilin-shuji)/OALAR/figures/'
loc = './results/std/'
output ='D:/Dropbox/share(peilin-shuji)/IJCAI2015-AASOP2/figures/'
# loc = './results/std/'
# output = './results/std/'
datas = ['svmguide1.b','pendigits.b','cod-rna_scale.b','covtype_scale.b','w8a.b','mushrooms.b','aloi.b','cod-rna_scale_2.b','segment.b','satimage.b','letter.b',\
'svmguide3.b','splice.b','spambase.b','optdigits.b','magic04.b','madelon.b',\
'kddcup99_10Percent.b','isolet1.b','ijcnn1.b','german.b','covtype_scale_2.b','clean.b','a8a.b']

labels = ['PE','APE', 'RPE', 'PA','APA','RPA','PAI','APAI','RPAI','PAII','APAII','RPAII',\
		  'SOP','ASOP','RSOP','AASOP','AASOP2','AROW','AAROW','RAROW']
markers = ['+', '+', '+', 'v', 'v', 'v', '^', '^', '^', 'p', 'p', 'p', \
			's', 'o','x','*','s',\
			'D', 'D','D']
ls = ['-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', \
'-', '-','-','-','-',\
'-', '-','-'] 
filltypes = ['none', 'none', 'none', 'none', 'none', 'none', 'none', 'none', 'none', 'none', 'none', 'none',\
 'none', 'none','none','none','none',\
 'none', 'none','none']
colors = ['black', 'blue','magenta', 'black','blue','magenta','black','blue','magenta', 'black','blue','magenta',\
 'black', 'black','green','magenta','red',\
 'black','Red','green'] 
x_labels=['Varied Query Ratio','Log of Varied Query Ratio','Varied Query Ratio','Log of Varied Query Ratio']
y_labels=['Accuracy','Accuracy','F1','F1']
file_names=['_accuracy','_accuracy_log','f1','f1_log']

res_each_alg = 8;
all_que = [0,3,6,9,12,17]
line_width = 2.3
marker_size = 8
marker_edge_width = 2
legend_size = 19
label_size = 18
tick_size = 16
legend_font_size = 8
output_ext = ".pdf"

ord = [1,4,7,10,13,14,15,16] #AASOP2
for data in datas:
	# print data	
	datafile = loc+data		
	if os.path.isfile(datafile) == False:
		print datafile + "\t does not exist"
		continue
	else:
		print data
	
	shutil.copyfile(loc+data+'_fixed.txt',output+data+'_fixed.txt')
	shutil.copyfile(datafile,output+data)
	M = np.loadtxt(datafile)	
	data = re.sub('\.b', '', data)
	n,d = M.shape
	print n,d
	
	for i in all_que:
		for j in range(d):
			M[i*res_each_alg,j] = (j+1)*1.0/d
			M[i*res_each_alg+2,j] = M[i*res_each_alg+1,0]
			M[i*res_each_alg+4,j] = M[i*res_each_alg+2,0]			

	for t in range(4):
		fig = plt.figure()
		ax = fig.add_subplot(1,1,1)	
		for i in ord:	
			plt.plot(M[i*res_each_alg,:], M[i*res_each_alg+2,:],\
					lw=line_width,label = labels[i], ls=ls[i], color=colors[i], marker = markers[i],\
					fillstyle=filltypes[i],markersize=marker_size,mew=marker_edge_width)					
		plt.ylabel(y_labels[t],fontsize=label_size)
		plt.grid(True,which="both",ls="--", color='0.4')
		ax.tick_params(axis='x', labelsize=tick_size)
		ax.tick_params(axis='y', labelsize=tick_size)
		if (t+1)%2 == 0:
			ax.set_xscale('log')
		plt.legend(loc=4, ncol=2, shadow=True, fancybox=True,prop={'size':legend_size},fontsize=legend_font_size)
		plt.savefig(output+data+file_names[t]+output_ext)
		plt.close(fig)
