#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include "page.h"
#include "question.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;

Page::Page(std::vector<Question> qs, const Mat& src, Size a, Size b, std::string fn) {
  calibrationRect = a;
  page = b;
  src.copyTo(image);
  questions = qs;
  fname = fn;
}
  
void Page::read(void) { // read all boxes and set questions' values
  Scalar total;
  Mat t;
  Mat display;
  image.copyTo(display);

  for(int i=0; i<questions.size(); i++) {
    questions[i].scale(calibrationRect, page);
    Point topLeftCorner (questions[i].getLL().x, page.height - questions[i].getUR().y);
    Point bottomRightCorner (questions[i].getUR().x, page.height - questions[i].getLL().y);
    t = image(Rect(topLeftCorner, bottomRightCorner)); // assign a Mat to where a box should be
    total = mean(t); // finds average magnitude for the box
    if(pow(total[0], 2) + pow(total[1], 2) + pow(total[2], 2) < 67500) { // checks to see if box is black (filled in) and sets question's answer accordingly
      questions[i].setAnswer(true);
    }
    else {
      questions[i].setAnswer(false);
    }
    rectangle(display, Rect(topLeftCorner, bottomRightCorner), Scalar(0,0,255));
  }
  namedWindow("display", 1);
  imshow("display", display);
  waitKey(0);
}

std::vector<bool> Page::answers(void) { // return all answers to questions
  std::vector<bool> a;
  for(int i=0; i<questions.size(); i++) {
    a.push_back(questions[i].getAnswer());
  }
  return a;
}

std::string Page::filename(void) {
  return fname;
}

Size Page::getCalibrationSize() {
  Size ret (calibrationRect);
  return ret;
}

Size Page::getPageSize() {
  Size ret (page);
  return ret;
}

std::vector<Question>& Page::getQuestions() {
  return questions;
}

void Page::align() {
  std::vector<Vec3f> circles;
  getCalibrationCircles(circles);
  rotateImage(getAngleOffset(circles));
}

void Page::crop() {
  std::vector<Vec3f> circles;
  getCalibrationCircles(circles);
  if(std::floor(getAngleOffsetTop(circles)) != std::floor(getAngleOffsetBottom(circles))) {
    std::cout << "Skewed" << std::endl;
  }
  Rect r (cvFloor(circles[0][0]), cvFloor(circles[0][1]), cvFloor(circles[1][0])-cvFloor(circles[0][0]), cvFloor(circles[2][1])-cvFloor(circles[0][1]));
  Mat d (image, r);
  d.copyTo(image);
}

void Page::getCalibrationCircles(vector<Vec3f>& real) {
  Mat source, gray;
  image.copyTo(source);
  std::vector<Vec3f> circles;

  cvtColor(source, gray, CV_BGR2GRAY);
  GaussianBlur(gray, gray, Size(9, 9), 2, 2);
  threshold(gray, gray, 127, 255, THRESH_BINARY);

  HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 0.6, gray.rows/10, 1, 1, 0, gray.rows/60);

  /*
    src_gray: Input image (grayscale)
    circles: A vector that stores sets of 3 values: x_{c}, y_{c}, r for each detected circle.
    CV_HOUGH_GRADIENT: Define the detection method. Currently this is the only one available in OpenCV
    dp = 1: The inverse ratio of resolution
    min_dist = src_gray.rows/8: Minimum distance between detected centers
    param_1 = 200: Upper threshold for the internal Canny edge detector
    param_2 = 100: Threshold for center detection.
    min_radius = 0: Minimum radio to be detected. If unknown, put zero as default.
    max_radius = 0: Maximum radius to be detected. If unknown, put zero as default
  */

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

#ifdef DISPLAY
  Mat display;
  source.copyTo(display);
  circle(display, Point(circles[a][0], circles[a][1]), circles[a][2], Scalar(0, 0, 255), -1, 8, 0);
  circle(display, Point(circles[b][0], circles[b][1]), circles[b][2], Scalar(0, 0, 255), -1, 8, 0);
  circle(display, Point(circles[c][0], circles[c][1]), circles[c][2], Scalar(0, 0, 255), -1, 8, 0);
  circle(display, Point(circles[d][0], circles[d][1]), circles[d][2], Scalar(0, 0, 255), -1, 8, 0);
  pyrDown(display, display, Size(display.cols/2, display.rows/2));
  namedWindow("align", 1);
  imshow("align", display);
  waitKey(0);
#endif

}

double Page::getAngleOffsetTop(vector<Vec3f> circles) {
  double angle = atan((circles[0][1]-circles[1][1])/(circles[0][0]-circles[1][0]));
  return angle*180/M_PI;
}

double Page::getAngleOffsetBottom(vector<Vec3f> circles) {
  double angle = atan((circles[2][1] - circles[3][1])/(circles[2][0] - circles[3][0]));
  return angle*180/M_PI;
}

double Page::getAngleOffset(vector<Vec3f> circles) {
  return getAngleOffsetTop(circles);
}

void Page::rotateImage(double angle) {
  Point2f src_center(image.cols/2.0F, image.rows/2.0F);
  Mat rot_mat = getRotationMatrix2D(src_center, angle, 1.0);
  warpAffine(image, image, rot_mat, image.size());
}
