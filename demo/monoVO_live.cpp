#include "system.hpp"

using namespace ssvo;

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);
    LOG_ASSERT(argc == 3) << "\n Usage : ./monoVO_live config_file videoID";

    const std::string video_stream_address = argv[2];

    cv::VideoCapture vc;

    if(!vc.open(video_stream_address))
    {
        std::cout << "error in open camera." << std::endl;
        return -1;
    }

    System vo(argv[1]);

    std::string image_name;
    double timestamp;
    for(;;)
    {
        cv::Mat image;
        if(!vc.read(image))
        {
            std::cout << "no image" << std::endl;
            continue;
        }

        vo.process(image, cv::getTickCount());
    }

    vo.saveTrajectoryTUM("trajectory.txt");
    cv::waitKey(0);

    return 0;
}