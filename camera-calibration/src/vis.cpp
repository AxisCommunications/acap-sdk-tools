#include "vis.hpp"

void displayDetection(const cv::Mat& image,
                      const std::vector<AprilTags::TagDetection>& detections) {
  cv::Mat vis_img;
  image.copyTo(vis_img);

  cv::cvtColor(vis_img, vis_img, cv::COLOR_GRAY2BGR);
  for (size_t i = 0; i < detections.size(); ++i) {
    const auto& det = detections[i];

    for (int j = 0; j < 4; ++j)
      cv::circle(vis_img, cv::Point(det.p[j].first, det.p[j].second), 3,
                 cv::Scalar(0, 0, 255), 2);
  }
  cv::imshow("apriltags", vis_img);
  cv::waitKey(0);
}
