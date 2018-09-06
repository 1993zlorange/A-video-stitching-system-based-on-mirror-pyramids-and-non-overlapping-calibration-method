function [ u ] = projection(T_deata,T0,Tj, x )
u=inv(T_deata)*inv(T0)*T_deata*Tj*x
end
