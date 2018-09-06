#include <iostream>
using namespace std;
//图像到世界坐标系坐标映射的类
class img2wrd
{
	
public:
	//!the map from perspective to world
	void perspective2world(float x_src, float y_src, float fov_src, int w_src, int h_src, float xyz_dst[3]);

	//!the map from errect to world
	void errect2world(float x_src, float y_src, int w_src, int h_src, float xyz_dst[3]);

	//!the map from fisheye to world
	void fisheye2world(float x_src, float y_src, int w_src, int h_src, float xyz_dst[3]);







};