#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

struct KeypointWD
{
    int r;              // image row of keypoint location
    int c;              // image column of keypoint location
    float response;     // keypoint response
    cv::Mat descriptor; // corresponding descriptor
};

// path_left = /home/suraj/Kiti_dataset/archive/data_object_image_2/testing/image_2/
// path_right = /home/suraj/Kitti_dataset/archive/data_object_image_3/testing/image_3/
class ImageLoader
{
public:
    ImageLoader(const std::string &left_path, const std::string &right_path) : left_path_(left_path), right_path_(right_path), counter_(0) {}
    ~ImageLoader() {}
    std::pair<cv::Mat, cv::Mat> getNextImagePair()
    {
        for (const auto &entry : std::filesystem::directory_iterator(left_path_))
            if (std::filesystem::is_regular_file(entry.path()))
                left_paths_.push_back(entry.path());

        for (const auto &entry : std::filesystem::directory_iterator(right_path_))
            if (std::filesystem::is_regular_file(entry.path()))
                right_paths_.push_back(entry.path());

        std::sort(left_paths_.begin(), left_paths_.end());
        std::sort(right_paths_.begin(), right_paths_.end());

        left_right_image_.first = cv::imread(left_paths_[counter_], cv::IMREAD_GRAYSCALE);
        left_right_image_.second = cv::imread(right_paths_[counter_], cv::IMREAD_GRAYSCALE);

        counter_++;
        return left_right_image_;
    }

private:
    std::string left_path_;
    std::string right_path_;
    std::vector<std::string> left_paths_;
    std::vector<std::string> right_paths_;
    int counter_;
    std::pair<cv::Mat, cv::Mat> left_right_image_;
    ImageLoader() {}
};

// class FeatureDetector
// {
// public:
//     FeatureDetector()
//     {
//     }

// private:
// };

// class ImageLoader
// {
// };

int main()
{
    std::string left_directory_path = "/home/suraj/Kitti_dataset/archive/data_object_image_2/testing/image_2/";
    std::string right_directory_path = "/home/suraj/Kitti_dataset/archive/data_object_image_3/testing/image_3/";
    ImageLoader image_loader(left_directory_path, right_directory_path);
    for(int i = 0; i<10; i++) {
    std::pair<cv::Mat, cv::Mat> left_right_image = image_loader.getNextImagePair();

    // Display the left image
    cv::imshow("left image", left_right_image.first);
    cv::waitKey(0);

    // Display the right image
    cv::imshow("right image", left_right_image.second);
    cv::waitKey(0);
    }
    // // Detect SIFT keypoints and descriptors
    // cv::Ptr<cv::Feature2D> sift = cv::SIFT::create();
    // std::vector<cv::KeyPoint> keypoints;
    // cv::Mat descriptors;
    // sift->detectAndCompute(image, cv::noArray(), keypoints, descriptors);

    // // Store keypoints and descriptors in the specified format
    // std::vector<KeypointWD> keypoints_with_descriptors;
    // for (size_t i = 0; i < keypoints.size(); ++i)
    // {
    //     KeypointWD kp;
    //     kp.r = keypoints[i].pt.y;
    //     kp.c = keypoints[i].pt.x;
    //     kp.response = keypoints[i].response;
    //     kp.descriptor = descriptors.row(i);
    //     keypoints_with_descriptors.push_back(kp);
    // }

    // // Draw keypoints on the image
    // cv::Mat image_with_keypoints;
    // cv::drawKeypoints(image, keypoints, image_with_keypoints);

    // // Display the image with keypoints
    // cv::imshow("Image with SIFT Keypoints", image_with_keypoints);
    // cv::waitKey(0);

    // Now you can use the keypoints_with_descriptors vector as needed
    // For example, you can serialize it to a file or process further

    return 0;
}
