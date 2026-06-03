#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <sys/stat.h>
#include <thread>

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
	
	auto now = std::chrono::system_clock::now();
	auto ts = std::chrono::duration_cast<std::chrono::seconds>(	
		now.time_since_epoch()
	).count();
	std::time_t time_t_now = (std::time_t)ts;
	char date_buf[11];
	std::strftime(date_buf, sizeof(date_buf), "%Y-%m-%d", std::localtime(&time_t_now));//grab date as a string for the folder 
	std::string folder = "../img/" + std::string(date_buf);
	mkdir(folder.c_str(), 0777); // everyone can read and write

	if(mode == "--pic") {
		cv::Mat frame;
		cap >> frame;
		if (frame.empty()) return -1;

		std::string path_name = folder + "/" + std::to_string(ts) + ".png";
		cv::imwrite(path_name, frame);
		std::cout << "saved image at" << path_name << std::endl;

	} else if (mode == "--video") {
		int default_fps= 30;
		int duration = 10; //default
		int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
		int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
		double actual_fps = cap.get(cv::CAP_PROP_FPS);
		int fps = (actual_fps > 0) ? (int)actual_fps : default_fps;

		std::cout << "camera fps: " << actual_fps <<std::endl;

		if (argc > 2){
			duration = std::stoi(argv[2]);
		}
		
		
		std::string path_name = folder + "/" + std::to_string(ts) + ".mp4";

		// video writer
		
		cv::VideoWriter writer(
			path_name,
			cv::VideoWriter::fourcc('H', '2', '6', '4'),
			fps,
			cv::Size(width, height)		
		);

		if (!writer.isOpened()){
			std::cerr << "failed to open video writer" <<std::endl;
			return -1;
		}

		std::cout << "recording. ctrl c to stop." <<std::endl;
		auto start = std::chrono::steady_clock::now();
		auto next_frame = start;
		int frame_count = 0;
		int total_frames = fps * duration;

		std::cout << "fps: " << fps << "\nduration: " << duration << "total_frames: " << total_frames << "actual_fps: " << actual_fps << "\n";
		
		cv::Mat frame;
		while (frame_count < total_frames){
			cap >> frame;
			if (frame.empty()) break;
			writer.write(frame); //add actual frame to the video
			frame_count++;
			
			//wait based on fps
			next_frame += std::chrono::milliseconds((1000 / fps)/2);
			//this is relative to the start time
			//locks spacing to even intervals, 
			//besides the first 1 or 2. I am not sure why I need to
			//divide by 2 - it was taking twice as long to record as it
			//should have for some reason. maybe camera processing time.
			std::this_thread::sleep_until(next_frame);
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
