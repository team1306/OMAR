#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

void help()
{
  cout << "\nThis program demonstrates line finding with the Hough transform.\n"
         "Usage:\n"
    "./houghlines <image_name>, Default is pic1.jpg\n" << endl;
}

int main(int argc, char** argv)
{
  const char* filename = argc >= 2 ? argv[1] : "pic1.jpg";

  Mat src = imread(filename, 0);
  resize(src, src, Size(625, 813), 0, 0, INTER_LINEAR);
  if(src.empty())
    {
      help();
      cout << "can not open " << filename << endl;
      return -1;
    }

  Mat orig, dst;
  Canny(src, dst, 50, 200, 3);
  cvtColor(dst, orig, CV_GRAY2BGR);

  vector<Vec2f> lines;
  HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );int key = 0;
  
  int hi = 1, lo = 1;
  int res = 50;

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
	//GaussianBlur(snooker, snooker, Size(9, 9), 2, 2);

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

  /*for( size_t i = 0; i < lines.size(); i++ )
    {
      float rho = lines[i][0], theta = lines[i][1];
      Point pt1, pt2;
      double a = cos(theta), b = sin(theta);
      double x0 = a*rho, y0 = b*rho;
      pt1.x = cvRound(x0 + 1000*(-b));
      pt1.y = cvRound(y0 + 1000*(a));
      pt2.x = cvRound(x0 - 1000*(-b));
      pt2.y = cvRound(y0 - 1000*(a));
      line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
      }
  imshow("source", src);
  imshow("detected lines", cdst);

  waitKey();*/

}
