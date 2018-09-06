function [ A_result ] = matrix_forming( AK_1,AK_2 )
%UNTITLED5 此处显示有关此函数的摘要
%   此处显示详细说明
[m,n]=size(AK_1);
[m2,n2]=size(AK_2);
for(i=1:m)
    for(j=1:n)
    A_result(i,j)=AK_1(i,j);  
    end
end
for(i=1+m:m2+m)
    for(j=1:n)
    A_result(i,j)=AK_2(i-m,j);  
    end
end

end

