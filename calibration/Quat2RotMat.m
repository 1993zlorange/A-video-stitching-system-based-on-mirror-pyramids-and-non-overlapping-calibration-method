function r=Quat2RotMat(q)
w=q(1);
x=q(2);
y=q(3);
z=q(4);
 
r=zeros(3,3);
r(1,1)=1-2*y*y-2*z*z;
r(1,2)=2*x*y+2*w*z;
r(1,3)=2*x*z-2*w*y;
 
r(2,1)=2*x*y-2*w*z;
r(2,2)=1-2*x*x-2*z*z;
r(2,3)=2*z*y+2*w*x;
 
r(3,1)=2*x*z+2*w*y;
r(3,2)=2*y*z-2*w*x;
r(3,3)=1-2*x*x-2*y*y;
r=r'; %matlab矩阵以列为主序，因此这里需要转置
end



