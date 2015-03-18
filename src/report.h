/**
 * @file report.h
 * @brief Parses binary data from Pages and writes the resulting data to a report
 * file.
 */

#ifndef __REPORT_H__
#define __REPERT_H__

#include <string>
#include "database.h"

/**
 * @class Report
 * @brief Parses binary data from Pages and writes the resulting data to a report
 * file.
 *
 * From a Database, each Report retrieves the data and stores it in Fields. Then 
 * each Field reformats the binary info as the actual type of data. Finally, the 
 * Report can write the resulting values to a file in either CSV or JSON.
 */

class Report {
 public:

  /**
   * Construct a Report with a reference to the appropriate Database containing 
   * the data.
   *
   * @param db A reference to a Database
   */

  Report(Database&);

  /**
   * Read the binary data from the database and store it as Fields.
   */

  void initialize();

  /**
   * Tell each Field to parse its binary data into a real value.
   */

  void parse();

  /**
   * Retrieve the parsed values from each Field and write it to a file in either
   * CSV or JSON.
   *
   * @param reportFile Path to the report file
   */

  void writeToFile(std::string);

 private:
  Database& database;
  std::vector<Field> fields;
};

#endif
