#pragma once
#include "opencv2/opencv.hpp"
#include <vector>
using namespace cv;
using namespace std;

#include <opencv2/cudacodec.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudawarping.hpp>
#include "opencv2/stitching/detail/exposure_compensate.hpp"
#include "opencv2/stitching/detail/blenders.hpp"
#include "opencv2/stitching/detail/seam_finders.hpp"
#include "opencv2/stitching/detail/util.hpp"
#include "opencv2/stitching/detail/warpers.hpp"
#include "opencv2/stitching/warpers.hpp"
using namespace cuda;
using namespace cv::detail;

Mat ypr2rotation(double yaw, double pitch, double roll);
void coordtrans_fisheye2erect(double x, double y, double dst_w, Mat R, Mat fc, Mat cc, Mat kc, double valid_fov, double &xout, double &yout);

struct CameraPara
{
	int w, h;
	int width,height;
	float yaw, pitch, roll,fc;
	Rect roi;
	float D[4];//distortion
float kk[3][3];
	Mat R,  cc, alpha_c;
};

class videoStitcher
{
private:
	int m_init;
	int m_frame_cnt;
	int m_isGpuMat;

	int m_src_num;
	int m_dst_w, m_dst_h;
     int m_flag;

	// Ëã·¨²ÎÊý
	int m_seam_scale;

	vector<CameraPara>	m_cp;

	Ptr<SeamFinder>		m_seam_finder;
	Ptr<Blender>		m_blender;

	vector<Point>       m_corners;
	vector<Size>        m_sizes;
	vector<Mat>         m_maps_x;
	vector<Mat>         m_maps_y;
	vector<UMat>        m_maps_weight;

	vector<UMat>        m_imgs_warped;
	vector<UMat>		m_imgs_warped_f;

	vector<UMat>        m_masks_warped;
	vector<UMat>        m_masks_seam;

	Mat                 m_result;

	GpuMat				m_d_result;
	vector<GpuMat>      m_d_imgs;
	vector<GpuMat>      m_d_maps_x;
	vector<GpuMat>      m_d_maps_y;
	vector<GpuMat>		m_d_maps_weight;
	vector<GpuMat>      m_d_imgs_warped;
	vector<GpuMat>      m_d_imgs_warped_f;

	void find_seams(void);
	void calc_weights(void);
public:
	bool loadParas(vector<Mat> imgs);
	void stitching(vector<Mat> imgs, InputOutputArray pano);
	videoStitcher(void);
	~videoStitcher(void);
};
