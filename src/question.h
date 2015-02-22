/**
 * @file question.h
 * @brief A Question object stores information such as the text associated to the
 * question, the location of the box on the page, and the set of Questions it 
 * belongs to.
 */

#ifndef __QUESTION_H__
#define __QUESTION_H__

#include <string>
#include <opencv/cv.h>

using namespace cv;

/**
 * @class Question
 * @brief A representation of a box on the page
 */

class Question {
 public:

  /**
   * Set the page position and the question text.
   *
   * @param a X coordinate of the upper right corner
   * @param b Y coordinate of the upper right corner
   * @param c X coordinate of the lower left corner
   * @param d Y coordinate of the lower left corner
   * @param quest Question text
   */

  Question(int, int, int, int, std::string);

  /**
   * Set the page position and the question text.
   *
   * @param n1 Point representing upper right corner
   * @param n2 Point representing lower left corner
   * @param quest Question text
   */

  Question(Point, Point, std::string);

  /**
   * Set the page position and the question text and scale the position based on 
   * a scaling factor.
   *
   * @param a X coordinate of the upper right corner
   * @param b Y coordinate of the upper right corner
   * @param c X coordinate of the lower left corner
   * @param d Y coordinate of the lower left corner
   * @param width Actual width of the page
   * @param height Actual height of the page
   * @param calRectX Width of the rectangle defined by the calibration circles
   * @param calRectY Height of the rectangle defined by the calibration circles
   * @param quest Question text
   */

  Question(int, int, int, int, int, int, int, int, std::string);

  /**
   * Set the page position and the question text and scale the position based on 
   * a scaling factor.
   *
   * @param n1 Point representing upper right corner
   * @param n2 Point representing lower left corner
   * @param pageSize Actual size of the page
   * @param calRect Size of the rectangle defined by the calibration circles
   * @param quest Question text
   */

  Question(Point, Point, Size, Size, std::string);

  /**
   * Scale the size and position of the box given the original size of the page 
   * and the size of the rectangle defined by the calibration circles, both in 
   * arbitrary units.
   *
   * @param width Width of the Page
   * @param height Height of the Page
   * @param calRectX Width of the rectangle defined by the calibration circles
   * @param calRectY Height of the rectangle defined by the calibration circles
   */

  void scale(int, int, int, int);

  /**
   * Scale the size and position of the box given the original size of the page 
   * and the size of the rectangle defined by the calibration circles, both in 
   * arbitrary units.
   *
   * @param a Size of the Page
   * @param b Size of the rectangle defined by the calibration circles
   */

  void scale(Size, Size);

  /**
   * Get the coordinate of the upper right corner of the question box.
   *
   * @return The upper right corner of the question box
   */

  Point getUR(void);

  /**
   * Get the coordinate of the lower left corner of the question box.
   *
   * @return The upper lower left of the question box
   */

  Point getLL(void);

  /**
   * Get the text associated with the question.
   *
   * @return The text associated with the question
   */

  std::string getName(void) {return q;}

  /**
   * Set whether the box is marked or not.
   *
   * @param Whether or not the box is black
   */

  void setAnswer(bool);

  /**
   * Get whether the box is marked or not.
   *
   * @return Whether or not the box is black
   */

  bool getAnswer(void) {return answer;}
 private:
  pt ur, ll;
  std::string q;
  bool answer;
};

#endif
