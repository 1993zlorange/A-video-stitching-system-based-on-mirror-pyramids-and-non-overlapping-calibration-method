     function F = myfun(x)
    %  F =norm(AK_1*x(1:4))^2+norm(AK_2*x(1:4))^2+norm(A_result_K1*x(5:7)-b_result_K1)^2+norm(A_result_K2*x(5:7)-b_result_K2)^2;
load('tempresult.mat');
%-----------------------------fun1------------------------------
%     var_R=[];
%          var_T=[];
%         for R_fun=1:n_om_left-1
%         tempx=x;
%         temp_q=equatorialParams2Quaternion(tempx);
%         eval(['var_R=[var_R ; AK_' num2str(R_fun) '*temp_q];']);
%         end
%         for T_fun=1:n_om_left-1
%         eval(['var_T=[var_T ; BK_' num2str(T_fun) '*x(4:6)-b_' num2str(T_fun) '];']);
%         end
%         F=[var_R ;var_T];
 %------------------------------------------------fun2----------------
 
       var_R=[];
         var_T=[];
        for R_fun=1:n_om_left-1
        tempx=x;
        temp_q=equatorialParams2Quaternion(tempx);
        temp_r=equatorialParams2Rotation(temp_q);
        eval(['var_R=[var_R ;(AK_' num2str(R_fun) '*temp_q)];']);
        end
        for T_fun=1:n_om_left-1
        eval(['var_T=[var_T ; TTc_right_' num2str(T_fun) '-temp_r*TTc_left_' num2str(T_fun) '];']);
        end
        F=[var_R ;var_T];
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
% ----------------------------
%     var_R=[];
%          var_T=[];
%         for R_fun=1:n_om_left-1
%         eval(['var_R=[var_R ; norm(AK_' num2str(R_fun) '*x(1:4))];']);
%         end
% 
%         F=[var_R];

      end

% function F=myfun(x)
% k=1:n_om_left;
% % dds=A(4*(k-1):4*k,1:4);
% F=A[4(k-1)*4*k,1:4]*x(1:4);
% % eval(['F=AK_' num2str(k) '*x(1:4))];']);
% end