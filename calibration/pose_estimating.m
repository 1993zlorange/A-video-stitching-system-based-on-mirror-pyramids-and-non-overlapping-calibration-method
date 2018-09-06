% function [ R_result,T_result ] = pose_estimating(  om_left_list,T_left_list,om_right_list ,T_right_list )
function [ TRC_left,TRC_right,KK_left,KK_right,kc_left,kc_right ,angle,angle_old] = pose_estimating(calib_file_name_left,calib_file_name_right)
%load数据
%   calib_file_name_left = 'Calib_Results_left.mat';
%   calib_file_name_right = 'Calib_Results_right.mat';
load_stereo_calib;
[m1,n_om_left]=size(om_left_list);
[m2,n_om_right]=size(om_right_list);
[m3,n_T_left]=size(T_left_list);
[m4,n_T_right]=size(T_right_list);
%求解TK
for TK_R_left=1:n_om_left-1
    TK_string_left=['[TRc_left_',num2str(TK_R_left), ',TTc_left_',num2str(TK_R_left),']='];
    TK_string_left=[TK_string_left,'TK_solving(Rc_left_1,Rc_left_',num2str(TK_R_left+1)];
    TK_string_left=[TK_string_left,',Tc_left_1,Tc_left_',num2str(TK_R_left+1),');'];
    eval([TK_string_left]);
end
for TK_R_right=1:n_om_left-1
    TK_string_right=['[TRc_right_',num2str(TK_R_right), ',TTc_right_',num2str(TK_R_right),']='];
    TK_string_right=[TK_string_right,'TK_solving(Rc_1,Rc_',num2str(TK_R_right+1)];
    TK_string_right=[TK_string_right,',Tc_1,Tc_',num2str(TK_R_right+1),');'];
    eval([TK_string_right]);
end
%求解相对R
 for c_om_left=1:n_om_left-1
eval(['Q_left_' num2str(c_om_left) '=dcm2quat(TRc_left_' num2str(c_om_left) ');']);
 end
 for c_om_right=1:n_om_right-1
% eval(['Rc_right_' num2str(TK_R_right) '=Rc_' num2str(TK_R_right) ';']);
% eval(['Tc_right_' num2str(TK_R_right) '=Tc_' num2str(TK_R_right) ';']);
eval(['Q_right_' num2str(c_om_right) '=dcm2quat(TRc_right_' num2str(c_om_right) ');']);
 end

 for AK_om_right=1:n_om_right-1
eval(['AK_' num2str(AK_om_right) '=AK_solving(Q_left_' num2str(AK_om_right) ',Q_right_' num2str(AK_om_right) ');']);
 end
 
 A=AK_1;
 for A_om_right=2:n_om_right-1
eval(['A=matrix_forming(A,AK_' num2str(A_om_right) ');']);

 end
% A=matrix_forming(AK_1,AK_2);
[U S V]=svd(A);
Q_relative=V(:,4);
%求解相对T
R_relative=quat2dcm(Q_relative');
%---------------------------------------for T----------------------------
%  for BK_om_right=1:n_om_right-1
 for BK_om_right=1:n_om_right-1
 string_BK=['[BK_' num2str(BK_om_right) ',b_' num2str(BK_om_right) ']=BK_solving(R_ref,TRc_left_' num2str(BK_om_right) ',TTc_left_' num2str(BK_om_right) ',TTc_right_' num2str(BK_om_right) ');'];
eval(['[BK_' num2str(BK_om_right) ',b_' num2str(BK_om_right) ']=BK_solving(R_relative,TRc_left_' num2str(BK_om_right) ',TTc_left_' num2str(BK_om_right) ',TTc_right_' num2str(BK_om_right) ');']);
 end
 B=BK_1;
 for B_om_right=2:n_om_right-1
eval(['B=matrix_forming(B,BK_' num2str(B_om_right) ');']);
 end
 b=b_1;
 for b_om_right=2:n_om_right-1
eval(['b=matrix_forming(b,b_' num2str(b_om_right) ');']);
 end
 T_relative=B\b;
 
 
%----------------------------------isnonlin------------
string_save=[];
string_save=[string_save 'save ' 'tempresult ' 'n_om_left'];
for n_save=1:n_om_left-1
string_save = [string_save  ' AK_' num2str(n_save) ' BK_' num2str(n_save) ' b_' num2str(n_save) ' A ' 'B ' 'b '  ' TTc_left_' num2str(n_save)  ' TTc_right_' num2str(n_save)];
end
eval([string_save]);
       
sor=rotation2EquatorialParams(R_relative);
% sor=rotation2EquatorialParams(eye(3));
x0=sor;
%       x0=[sor ;T_relative]
[xMY,resnorm] = lsqnonlin(@myfun,x0);
fprintf(1,'Rotation vector:   xMY = [ %3.5f   %3.5f  %3.5f ]\n',xMY);
fprintf(1,'resident:    %3.5f \n',resnorm);
q_new=equatorialParams2Quaternion(xMY(1:3));
R_new=equatorialParams2Rotation(xMY(1:3));
[angle(1),angle(2),angle(3)]=dcm2angle(R_new,'YXZ');
angle=angle*180/pi;
[angle_old(1),angle_old(2),angle_old(3)]=dcm2angle(R_relative,'YXZ');
angle_old=angle_old*180/pi;

%  T_relative=xMY(4:6);  
%------------------------------------cvx--------------------------
%  cvx_begin
% 
%     variable x(n-1);
%     expressions x_new(4);
%      x_new(1:3)=x(1:3);
%   x_new(4)=sqrt(1-x(1)^2-x(2)^2-x(3)^2);
% %     minimize   (( norm(A*x_new(1:4)) )+( norm(B*x(4:6)-b) ));
% minimize norm(A*x_new(1:4));
% % norm(x_new,2)<=1;
% cvx_end
% disp( 'Residual vector:' );
% disp( [ '   B*x-b = [ ', sprintf( '%7.4f ', B*x(4:6)-b ), ']' ] );
% Q_relative=x(1:4);
% T_relative=x(4:6);
T_relative=zeros(3,1);
% T_relative=B\b;
a=B*T_relative-b;
 x0=[Q_relative;T_relative];


%---------------------------------------draw------------------------------    
%     if 1,
%     figure(8);
%     plot3(X_right(1,:),X_right(2,:),X_right(3,:),'bo');
%     hold on;
%     [Xr2] = rigid_motion(X_left,om,T);
%      plot3(X_left(1,:),X_left(2,:),X_left(3,:),'go');
%     plot3(Xr2(1,:),Xr2(2,:),Xr2(3,:),'r+');
%     hold off;
%     drawnow;
%     end;
%     if 1,
%     figure(9);
%     plot3(X_right(1,:),X_right(2,:),X_right(3,:),'bo');
%     hold on;
% %   [Xr2] = rigid_motion(X_left,R_relative',T);
%     R_REF=rodrigues(om);
%     [Xr2] = rigid_motion2(X_right,R_REF',T_r2l);
%     plot3(X_left(1,:),X_left(2,:),X_left(3,:),'go');
%     plot3(Xr2(1,:),Xr2(2,:),Xr2(3,:),'r+');
%     hold off;
%     drawnow;
%     end;
%     if 1,
%     figure(10);
%     plot3(X_right_1(1,:),X_right_1(2,:),X_right_1(3,:),'bo');
%     hold on;
%    [Xr2] = rigid_motion2(X_right_1,R_new,T_relative);
% 
% %  [Xr2] = rigid_motion(X_right,R_ref,T_r2l);
%     plot3(X_left_1(1,:),X_left_1(2,:),X_left_1(3,:),'go');
%     plot3(Xr2(1,:),Xr2(2,:),Xr2(3,:),'r+');
%     hold off;
%     drawnow;
%     end;
%       
%  %for c++;
% [angle_my(1), angle_my(2), angle_my(3)]=dcm2angle(R_relative,'YXZ');
% angle_my_360=angle_my/pi*180;
% [angle_B(1), angle_B(2), angle_B(3)]=dcm2angle(R_REF','YXZ');
% angle_B_360=angle_B/pi*180;
% string_save=[];
% string_save=[string_save 'save ' 'resultfor2 ' 'angle_my_360 ' 'angle_B_360 ' 'angle '];
%  string_save = [string_save  'KK_left ' 'kc_left ' 'KK_right ' 'kc_right ' ];
%  eval([string_save]);
% 
%------------------------------for save-----------------
 TRC_left=TRc_left_1;
 for TRC_om_left=2:n_om_right-1
eval(['TRC_left=matrix_forming(TRC_left,TRc_left_' num2str(TRC_om_left) ');']);

 end
 
  TRC_right=TRc_right_1;
 for TRC_om_right=2:n_om_right-1
eval(['TRC_right=matrix_forming(TRC_right,TRc_right_' num2str(TRC_om_right) ');']);

 end

end

