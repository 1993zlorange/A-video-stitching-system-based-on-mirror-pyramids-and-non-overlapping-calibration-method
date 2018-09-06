#include "wrd2img.h"
#include <iostream>
#include "math.h"
#include"matrix.h"
using namespace std;
#define pi 3.1415926535897932384626433832795f

void wrd2img::world2erect(float x_src, float y_src, float z_src, int h_dst, int w_dst, float xy_dst[2])//世界坐标系到全景图像坐标映射
{
	float yaw = 0;
	float pitch, fw, fh, u, v;

	//evaluate yaw,pitch using (xyz)
	if (z_src > 0)
	{
		yaw = atan(x_src / z_src);
	}
	else
	{
		yaw = atan(x_src / z_src) + pi;
	}

	if (yaw > pi)
	{
		yaw = -(2 * pi - yaw);

	}

	pitch = asin(y_src);


	fw = w_dst / 2 / pi;
	fh = h_dst / pi;
	u = yaw * fw + w_dst / 2;
	v = pitch * fh + h_dst / 2;
	xy_dst[0] = u;
	xy_dst[1] = v;


}

void wrd2img::world2perspective(float x_src, float y_src, float z_src, float fov_dst, int h_dst, int w_dst, float xy_dst[2])
{
	float f, cx, cy;
	f = (float)w_dst / 2.0f / tan(fov_dst / 2);
	
	if (z_src > 0)
	{

		x_src = x_src / z_src;
		y_src = y_src / z_src;
		z_src = 1;

		cx = w_dst / 2.0f;
		cy = h_dst / 2.0f;

		float k[3][3] = {
			{ f, 0, cx },
			{ 0, f, cy },
			{ 0, 0, 1 }
		};

		float cor_c[3][1] = { { x_src }, { y_src }, { z_src } };
		float result_z[3];

		matrix_mul(k, cor_c, result_z);
		xy_dst[0] = result_z[0];
		xy_dst[1] = result_z[1];
	}
	else
	{
		xy_dst[0] = -1;
		xy_dst[1] = -1;


	}


	


}

void wrd2img::world2fisheye(float x_src, float y_src, float z_src, float D_dst[4], float fov_dst, int h_dst, int w_dst, float xy_dst[2])
{
    float f = sqrt(w_dst*w_dst + h_dst*h_dst) / fov_dst;
    //float f = (w_dst) / fov_dst;
   // f=(w_dst) / sqrt(w_dst*w_dst + h_dst*h_dst) *f;
	float cx = w_dst / 2;
	float cy = h_dst / 2;
	float r = sqrt(x_src*x_src + y_src*y_src);
	if (z_src > 0)
	{

		if (r == 0)
		{
			x_src = y_src = 0;
        }
		else
		{
			float theta = atan2(r, z_src);
            if (theta >= (fov_dst/ 2))
			{
				xy_dst[0] = -1;
				xy_dst[1] = -1;
				return;
			}
			float theta2 = theta*theta;
			float theta4 = theta2*theta2;
			float theta6 = theta4*theta2;
			float theta8 = theta4*theta4;
			float theta_d = theta * (1 +
				D_dst[0] * theta2 +
				D_dst[1] * theta4 +
				D_dst[2] * theta6 +
				D_dst[3] * theta8);
			x_src = x_src / r * theta_d;
			y_src = y_src / r * theta_d;

		}

		xy_dst[0] = f * x_src + cx;
		xy_dst[1] = f * y_src + cy;
	}
	else
	{
		xy_dst[0] = -1;
		xy_dst[1] = -1;


	}

}
