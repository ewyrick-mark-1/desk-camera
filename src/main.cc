#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
	std::cout << "Hello world" << std::endl;
	
	cv::VideoCapture cap(0);
	if(!cap.isOpened()){
		std::cerr << "failed" << std::endl;
		return -1;
	}

	cv::Mat frame;

	cap >> frame;

	if(frame.empty()) return -1;
	
	cv::imwrite("/mnt/myshare/img/image.png", frame)g
	std::cout << "open cv version: " << CV_VERSION <<std::endl;	
		
	return 0;

}
