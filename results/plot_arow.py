
# coding: utf-8

# In[60]:

import numpy as np
import re
import matplotlib.pyplot as plt
import matplotlib as mpl
import os.path
import shutil
import glob
# from matplotlib.font_manager import FontProperties

mpl.rcParams['ps.fonttype']=42 # avoid using type 3 fonts
mpl.rcParams['pdf.fonttype']=42 # avoid using type 3 fonts

ord = []
all_que = []

input_loc = './11Jun/'
output = input_loc

x_label = 'Varied Query Ratio'
y_label = 'Accuracy'
metric = 'acc'

line_width=2
marker_size = 6
marker_edge_width = 1
legend_size = 5
legend_font_size = 5

label_size = 18
tick_size = 16

tick_size = 16


output_ext = ".pdf"


# datas = ['url','webspam','a8a','aloi','clean','covtype','ijcnn1',\
# 'kddcup99','letter','magic04','optdigits','satimage','spambase','w8a']
datas = ['covtype.scale']

for data in datas:
	print data

	if data == 'url':
		legend_size = 22
		legend_font_size = 12
	else:
		legend_size = 18
		legend_font_size = 12

	# make sure the result file exists
	data_fullname = input_loc + data + '.b.txt'
	if os.path.isfile(data_fullname) == False:
		print data_fullname + "\t does not exist"
		continue

	# read in the data into results dictionary
	results = {}
	algorithms = []
	d = 0 #number of queries
	with open(data_fullname,'r') as fin:
		alg_name = ''
		for line in fin.readlines():
			line_split = line.strip().split(' ')
			if len(line_split) == 1:
				alg_name = line_split[0]
				# algorithms.append(alg_name)
				results[alg_name] = {}
			else:
				d = len(line_split) - 1
				results[alg_name][line_split[0]] = [float(column) for column in line_split[1:]]

	# real alg names shown in the output figues
	real_alg_names = []
	if data == 'url':
		algorithms = ['APE', 'APAII', 'ASOPD', 'AROWD', 'RAROWD', 'AAROWD', 'AAROWD2']
		real_alg_names = ['APE','APAII','ASOP-d','SOL-d', 'SORL-d', 'SOAL-d-M','SOAL-d-S']
	else:
		algorithms = ['APE', 'APAII', 'ASOP', 'AROW', 'RAROW', 'AAROW', 'AAROW2']		
		real_alg_names = ['APE','APAII','ASOP','SOL','SORL','SOAL-M','SOAL-S']

	markers = ['x', 'p', 'o', 'D', 'd', '>', 's']
	colors = ['darkgray','blue','magenta','black','green','darkorchid','red']
	
	# print len(algorithms), len(real_alg_names), len(markers), len(colors)
	assert(len(algorithms) == len(real_alg_names) and len(algorithms) == len(markers) and len(markers) == len(colors))

	
		# print len(markers), len(ls),len(filltypes),len(colors)
	
	# set the y limits of output figure of each data
	y_limits={}
	y_limits['clean']=np.arange(0.50, 0.75, 0.05)
	y_limits['covtype.scale']=np.arange(0.55, 0.8, 0.05)
	y_limits['ijcnn']=np.arange(0.85, 0.95, 0.02)
	y_limits['letter']=np.arange(0.94, 1.0, 0.02)
	y_limits['magic04']=np.arange(0.50, 0.80, 0.05)
	y_limits['a8a']=np.arange(0.73, 0.87, 0.02)
	y_limits['optdigits']=np.arange(0.5, 0.95, 0.05)
	y_limits['satimage']=np.arange(0.70, 1, 0.05)
	y_limits['spambase']=np.arange(0.40, 0.9, 0.05)
	y_limits['aloi']=np.arange(0.46, 0.62, 0.02)
	y_limits['kddcup99']	= np.arange(0.980, 0.995, 0.005);
	y_limits['w8a']=np.arange(0.95,0.99,0.005)
	y_limits['webspam']=np.arange(0.82,0.94,0.02)
	y_limits['url']=np.arange(0.950,0.990,0.005)
	# selected_ind['w8a']=np.arange(0.95,0.99,0.005)

	# set the x ticks of each algorithm for each data, using real algorithms names
	x_ticks = {}
	x_ticks['SOL']=range(d);

	if data == 'a8a':
		x_ticks['APE']=[0,1,2]+range(3,d,2);
		x_ticks['APAII']=range(2,d);
		x_ticks['ASOP']=range(d);
		x_ticks['SOAL-S']=[0, 6, 10, 12]+range(14,d);
		x_ticks['SOAL-M']=[4,5]+range(6,d);
	elif data in ['aloi']:
		x_ticks['APE']=range(4,d);
		x_ticks['APAII']=range(2,d);
		x_ticks['ASOP']=range(d);
		x_ticks['SOAL-S']=[4]+range(6,d);
	elif data == 'clean':
		x_ticks['APE']=range(4,d);
		x_ticks['APAII']=range(3,d);
		x_ticks['ASOP']=range(2,d);
		x_ticks['SOAL-S']=[0,4]+range(6,d);
	elif data == 'covtype':
		x_ticks['APE']=[2,4,6]+range(7,d);
		x_ticks['APAII']=[0,2,4]+range(5,d);
		x_ticks['ASOP']=[0,2] + range(4,d);
		x_ticks['SOAL-S']=[0,4]+range(6,d);
	elif data == 'ijcnn1':
		x_ticks['APE']=[2,4,5,6]+range(7,d);
		x_ticks['APAII']=[2,3,4]+range(5,d);
		x_ticks['ASOP']=range(d);
		x_ticks['SOAL-S']=[3,5,7]+range(8,d);
	elif data == 'letter':
		x_ticks['APE']=[2,4,6]+range(7,d);
		x_ticks['APAII']=[0,2,4]+range(5,d);
		x_ticks['ASOP']=range(d);
		x_ticks['SOAL-S']=range(8,d);
		x_ticks['SOAL-M']=range(4,d);

	elif data == 'magic04':
		x_ticks['APE']=[2,4,6]+range(7,d);
		x_ticks['APAII']=[0,2,4]+range(5,d);
		x_ticks['ASOP']=range(d);
		x_ticks['SOAL-S']=[7, 9, 11]+range(12,d);
		x_ticks['SOAL-M']=range(4,5)+range(7,d);

	elif data == 'optdigits':
		x_ticks['APE']=[2,4,5,6]+range(7,d);
		x_ticks['APAII']=[2,4]+range(5,d);
		x_ticks['ASOP']=range(d);
		x_ticks['SOAL-S']=[7]+range(8,d);
		x_ticks['SOAL-M']=[3] +range(5,d);

	elif data in ['satimage']:
		x_ticks['APE']=[4,5,6]+range(7,d);
		x_ticks['APAII']=[4]+range(6,d);
		x_ticks['ASOP']=range(d);
		x_ticks['SOAL-S']=range(10,d);
		x_ticks['SOAL-M']=[5,6,7]+range(9,d);

	elif data in ['spambase']:
		x_ticks['APE']=[4,5,6]+range(7,d);
		x_ticks['APAII']=[2,4]+range(6,d);
		x_ticks['ASOP']=range(d);
		x_ticks['SOAL-S']=[2,4,5,6]+range(8,d);
	elif data=='w8a':
		x_ticks['APE']=[4,5,6]+range(7,d);
		x_ticks['APAII']=[2,3]+range(4,d);
		x_ticks['ASOP']=[0,2]+range(3,d);
		x_ticks['SOAL-S']=[7]+range(9,d);
		x_ticks['SOAL-M']=[4,5,6,7]+range(8,d);

	elif data=='kddcup99':
		x_ticks['APE']=[4,5,6]+range(7,d);
		x_ticks['APAII']=[1,3]+range(5,d);
		x_ticks['ASOP']=[0,2]+range(3,d);
		x_ticks['SOAL-S']=[5,7]+range(9,d);
	elif data=='gisette.100':
		x_ticks['APE']=[4,5,6]+range(7,d);
		x_ticks['APAII']=[1,3]+range(5,d);
		x_ticks['ASOP']=[0,2]+range(3,d);
		x_ticks['SOAL']=[3,7,8]+range(9,d);
	elif data == 'webspam':
		x_ticks['APE']=range(4,d);
		x_ticks['APAII']=range(3,d);
		x_ticks['ASOP']=range(0,d);
		x_ticks['SOAL-S']=range(4,d)
		x_ticks['SOAL-M']=range(3,d)

	elif data == 'url':
		x_ticks['APE']=range(2,d);
		x_ticks['APAII']=range(1,d);
		x_ticks['ASOP-d']=range(d);
		x_ticks['SOAL-d-S']=[7,9,11] + range(13,d)
		x_ticks['SORL-d']=x_ticks['SOAL-d-S']
		x_ticks['SOAL-d-M']=[5,6,7,8,9] + range(10,d)
	else:
		x_ticks['APE']=[0,2,4]+range(6,d);
		x_ticks['APAII']=[0,2,4]+range(5,d);
		x_ticks['ASOP']=[0,2]+range(3,d);
		x_ticks['SOAL-S']=[0,3,5,7]+range(9,d);
	
	if 'SOAL-S' in x_ticks:
	 	if 'SOAL-M' not in x_ticks:
			x_ticks['SOAL-M'] = x_ticks['SOAL-S']
		if 'SORL' not in x_ticks:
			x_ticks['SORL'] = x_ticks['SOAL-S']

	# print x_ticks
	fig = plt.figure()
	ax = fig.add_subplot(1,1,1)
	# print algorithms
	for i_alg in range(len(algorithms)):
		alg = algorithms[i_alg]
		real_alg = real_alg_names[i_alg]
		# print alg, real_alg
		if real_alg in ['SOL', 'SOL-d']:
			que = list(np.linspace(0,1,10))
			res = results[alg][metric][0:len(que)]
			# print len(que), len(res), results[alg][metric][0]
		else:
			que = [ results[alg]['que'][ind] for ind in x_ticks[real_alg] ]
			res = [ results[alg][metric][ind] for ind in x_ticks[real_alg] ]
		if data in ['aloi']:
			res.sort()
		plt.plot(que, res ,lw = line_width, label = real_alg_names[i_alg],\
			 ls = '-', color = colors[i_alg], marker = markers[i_alg], \
			 fillstyle = 'none',markersize = marker_size, mew = marker_edge_width)	
	
	plt.yticks(y_limits[data])
	plt.xlabel(x_label,fontsize=label_size)
	plt.ylabel(y_label,fontsize=label_size)
	plt.grid(True,which="both",ls="--", color='0.4')
	ax.tick_params(axis='x', labelsize=tick_size)
	ax.tick_params(axis='y', labelsize=tick_size)

	legend_location =''
	if metric == 'time':
		legend_location = 'best'
	else:
		legend_location = 'best'

	# Shrink current axis by 20%
	box = ax.get_position()
	ax.set_position([box.x0, box.y0, box.width * 0.8, box.height])

	# Put a legend to the right of the current axis
	# ax.legend(loc='center left', bbox_to_anchor=(1, 0.5))

	# plt.legend(loc=legend_location, ncol=3, fancybox=True,prop={'size':legend_size},fontsize=legend_font_size)
	plt.savefig(output + data + '_' + metric + output_ext)
	plt.close(fig)

	# print x_ticks
	fig = plt.figure()
	ax = fig.add_subplot(1,1,1)
	# print algorithms
	for i_alg in range(len(algorithms)):
		alg = algorithms[i_alg]
		real_alg = real_alg_names[i_alg]
		# print alg, real_alg
		if real_alg in ['SOL', 'SOL-d']:
			que = list(np.linspace(0,1,10))
			res = results[alg][metric][0:len(que)]
			# print len(que), len(res), results[alg][metric][0]
		else:
			que = [ results[alg]['que'][ind] for ind in x_ticks[real_alg] ]
			res = [ results[alg][metric][ind] for ind in x_ticks[real_alg] ]
		if data in ['aloi']:
			res.sort()
		plt.plot(que, res ,lw = line_width, label = real_alg_names[i_alg],\
			 ls = '-', color = colors[i_alg], marker = markers[i_alg], \
			 fillstyle = 'none',markersize = marker_size, mew = marker_edge_width)	

	plt.xlabel(x_label,fontsize=label_size)
	plt.ylabel(y_label,fontsize=label_size)
	plt.grid(True,which="both",ls="--", color='0.4')
	ax.tick_params(axis='x', labelsize=tick_size)
	ax.tick_params(axis='y', labelsize=tick_size)
	
	plt.yticks(y_limits[data])
	
	legend_location =''
	if metric == 'time':
		legend_location = 'best'
	else:
		legend_location = 'best'

	ax.set_xscale('log')
	# plt.legend(loc=legend_location, ncol=3, fancybox=True,prop={'size':legend_size},fontsize=legend_font_size)
	# plt.legend(loc=legend_location, ncol=1, shadow=True, fancybox=True,prop={'size':legend_size},fontsize=legend_font_size)
	plt.savefig(output + data + '_' + metric + '_log' + output_ext)
	plt.close(fig)


	# arg_sort = np.argsort(M[i*res_each_alg,:])
	# 	M[i*res_each_alg,:] = M[i*res_each_alg,arg_sort]
	# 	M[i*res_each_alg+2,:] = M[i*res_each_alg+2,arg_sort]
	# 	M[i*res_each_alg+4,:] = M[i*res_each_alg+4,arg_sort]
	# 	M[i*res_each_alg+6,:] = M[i*res_each_alg+6,arg_sort]
	# 	if m == 3:
	# 		plt.plot(M[i*res_each_alg,:], M[i*res_each_alg+ind_each_file[t],:],lw=line_width,label = algorithms[i],\
	# 		 ls=ls[i], color=colors[i], marker = markers[i],fillstyle='none',markersize=marker_size,mew=marker_edge_width)
	# 	else:
	# 		if data =='covtype':
	# 			tmp1=np.concatenate((M[i*res_each_alg, selected_ind[algorithms[i]]],np.ones(1)),axis=1);
	# 			tmp2=np.zeros(1)
	# 			tmp2[0]= M[i*res_each_alg+ind_each_file[t],d-1]
	# 			tmp3=np.concatenate((M[i*res_each_alg+ind_each_file[t],selected_ind[algorithms[i]]],tmp2),axis=1)
	# 			plt.plot(tmp1, tmp3,lw=line_width,label = algorithms[i], ls=ls[i], color=colors[i],fillstyle='none',\
	# 			 marker = markers[i],markersize=marker_size,mew=marker_edge_width)
	# 		else:
	# 			plt.plot(M[i*res_each_alg,selected_ind[algorithms[i]]], M[i*res_each_alg+ind_each_file[t],selected_ind[algorithms[i]]],\
	# 			lw=line_width,label = algorithms[i],\
	# 			 ls=ls[i], color=colors[i], marker = markers[i],fillstyle='none',markersize=marker_size,mew=marker_edge_width)

	# 	if t < 4:
	# 		ax.yaxis.set_ticks(selected_ind[data])
	# 		# print 'test'