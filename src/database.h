/**
 * @file database.h
 * @brief A wrapper class which provides abstract access to the database in term
 * of Page objects.
 */

#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <vector>
#include "page.h"
#include <SQLiteCpp/SQLiteCpp.h>

#define PAGE_NOT_FOUND 20

/**
 * @class Database
 * @brief A simple database wrapper.
 *
 * Each row of the SQLite database represents one file or image of a scanned 
 * sheet. The getter and setter methods are designed to accept or return Page 
 * instances to abstract away things like filenames and ids.
 */

class Database {
 public:

  /**
   * Initialize database from the filename specified. Questions are stored in
   * one table and pages are stored in another.
   *
   * @param pagesfile Absolute path to the sqlite database file
   */
  
  Database(std::string);

  /**
   * Retrieve all questions stored in the question table.
   *
   * @return A Question vector
   */

  std::vector<Question> getQuestions();

  /**
   * Get a vector of pages representing the files stored in the database.
   *
   * @return Vector of pages in the database
   */

  std::vector<Page> getPages();

  /**
   * Retrieve a page by its filename with Question vector specified.
   *
   * @param filename The name of the file to be retrieved
   * @param questions A Question vector associated with the page
   * @return A page from the database
   */

  Page getPage(std::string, std::vector<Question>);

  /**
   * Update a file in the database based on the data stored in a Page. If the
   * file already exists, update its row, but if the file isn't in the database
   * yet, create a new row.
   *
   * @param update Page containing data to be written to the database
   */

  void updatePage(Page);

 private:

  /// SQLite database object
  SQLite::Database database;

};

#endif