% function [OulerAngle, flag,err] = RotaToOula(R)
function [OulerAngle] = RotaToOula(R)
threshold = 0.0001;
OulerAngle = [];
flag = 0;
r1 = R(1,1);  r2 = R(1,2);   r3 = R(1,3);   
r4 = R(2,1);  r5 = R(2,2);   r6 = R(2,3); 
r7 = R(3,1);  r8 = R(3,2);   r9 = R(3,3);

Rz = atan( r4 / r1 );                     
sz = sin(Rz);   cz = cos(Rz);
Ry = atan( (-r7) / (r1*cz + r4*sz) );
Rx = atan( (r3*sz - r6*cz) / (r5*cz - r2*sz) );
% err = submatrix(Rx,Ry,Rz,R);
% if (err <  threshold)
%     OulerAngle = [Rx Ry Rz];
%     flag = 1;
% end
   OulerAngle = [Rx Ry Rz];
