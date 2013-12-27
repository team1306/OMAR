#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "align.h"
#include <vector>
#include <cmath>

using namespace cv;

void getCalibrationCircles(const Mat& src, vector<Vec3f>& real) {
  Mat gray, source;
  source = src;
  std::vector<Vec3f> circles;

  cvtColor(source, gray, CV_BGR2GRAY);
  GaussianBlur(gray, gray, Size(9, 9), 2, 2);
 
  HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 0.5, 20, 15, 15, 3, 25);

  int dista, distb, distc, distd; // a is top left, b is top right, c is bottom left, d is bottom right
  int a, b, c, d;
  dista = distb = distc = distd = source.cols*source.cols + source.rows*source.rows;
  for(int i=0; i<circles.size(); i++) {
    if(circles[i][0]*circles[i][0] + circles[i][1]*circles[i][1] < dista) {
      dista = circles[i][0]*circles[i][0] + circles[i][1]*circles[i][1];
      a = i;
    }
    if((source.cols - circles[i][0])*(source.cols - circles[i][0]) + circles[i][1]*circles[i][1] < distb) {
      distb = (source.cols - circles[i][0])*(source.cols - circles[i][0]) + circles[i][1]*circles[i][1];
      b = i;
    }
    if(circles[i][0]*circles[i][0] + (source.rows - circles[i][1])*(source.rows - circles[i][1]) < distc) {
      distc = circles[i][0]*circles[i][0] + (source.rows - circles[i][1])*(source.rows - circles[i][1]);
      c = i;
    }
    if((source.cols - circles[i][0])*(source.cols - circles[i][0]) + (source.rows - circles[i][1])*(source.rows - circles[i][1]) < distd) {
      distd = (source.cols - circles[i][0])*(source.cols - circles[i][0]) + (source.rows - circles[i][1])*(source.rows - circles[i][1]);
      d = i;
    }
  }

  real.push_back(circles[a]);
  real.push_back(circles[b]);
  real.push_back(circles[c]);
  real.push_back(circles[d]);

  /*Mat display (gray);
  circle(display, Point(circles[a][0], circles[a][1]), circles[a][2], Scalar(0, 0, 255));
  circle(display, Point(circles[b][0], circles[b][1]), circles[b][2], Scalar(0, 0, 255));
  circle(display, Point(circles[c][0], circles[c][1]), circles[c][2], Scalar(0, 0, 255));
  circle(display, Point(circles[d][0], circles[d][1]), circles[d][2], Scalar(0, 0, 255));
  namedWindow("display", 1);
  imshow("display", display);
  waitKey(0);*/
}

double getAngleOffset(vector<Vec3f> circles) {
  double angle = atan((circles[2][1]-circles[3][1])/(circles[2][0]-circles[3][0]));
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
  Rect r (cvFloor(circles[0][0]), cvFloor(circles[0][1]), cvFloor(circles[1][0])-cvFloor(circles[0][0]), cvFloor(circles[2][1])-cvFloor(circles[0][1]));
  Mat d (source, r);
  d.copyTo(dest);
}
