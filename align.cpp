#include "cv.h"
#include "highgui.h"
#include "align.h"
#include <vector>
#include <cmath>

using namespace cv;

void getCalibrationCircles(const Mat& src, vector<Vec3f>& real) {
  Mat gray, source;
  source = src;
  std::vector<Vec3f> circles;

  cvtColor(source, gray, CV_BGR2GRAY);
  //GaussianBlur(gray, gray, Size(9, 9), 2, 2);

  HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 2, 32, 1, 1, 5, 20);

  int dista, distb, distc, distd; // a is top left, b is top right, c is bottom left, d is bottom right
  int a, b, c, d;
  dista = distb = distc = distd = std::pow(source.cols, 2) + std::pow(source.rows, 2);
  for(int i=0; i<circles.size(); i++) {
    if(std::pow(circles[i][0], 2) + std::pow(circles[i][1], 2) < dista) {
      dista = std::pow(circles[i][0], 2) + std::pow(circles[i][1], 2);
      a = i;
    }
    if(std::pow(source.cols - circles[i][0], 2) + std::pow(circles[i][1], 2) < distb) {
      distb = std::pow(source.cols - circles[i][0], 2) + std::pow(circles[i][1], 2);
      b = i;
    }
    if(std::pow(circles[i][0], 2) + std::pow(source.rows - circles[i][1], 2) < distc) {
      distc = std::pow(circles[i][0], 2) + std::pow(source.rows - circles[i][1], 2);
      c = i;
    }
    if(std::pow(source.cols - circles[i][0], 2) + std::pow(source.rows - circles[i][1], 2) < distd) {
      distd = std::pow(source.cols - circles[i][0], 2) + std::pow(source.rows - circles[i][1], 2);
      d = i;
    }
  }

  real.push_back(circles[a]);
  real.push_back(circles[b]);
  real.push_back(circles[c]);
  real.push_back(circles[d]);
}

double getAngleOffset(vector<Vec3f> circles) {
  double angle = atan((circles[0][1]-circles[1][1])/(circles[0][0]-circles[1][0]));
  return angle*180/PI;
}

void rotateImage(const Mat& source, Mat& dst, double angle) {
  Point2f src_center(source.cols/2.0F, source.rows/2.0F);
  Mat rot_mat = getRotationMatrix2D(src_center, angle, 1.0);
  warpAffine(source, dst, rot_mat, source.size());
}

void align(const Mat& source, Mat& dst) {
  std::vector<Vec3f> circles;
  getCalibrationCircles(source, circles);
  rotateImage(source, dst, getAngleOffset(circles));
}

void crop(const Mat& source, Mat& dest) {
  std::vector<Vec3f> circles;
  getCalibrationCircles(source, circles);
  Rect r (cvFloor(circles[0][0]), cvFloor(circles[0][1]), cvFloor(circles[3][0])-cvFloor(circles[0][0]), cvFloor(circles[3][1])-cvFloor(circles[0][1]));
  Mat d (source, r);
  d.copyTo(dest);
}
