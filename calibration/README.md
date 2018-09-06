# need
* matlab calibration tool box

# entrance ：entrance.m（include analysis of error）
* extract TRC_left，TRC_right to TRC_1_x
* doing pose_estimating to get the rotation matrix
* generate the random point of projection into m1
* through T_12（euler angle transfered into rotation matrix），TRC_1_x，TRC_2_x to do the reprojection
* calculate the error
 *after caclulation of the reprojection the offset of x,y is aver_errorx12,aver_errory12
 *calculate the distance n_picture_x，aver_error_norm12_y，aver_error_norm13_y， aver_error_norm14_y
 
# calculate the relative motion parametres（pose_estimating.m）
* first caculate the intrisic parametres
* take the motion parametres and the intrisic parametres of the camera every time the calibration pattern move compared with the camera into Rc_left，Tc_left 
* calculate the motion parametres of the relative attitude into TRc_left，TTc_left
* calculate the relative motion parametres in to R_relative(euler angle)
* save as TRC_left,TRC_right





