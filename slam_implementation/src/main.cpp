#include <opencv2/opencv.hpp>
#include <vector>

struct KeypointWD {
    int r;            // image row of keypoint location
    int c;            // image column of keypoint location
    float response;   // keypoint response
    cv::Mat descriptor;   // corresponding descriptor
};

int main() {
    // Read the image
    cv::Mat image = cv::imread("/home/suraj/Pictures/Screenshots/Screenshot from 2024-04-02 13-48-29.png", cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Error: Couldn't read the image." << std::endl;
        return -1;
    }

    // Detect SIFT keypoints and descriptors
    cv::Ptr<cv::Feature2D> sift = cv::SIFT::create();
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    sift->detectAndCompute(image, cv::noArray(), keypoints, descriptors);

    // Store keypoints and descriptors in the specified format
    std::vector<KeypointWD> keypoints_with_descriptors;
    for (size_t i = 0; i < keypoints.size(); ++i) {
        KeypointWD kp;
        kp.r = keypoints[i].pt.y;
        kp.c = keypoints[i].pt.x;
        kp.response = keypoints[i].response;
        kp.descriptor = descriptors.row(i);
        keypoints_with_descriptors.push_back(kp);

    }

        // Draw keypoints on the image
    cv::Mat image_with_keypoints;
    cv::drawKeypoints(image, keypoints, image_with_keypoints);


    // Display the image with keypoints
    cv::imshow("Image with SIFT Keypoints", image_with_keypoints);
    cv::waitKey(0);

    // Now you can use the keypoints_with_descriptors vector as needed
    // For example, you can serialize it to a file or process further

    return 0;
}
