# A-video-stitching-system-based-on-mirror-pyramids-and-non-overlapping-calibration-method
code for CISP-BMEI2017 A video stitching system based on mirror pyramids and non-overlapping calibration method

# Abstract
The panoramic cameras on the market do not allow seamless stitching of the object close to the camera with the
existence of non-zero parallax angle. Meanwhile, the traditional real-time stitching technology requires that the geometry of the
camera group is known, and the external projection points are used to manually find feature points in the overlapped region.
Therefore, this paper presents a method in creating a mirror reflection panoramic real-time splicing system by calibration.
And because that the images taken by each camera have very narrow overlapping areas, a non-overlapping calibration method
is proposed, requires only four fixed calibration patterns by rotations to complete a simple and convenient calibration work
with evident effect. The ability of the camera being built on capturing a close-up shot during live video is of great significance
for the future of panoramic video shooting.
# Index
Terms—Mirror pyramids, panoramic camera, real-time stitching system, calibration,
# imform
The code is seperated into calibaration and stitching 

# calibration(matlab)
## need
* matlab calibration tool box

## entrance ：entrance.m（include analysis of error）
* extract TRC_left，TRC_right to TRC_1_x
* doing pose_estimating to get the rotation matrix
* generate the random point of projection into m1
* through T_12（euler angle transfered into rotation matrix），TRC_1_x，TRC_2_x to do the reprojection
* calculate the error
 *after caclulation of the reprojection the offset of x,y is aver_errorx12,aver_errory12
 *calculate the distance n_picture_x，aver_error_norm12_y，aver_error_norm13_y， aver_error_norm14_y
 
## calculate the relative motion parametres（pose_estimating.m）
* first caculate the intrisic parametres
* take the motion parametres and the intrisic parametres of the camera every time the calibration pattern move compared with the camera into Rc_left，Tc_left 
* calculate the motion parametres of the relative attitude into TRc_left，TTc_left
* calculate the relative motion parametres in to R_relative(euler angle)
* save as TRC_left,TRC_right

# stitching(c++)
using the result of the calibration(relative camera parametres) to project the images captured by the cameras 
(there is another edition that the relative camera parametres are calulated by the software of KOLOR)
The projecting process used the projection-transforming library
github address:https://github.com/1993zlorange/projection-transforming
