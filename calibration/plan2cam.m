function [ XC ] = plan2cam( cali_test ,npicture)
%UNTITLED 此处显示有关此函数的摘要
%   此处显示详细说明

load(cali_test);
for i=1:npicture
eval(['XC_' num2str(i) '=rigid_motion2(X_' num2str(i) ',Rc_' num2str(i) ',Tc_' num2str(i) ');']);
end

XC=[];
for i=1:npicture
eval(['XC=[XC XC_' num2str(i) '];']);
end


end

