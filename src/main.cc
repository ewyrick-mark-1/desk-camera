#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
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
	
	auto now = std::chrono::system_clock::now().time_since_epoch().count(); //unique file names
	std::string path_name= "../img/" + std::to_string(now) + ".png";
	cv::imwrite(path_name, frame);
	std::cout << "open cv version: " << CV_VERSION <<std::endl;	
		
	return 0;

}
