n_picture_x=[];
aver_error_norm12_old_y=[];
aver_error_norm12_y=[];
aver_error_norm13_y=[];
aver_error_norm14_y=[];
 for n_picture=3:8
%  n_picture=8;


calib_file_name_1 = '1_Results.mat';
calib_file_name_2 = '2_Results.mat';
calib_file_name_3 = '3_Results.mat';
 calib_file_name_4 = '4_Results.mat';

[ TRC_1,TRC_2,KK_1,KK_2,kc_1,kc_2 ,angle_12,angle_12_old] = pose_estimating(calib_file_name_1,calib_file_name_2);
[ TRC_1,TRC_4,KK_1,KK_4,kc_1,kc_4 ,angle_14,angle_14_old] = pose_estimating(calib_file_name_1,calib_file_name_4);
[ TRC_1,TRC_3,KK_1,KK_3,kc_1,kc_3 ,angle_13,angle_13_old] = pose_estimating(calib_file_name_1,calib_file_name_3);
[angle_13_new]=poseestimating_new( TRC_1,TRC_2, TRC_3,TRC_4,angle_12,angle_14);

%------------------------------重投影--------------------------

%还原TRC

for i=1:n_picture
eval(['TRC_1_' num2str(i) '=TRC_1((i-1)*3+1:(i*3),:);']);
end 
for i=1:n_picture
eval(['TRC_2_' num2str(i) '=TRC_2((i-1)*3+1:(i*3),:);']);
end 
for i=1:n_picture
eval(['TRC_3_' num2str(i) '=TRC_3((i-1)*3+1:(i*3),:);']);
end 
for i=1:n_picture
eval(['TRC_4_' num2str(i) '=TRC_4((i-1)*3+1:(i*3),:);']);
end 

% cali_test_1='1_test.mat';
% cali_test_2='2_test.mat';
% cali_test_3='3_test.mat';
% cali_test_4='4_test.mat';
cali_test_1='1_Results.mat';
cali_test_2='2_Results.mat';
cali_test_3='3_Results.mat';
cali_test_4='4_Results.mat';
npicture=9;
%---------------------------模拟点--------------------
% Centroid=[0 0 0];
% spread=[.12 .2 .22; .2 .34 .36;.22 .36 .43;];
% 
% N=500;
% 
%   M1 = mvnrnd(Centroid, spread*eye(3), N)';
% plot3(M1(1,:),M1(2,:),M1(3,:),'go');

%标定板坐标投到相机坐标系
[ XC_1 ] = plan2cam( cali_test_1 ,npicture);
[ XC_2 ] = plan2cam( cali_test_2 ,npicture);
[ XC_3 ] = plan2cam( cali_test_3 ,npicture);
[ XC_4 ] = plan2cam( cali_test_4 ,npicture);

% for i=1:npicture
% eval(['XC_1_' num2str(i) '=XC_1(:,(i-1)*48+1:(i*48));']);
% end 
% for i=1:npicture
% eval(['XC_2_' num2str(i) '=XC_2(:,(i-1)*48+1:(i*48));']);
% end 
% for i=1:npicture
% eval(['XC_3_' num2str(i) '=XC_3(:,(i-1)*48+1:(i*48));']);
% end 
% for i=1:npicture
% eval(['XC_4_' num2str(i) '=XC_4(:,(i-1)*48+1:(i*48));']);
% end 




angle_12=angle_12*pi/180;
angle_13=angle_13*pi/180;
angle_14=angle_14*pi/180;
angle_12_old=angle_12_old*pi/180;
T_12=angle2dcm(angle_12(1),angle_12(2),angle_12(3),'YXZ');
T_13=angle2dcm(angle_13(1),angle_13(2),angle_13(3),'YXZ');
T_14=angle2dcm(angle_14(1),angle_14(2),angle_14(3),'YXZ');
 T_12_old=angle2dcm(angle_12_old(1),angle_12_old(2),angle_12_old(3),'YXZ');
%---------------------------投影标定板的点--------------------------
% for j=1:8
% for i=1:48
% eval(['  [ u ] = projection(T_12_old,TRC_1_' num2str(j) ',TRC_2_' num2str(j) ', XC_2_' num2str(j+1) '(:,' num2str(i) ') ); ']);
% TEST=inv(T_12)*inv(TRC_1_1)*T_12*TRC_2_1;
% [test(1),test(2),test(3)]=dcm2angle(TEST,'YXZ');
% test=test*180/pi;
% plot3(u(1),u(2),u(3),'r+');
% eval(['error=norm((u-XC_2_' num2str(j+1) '(:,' num2str(i) ')),2);  ']);
%  fprintf(1,'error:    %3.5f \n',error);
% hold on;
% end
% end
% plot3( XC_2(1,:),XC_2(2,:),XC_2(3,:),'go');
%---------------------------------投影随机点-----------------------------

%变量
 N=500;
% for N =100 :50:500
%initial
sum_errorx12_old=0;
sum_errory12_old=0;
sum_errorx12=0;
sum_errory12=0;
sum_errorx13=0;
sum_errory13=0;
sum_errorx14=0;
sum_errory14=0;

for j=1:3

    Centroid=[0 0 0];
spread=[.12 .2 .22; .2 .34 .36;.22 .36 .43;];
  M1 = mvnrnd(Centroid, spread*eye(3), N)';
  M1=M1*30;
% plot3(M1(1,:),M1(2,:),M1(3,:),'go');
% hold on;
eval(['   u12_old  = projection(T_12_old,TRC_1_' num2str(j) ',TRC_2_' num2str(j) ', M1(:,:) ); ']);
eval(['   u12  = projection(T_12,TRC_1_' num2str(j) ',TRC_2_' num2str(j) ', M1(:,:) ); ']);
eval(['   u13  = projection(T_13,TRC_1_' num2str(j) ',TRC_3_' num2str(j) ', M1(:,:) ); ']);
eval(['   u14  = projection(T_14,TRC_1_' num2str(j) ',TRC_4_' num2str(j) ', M1(:,:) ); ']);
% TEST=inv(T_12)*inv(TRC_1_1)*T_12*TRC_2_1;
% [test(1),test(2),test(3)]=dcm2angle(TEST,'YXZ');
% test=test*180/pi;
% plot3(u(1,:),u(2,:),u(3,:),'r+');
% hold on;

% figure;
%-------------------------------计算误差---------------
for i=1:N
eval(['errorx12_old=u12_old(1,' num2str(i) ')-M1(1,' num2str(i) ');  ']);
eval(['errory12_old=u12_old(2,' num2str(i) ')-M1(2,' num2str(i) ');  ']);
eval(['errorx12=u12(1,' num2str(i) ')-M1(1,' num2str(i) ');  ']);
eval(['errory12=u12(2,' num2str(i) ')-M1(2,' num2str(i) ');  ']);
eval(['errorx13=u13(1,' num2str(i) ')-M1(1,' num2str(i) ');  ']);
eval(['errory13=u13(2,' num2str(i) ')-M1(2,' num2str(i) ');  ']);
eval(['errorx14=u14(1,' num2str(i) ')-M1(1,' num2str(i) ');  ']);
eval(['errory14=u14(2,' num2str(i) ')-M1(2,' num2str(i) ');  ']);
sum_errorx12_old=sum_errorx12_old+abs(errorx12_old);
sum_errory12_old=sum_errory12_old+abs(errory12_old);
sum_errorx12=sum_errorx12+abs(errorx12);
sum_errory12=sum_errory12+abs(errory12);
sum_errorx13=sum_errorx13+abs(errorx13);
sum_errory13=sum_errory13+abs(errory13);
sum_errorx14=sum_errorx14+abs(errorx14);
sum_errory14=sum_errory14+abs(errory14);
% plot(errorx,errory,'r+');
% hold on;
end


end

aver_errorx12_old=sum_errorx12_old/ (N*n_picture);
aver_errory12_old=sum_errory12_old/ (N*n_picture);
aver_error12_old=[aver_errorx12_old,aver_errory12_old]';
aver_error_norm12_old=norm(aver_error12_old,2);

aver_errorx12=sum_errorx12/ (N*n_picture);
aver_errory12=sum_errory12/ (N*n_picture);
aver_error12=[aver_errorx12,aver_errory12]';
aver_error_norm12=norm(aver_error12,2);

aver_errorx13=sum_errorx13/ (N*n_picture);
aver_errory13=sum_errory13/ (N*n_picture);
aver_error13=[aver_errorx13,aver_errory13]';
aver_error_norm13=norm(aver_error13,2);

aver_errorx14=sum_errorx14/ (N*n_picture);
aver_errory14=sum_errory14/ (N*n_picture);
aver_error14=[aver_errorx14,aver_errory14]';
aver_error_norm14=norm(aver_error14,2);

% plot(N,aver_error_norm,'r+');
% hold on;
n_picture_x=[n_picture_x  n_picture];
aver_error_norm12_old_y=[aver_error_norm12_old_y  aver_error_norm12_old];
aver_error_norm12_y=[aver_error_norm12_y  aver_error_norm12];
aver_error_norm13_y=[aver_error_norm13_y  aver_error_norm13];
aver_error_norm14_y=[aver_error_norm14_y  aver_error_norm14];
% printf(1,'error:    %3.5f  %3.5f \n',aver_errorx ,aver_errory);
% end
 end
% bar(n_picture_x,aver_error_norm_y);
%-----------------------------------画图--------------------
% plot(n_picture_x,aver_error_norm12_old_y,'k-o','linewidth',2,'markersize',4);
% hold on;
plot(n_picture_x,aver_error_norm12_y,'k-o','linewidth',2,'markersize',4);
hold on;
plot(n_picture_x,aver_error_norm13_y,'k-+','linewidth',2,'markersize',4);
hold on;
plot(n_picture_x,aver_error_norm14_y,'k--','linewidth',2);
set(gca,'FontSize',12, 'FontName','标楷体');
xlabel('number of pose','fontname','标楷体','fontweight','bold','fontsize',12);
ylabel('average error','fontname','标楷体','fontweight','bold','fontsize',12);
legend cam1-cam2 cam1-cam3 cam1-cam4;
legend('boxoff');
set(legend,'fontname','标楷体');
set(legend,'fontweight','bold');
hold off;
% string_save=[];
% string_save=[string_save 'save ' 'resultfor4 ' 'angle_12 ' 'angle_13 ' 'angle_14 '];
%   string_save = [string_save  'angle_12_old ' 'angle_13_old ' 'angle_14_old ' ];
%   string_save = [string_save  'KK_1 ' 'KK_2 ' 'KK_3 ' 'KK_4 ' ];
%     string_save = [string_save  'kc_1 ' 'kc_2 ' 'kc_3 ' 'kc_4 ' ];
%  eval([string_save]);