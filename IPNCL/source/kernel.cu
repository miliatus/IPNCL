#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <cmath>
#include "../header/IPNCLImage.h"
#include "../header/GaussianFilter.cuh"
#include "../header/IPNCL.h"
#include "../header/Negative.cuh"
#include "../header/GrayScale.cuh"
#include "../header/GammaCorrection.cuh"
#include "../header/Brightness.cuh"
#include "../header/Thresholding.cuh"
#include "../header/Contrast.cuh"
#include "../header/PassFilter.cuh"
#include "../header/MedianFilter.cuh"
#include <time.h>

typedef unsigned char uchar;

using namespace cv;

int main(int argc, char **argv) {

	time_t start, koniec;
	double roznica;


	IPNCLImage obj2("image.jpg");

	IPNCL::filter<GammaCorrection>(&obj2, new GammaCorrection(0.5));
		obj2.showImage(2000);

	obj2.saveImage("image_result.jpg");


	return 0;
}
