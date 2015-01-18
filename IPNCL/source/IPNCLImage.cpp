/*
 * IPNCLImage.cpp
 *
 *      Author: kebolt
 */

#include "../header/IPNCLImage.h"

IPNCLImage::IPNCLImage(std::string imageSource) {
	image = imread(imageSource);

	imageSize = sizeof(uchar)*image.rows*image.cols;

	bChannel = new uchar [imageSize];
	gChannel = new uchar [imageSize];
	rChannel = new uchar [imageSize];

	d_bChannel = NULL;
	d_gChannel = NULL;
	d_rChannel = NULL;

	d_bResultChannel = NULL;
	d_gResultChannel = NULL;
	d_rResultChannel = NULL;

	for(int i = 0;i < image.cols ;i++) {
		for(int j = 0;j < image.rows ;j++) {
			Vec3b intensity = image.at<Vec3b>(j,i);

			bChannel[j*image.cols+i] = intensity.val[0];
			gChannel[j*image.cols+i] = intensity.val[1];
			rChannel[j*image.cols+i] = intensity.val[2];
	    }
	}
}

IPNCLImage::~IPNCLImage() {
	if(!bChannel) {
		delete bChannel;
	}
	if(!gChannel) {
		delete bChannel;
	}
	if(!rChannel) {
		delete bChannel;
	}
	if(!d_bChannel) {
		cudaFree(d_bChannel);
	}
	if(!d_gChannel) {
		cudaFree(d_gChannel);
	}
	if(!d_rChannel) {
		cudaFree(d_rChannel);
	}
	if(!d_bResultChannel) {
		cudaFree(d_bResultChannel);
	}
	if(!d_gResultChannel) {
		cudaFree(d_gResultChannel);
	}
	if(!d_rResultChannel) {
		cudaFree(d_rResultChannel);
	}
}

void IPNCLImage::initDeviceMemoryForImage() {
	if(d_bChannel == NULL) {
		cudaMalloc((void**)&d_bChannel, imageSize);
	}
	if(d_gChannel == NULL) {
		cudaMalloc((void**)&d_gChannel, imageSize);
	}
	if(d_rChannel == NULL) {
		cudaMalloc((void**)&d_rChannel, imageSize);
	}
	if(d_bResultChannel == NULL) {
		cudaMalloc((void**)&d_bResultChannel, imageSize);
	}
	if(d_gResultChannel == NULL) {
		cudaMalloc((void**)&d_gResultChannel, imageSize);
	}
	if(d_rResultChannel == NULL) {
		cudaMalloc((void**)&d_rResultChannel, imageSize);
	}
}

void IPNCLImage::freeDeviceMemory() {
	if(!d_bChannel) {
		cudaFree(d_bChannel);
	}
	if(!d_gChannel) {
		cudaFree(d_gChannel);
	}
	if(!d_rChannel) {
		cudaFree(d_rChannel);
	}
	if(!d_bResultChannel) {
		cudaFree(d_bResultChannel);
	}
	if(!d_gResultChannel) {
		cudaFree(d_gResultChannel);
	}
	if(!d_rResultChannel) {
		cudaFree(d_rResultChannel);
	}
}

uchar* IPNCLImage::getRHostChannel() {
	return rChannel;
}
uchar* IPNCLImage::getGHostChannel() {
	return gChannel;
}
uchar* IPNCLImage::getBHostChannel() {
	return bChannel;
}
uchar* IPNCLImage::getRDeviceChannel() {
	return d_rChannel;
}
uchar* IPNCLImage::getGDeviceChannel() {
	return d_gChannel;
}
uchar* IPNCLImage::getBDeviceChannel() {
	return d_bChannel;
}
uchar* IPNCLImage::getRResultDeviceChannel() {
	return d_rResultChannel;
}
uchar* IPNCLImage::getGResultDeviceChannel() {
	return d_gResultChannel;
}
uchar* IPNCLImage::getBResultDeviceChannel() {
	return d_bResultChannel;
}

void IPNCLImage::copyImageToDeviceMemory() {
	cudaMemcpy(d_bChannel, bChannel, imageSize, cudaMemcpyHostToDevice);
	cudaMemcpy(d_gChannel, gChannel, imageSize, cudaMemcpyHostToDevice);
	cudaMemcpy(d_rChannel, rChannel, imageSize, cudaMemcpyHostToDevice);
}

void IPNCLImage::copyImageFromResultToHostMemory() {
	cudaMemcpy(bChannel, d_bResultChannel, imageSize, cudaMemcpyDeviceToHost);
	cudaMemcpy(gChannel, d_gResultChannel, imageSize, cudaMemcpyDeviceToHost);
	cudaMemcpy(rChannel, d_rResultChannel, imageSize, cudaMemcpyDeviceToHost);

	//Create also new version of image
	for(int i = 0;i < getCols() ;i++) {
		for(int j = 0;j < getRows();j++) {
			image.at<Vec3b>(j, i) = Vec3b(getBHostChannel()[j*getCols()+i], getGHostChannel()[j*getCols()+i], getRHostChannel()[j*getCols()+i]);
	    }
	}
}

int IPNCLImage::getRows() {
	return image.rows;
}
int IPNCLImage::getCols() {
	return image.cols;
}

void IPNCLImage::saveImage(std::string imageName) {
	imwrite(imageName, image);
}
void IPNCLImage::showImage(int delay) {
	imshow("IPNCLImage", image);
	waitKey(delay);
}

