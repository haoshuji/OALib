
# coding: utf-8

# In[60]:

import numpy as np
import re
import matplotlib as mpl
import matplotlib.pyplot as plt
import os.path
import shutil
import glob
mpl.rcParams['ps.fonttype']=42 # avoid using type 3 fonts
mpl.rcParams['pdf.fonttype']=42 # avoid using type 3 fonts

output = 'D:/Dropbox/share(hoi-shuji)/SOAL-AAAI16-v2/figures/'
loc=output

res_each_alg = 8;
line_width=2.3#[1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1,1,1, 1,1,1]
marker_size = 8
marker_edge_width = 2
legend_size = 23
legend_font_size = 13
label_size = 18
tick_size = 16
output_ext = ".pdf"
datas = ['url','webspam','a8a','aloi','clean','covtype_scale','ijcnn1',\
'kddcup99','letter','magic04','optdigits','satimage','spambase','w8a']
for data in datas:
	print data
	data_full_name = loc+data+'.txt'
	# for name in glob.glob(data_full_name+'*'):
	# 	print name
	if os.path.isfile(data_full_name) == False:
		print data_full_name + "\t does not exist"
		continue
	# else:
	# 	print data
	# 	if os.path.isfile(loc+data+'_fixed.txt') == False:
	# 		shutil.copyfile(loc+data+'_fixed.txt',output+data+'_fixed.txt')
	# 		shutil.copyfile(data_full_name,output+data)


	M = np.loadtxt(data_full_name)
	data = re.sub('\_b', '', data)
	n,d = M.shape
	# print n,d
	ord = []; all_que=[];markers =[];ls=[];filltypes=[];colors=[];
	x_labels=['Varied Query Ratio','Log of Varied Query Ratio']
	y_labels=['Time(s)','Time(s)']
	file_names=['_time']
	algorithms = []

	if n == 176:
		if data == 'url':
			algorithms = ['PE','APE', 'RPE', 'PA','APA','RPA','PAI','APAI','RPAI','PAII','APAII','RPAII','SOP','ASOP-diag',\
			'RSOP','AASOP-diag','AASOP2-diag','SOL-diag','AAROW','SOAL-diag','SORL-diag','AROW']
		else:
			algorithms = ['PE','APE', 'RPE', 'PA','APA','RPA','PAI','APAI','RPAI','PAII','APAII','RPAII','SOP','ASOP',\
			'RSOP','AASOP','AASOP2','SOL','AAROW','SOAL','SORL','AROW']
		ord = [1,10,13,17,20,19]
		all_que = [0,3,6,9,12,17,21]
		markers = ['+', 'x', '+', 'v', 'v', 'v', '^', '^', '^', 'p', 'p', 'p','s', 'o','x','o','x', 'D','<', 's','d','>']
		ls = ['-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-','-', '-','-', '-','-','-','-','-']
		filltypes = ['none', 'none', 'none', 'none', 'none', 'none', 'none', 'none', 'none', 'none', 'none', 'none', 'none',\
		'none', 'none', 'none','none', 'none','none', 'none','none','none']
		colors = ['black', 'darkorchid','magenta', 'black','blue','magenta', 'black','blue','magenta','black','blue','magenta',\
		'black', 'magenta','green','magenta','green','black','blue','red','green','black']
		# print len(markers), len(ls),len(filltypes),len(colors)
	else:
		if data == 'url':
			algorithms = ['PE','APE', 'RPE', 'PA','APA','RPA','PAI','APAI','RPAI','PAII','APAII','RPAII','SOP','ASOP-diag',\
			'RSOP','SOL','AAROW','SOAL-diag','SORL-diag','AROW']
		else:
			algorithms = ['PE','APE', 'RPE', 'PA','APA','RPA','PAI','APAI','RPAI','PAII','APAII','RPAII','SOP','ASOP','RSOP',\
			'SOL','AAROW','SOAL','SORL','AROW']
		ord = [1,10,13,15,18,17]
		all_que = [0,3,6,9,12,15,19]
		markers = ['+', 'x', '+', 'v', 'v', 'v', '^', '^', '^', 'p', 'p', 'p','s', 'o','x', 'D','<', 's','d','>']
		ls = ['-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-','-', '-','-', '-','-','-']
		filltypes = ['none', 'none', 'none', 'none', 'none', 'none', 'none', 'none', 'none', 'none', 'none', 'none', 'none',\
		 'none','none', 'none','none', 'none','none','none']
		colors = ['black', 'darkorchid','magenta', 'black','blue','magenta', 'black','blue','magenta','black','blue','magenta',\
		'black', 'magenta','green','black','blue','red','green','black']

	selected_ind={}
	selected_ind['clean']=np.arange(0.50, 0.80, 0.05)
	selected_ind['covtype']=selected_ind['clean']
	selected_ind['ijcnn1']=np.arange(0.85, 0.95, 0.02)
	selected_ind['letter']=np.arange(0.94, 1.0, 0.02)
	selected_ind['magic04']=np.arange(0.50, 0.80, 0.05)
	selected_ind['a8a']=np.arange(0.73, 0.87, 0.02)
	selected_ind['optdigits']=np.arange(0.5, 0.95, 0.05)
	selected_ind['satimage']=np.arange(0.70, 1, 0.05)
	selected_ind['spambase']=np.arange(0.40, 0.9, 0.05)
	selected_ind['aloi']=np.arange(0.46, 0.62, 0.02)
	selected_ind['kddcup99_10Percent']	= np.arange(0.980, 0.995, 0.005);
	selected_ind['w8a']=np.arange(0.95,0.99,0.005)
	selected_ind['webspam']=np.arange(0.82,0.94,0.02)
	# selected_ind['w8a']=np.arange(0.95,0.99,0.005)

	# print data

	if data == 'a8a':
		selected_ind['APE']=[2]+range(3,d);
		selected_ind['APAII']=range(2,d);
		selected_ind['ASOP']=range(d);
		selected_ind['SOAL']=[0,4]+range(6,d);
		selected_ind['SORL']=selected_ind['SOAL']
	elif data in ['aloi']:
		selected_ind['APE']=range(4,d);
		selected_ind['APAII']=range(2,d);
		selected_ind['ASOP']=range(d);
		selected_ind['SOAL']=[0,4]+range(6,d);
		selected_ind['SORL']=selected_ind['SOAL']
	elif data == 'clean':
		selected_ind['APE']=range(4,d);
		selected_ind['APAII']=range(3,d);
		selected_ind['ASOP']=[2,5]+range(7,d);
		selected_ind['SOAL']=[0,4]+range(6,d);
		selected_ind['SORL']=selected_ind['SOAL']
	elif data == 'covtype_scale':
		selected_ind['APE']=[2,4,6]+range(7,d);
		selected_ind['APAII']=[0,2,4]+range(5,d);
		selected_ind['ASOP']=range(3,d);
		selected_ind['SOAL']=[0]+range(6,d);
		selected_ind['SORL']=selected_ind['SOAL']
	elif data == 'ijcnn1':
		selected_ind['APE']=[2,4,5,6]+range(7,d);
		selected_ind['APAII']=[2,3,4]+range(5,d);
		selected_ind['ASOP']=range(d);
		selected_ind['SOAL']=[0,3,5,7]+range(8,d);
		selected_ind['SORL']=selected_ind['SOAL']
	elif data == 'letter':
		selected_ind['APE']=[2,4,6]+range(7,d);
		selected_ind['APAII']=[0,2,4]+range(5,d);
		selected_ind['ASOP']=range(d);
		selected_ind['SOAL']=[5,7]+range(8,d);
		selected_ind['SORL']=selected_ind['SOAL']
	elif data == 'magic04':
		selected_ind['APE']=[2,4,6]+range(7,d);
		selected_ind['APAII']=[0,2,4]+range(5,d);
		selected_ind['ASOP']=range(d);
		selected_ind['SOAL']=[0,5,7]+range(8,d);
		selected_ind['SORL']=selected_ind['SOAL']
	elif data == 'optdigits':
		selected_ind['APE']=[2,4,5,6]+range(7,d);
		selected_ind['APAII']=[2,4]+range(5,d);
		selected_ind['ASOP']=range(d);
		selected_ind['SOAL']=[2,5,7]+range(8,d);
		selected_ind['SORL']=selected_ind['SOAL']
	elif data in ['satimage']:
		selected_ind['APE']=[4,5,6]+range(7,d);
		selected_ind['APAII']=[4]+range(6,d);
		selected_ind['ASOP']=range(d);
		selected_ind['SOAL']=[5,7]+range(8,d);
		selected_ind['SORL']=selected_ind['SOAL']
	elif data in ['spambase']:
		selected_ind['APE']=[4,5,6]+range(7,d);
		selected_ind['APAII']=[2,4]+range(6,d);
		selected_ind['ASOP']=range(d);
		selected_ind['SOAL']=[2,4,5,6]+range(8,d);
		selected_ind['SORL']=selected_ind['SOAL']
	elif data=='w8a':
		selected_ind['APE']=[4,5,6]+range(7,d);
		selected_ind['APAII']=[1,3]+range(5,d);
		selected_ind['ASOP']=[0,2]+range(3,d);
		selected_ind['SOAL']=[2,5,7]+range(8,d);
		selected_ind['SORL']=selected_ind['SOAL']
	elif data=='kddcup99_10Percent':
		selected_ind['APE']=[4,5,6]+range(7,d);
		selected_ind['APAII']=[1,3]+range(5,d);
		selected_ind['ASOP']=[0,2]+range(3,d);
		selected_ind['SOAL']=[5,7]+range(9,d);
		selected_ind['SORL']=selected_ind['SOAL']
	elif data=='gisette.100':
		selected_ind['APE']=[4,5,6]+range(7,d);
		selected_ind['APAII']=[1,3]+range(5,d);
		selected_ind['ASOP']=[0,2]+range(3,d);
		selected_ind['SOAL']=[3,7,8]+range(9,d);
		selected_ind['SORL']=selected_ind['SOAL']
	elif data == 'webspam':
		selected_ind['APE']=range(4,d);
		selected_ind['APAII']=range(3,d);
		selected_ind['ASOP']=range(0,d);
		selected_ind['SOAL']=[0,5,7]+range(9,d);
		selected_ind['SORL']=selected_ind['SOAL']
		selected_ind['AROW']=selected_ind['APAII']
		selected_ind['AAROW']=selected_ind['APAII']
	elif data == 'url':
		selected_ind['APE']=range(d);
		selected_ind['APAII']=range(d);
		selected_ind['ASOP-diag']=range(d);
		selected_ind['SOAL-diag']=range(9,d);
		selected_ind['SORL-diag']=selected_ind['SOAL-diag']
	else:
		selected_ind['APE']=[0,2,4]+range(6,d);
		selected_ind['APAII']=[0,2,4]+range(5,d);
		selected_ind['ASOP']=[0,2]+range(3,d);
		selected_ind['SOAL']=[0,3,5,7]+range(9,d);
		selected_ind['SORL']=selected_ind['SOAL']

	for i in all_que:
		M[i*res_each_alg,:] = np.linspace(0,1,d)
		M[i*res_each_alg+2,:] = M[i*res_each_alg+2,0]
		M[i*res_each_alg+4,:] = M[i*res_each_alg+4,0]
		M[i*res_each_alg+6,:] = M[i*res_each_alg+6,0]

	for t in range(len(file_names)):
		fig = plt.figure()
		ax = fig.add_subplot(1,1,1)
		for m in range(len(ord)):
			i = ord[m]
			# print i
			plt.plot(M[i*res_each_alg,:], M[i*res_each_alg+6,:],lw=line_width,label = algorithms[i], ls=ls[i], color=colors[i],\
			 marker = markers[i],fillstyle=filltypes[i],markersize=marker_size,mew=marker_edge_width)

		plt.xlabel(x_labels[t],fontsize=label_size)
		plt.ylabel(y_labels[t],fontsize=label_size)
		plt.grid(True,which="both",ls="--", color='0.4')
		ax.tick_params(axis='x', labelsize=tick_size)
		ax.tick_params(axis='y', labelsize=tick_size)
		if data == 'covtype_scale' or data == 'clean':
			if 'log' in file_names[t]:
				ax.set_xscale('log')
				plt.legend(loc='best', ncol=2, shadow=True, fancybox=True,prop={'size':legend_size},fontsize=legend_font_size)
			else:
				# print data
				plt.legend(loc=(0.02,0.5), ncol=2, shadow=True, fancybox=True,prop={'size':legend_size},fontsize=legend_font_size)
		else:
			if 'log' in file_names[t]:
				ax.set_xscale('log')
				plt.legend(loc='best', ncol=2, shadow=True, fancybox=True,prop={'size':legend_size},fontsize=legend_font_size)
			else:
				plt.legend(loc='best', ncol=2, shadow=True, fancybox=True,prop={'size':legend_size},fontsize=legend_font_size)
		plt.savefig(output+data+file_names[t]+output_ext)
		plt.close(fig)
