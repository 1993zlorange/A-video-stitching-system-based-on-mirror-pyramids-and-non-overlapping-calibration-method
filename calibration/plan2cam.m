function [ XC ] = plan2cam( cali_test ,npicture)
%UNTITLED �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��

load(cali_test);
for i=1:npicture
eval(['XC_' num2str(i) '=rigid_motion2(X_' num2str(i) ',Rc_' num2str(i) ',Tc_' num2str(i) ');']);
end

XC=[];
for i=1:npicture
eval(['XC=[XC XC_' num2str(i) '];']);
end


end

