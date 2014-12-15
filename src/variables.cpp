#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int hi = 1, lo = 1;
int res = 50;

int main(int argc, char* argv[]) {
  Mat orig = imread(argv[1]);
  resize(orig, orig, Size(625, 813), 0, 0, INTER_LINEAR);
  int key = 0;

  namedWindow("circles", 1);
  createTrackbar("hi", "circles", &hi, 255);
  createTrackbar("lo", "circles", &lo, 255);
  createTrackbar("res", "circles", &res, 255);

    do
      {
        // update display and snooker, so we can play with them
        Mat display;
	orig.copyTo(display);

        Mat snooker;
        cvtColor(orig, snooker, CV_RGB2GRAY);
	GaussianBlur(snooker, snooker, Size(9, 9), 2, 2);

        vector<Vec3f> circles;

        // also preventing crash with hi, lo threshold here...
        HoughCircles(snooker, circles, CV_HOUGH_GRADIENT, res/100+0.1, snooker.rows/10, hi > 0 ? hi : 1, lo > 0 ? lo : 1, 0, snooker.rows/60);
        for( size_t i = 0; i < circles.size(); i++ )
	  {
	    Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
	    int radius = cvRound(circles[i][2]);

	    // draw the green circle center
	    circle( display, center, 3, Scalar(0,255,0), -1, 8, 0 );

	    // draw the blue circle outline
	    circle( display, center, radius, Scalar(255,0,0), 3, 8, 0 );
	  }

	Mat tiny;
	resize(display, tiny, Size(417, 542), 0, 0, INTER_LINEAR);
        imshow("circles", tiny);
        imshow("snooker", snooker);
        key = waitKey(33);
      } while((char)key != 27);
    return 0;
}
