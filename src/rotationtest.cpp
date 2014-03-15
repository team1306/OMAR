#include "cv.h"
#include "highgui.h"

using namespace cv;

int main() {
  Mat src;
  src = imread("billards.png");
  
  Point2f src_center(src.cols/2.0F, src.rows/2.0F);
  Mat rot_mat = getRotationMatrix2D(src_center, 15, 1.0);
  Mat dist;
  warpAffine(src, dist, rot_mat, src.size());
  
  namedWindow("circles", 1);
  imshow("circles", dist);

  waitKey(0);
  return 0;
}
