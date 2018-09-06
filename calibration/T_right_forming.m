function [ T ] = T_right_forming( quat )
%UNTITLED4 此处显示有关此函数的摘要
%   此处显示详细说明
T(1,1)=quat(1);T(1,2)=-quat(2);T(1,3)=-quat(3);T(1,4)=-quat(4);
T(2,1)=quat(2);T(2,2)=quat(1);T(2,3)=quat(4);T(2,4)=-quat(3);
T(3,1)=quat(3);T(3,2)=-quat(4);T(3,3)=quat(1);T(3,4)=quat(2);
T(4,1)=quat(4);T(4,2)=quat(3);T(4,3)=-quat(2);T(4,4)=quat(1);

end

