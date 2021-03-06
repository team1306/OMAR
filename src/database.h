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
#include "SQLiteCpp/SQLiteCpp.h"

#define PAGE_NOT_FOUND 20

/*
 * questions table
 * urx | ury | llx | lly | question text
 */

/*
 * pages table
 * filename | calrectx | calrecty | pagesizex | pagesizey
 */

/*
 * data table
 * qid | pid | data
 */

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
   * one table and pages are stored in another. The other filename refers to the
   * .pos file so that the constructor can validate the Questions table.
   *
   * @param dbfilename Absolute path to the sqlite database file
   * @param posfile Absolute path to the .pos file
   */
  
  Database(std::string, std::string);

  /**
   * Update the Questions table with the questions contained in the vector 
   * specified.
   *
   * @param fileQuestions Vector of questions to write to table
   */

  void updateQuestions(std::vector<Question>);

  /**
   * Update a file in the database based on the data stored in a Page. If the
   * file already exists, update its row, but if the file isn't in the database
   * yet, create a new row.
   *
   * @param update Page containing data to be written to the database
   */

  void updatePage(Page);

  /**
   * Retrieve a page by its filename.
   *
   * @param filename The name of the file to be retrieved
   * @return A page from the database
   */

  Page getPage(std::string);

  /**
   * Retrieve a page by its id.
   *
   * @param pageid The id of the page to be retrieved.
   * @return A page from the database
   */

  Page getPage(int);

  /**
   * Retrieve all pages. This is very slow and should be avoided. Use getPage 
   * instead.
   *
   * @return All pages in the database.
   */

  std::vector<Page> getPages();

  /**
   * Return all of the questions stored in the database.
   *
   * @return A vector of Questions
   */

  std::vector<Question> getQuestions();

 private:
  
  std::vector<Question> getData(int);

  /// SQLite database object
  SQLite::Database database;

};

#endif
