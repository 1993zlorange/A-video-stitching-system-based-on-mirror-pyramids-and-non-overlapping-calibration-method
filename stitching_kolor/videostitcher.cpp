#include "videostitcher.h"
#include "imgin2imgout_img.h"
#include "tinyxml.h"
#include "tinystr.h"
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
bool ReadXmlFile(string& szFileName, float yaw[4], float pitch[4], float roll[4], float fov[4], float D[4][4])
{//读取Xml文件，并遍历
    try
    {

        string fullPath = szFileName;
        //创建一个XML的文档对象。
        TiXmlDocument *myDocument = new TiXmlDocument(fullPath.c_str());
        myDocument->LoadFile();
        //获得根元素，即pano。
        TiXmlElement *RootElement = myDocument->RootElement();
        //获得第一个paono子节点。
        TiXmlElement *firstchild = RootElement->FirstChildElement();
        //追踪到image节点
        TiXmlElement *image = firstchild->NextSiblingElement();
        while (1)
        {
            string img_value = image->Value();
            if (img_value == "images")
            {
                break;
            }
            image = image->NextSiblingElement();
        }
        //read first camera para
        TiXmlElement *firstimage = image->FirstChildElement();
        TiXmlElement *firstimagefistchild = firstimage->FirstChildElement();
        TiXmlElement *firstimagecamera = firstimagefistchild->NextSiblingElement();
        float yaw_1 = atof(firstimagecamera->Attribute("yaw")) / CV_PI * 180;
        float pitch_1 = atof(firstimagecamera->Attribute("pitch")) / CV_PI * 180;
        float roll_1 = atof(firstimagecamera->Attribute("roll")) / CV_PI * 180;
        float f_1 = atof(firstimagecamera->Attribute("f")) / CV_PI * 180;
        float k1_1 = atof(firstimagecamera->Attribute("k1"));
        float k2_1 = atof(firstimagecamera->Attribute("k2"));
        float k3_1 = atof(firstimagecamera->Attribute("k3"));
        float offset_x_1 = atof(firstimagecamera->Attribute("offset_x"));
        float offset_y_1 = atof(firstimagecamera->Attribute("offset_y"));

        //read second camera para
        TiXmlElement *secondimage = firstimage->NextSiblingElement();
        TiXmlElement *secondimagefistchild = secondimage->FirstChildElement();
        TiXmlElement *secondimagecamera = secondimagefistchild->NextSiblingElement();
        float yaw_2 = atof(secondimagecamera->Attribute("yaw")) / CV_PI * 180;
        float pitch_2 = atof(secondimagecamera->Attribute("pitch")) / CV_PI * 180;
        float roll_2 = atof(secondimagecamera->Attribute("roll")) / CV_PI * 180;
        float f_2 = atof(secondimagecamera->Attribute("f")) / CV_PI * 180;
        float k1_2 = atof(secondimagecamera->Attribute("k1"));
        float k2_2 = atof(secondimagecamera->Attribute("k2"));
        float k3_2 = atof(secondimagecamera->Attribute("k3"));
        float offset_x_2 = atof(secondimagecamera->Attribute("offset_x"));
        float offset_y_2 = atof(secondimagecamera->Attribute("offset_y"));

        //read third camera para
        TiXmlElement *thirdimage = secondimage->NextSiblingElement();
        TiXmlElement *thirdimagefistchild = thirdimage->FirstChildElement();
        TiXmlElement *thirdimagecamera = thirdimagefistchild->NextSiblingElement();
        float yaw_3 = atof(thirdimagecamera->Attribute("yaw")) / CV_PI * 180;
        float pitch_3 = atof(thirdimagecamera->Attribute("pitch")) / CV_PI * 180;
        float roll_3 = atof(thirdimagecamera->Attribute("roll")) / CV_PI * 180;
        float f_3 = atof(thirdimagecamera->Attribute("f")) / CV_PI * 180;
        float k1_3 = atof(thirdimagecamera->Attribute("k1"));
        float k2_3 = atof(thirdimagecamera->Attribute("k2"));
        float k3_3 = atof(thirdimagecamera->Attribute("k3"));
        float offset_x_3 = atof(thirdimagecamera->Attribute("offset_x"));
        float offset_y_3 = atof(thirdimagecamera->Attribute("offset_y"));

        //read forth camera para
        TiXmlElement *fotrhimage = thirdimage->NextSiblingElement();
        TiXmlElement *fotrhimagefistchild = fotrhimage->FirstChildElement();
        TiXmlElement *fotrhimagecamera = fotrhimagefistchild->NextSiblingElement();
        float yaw_4 = atof(fotrhimagecamera->Attribute("yaw")) / CV_PI * 180;
        float pitch_4 = atof(fotrhimagecamera->Attribute("pitch")) / CV_PI * 180;
        float roll_4 = atof(fotrhimagecamera->Attribute("roll")) / CV_PI * 180;
        float f_4 = atof(fotrhimagecamera->Attribute("f")) / CV_PI * 180;
        float k1_4 = atof(fotrhimagecamera->Attribute("k1"));
        float k2_4 = atof(fotrhimagecamera->Attribute("k2"));
        float k3_4 = atof(fotrhimagecamera->Attribute("k3"));
        float offset_x_4 = atof(fotrhimagecamera->Attribute("offset_x"));
        float offset_y_4 = atof(fotrhimagecamera->Attribute("offset_y"));

        //assignment
        yaw[0] = yaw_1; yaw[1] = yaw_2; yaw[2] = yaw_3; yaw[3] = yaw_4;
        pitch[0] = pitch_1; pitch[1] = pitch_2; pitch[2] = pitch_3; pitch[3] = pitch_4;
        roll[0] = roll_1; roll[1] = roll_2; roll[2] = roll_3; roll[3] = roll_4;
        fov[0] = f_1; fov[1] = f_2; fov[2] = f_3; fov[3] = f_4;
        D[0][0] = k1_1; D[0][1] = k2_1; D[0][2] = k3_1; D[0][3] = 0;
        D[1][0] = k1_2; D[1][1] = k2_2; D[1][2] = k3_2; D[1][3] = 0;
        D[2][0] = k1_3; D[2][1] = k2_3; D[2][2] = k3_3; D[2][3] = 0;
        D[3][0] = k1_4; D[3][1] = k2_4; D[3][2] = k3_4; D[3][3] = 0;
    }
    catch (string& e)
    {
        return false;
    }
    return true;
}
#define SRC_NUM_MAX 4
bool videoStitcher::loadParas(vector<Mat> imgs)
{
	
    m_src_num =4;
	//int src_w = 1920;
	//int src_h = 1080;
	int src_w = imgs[0].size().width;
	int src_h = imgs[0].size().height;
    Rect roi(540, 0, src_w-540*2, src_h);

    //float yaw[SRC_NUM_MAX] = { -158.551, -61.824,24.137, 115.250 };
    //float pitch[SRC_NUM_MAX] = {  -3.345, -4.341, -4.911, -5.321 };
    //float roll[SRC_NUM_MAX] = { 2.654,-3.178,2.089,-1.241};
    //float fc_data[SRC_NUM_MAX] = { 141.723f, 141.723f,  141.723f, 141.723f};
    //float kc_data[SRC_NUM_MAX][4] = { {0.0f , 0.0f ,0.0f ,0.0f },
     //{0.0f , 0.0f ,0.0f ,0.0f },
    //{0.0f , 0.0f ,0.0f ,0.0f },
    //{0.0f , 0.0f ,0.0f ,0.0f }};
    float yaw[SRC_NUM_MAX] ;
    float pitch[SRC_NUM_MAX] ;
    float roll[SRC_NUM_MAX] ;
    float fc_data[SRC_NUM_MAX] ;
    float D[SRC_NUM_MAX][4];

    //find the xml
    string fileName = "10.28.xml";
    ReadXmlFile(fileName, yaw, pitch, roll, fc_data, D);


	// 算法参数
    m_seam_scale = max(1, 	m_dst_h / 400);
     //   m_seam_scale =1;
	m_cp.resize(m_src_num);
	int t;
	for (t=0; t<m_src_num; t++)
	{
		m_cp[t].width = src_w;
		m_cp[t].height = src_h;
		m_cp[t].roi = roi;
        m_cp[t].yaw = -yaw[t] * CV_PI / 180.0;
        m_cp[t].pitch =- pitch[t] * CV_PI / 180.0;
        m_cp[t].roll = -roll[t] * CV_PI / 180.0;
		m_cp[t].fc = fc_data[t] * CV_PI / 180.0;
		for (int k = 0; k < 4; k++)
		{
            m_cp[t].D[k] = D[t][k];
		}
	
	}

	// calculate map
	imgin2imgout_img imgin2imgout_img22;
	printf("map calculating\n");
	m_maps_x.resize(m_src_num);
	m_maps_y.resize(m_src_num);
	m_corners.resize(m_src_num);
	m_sizes.resize(m_src_num);
//create map using panomath
    for (t = 0; t < m_src_num; t++)
	{
        float corner_f[2];
        float m_size_f[2];
		Mat map_x(Size(m_dst_w, m_dst_h), CV_32FC1);
		Mat map_y(Size(m_dst_w, m_dst_h), CV_32FC1);
		imgin2imgout_img22.fisheye2errect_map(imgs[t], m_cp[t].yaw, m_cp[t].pitch, m_cp[t].roll, m_cp[t].D, m_dst_w, m_dst_h, m_cp[t].fc,map_x, map_y,corner_f,m_size_f);
        m_corners[t].x=corner_f[0];
        m_corners[t].y=corner_f[1];
        m_sizes[t]=Size(m_size_f[0],m_size_f[1]);
        m_corners[t].x=m_corners[t].x;
        if(t==1)
        {
         m_sizes[t]=Size(m_size_f[0]-52,m_size_f[1]);
        }
        else
        {
          m_sizes[t]=Size(m_size_f[0],m_size_f[1]);
         }
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

	for (t=0; t<m_src_num; t++)
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
		for (t=0; t<m_src_num; t++)
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
        Rect roi(0,360,m_dst_w,m_dst_h-700);
        Size dst_size=Size(m_dst_w,m_dst_h-700);
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
        Rect roi(0,360,m_dst_w,m_dst_h-700);
        Size dst_size=Size(m_dst_w,m_dst_h-700);
        GpuMat a(dst_size, CV_32FC3);
          a= m_d_result(roi);
//		m_d_result.convertTo(pano, CV_8UC3);
                a.convertTo(pano, CV_8UC3);
	}



	m_flag = 0;
}

