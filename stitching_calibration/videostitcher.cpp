#include "videostitcher.h"
#include "imgin2imgout_img.h"

#include <string>
#include "assert.h"



videoStitcher::videoStitcher(void)
{
	m_init = 0;
	m_frame_cnt = -1;
	m_flag = 0;
}

videoStitcher::~videoStitcher(void)
{
}

#define SRC_NUM_MAX 4
bool videoStitcher::loadParas(vector<Mat> imgs)
{
	
   m_src_num = 4;

	m_imgs_warped.resize(m_src_num);
	m_imgs_warped_f.resize(m_src_num);;
    int src_w = imgs[0].size().width;
    int src_h = imgs[0].size().height;
    Rect roi(540, 0, src_w-540*2, src_h);

	float yaw[SRC_NUM_MAX] = { 0, 92.3632,-179.7361, -90.96 };
	float pitch[SRC_NUM_MAX] = {  0, -1.8454, 0.0002, 0.7179 };
	float roll[SRC_NUM_MAX] = { 0,-1.9232,-0.1248,-0.7296};
	//float fc_data[SRC_NUM_MAX] = { { 141.723f }, { 141.723f }, { 141.723f }, { 141.723f } };
			float kk_1[3][3] = 
			{
				{ 862.3319, 0, 943.1206 },
				{0,871.6397,531.1547},
				{0,0,1}
			};
			float kk_2[3][3] =
			{
				{ 882.5380, 0, 937.2897 },
				{ 0, 891.1425, 540.3520 },
				{ 0, 0, 1 }
			};
			float kk_3[3][3] =
			{
				{ 878.6333, 0, 959.2584 },
				{ 0, 889.3848, 531.6276 },
				{ 0, 0, 1 }
			};
			float kk_4[3][3] =
			{
				{ 874.9527, 0, 939.3208 },
				{ 0, 882.4541, 547.5136 },
				{ 0, 0, 1 }
			};
	float D[SRC_NUM_MAX][4] = { { 0.0640f, 0.0052f, 0.0f, 0.0f },
	{ 0.0530f, 0.0106f, 0.0f, 0.0f },
	{ 0.0513f, 0.0085f, 0.0f, 0.0f } ,
	{ 0.0537f, 0.0039f, 0.0f, 0.0f } };
	//float yaw[SRC_NUM_MAX] = { -158.551, -61.824, 24.137, 115.250 };
	//float pitch[SRC_NUM_MAX] = { -3.345, -4.341, -4.911, -5.321 };
	//float roll[SRC_NUM_MAX] = { 2.654, -3.178, 2.089, -1.241 };
	//float fc_data[SRC_NUM_MAX] = { { 141.723f }, { 141.723f }, { 141.723f }, { 141.723f } };
	//float D[SRC_NUM_MAX][4] = { { 0.0f, 0.0f, 0.0f, 0.0f },
	//{ 0.0f, 0.0f, 0.0f, 0.0f },
	//{ 0.0f, 0.0f, 0.0f, 0.0f },
	//{ 0.0f, 0.0f, 0.0f, 0.0f } };
	//float yaw[SRC_NUM_MAX] ;
	//float pitch[SRC_NUM_MAX] ;
	//float roll[SRC_NUM_MAX] ;
	//float fc_data[SRC_NUM_MAX] ;
	//float D[SRC_NUM_MAX][4];
	//string fileName = "./distort=0.xml";
	//ReadXmlFile(fileName, yaw, pitch, roll, fc_data, D);
	//Ëã·¨²ÎÊý
	m_cp.resize(m_src_num);
	//for (int t = 0; t<m_src_num; t++)
	//{
	//	m_cp[t].width = src_w;
	//	m_cp[t].height = src_h;
	//	m_cp[t].yaw = -yaw[t] * CV_PI / 180.0;
	//	m_cp[t].pitch =- pitch[t] * CV_PI / 180.0;
	//	m_cp[t].roll = -roll[t] * CV_PI / 180.0;
	//	m_cp[t].fc = fc_data[t] * CV_PI / 180.0;
	//
	//	for (int k = 0; k < 4; k++)
	//	{
	//		m_cp[t].D[k] = D[t][k];
	//	}
	//	
	//}
	for (int t = 0; t<m_src_num; t++)
	{
		m_cp[t].width = src_w;
		m_cp[t].height = src_h;
		m_cp[t].yaw = -yaw[t] * CV_PI / 180.0;
		m_cp[t].pitch =- pitch[t] * CV_PI / 180.0;
		m_cp[t].roll = -roll[t] * CV_PI / 180.0;

	
		for (int k = 0; k < 4; k++)
		{
			m_cp[t].D[k] = D[t][k];
		}	
	}

	for (int j = 0; j < 3; j++)
	{
		for (int p = 0; p < 3; p++)
		{
			m_cp[0].kk[j][p] = kk_1[j][p];

		}		
	}
	for (int j = 0; j <3; j++)
	{
		for (int p = 0; p <3; p++)
		{
            m_cp[1].kk[j][p] = kk_2[j][p];

		}

	}
	for (int j = 0; j <3; j++)
	{
		for (int p = 0; p < 3; p++)
		{
            m_cp[2].kk[j][p] = kk_3[j][p];

		}

	}
	for (int j = 0; j < 3; j++)
	{
		for (int p = 0; p < 3; p++)
		{
            m_cp[3].kk[j][p] = kk_4[j][p];

		}

	}
m_seam_scale = max(1, m_dst_h / 400);
//m_seam_scale = 1;




	// calculate map
	imgin2imgout_img imgin2imgout_img22;
	printf("map calculating\n");
	m_maps_x.resize(m_src_num);
	m_maps_y.resize(m_src_num);
	m_corners.resize(m_src_num);
	m_sizes.resize(m_src_num);
//create map using panomath
    for (int t = 0; t < m_src_num; t++)
	{
        float corner_f[2];
        float m_size_f[2];
		Mat map_x(Size(m_dst_w, m_dst_h), CV_32FC1);
		Mat map_y(Size(m_dst_w, m_dst_h), CV_32FC1);
imgin2imgout_img22.fisheye2errect_map(imgs[t], m_cp[t].yaw, m_cp[t].pitch, m_cp[t].roll, m_cp[t].D, m_dst_w, m_dst_h, m_cp[t].kk, map_x, map_y, corner_f, m_size_f);

        m_corners[t].x=corner_f[0];
        m_corners[t].y=corner_f[1];
        m_sizes[t]=Size(m_size_f[0],m_size_f[1]);
        Rect map_roi(m_corners[t].x, m_corners[t].y, m_sizes[t].width, m_sizes[t].height);

		m_maps_x[t].create(m_sizes[t], CV_32FC1);
		m_maps_y[t].create(m_sizes[t], CV_32FC1);
		m_maps_x[t] = map_x(map_roi);
		m_maps_y[t] = map_y(map_roi);
		
	}


	m_maps_weight.resize(m_src_num);

	m_imgs_warped.resize(m_src_num);
	m_imgs_warped_f.resize(m_src_num);

	m_masks_warped.resize(m_src_num);
	m_masks_seam.resize(m_src_num);

    for (int t=0; t<m_src_num; t++)
	{
		m_imgs_warped[t].create(m_sizes[t], CV_8UC3);
		m_imgs_warped_f[t].create(m_sizes[t], CV_32FC3);

		m_masks_warped[t].create(m_sizes[t], CV_8UC1);
		m_masks_seam[t].create(m_sizes[t], CV_8UC1);

		Mat mask(Size(m_cp[t].width, m_cp[t].height), CV_8UC1);
		mask.setTo(Scalar::all(255));
		cv::remap(mask, m_masks_warped[t], m_maps_x[t], m_maps_y[t], CV_INTER_NN, BORDER_CONSTANT);
	}

	if (m_isGpuMat == 0)
	{
		m_result.create(Size(m_dst_w, m_dst_h), CV_32FC3);
	}
	else
	{
		m_d_imgs.resize(m_src_num);
		m_d_maps_x.resize(m_src_num);
		m_d_maps_y.resize(m_src_num);
		m_d_maps_weight.resize(m_src_num);
		m_d_imgs_warped.resize(m_src_num);
        for (int t=0; t<m_src_num; t++)
		{
			m_d_imgs[t].create(Size(m_cp[t].width, m_cp[t].height), CV_8UC3);
			m_d_maps_x[t].create(m_sizes[t], CV_32FC1);
			m_d_maps_y[t].create(m_sizes[t], CV_32FC1);
			m_d_maps_weight[t].create(m_sizes[t], CV_32FC3);
			m_d_imgs_warped[t].create(m_sizes[t], CV_8UC3);

			m_d_maps_x[t].upload(m_maps_x[t]);
			m_d_maps_y[t].upload(m_maps_y[t]);
		}
		m_d_result.create(Size(m_dst_w, m_dst_h), CV_32FC3);
	}
	return true;
}

void videoStitcher::find_seams(void)
{
	printf("\n seam finding...\n");

	bool try_cuda = true;
	string seam_find_type = "gc_color";

	// prpare seam finder
	Ptr<SeamFinder> seam_finder;
	if (seam_find_type == "no")
		seam_finder = makePtr<detail::NoSeamFinder>();
	else if (seam_find_type == "voronoi")
		seam_finder = makePtr<detail::VoronoiSeamFinder>();
	else if (seam_find_type == "gc_color")
	{
#ifdef HAVE_OPENCV_CUDALEGACY
		if (try_cuda && cuda::getCudaEnabledDeviceCount() > 0)
			seam_finder = makePtr<detail::GraphCutSeamFinderGpu>(GraphCutSeamFinderBase::COST_COLOR);
		else
#endif
			seam_finder = makePtr<detail::GraphCutSeamFinder>(GraphCutSeamFinderBase::COST_COLOR);
	}
	else if (seam_find_type == "gc_colorgrad")
	{
#ifdef HAVE_OPENCV_CUDALEGACY
		if (try_cuda && cuda::getCudaEnabledDeviceCount() > 0)
			seam_finder = makePtr<detail::GraphCutSeamFinderGpu>(GraphCutSeamFinderBase::COST_COLOR_GRAD);
		else
#endif
			seam_finder = makePtr<detail::GraphCutSeamFinder>(GraphCutSeamFinderBase::COST_COLOR_GRAD);
	}
	else if (seam_find_type == "dp_color")
		seam_finder = makePtr<detail::DpSeamFinder>(DpSeamFinder::COLOR);
	else if (seam_find_type == "dp_colorgrad")
		seam_finder = makePtr<detail::DpSeamFinder>(DpSeamFinder::COLOR_GRAD);
	if (!seam_finder)
	{
		cout << "Can't create the following seam finder '" << seam_find_type << "'\n";
		return;
	}

	int t;
	if (m_seam_scale == 1)
	{
		for (t=0; t<m_src_num; t++)
		{
			m_imgs_warped[t].convertTo(m_imgs_warped_f[t], CV_32FC3);
			m_masks_warped[t].copyTo(m_masks_seam[t]);
		}
		seam_finder->find(m_imgs_warped_f, m_corners, m_masks_seam);
	}
	else
	{
		vector<UMat> imgs_warped_ds(m_src_num);
		vector<UMat> imgs_warped_f_ds(m_src_num);
		vector<UMat> masks_seam_ds(m_src_num);
		for (t=0; t<m_src_num; t++)
		{
			Size size_ds = Size(m_sizes[t].width/m_seam_scale, m_sizes[t].height/m_seam_scale);
			imgs_warped_ds[t].create(size_ds, CV_8UC3);
			imgs_warped_f_ds[t].create(size_ds, CV_32FC3);
			masks_seam_ds[t].create(size_ds, CV_8UC1);

			cv::resize(m_imgs_warped[t], imgs_warped_ds[t], imgs_warped_ds[t].size(), 0, 0, INTER_LINEAR);
			imgs_warped_ds[t].convertTo(imgs_warped_f_ds[t], CV_32FC3);
			cv::resize(m_masks_warped[t], masks_seam_ds[t], masks_seam_ds[t].size(), 0, 0, INTER_NEAREST);
		}
		seam_finder->find(imgs_warped_f_ds, m_corners, masks_seam_ds);
		for (t=0; t<m_src_num; t++)
			cv::resize(masks_seam_ds[t], m_masks_seam[t], m_masks_seam[t].size(), 0, 0, INTER_NEAREST);

		Mat mask(Size(m_dst_w, m_dst_h), CV_8UC1);
		mask.setTo(0);
		for (t = 0; t < m_src_num; ++t)
		{
			Rect roi(m_corners[t].x, m_corners[t].y, m_sizes[t].width, m_sizes[t].height);
			Mat tmp;
			m_masks_seam[t].copyTo(tmp);
			tmp.setTo(0, mask(roi) > 0);
//			dilate(tmp, tmp, Mat(), Point(-1,-1), 5);
			tmp.copyTo(m_masks_seam[t]);
			mask(roi).setTo(255, tmp > 0);
		}
	}

	Mat dilated_mask, seam_mask, mask_warped;
	for (t=0; t<m_src_num; t++)
	{
		dilate(m_masks_seam[t], dilated_mask, Mat(), Point(-1,-1), 20);
//		m_masks_seam[t].copyTo(dilated_mask);
		cv::resize(dilated_mask, seam_mask, m_masks_seam[t].size());
		m_masks_warped[t].copyTo(mask_warped);
		mask_warped = seam_mask & mask_warped;
		mask_warped.copyTo(m_masks_seam[t]);
	}
}

void calcWeightMaps(const std::vector<UMat> &masks, const std::vector<Point> &corners,
									  std::vector<UMat> &weight_maps, float sharpness)
{
	weight_maps.resize(masks.size());
	for (size_t i = 0; i < masks.size(); ++i)
		createWeightMap(masks[i], sharpness, weight_maps[i]);

	Rect dst_roi = resultRoi(corners, masks);
	Mat weights_sum(dst_roi.size(), CV_32F);
	weights_sum.setTo(0);

	for (size_t i = 0; i < weight_maps.size(); ++i)
	{
		Rect roi(corners[i].x - dst_roi.x, corners[i].y - dst_roi.y,
			weight_maps[i].cols, weight_maps[i].rows);
		cv::add(weights_sum(roi), weight_maps[i], weights_sum(roi));
	}

	for (size_t i = 0; i < weight_maps.size(); ++i)
	{
		Rect roi(corners[i].x - dst_roi.x, corners[i].y - dst_roi.y,
			weight_maps[i].cols, weight_maps[i].rows);
		Mat tmp = weights_sum(roi);
		tmp.setTo(1, tmp < std::numeric_limits<float>::epsilon());
		cv::divide(weight_maps[i], tmp, weight_maps[i]);
	}
}

void videoStitcher::calc_weights(void)
{
	float blend_width = 50;
	int t;

	calcWeightMaps(m_masks_seam, m_corners, m_maps_weight, 1.0f/blend_width);
	for (t=0; t<m_src_num; t++)
	{
		Mat channels[3];
		int c;
		for (c=0; c<3; c++)
			m_maps_weight[t].copyTo(channels[c]);
		cv::merge(channels, 3, m_maps_weight[t]);
	}

	if (m_isGpuMat == 1)
	{
		for (t=0; t<m_src_num; t++)
			m_d_maps_weight[t].upload(m_maps_weight[t]);
	}
}
/*
void videoStitcher::calc_weights(void)
{
	float blend_width = 10;

	int t;
	// calculating weights_map
	vector<Mat> weights(m_src_num);
	UMat weights_sum(Size(m_dst_w,m_dst_h), CV_32FC1);
	weights_sum.setTo(0);
	for (t=0; t<m_src_num; t++)
	{
		cv::detail::createWeightMap(m_masks_seam[t], 1.0f/blend_width, weights[t]);
		Rect roi(m_corners[t].x, m_corners[t].y, m_sizes[t].width, m_sizes[t].height);
		cv::add(weights_sum(roi), weights[t], weights_sum(roi));
	}
	for (t=0; t<m_src_num; t++)
	{
		Rect roi(m_corners[t].x, m_corners[t].y, m_sizes[t].width, m_sizes[t].height);
		cv::divide(weights[t], weights_sum(roi), weights[t]);
		Mat channels[3];
		int c;
		for (c=0; c<3; c++)
			weights[t].copyTo(channels[c]);
		cv::merge(channels, 3, m_maps_weight[t]);
	}
	if (m_isGpuMat == 1)
	{
		for (t=0; t<m_src_num; t++)
			m_d_maps_weight[t].upload(m_maps_weight[t]);
	}
}*/

void videoStitcher::stitching(vector<Mat> imgs, InputOutputArray pano)
{
	assert(m_flag == 0);
	m_flag = 1;

    if (m_init == 0)
	{
		if (pano.kind() == _InputArray::MAT)
		{
			m_isGpuMat = 0;
			m_dst_w = pano.getMat().cols;
			m_dst_h = pano.getMat().rows;
		}
		else if (pano.kind() == _InputArray::CUDA_GPU_MAT)
		{
			m_isGpuMat = 1;
			m_dst_w = pano.getGpuMat().cols;
			m_dst_h = pano.getGpuMat().rows;
		}
		else
		{
			m_init = -1;
			printf("pano input type error.\n");
			return;
		}

		if (!this->loadParas(imgs))
		{
			m_init = -1;
			printf("videoStitcher loadParas failed.\n");
			return;
		}
		m_src_num = min(m_src_num, (int)imgs.size());
		m_init = 1;
	}
	if (m_init != 1)
		return;

	m_frame_cnt++;

	int t;
	//calc seamline
	bool do_seam_find = (m_frame_cnt==0);
	if (do_seam_find)
	{
		for (t=0; t<m_src_num; t++)
			cv::remap(imgs[t], m_imgs_warped[t], m_maps_x[t], m_maps_y[t], CV_INTER_CUBIC);

		find_seams();
		calc_weights();
	}

//	if (m_frame_cnt % 200 == 0) //debug use
//		calc_weights();

	if (m_frame_cnt % 200 == 0)
	{
		printf("exposure compensator...\n");
		for (t=0; t<m_src_num; t++)

			cv::remap(imgs[t], m_imgs_warped[t], m_maps_x[t], m_maps_y[t], CV_INTER_CUBIC);

		Ptr<ExposureCompensator> compensator;
        int expos_comp_type = ExposureCompensator::GAIN ;
        compensator = ExposureCompensator::createDefault(expos_comp_type);
        compensator->feed(m_corners, m_imgs_warped, m_masks_warped);
        GainCompensator* gc = dynamic_cast<GainCompensator*>(compensator.get());
        vector<double> gains = gc->gains();
		for (t=0; t<m_src_num; t++)
		{
			m_d_maps_weight[t].upload(m_maps_weight[t]);
            cuda::multiply(m_d_maps_weight[t], Scalar(gains[t],gains[t],gains[t]), m_d_maps_weight[t]);
		}
	}

	if (m_isGpuMat == 0)
	{
		for (t=0; t<m_src_num; t++)
		{
			cv::remap(imgs[t], m_imgs_warped[t], m_maps_x[t], m_maps_y[t], CV_INTER_CUBIC);
			m_imgs_warped[t].convertTo(m_imgs_warped_f[t], CV_32FC3);
			if (t == 0)
				cv::multiply(m_imgs_warped_f[t], m_maps_weight[t], m_result);
			else
			{
				cv::multiply(m_imgs_warped_f[t], m_maps_weight[t], m_imgs_warped_f[t]);
				cv::add(m_result, m_imgs_warped_f[t], m_result);
			}
		}

        //output for scaling
        Rect roi(0,340,m_dst_w,m_dst_h-650);
        Size dst_size=Size(m_dst_w,m_dst_h-650);
        Mat a(dst_size, CV_32FC3);
          a= m_result(roi);
           a.convertTo(pano, CV_8UC3);
    //	m_result.convertTo(pano, CV_8UC3);
	}
	else
	{
		m_d_result.setTo(Scalar(0,0,0));
		GpuMat d_img_warped_f;
		for (t=0; t<m_src_num; t++)
		{
			Rect roi(m_corners[t].x, m_corners[t].y, m_sizes[t].width, m_sizes[t].height);
			m_d_imgs[t].upload(imgs[t]);
			cuda::remap(m_d_imgs[t], m_d_imgs_warped[t], m_d_maps_x[t], m_d_maps_y[t], INTER_CUBIC);
			m_d_imgs_warped[t].convertTo(d_img_warped_f, CV_32FC3);
			if (t == 0)
				cuda::multiply(d_img_warped_f, m_d_maps_weight[t], m_d_result(roi));
			else
			{
				cuda::multiply(d_img_warped_f, m_d_maps_weight[t], d_img_warped_f);
				cuda::add(d_img_warped_f, m_d_result(roi), m_d_result(roi));
			}
        }\
       //output for scaling
        Rect roi(0,340,m_dst_w,m_dst_h-650);
        Size dst_size=Size(m_dst_w,m_dst_h-650);
        GpuMat a(dst_size, CV_32FC3);
          a= m_d_result(roi);
//		m_d_result.convertTo(pano, CV_8UC3);
                a.convertTo(pano, CV_8UC3);
	}



	m_flag = 0;
}

