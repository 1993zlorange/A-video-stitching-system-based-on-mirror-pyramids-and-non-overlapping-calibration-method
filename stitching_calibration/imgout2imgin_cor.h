//#include <iostream>
//using namespace std;
//���ͼ������ͼ�������ӳ��
class imgout2imgin_cor
{
public:
	//! the map from perspective to erect
	void perspective2erect(float yaw, float pitch, float roll, float x_src, float y_src ,  int w_src, int  h_src, int w_dst, int h_dst, float fov_src, float xy_dst[2]);

	//! the map from erect to perspective
	void errect2perspective(float yaw, float pitch, float roll, float x_src, float y_src, int w_src, int  h_src, int w_dst, int h_dst, float fov_dst, float xy_dst[2]);
	
	//! the map from erect to fisheye
	void errect2fisheye(float yaw, float pitch, float roll, float x_src, float y_src, int w_src, int  h_src, int w_dst, int h_dst, float fov_dst,float D_dst[4],float xy_dst[2]);

	void errect2fisheye(float yaw, float pitch, float roll, float x_src, float y_src, int w_src, int  h_src, int w_dst, int h_dst, float kk_dst[3][3], float D_dst[4], float xy_dst[2]);
	//! the map from perspective to erect
	void fisheye2erect(float yaw, float pitch, float roll, float x_src, float y_src, int w_src,  int w_dst, int h_dst, float fov_src, float xy_dst[2]);



	


};












