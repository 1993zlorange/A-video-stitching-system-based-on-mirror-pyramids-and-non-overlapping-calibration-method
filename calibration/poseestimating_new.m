function [ angle_13_new ] =poseestimating_new(  TRC_1,TRC_2, TRC_3,TRC_4,angle_12,angle_14)
%calculate the camera that are not adjecent
% 
%还原TRC
n_picture=8;
for i=1:n_picture
eval(['TRC_1_' num2str(i) '=dcm2quat(TRC_1((i-1)*3+1:(i*3),:));']);
end 
for i=1:n_picture
eval(['TRC_2_' num2str(i) '=dcm2quat(TRC_2((i-1)*3+1:(i*3),:));']);
end 
for i=1:n_picture
eval(['TRC_3_' num2str(i) '=dcm2quat(TRC_3((i-1)*3+1:(i*3),:));']);
end 
for i=1:n_picture
eval(['TRC_4_' num2str(i) '=dcm2quat(TRC_4((i-1)*3+1:(i*3),:));']);
end 
T_angle_12=angle2quat(angle_12(1),angle_12(2),angle_12(3),'YXZ');
T_angle_14=angle2quat(angle_14(1),angle_14(2),angle_14(3),'YXZ');
%---------------------------AK_new_k--------------------
for AK_om_right=1:n_picture
eval(['AK_new_1_' num2str(AK_om_right) '=T_left_forming(TRC_1_' num2str(AK_om_right) ')-T_right_forming(TRC_3_' num2str(AK_om_right) ');']);
end
for AK_om_right=1:n_picture
eval(['AK_new_2_' num2str(AK_om_right) '=T_left_forming(TRC_2_' num2str(AK_om_right) ')*inv(T_left_forming(T_angle_12))-T_right_forming(TRC_3_' num2str(AK_om_right) ')*inv(T_left_forming(T_angle_12));']);
end
 for AK_om_right=1:n_picture
 eval(['AK_new_3_' num2str(AK_om_right) '=T_left_forming(TRC_4_' num2str(AK_om_right) ')*inv(T_left_forming(T_angle_14))-T_right_forming(TRC_3_' num2str(AK_om_right) ')*inv(T_left_forming(T_angle_14));']);
 end


 A_new=AK_new_1_1;
 A_new=matrix_forming(A_new,AK_new_2_1);
  A_new=matrix_forming(A_new,AK_new_3_1);
for A_om_right=2:n_picture
eval(['A_new=matrix_forming(A_new,AK_new_1_' num2str(A_om_right) ');']);
 eval(['A_new=matrix_forming(A_new,AK_new_2_' num2str(A_om_right) ');']);
  eval(['A_new=matrix_forming(A_new,AK_new_3_' num2str(A_om_right) ');']);
end

[U S V]=svd(A_new);
Q_relative=V(:,4);

%求解相对T
R_relative=quat2dcm(Q_relative');
[angle_13_new(1),angle_13_new(2),angle_13_new(3)]=dcm2angle(R_relative,'YXZ');
 angle_13_new=angle_13_new*180/pi;
end

