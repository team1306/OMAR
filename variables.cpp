#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>

using namespace cv;

int hi = 1, lo = 1;

int getDir(std::string dir, std::vector<std::string> &files) {
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
    std::cout << "Error opening " << dir << std::endl;
    return 1;
  }
  
  while ((dirp = readdir(dp)) != NULL) {
    if(string(dirp->d_name) != "." && string(dirp->d_name) != "..") {
      files.push_back(dir + "/" + string(dirp->d_name));
    }
  }
  closedir(dp);
  return 0;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> files;
  getDir(argv[1], files);
  std::cout << "listed files" << std::endl;
  std::string f;    
  namedWindow("circles", 1);
  createTrackbar("hi", "circles", &hi, 255);
  createTrackbar("lo", "circles", &lo, 255);

  do {
    f = files.back();
    files.pop_back();
    Mat orig = imread(f);
    int key = 0;


    pyrDown(orig, orig, Size(orig.cols/2, orig.rows/2));

    std::cout << "loaded file" << std::endl;

    do
    {
        // update display and snooker, so we can play with them
      Mat display = orig.clone();

        Mat snooker;
        cvtColor(orig, snooker, CV_RGB2GRAY);
	GaussianBlur(snooker, snooker, Size(9, 9), 2, 2);

        vector<Vec3f> circles;

        // also preventing crash with hi, lo threshold here...
        HoughCircles(snooker, circles, CV_HOUGH_GRADIENT, 0.5, 20.0, hi > 0 ? hi : 1, lo > 0 ? lo : 1, 3, 25);
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
    } while((char)key != 97);
  } while(1);
  return 0;
}

