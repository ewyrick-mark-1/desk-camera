#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
int main(int argc, char* argv[]) {
	std::cout << "Hello world" << std::endl;
	
	//parse the arguments /flags
	
	std::string mode = "--pic"; //the default mode is picture
	
	if (argc > 1){
		mode = argv[1];
	}

	cv::VideoCapture cap(0);
	if(!cap.isOpened()){
		std::cerr << "failed" << std::endl;
		return -1;
	}
	
	auto now = std::chrono::system_clock::now().time_since_epoch().count(); //unique file names
										//
										//
	if(mode == "--pic") {
		cv::Mat frame;
		cap >> frame;
		if (frame.empty()) return -1;

		std::string path_name = "../img/" + std::to_string(now) + ".png";
		cv::imwrite(path_name, frame);
		std::cout << "saved image at" << path_name << std::endl;

	} else if (mode == "--video") {
		int fps = 30;
		int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
		int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

		std::string path_name = "../img/" + std::to_string(now) + ".avi";

		// video writer
		
		cv::VideoWriter writer(
			path_name,
			cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
			fps,
			cv::Size(width, height)		
		);

		if (!writer.isOpened()){
			std::cerr << "failed to open video writer" <<std::endl;
			return -1;
		}

		std::cout << "recording. ctrl c to stop." <<std::endl;
		cv::Mat frame;
		while (true){
			cap >> frame;
			if (frame.empty()) break;
			writer.write(frame); //add actual frame to the video
		}
		writer.release();
		std::cout << "Saved video: " << path_name << std::endl;
	} else {
		std::cerr << "unknown flag. check yoself before you wreck yoself" << std::endl;
		return -1;
	}
	
	cap.release();
	std::cout << "OpenCV version" << CV_VERSION << std::endl;
	return 0;

}
