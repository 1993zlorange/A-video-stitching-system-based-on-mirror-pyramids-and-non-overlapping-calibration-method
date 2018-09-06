function err = submatrix(ax,ay,az,R)
OulerAngle = [ax,ay,az];
R1 = OulerToRota(OulerAngle);
Err = R1 - R;
sum = 0;
[n,m] = size(R);
for i = 1 : n
    for j = 1 :m
        sum = sum + abs(Err(i, j));
    end
end
err = sum / (n*m);

    