/**
 * @file tournament.h
 * @brief A representation of a single tournament.
 */

#ifndef __TOURNAMENT_H__
#define __TOURNAMENT_H__

#include <vector>
#include <string>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "page.h"

/**
 * @class Tournament
 * @brief A representation of a single tournament.
 *
 * Each tournament loads images from files, stores them as Pages, and processes 
 * them to extract data. The class includes method to run preprocessing and 
 * processing code on every Page.
 */

class Tournament {
 public:

  /**
   * Initialize a Tournament with a list of filenames to read the images from.
   *
   * @param files Vector of filename strings relative to the directory of 
   * execution
   */

  Tournament(std::vector<std::string>&);

  /**
   * Initialize a Tournament with a directory in which to find the image files.
   *
   * @param dir The path to the directory containing the images
   */

  Tournament(std::string);

  /**
   * Read which files have already been processed from loaded.dat
   *
   * @return A vector of the files already processed
   * @todo Instead of reading the loaded files from a file, this should access a
   * Database instance
   */

  std::vector<std::string> readLoaded(void);

  /**
   * Load the files listed in a vector into memory, ignoring those returned by 
   * readLoaded(). However, if force specified, it loads every file it can find.
   *
   * @param files A vector of files to load into memory
   * @param force Whether or not to ignore which files have already been loaded
   * (defaults to false)
   */

  void loadScans(std::vector<std::string>, bool = 0);

  /**
   * Load the files in the specified directory into memory, ignoring those 
   * returned by readLoaded(). However, if force specified, it loads every file 
   * it can find.
   *
   * @param dir The directory containing the image files
   * @param force Whether or not to ignore which files have already been loaded
   * (defaults to false)
   */

  void loadScans(std::string, bool = 0);

  /**
   * Run the preprocessing method on every Page according to the data contained
   * in the specified .cal and .pos files.
   *
   * @param posFile Path to the .pos file
   * @param calFile Path to the .cal file
   */

  void prepare(const std::string, const std::string);

  /**
   * Run the processing method on every Page to extract the information from the
   * images. Must be run after prepare(const std::string, const std::string).
   */

  void process();

  /**
   * Report the extracted data to the specified file. Must be run after 
   * process().
   *
   * @param file Path to the report file
   */

  void report(std::string);

  /**
   * Push the files in the directory onto the output vector. This bit is voodoo
   * and should not be tampered with.
   *
   * @param dir Directory to search
   * @param files Output vector to contain the names of found files
   * @return Success
   */

  int getDir(std::string, std::vector<std::string>&);

  /**
   * Get the data extracted from Page members as a two dimensional vector of 
   * booleans.
   *
   * @return A two dimensional vector of booleans representing whether or not 
   * each box was checked
   */

  std::vector<std::vector<bool> > answers(void);

  /**
   * Get the points of the upper right corners of the question boxes associated
   * with this tournament.
   *
   * @return A point vector of the upper right corners of the question boxes
   */

  std::vector<Point> getUR(void) {return ur;}

  /**
   * Get the points of the lower left corners of the question boxes associated
   * with this tournament.
   *
   * @return A point vector of the lower left corners of the question boxes
   */

  std::vector<Point> getLL(void) {return ll;}

 private:
  Size calibrationRect;
  std::vector<std::string> questions;
  std::vector<Page> pages;
  std::vector<Mat> srcs;
  std::vector<std::string> names;
  std::vector<Point> ur, ll;
};

#endif
