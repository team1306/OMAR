#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;

int hi = 1, lo = 1;

int main(int argc, char* argv[]) {
    Mat orig = imread("scans/form1.jpg");
    int key = 0;

    namedWindow("circles", 1);
    createTrackbar("hi", "circles", &hi, 255);
    createTrackbar("lo", "circles", &lo, 255);

    pyrDown(orig, orig, Size(orig.cols/2, orig.rows/2));

    std::cout << "loaded file" << std::endl;

    do
    {
        // update display and snooker, so we can play with them
        Mat display = orig.clone();

        Mat snooker;
        cvtColor(orig, snooker, CV_RGB2GRAY);

        vector<Vec3f> circles;

        // also preventing crash with hi, lo threshold here...
        HoughCircles(snooker, circles, CV_HOUGH_GRADIENT, 2, 32.0, hi > 0 ? hi : 1, lo > 0 ? lo : 1 , 5, 20);
        for( size_t i = 0; i < circles.size(); i++ )
        {
             Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
             int radius = cvRound(circles[i][2]);

             // draw the green circle center
             circle( display, center, 3, Scalar(0,255,0), -1, 8, 0 );

             // draw the blue circle outline
             circle( display, center, radius, Scalar(255,0,0), 3, 8, 0 );
        }

        imshow( "circles", display );
        imshow("snooker", snooker);
        key = waitKey(33);
    } while((char)key != 27);
    return 0;
}
