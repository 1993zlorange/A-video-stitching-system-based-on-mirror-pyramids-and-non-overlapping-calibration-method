#include <iostream>
using namespace std;
//世界坐标系到图像坐标系
class wrd2img
{
public:
	/* !help
	input:
	x_src, y_src, z_src: src coordinates of world image
	h_src: height of src image
	w_src:wedth of src image
	output:
	xy_dst:dst corrdinates of errect image

	*/
	void world2erect(float x_src, float y_src, float z_src, int h_dst, int w_dst,float xy_dst[2]);//世界坐标系到全景图像坐标映射

	/* ! help
	input:
	x_src, y_src, z_src: src coordinates of world image
	h_src: height of src image
	w_src:wedth of src image
	output:
	xy_dst:dst corrdinates of errect image

	*/
	void world2perspective(float x_src, float y_src, float z_src, float fov_dst ,int h_dst, int w_dst, float xy_dst[2]);

	void world2perspective(float x_src, float y_src, float z_src, float K[3][3], float D[5], float xy_dst[2]);

	void world2fisheye(float x_src, float y_src, float z_src, float D_dst[4], float fov_dst, int h_dst, int w_dst, float xy_dst[2]);

	void world2fisheye(float x_src, float y_src, float z_src, float D_dst[4], float kk[3][3], int h_dst, int w_dst, float xy_dst[2]);





};


