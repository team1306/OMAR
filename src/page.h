/**
 * @file page.h
 * @brief An encapsulation of an image and its respective Question objects.
 */

#ifndef __PAGE_H__
#define __PAGE_H__

#include <string>
#include <vector>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "question.h"

using namespace cv;

/**
 * @class Page
 * @brief An encapsulation of an image and its metadata
 *
 * Each Page stores its image and information about its questions. It contains 
 * methods to read and return the answers.
 */

class Page {
 public:

  /**
   * Store the image and the metadata in member variables.
   *
   * @param qs A Question vector
   * @param src The source image
   * @param a The size of the calibration rectangle
   * @param b The size of the page
   * @param fn The name of the source file of the image
   */

  Page(std::vector<Question>, const Mat&, Size, Size, std::string);

  /**
   * Process the image by reading the mean value of each Question box and 
   * applying a threshold.
   */

  void read(void);

  /**
   * Get the data extracted from the image after a call to read().
   *
   * @return A vector of booleans representing the color of each Question box
   */

  std::vector<bool> answers(void);

  /**
   * Get the number of questions.
   *
   * @return The number of questions associated with the Page
   */

  int numq(void) {return questions.size();}

  /**
   * Get the name of the source file of the image.
   *
   * @return The name of the source file
   */

  std::string filename(void);

  /**
   * Get the size of the calibration rectangle.
   *
   * @return The size of the calibration rectangle
   */

  Size getCalibrationSize();

  /**
   * Get the size of the Page.
   *
   * @return The size of the Page
   */

  Size getPageSize();

  /**
   * Find the calibration circles and rotate the image to center the calibration
   * rectangle.
   */

  void align();

  /**
   * Find the calibration circles and crop the image to the calibration rectangle.
   */

  void crop();

 private:
  /**
   * Read an image and write the four strongest circles closest to the corners 
   * to the output vector of points.
   *
   * @param real Output vector containing the coordinates of the calibration 
   * circles
   */

  void getCalibrationCircles(std::vector<Vec3f>&);

  /**
   * Find the angle in radians of the line connecting the first two points in a 
   * vector with respect to the horizon.
   *
   * @param circles Vector of four points, only first two of which will be used
   * @return The angle between the points in radians
   */

  double getAngleOffsetTop(std::vector<Vec3f>);

  /**
   * Find the angle in radians of the line connecting the last two points in a 
   * vector with respect to the horizon.
   *
   * @param circles Vector of four points, only last two of which will be used
   * @return The angle between the points in radians
   */

  double getAngleOffsetBottom(std::vector<Vec3f>);

  /**
   * Defaults to getAngleOffsetTop().
   *
   * @param circles Vector of four points, only first two of which will be used
   * @return The angle between the points in radians
   */

  double getAngleOffset(std::vector<Vec3f>);

  /**
   * Rotate the source matrix by an angle and write it to the destination matrix.
   *
   * @param angle Angle to rotate
   */

  void rotateImage(double);

  std::string fname;
  std::vector<Question> questions;
  Size calibrationRect;
  Size page;
  Mat image;
};

#endif
