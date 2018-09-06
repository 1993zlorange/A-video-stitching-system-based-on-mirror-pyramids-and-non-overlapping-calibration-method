#include <iostream>
#include "math.h"
using namespace std;
#include "imgout2imgin_cor.h"
#include "imgin2imgout_img.h"
#include <opencv2/core/core.hpp>
#include <opencv/highgui.h>
using namespace cv;

imgout2imgin_cor imgotut2imgin;//实例化输出到输入图像坐标对应的类

void imgin2imgout_img::erect2perspective_map(Mat SrcImage, float yaw, float pitch, float roll, int w_dst, int h_dst, float fov_dst, Mat m_maps_x, Mat  m_maps_y)
{


	int row = SrcImage.rows;
	int col = SrcImage.cols;
	for (int i = 0; i <w_dst; i = i + 1)//每一列扫描
	{
		for (int j = 0; j <h_dst; j++)
		{
			float u = 0, v = 0;

			float cor_image[2] = {0,0};
			imgotut2imgin.perspective2erect(yaw, pitch, roll, i, j, w_dst, h_dst, col, row, fov_dst, cor_image);
			u = cor_image[0];
			v = cor_image[1];

			if (floor(u) >= col || floor(v) >= row || floor(u) < 0 || floor(v) < 0)
			{

				m_maps_x.at<float>(j, i) = -1;
				m_maps_y.at<float>(j, i) = -1;
			}
			else if (floor(u) < col && floor(v) < row && floor(u) >= 0 && floor(v) >= 0)
			{

				int a = floor(v);
				int b = floor(u);
				m_maps_x.at<float>(j, i) = u;
				m_maps_y.at<float>(j, i) = v;
			
			}
			else
			{
				m_maps_x.at<float>(j, i) = -1;
				m_maps_y.at<float>(j, i) = -1;
			}
		}
	}
}


Mat imgin2imgout_img::erect2perspective_image(Mat SrcImage, float yaw, float pitch, float roll, int w_dst, int h_dst, float fov_dst)	//全景图像到透视图像demo
	{
		//Mat DestData = Mat_<char>(height, width*3);//普通初始化
	  Mat DestData = Mat(cvSize(w_dst, h_dst), CV_8UC3);
		int row = SrcImage.rows;
		int col = SrcImage.cols;
		for (int i = 0; i <w_dst; i = i + 1)//每一列扫描
		{
			for (int j = 0; j <h_dst; j++)
			{
				float u=0, v=0;
				
				float cor_image[2] = {0,0};
				imgotut2imgin.perspective2erect(yaw, pitch, roll, i, j, w_dst, h_dst, col, row, fov_dst, cor_image);
				u = cor_image[0];
				v = cor_image[1];

				if (floor(u) >= col || floor(v) >= row || floor(u) < 0 ||floor(v) < 0)
				{
					double a = 0;
					DestData.at<Vec3b>(j, i) = a;
				}
				else if (floor(u) < col && floor(v) < row && floor(u) >=0 && floor(v) >=0)
				{
					
					int a = floor(v);
					int b = floor(u);
					DestData.at<Vec3b>(j, i) = SrcImage.at<Vec3b>(floor(v), floor(u));
				}
				else
				{
					double a = 0;
					DestData.at<Vec3b>(j, i) = a;
				}
			}
		}

		return DestData;
		
	}//全景图像到透视图像demo

void imgin2imgout_img::perspective2errect_map(Mat SrcImage, float yaw, float pitch, float roll, int w_dst, int h_dst, float fov_dst, Mat m_maps_x, Mat  m_maps_y)
{
	int row = SrcImage.rows;
	int col = SrcImage.cols;
	//scan from the dst img
	for (int i = 0; i <w_dst; i = i + 1)
	{
		for (int j = 0; j <h_dst; j++)
		{
			float u = 0, v = 0;

			float cor_image[2] = {0,0};
			imgotut2imgin.errect2perspective(yaw, pitch, roll, i, j, w_dst, h_dst, col, row, fov_dst, cor_image);
			u = cor_image[0];
			v = cor_image[1];

			if (floor(u) >= col || floor(v) >= row || floor(u) < 0 || floor(v) < 0)
			{

				m_maps_x.at<float>(j, i) = -1;
				m_maps_y.at<float>(j, i) = -1;
			}
			else if (floor(u) < col && floor(v) < row && floor(u) >= 0 && floor(v) >= 0)
			{

				int a = floor(v);
				int b = floor(u);
				m_maps_x.at<float>(j, i) = u;
				m_maps_y.at<float>(j, i) = v;

			}
			else
			{
				m_maps_x.at<float>(j, i) = -1;
				m_maps_y.at<float>(j, i) = -1;
			}
		}
	}

}
Mat imgin2imgout_img::perspective2errect_image(Mat SrcImage, float yaw, float pitch, float roll, int w_dst, int h_dst, float fov_src)//全景图像到透视图像demo
	{
		//Mat DestData = Mat_<char>(height, width*3);//普通初始化
	Mat DestData = Mat(cvSize(w_dst, h_dst), CV_8UC3) = 0;
		int row = SrcImage.rows;
		int col = SrcImage.cols;
		for (int i = 0; i < w_dst; i = i + 1)//每一列扫描
		{
			for (int j = 0; j <h_dst; j++)
			{


				float u = 0, v = 0;

				float cor_image[2] = {0,0};
				imgotut2imgin.errect2perspective(yaw, pitch, roll, i, j, col, row, w_dst, h_dst, fov_src, cor_image);
				u = cor_image[0];
				v = cor_image[1];

				if (floor(u) >= col || floor(v) >= row || floor(u) < 0 || floor(v) < 0)
				{
					double a = 0;
					DestData.at<Vec3b>(j, i) = a;
				}
				else if (floor(u) < col && floor(v) < row && floor(u) >= 0 && floor(v) >= 0)
				{

					int a = floor(v);
					int b = floor(u);
					DestData.at<Vec3b>(j, i) = SrcImage.at<Vec3b>(floor(v), floor(u));
				}
				else
				{
					double a = 0;
					DestData.at<Vec3b>(j, i) = a;
				}


			}
			

		}

		return DestData;
	
	
	
	
	}
void imgin2imgout_img::fisheye2errect_map(Mat SrcImage, float yaw, float pitch, float roll, float D_dst[4], int w_dst, int h_dst, float fov_dst, Mat m_maps_x, Mat  m_maps_y,float corner[2], float m_size[2] )
{
	int row = SrcImage.rows;
	int col = SrcImage.cols;
		int x_min = row;
		int x_max = -1;
		int y_min = col;
		int y_max = -1;
	//scan from the dst img
	for (int i = 0; i <w_dst; i = i + 1)
	{
		for (int j = 0; j <h_dst; j++)
		{
			float u = 0, v = 0;

			float cor_image[2] = {0,0};
			imgotut2imgin.errect2fisheye(yaw, pitch, roll, i, j, w_dst, h_dst, col, row, fov_dst, D_dst,cor_image);
			u = cor_image[0];
			v = cor_image[1];

			if (floor(u) >= col-1 || floor(v) >= row-1 || floor(u) < 0 || floor(v) < 0)
			{

				m_maps_x.at<float>(j, i) = -1;
				m_maps_y.at<float>(j, i) = -1;


			}
            else if (floor(u) < col-220&& floor(v) < row && floor(u) > 200&& floor(v) > 0)
			{

				int a = floor(v);
				int b = floor(u);

                m_maps_x.at<float>(j, i) = u;
             m_maps_y.at<float>(j, i) = v;
        //    m_maps_x.at<float>(j, i) = i*2;
      //  m_maps_y.at<float>(j, i) = j*2;
						x_min = min(x_min, i);
						x_max = max(x_max, i);
						y_min = min(y_min, j);
						y_max = max(y_max, j);

			}
			else
			{
				m_maps_x.at<float>(j, i) = -1;
				m_maps_y.at<float>(j, i) = -1;
			}
		}
	}
			corner[0] = x_min;
			corner[1] = y_min;
			m_size[0] = x_max - x_min + 1;
			m_size[1]=	y_max - y_min + 1;
			

}























