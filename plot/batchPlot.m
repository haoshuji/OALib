dataset={'covtype_b','magic04_b','a8a_b', 'aloi_b', 'clean_b', 'ijcnn1_b', 'kddcup99_10Percent_b', 'letter_b', 'optdigits_b', 'satimage_b', 'spambase_b', 'w8a_b'} 
dataset = {'covtype_scale_b','clean_b'}
input_loc = './11May/';
output_loc = 'D:\Dropbox\share(peilin-shuji)\OALAR-ICDM15\figures\parameters\';
for i=1:length(dataset),
    display(dataset{i});
    plot_parameter_sensitivity(input_loc,output_loc,dataset{i});
end
