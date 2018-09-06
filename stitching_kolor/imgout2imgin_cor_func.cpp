#include "imgout2imgin_cor.h"
#include "img2wrd.h"
#include "wrd2img.h"
#include <iostream>
#include "math.h"
#include "matrix.h"
using namespace std;
#define pi 3.1415926535897932384626433832795

//instantiation
img2wrd i2w;//class of img to world
wrd2img w2i;//class of world to image

void worldout2worldin(float yaw, float pitch, float roll, float x_src, float y_src, float z_src, float xyz_dst[3]);
//!
/*
output:
xyz_dst:the map from world out to world in
*/
void worldout2worldin(float yaw, float pitch, float roll, float x_src, float y_src, float z_src,float xyz_dst[3])
{
	float r = sqrt(pow(x_src, 2) + pow(y_src, 2) + pow(z_src, 2));
	x_src = x_src / r;
	y_src = y_src / r;
	z_src = z_src / r;
	float roll_r[3][3]=
	{
		{ cos(roll), -sin(roll), 0 },
		{ sin(roll), cos(roll), 0 },
		{ 0, 0, 1 }
	};
	float pitch_r[3][3]=
	{
		{ 1, 0, 0 },
		{ 0, cos(pitch), -sin(pitch) },
		{ 0, sin(pitch), cos(pitch) },
	};
	float yaw_r[3][3] =
	{

		{ cos(yaw), 0, sin(yaw) },
		{ 0, 1, 0 },
		{ -sin(yaw), 0, cos(yaw) },
	};
	float  R[3][3];
	matrix_mul(pitch_r, yaw_r, R);
	float  R2[3][3];
	matrix_mul(roll_r, R, R2);
	float cor_w[3][1]=
	{
		{ x_src },
		{ y_src },
		{ z_src },
	};
	matrix_mul(R2, cor_w, xyz_dst);



}
void imgout2imgin_cor::perspective2erect(float yaw, float pitch, float roll, float x_src, float y_src, int w_src, int  h_src, int w_dst, int h_dst, float fov_src, float xy_dst[2])//Í¸ÊÓÍ¼Ïñµ½È«¾°Í¼ÏñµÄ×ø±êÓ³Éä
{

	float cor_wout[3];
	float cor_win[3];

	i2w.perspective2world(x_src, y_src, fov_src, w_src, h_src, cor_wout);
	float x_wout = cor_wout[0];
	float y_wout = cor_wout[1];
	float z_wout = cor_wout[2];

	worldout2worldin(yaw, pitch, roll, x_wout, y_wout, z_wout, cor_win);
	float xw = cor_win[0];
	float yw = cor_win[1];
	float zw = cor_win[2];
	w2i.world2erect(xw, yw, zw, h_dst, w_dst, xy_dst);

}

void imgout2imgin_cor::errect2perspective(float yaw, float pitch, float roll, float x_src, float y_src, int w_src, int  h_src, int w_dst, int h_dst, float fov_dst, float xy_dst[2])
{
	float cor_wout[3];
	float cor_win[3];

	i2w.errect2world(x_src, y_src, w_src, h_src, cor_wout);
	float x_wout = cor_wout[0];
	float y_wout = cor_wout[1];
	float z_wout = cor_wout[2];

	worldout2worldin(yaw, pitch, roll, x_wout, y_wout, z_wout, cor_win);
	float xw = cor_win[0];
	float yw = cor_win[1];
	float zw = cor_win[2];
	w2i.world2perspective(xw, yw, zw, fov_dst, h_dst, w_dst, xy_dst);
}
void imgout2imgin_cor::errect2fisheye(float yaw, float pitch, float roll, float x_src, float y_src, int w_src, int  h_src, int w_dst, int h_dst, float fov_dst, float D_dst[4], float xy_dst[2])
{
	float cor_wout[3];
	float cor_win[3];

	i2w.errect2world(x_src, y_src, w_src, h_src, cor_wout);
	float x_wout = cor_wout[0];
	float y_wout = cor_wout[1];
	float z_wout = cor_wout[2];

	worldout2worldin(yaw, pitch, roll, x_wout, y_wout, z_wout, cor_win);
	float xw = cor_win[0];
	float yw = cor_win[1];
	float zw = cor_win[2];
	w2i.world2fisheye(xw, yw, zw, D_dst, fov_dst, h_dst, w_dst, xy_dst);

}
