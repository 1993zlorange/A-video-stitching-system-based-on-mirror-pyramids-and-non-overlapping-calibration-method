function [ R_re,T_re ] = TK_solving( R0,R1,T0,T1 )
    R_re =  R0*R1';
    T_re = T0 - R_re * T1;

end

