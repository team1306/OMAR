#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <vector>

using namespace cv;

int main() {
  Mat image = imread("./../oldscans/1-1.jpg");
  SimpleBlobDetector::Params params;
  params.minDistBetweenBlobs = 50.0f;
  params.filterByInertia = false;
  params.filterByConvexity = false;
  params.filterByColor = false;
  params.filterByCircularity = false;
  params.filterByArea = true;
  params.minArea = 20.0f;
  params.maxArea = 500.0f;
  // ... any other params you don't want default value

  // set up and create the detector using the parameters
  Ptr<FeatureDetector> blob_detector = new SimpleBlobDetector(params);
  blob_detector->create("SimpleBlob");

  // detect!
  std::vector<KeyPoint> keypoints;
  blob_detector->detect(image, keypoints);

  // extract the x y coordinates of the keypoints: 

  Mat display = image.clone();

  std::vector<int> X, Y;
  std::vector<float> R;
  for (int i=0; i<keypoints.size(); i++){
    circle(display, keypoints[i].pt, int(keypoints[i].size/2), Scalar(255, 0, 0), 3, 8, 0);
    X.push_back(keypoints[i].pt.x); 
    Y.push_back(keypoints[i].pt.y);
    R.push_back(keypoints[i].size/2);
  }
  imshow("circles", display);
}
