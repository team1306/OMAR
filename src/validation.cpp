#include "align.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;

int main(int argc, char* argv[]) {
  Mat m = imread(argv[1]);

  pyrDown(m, m, Size(m.cols/2, m.rows/2));
  pyrDown(m, m, Size(m.cols/2, m.rows/2));
  align(m, m);
  crop(m, m);
  return 0;
}
