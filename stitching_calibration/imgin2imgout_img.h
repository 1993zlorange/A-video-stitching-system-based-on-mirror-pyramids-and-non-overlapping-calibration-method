#include <iostream>
using namespace std;
// ‰»ÎÕºœÒ±‰ªªµΩ ‰≥ˆÕºœÒ
#include <opencv2/core/core.hpp>
#include <opencv/highgui.h>
using namespace cv;
class imgin2imgout_img
{
public:
	//!erect to perspective demo
	Mat erect2perspective_image(Mat SrcImage, float yaw, float pitch, float roll, int w_dst, int h_dst, float fov_dst);

	//!calculate map from erect to perspective
	/*input:
	SrcImage:src img
	(yaw,pitch,roll):euler angle
	(w_dst,h_dst):size of dst img
	fov_dst:fov of dst img
	output:
	m_maps_x:x coordinate of src img which correspond to the coordinate of dst img
	m_maps_y:y coordinate of src img which correspond to the coordinate of dst img
	mention:if (x,y)cannot be found the corresponding cor in dst img ,it will be -1;
	*/
	void erect2perspective_map(Mat SrcImage, float yaw, float pitch, float roll, int w_dst, int h_dst, float fov_dst, Mat m_maps_x, Mat  m_maps_y);

	//!perspective to erect   demo
	Mat perspective2errect_image(Mat SrcImage, float yaw, float pitch, float roll, int w_dst, int h_dst, float fov_src);

	//!calculate map from perspective to erect 
	/*input:
	SrcImage:src img
	(yaw,pitch,roll):euler angle
	(w_dst,h_dst):size of dst img
	fov_dst:fov of dst img
	output:
	m_maps_x:x coordinate of src img which correspond to the coordinate of dst img
	m_maps_y:y coordinate of src img which correspond to the coordinate of dst img
	mention:if (x,y)cannot be found the corresponding cor in dst img ,it will be -1;
	*/
	void perspective2errect_map(Mat SrcImage, float yaw, float pitch, float roll, int w_dst, int h_dst, float fov_dst, Mat m_maps_x, Mat  m_maps_y);

	/*input:
	SrcImage:src img
	(yaw,pitch,roll):euler angle
	(w_dst,h_dst):size of dst img
	fov_dst:fov of dst img
	D_dst£∫distortion of dst img
	output:
	m_maps_x:x coordinate of src img which correspond to the coordinate of dst img
	m_maps_y:y coordinate of src img which correspond to the coordinate of dst img
	mention:if (x,y)cannot be found the corresponding cor in dst img ,it will be -1;
	*/
	void fisheye2errect_map(Mat SrcImage,  float yaw, float pitch, float roll, float D_dst[4], int w_dst, int h_dst, float fov_dst, Mat m_maps_x, Mat  m_maps_y, float corner[2], float m_size[2]);
    void fisheye2errect_map(Mat SrcImage, float yaw, float pitch, float roll, float D_dst[4], int w_dst, int h_dst, float kk_dst[3][3], Mat m_maps_x, Mat  m_maps_y, float corner[2], float m_size[2]);
	//!erect to perspective demo
	Mat erect2fisheye_image(Mat SrcImage, float yaw, float pitch, float roll, int w_dst, int h_dst, float fov_dst);

	



};






