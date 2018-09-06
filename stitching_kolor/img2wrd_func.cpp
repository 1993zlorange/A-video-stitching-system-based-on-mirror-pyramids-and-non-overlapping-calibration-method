#include "img2wrd.h"
#include "matrix.h"
//#include <iostream>
#include "math.h"
//using namespace std;

#define pi 3.1415926535897932384626433832795

//透视图像到世界坐标系坐标映射
void img2wrd::perspective2world(float x_src, float y_src, float fov_src, int w_src, int h_src, float xyz_dst[3])
{
	float f, cx, cy;
	f = (float)w_src / 2.0f / tan(fov_src / 2);
	cx = w_src / 2.0f;
	cy = h_src / 2.0f;
	float k_verse[3][3] = {
		{ 1 / f, 0, -cx / f },
		{ 0, 1 / f, -cy / f },
		{ 0, 0, 1  }
	};
	float cor_c[3][1] = { { x_src }, { y_src }, { 1 } };


	matrix_mul(k_verse, cor_c, xyz_dst);



}//

void img2wrd::errect2world(float x_src, float y_src, int w_src, int h_src, float xyz_dst[3])
{
	float yaw = 0;
	float pitch, fw, fh, u, v;
	u = x_src;
	v = y_src;
	fw = w_src / 2 / pi;
	fh = h_src / pi;
	yaw = (u - w_src / 2) / fw;
	pitch = (v - h_src / 2) / fh;
	if (yaw > 0)
	{
		float cos_pitch = cos(pitch);
	}
	if (yaw < 0)
	{
		float cos_pitch = -cos(pitch);
	}
	xyz_dst[0] = sin(yaw)*cos(pitch);
	xyz_dst[1] = sin(pitch);
	xyz_dst[2] = cos(yaw)*cos(pitch);



}




