/**
 * @file align.h
 * @brief This file contains tools for finding the calibration circles and 
 * cropping and rotating the image to line up with those circles. The backbone 
 * is the Hough circle transform in getCalibrationCircles, and the rest of the 
 * methods are meant to utilize those circles.
 */

#ifndef __ALIGN_H__
#define __ALIGN_H__

#include "cv.h"
#include "highgui.h"
#include <vector>

#define PI 3.141592653589793238462

using namespace cv;

/**
 * Read an image and write the four strongest circles closest to the corners 
 * to the output vector of points.
 *
 * @param src Source image to read
 * @param real Output vector containing the coordinates of the calibration 
 * circles
 */

void getCalibrationCircles(const Mat&, std::vector<Vec3f>&);

/**
 * Find the angle in radians of the line connecting the first two points in a 
 * vector with respect to the horizon.
 *
 * @param circles Vector of four points, only first two of which will be used
 * @return The angle between the points in radians
 */

double getAngleOffsetTop(std::vector<Vec3f>);
double getAngleOffsetBottom(std::vector<Vec3f>);
double getAngleOffset(std::vector<Vec3f>);
void rotateImage(const Mat&, Mat&, double);
void align(const Mat&, Mat&);
void crop(const Mat&, Mat&);

#endif
