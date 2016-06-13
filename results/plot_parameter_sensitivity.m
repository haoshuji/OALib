function plot4(input_loc,output_loc,dataset)
    parameters = [10^-5, 10^-4,10^-3,10^-2,10^-1,10^0, 10^1,10^2,10^3,10^4,10^5];
    parameters2 = [10^-5,  1,  10^5];
    parameters3 = [10^-5,  1,  10^5];
    num_par = length(parameters)
    
    fid = fopen(strcat(input_loc, dataset, '_par_figure.txt'));
    fgets(fid);fgets(fid) %APA-I, APA-II
    tline = fgets(fid);
    C = strsplit(tline);
    AROW= zeros(num_par*num_par,1);    
    for i=1:(num_par*num_par),
        AROW(i) = str2double(C(i));
    end

    legendsize=10;
    labelsize=32;
    linewidth=2;
    marker_size=12;  
    
    X = parameters; Y = parameters;
    Z = zeros(num_par, num_par);    
    for i = 1:num_par,        
        for j = 1:num_par,            
            Z(i,j) = AROW((i-1)*num_par+j);
        end
    end
    h = figure('visible','off')
%     h = figure
%     scatter3(X,Y,Z,70,'r')
%     mesh(X,Y,Z)
    surf(X,Y,Z)
    colorbar
    xlabel('\eta', 'fontsize', labelsize)%, 'FontWeight','bold','Color', 'r')
    ylabel('\gamma', 'fontsize', labelsize)%,'FontWeight','bold','Color', 'r')
%     zlabel('AP@10', 'fontsize', labelsize)
    ax = gca;
    ax.XTick = parameters3;    
    ax.YTick = parameters3;    
    set(gca, 'XScale', 'log')
    set(gca, 'YScale', 'log')
    set(gca,'FontSize',20)
    view([0,90])
%     ti = get(gca,'TightInset')
%     set(gca,'Position',[ti(1) ti(2) 1-ti(3)-ti(1) 1-ti(4)-ti(2)]);
%     set(gca,'units','centimeters')
%     pos = get(gca,'Position');
%     ti = get(gca,'TightInset');
%     set(gcf, 'PaperUnits','centimeters');
%     set(gcf, 'PaperSize', [pos(3)+ti(1)+ti(3) pos(4)+ti(2)+ti(4)]);
%     set(gcf, 'PaperPositionMode', 'manual');
%     set(gcf, 'PaperPosition',[0 0 pos(3)+ti(1)+ti(3) pos(4)+ti(2)+ti(4)]);
    print(h,'-depsc',strcat(output_loc,dataset,'_par_OALAR.eps'));
    saveas(h,strcat(output_loc,dataset,'_par_OALAR.pdf'))
    close(h);  
  