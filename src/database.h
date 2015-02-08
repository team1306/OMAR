#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <vector>
#include "page.h"

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
   * Initialize database from the filename specified.
   *
   * @param filename Absolute path to the sqlite database file
   */
  
  Database(std::string);

  /**
   * Get a vector of pages representing the files stored in the database.
   *
   * @return Vector of pages in the database
   */

  std::vector<Page> getPages();

  /**
   * Retrieve a page by its filename.
   *
   * @param filename The name of the file to be retrieved
   * @return A page from the database
   */

  Page getPage(std::string);

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
  sqlite3 *database;

};

#endif
