function [ A_result ,b_result] = BK_solving(R_relative, R0_K,T0_K,Ti_K)
I=eye(3);
A_result=I-R0_K;
b_result=T0_K-R_relative*Ti_K;

end

