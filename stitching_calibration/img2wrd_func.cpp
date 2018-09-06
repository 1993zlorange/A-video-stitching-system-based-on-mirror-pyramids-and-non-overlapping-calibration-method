#include "img2wrd.h"
#include "matrix.h"
#include <opencv2/core/core.hpp>
#include <opencv/highgui.h>
using namespace cv;
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

void perspective2world(float x_src, float y_src, Mat RI_src_inv,int w_src, int h_src, float xyz_dst[3])
{

	float k[3][3] = 
		{
			{ RI_src_inv.at<float>(0, 0), RI_src_inv.at<float>(0, 1), RI_src_inv.at<float>(0, 2) },
			{ RI_src_inv.at<float>(1, 0), RI_src_inv.at<float>(1, 1), RI_src_inv.at<float>(1, 2) },
			{ RI_src_inv.at<float>(2, 0), RI_src_inv.at<float>(2, 1), RI_src_inv.at<float>(2, 2) }
		};
	float cor_c[3][1] = { { x_src }, { y_src }, { 1 } };


	matrix_mul(k, cor_c, xyz_dst);


}

void img2wrd::errect2world(float x_src, float y_src, int w_src, int h_src, float xyz_dst[3])
{
	float yaw = 0;
	float pitch, fw, fh, u, v;
	u = x_src;
	v = y_src;
	fw = w_src / 2 / pi;
	fh = h_src / pi;
	yaw = (u - w_src / 2) / fw;
	pitch = (v - +h_src / 2) / fh;
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

void img2wrd::fisheye2world(float x_src, float y_src, float fov_src, int w_src, float xyz_dst[3])
{
	float xw, yw, zw;
	float f, cx, cy;
	f = w_src / (fov_src);
	cx = w_src / 2;
	cy = w_src / 2;
	float x_theata, y_theata, z_theata;
	float theata_cor[3];
	float k_verse[3][3] = {
		{ 1 / f, 0, -cx / f },
		{ 0, 1 / f, -cy / f },
		{ 0, 0, 1 }
	};

	float cor_c[3][1] = { { x_src }, { y_src }, { 1 } };
	 matrix_mul(k_verse, cor_c,theata_cor);
	x_theata = theata_cor[0];
	y_theata = theata_cor[1];
	z_theata = theata_cor[2];
	float theata = sqrt(x_theata * x_theata + y_theata * y_theata);
	zw = cos(theata);
	yw = 0;
	if (y_theata >= 0)
	{
		yw = sqrt((sin(theata)*sin(theata)) / (1 + (   (x_theata / y_theata)*(x_theata / y_theata)  )));
	}
	else if (y_theata < 0)
	{
		yw = -sqrt((sin(theata)*sin(theata)) / (1 + (  (x_theata / y_theata)*(x_theata / y_theata)  )));
	}
	xw = x_theata / y_theata * yw;
	xyz_dst[0] = xw;
	xyz_dst[1] = yw;
	xyz_dst[2] = zw;
	

}




