%---------------------TEST Q_relative 4 AK---------------
for i=1:9
    
    
    eval(['q_test_' num2str(i) '=AK_' num2str(i) '*Q_relative;']);
end
%----------------------test ideal quat 4 AK-------------

angle_test=angle;

angle_test=angle_test*pi/180;
quat_test=angle2quat(angle_test(1),angle_test(2),angle_test(3));
quat_test=quat_test';
for i=1:9
    
    
    eval(['q_test2_' num2str(i) '=AK_' num2str(i) '*quat_test;']);
end





%-----------------------test Q_relative 4 c;------
for i=1:9
    
    
    eval(['c_test_' num2str(i) '=TTc_right_' num2str(i) '-R_relative*TTc_left_' num2str(i) ';']);
end

%----------------------- test quat_test 4 c------
R_test=quat2dcm(quat_test');
for i=1:9
    
    
    eval(['c_test2_' num2str(i) '=TTc_right_' num2str(i) '-R_test*TTc_left_' num2str(i) ';']);
end

%------------------------------test TRC---------
for i=1:9
    
    
    eval(['[TRC_left_test2_' num2str(i) '(1),TRC_left_test2_' num2str(i) '(2),TRC_left_test2_' num2str(i) '(3)]=dcm2angle(TRc_left_' num2str(i) ',''YXZ'');']);
     eval(['TRC_left_test2_' num2str(i) '=TRC_left_test2_' num2str(i)   '*180/pi;']);
end

for i=1:9
    
    
    eval(['[TRC_right_test2_' num2str(i) '(1),TRC_right_test2_' num2str(i) '(2),TRC_right_test2_' num2str(i) '(3)]=dcm2angle(TRc_right_' num2str(i) ',''YXZ'');']);
     eval(['TRC_right_test2_' num2str(i) '=TRC_right_test2_' num2str(i)   '*180/pi;']);
end

for i=1:9
    
    
    eval(['[RC_left_test2_' num2str(i) '(1),RC_left_test2_' num2str(i) '(2),RC_left_test2_' num2str(i) '(3)]=dcm2angle(Rc_left_' num2str(i) ',''YXZ'');']);
     eval(['RC_left_test2_' num2str(i) '=RC_left_test2_' num2str(i)   '*180/pi;']);
end

for i=1:9
    
    
    eval(['[RC_right_test2_' num2str(i) '(1),RC_right_test2_' num2str(i) '(2),RC_right_test2_' num2str(i) '(3)]=dcm2angle(Rc_' num2str(i) ',''YXZ'');']);
     eval(['RC_right_test2_' num2str(i) '=RC_right_test2_' num2str(i)   '*180/pi;']);
end


