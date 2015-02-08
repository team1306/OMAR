#include "database.h"
#include "page.h"
#include "question.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>

Database::Database(std::string filename) : database(filename) {
  
}

std::vector<Question> Database::getQuestions() {
  std::vector<Question> questions;

  SQLite::Statement query (database, "SELECT * FROM questions");

  while(query.executeStep()) {
    Question q (query.getColumn(1).getInt(), query.getColumn(2).getInt(), query.getColumn(3).getInt(), query.getColumen(4).getInt(), query.getColumn(5).getText());
    questions.push_back(q);
  }

  return questions;
}

std::vector<Page> Database::getPages() {
  std::vector<Page> pages;

  SQLite::Statement query (database, "SELECT * FROM pages");
}

Page Database::getPage(std::string filename, std::vector<Question> questions) {
  SQLite::Statement query (database, "SELECT * FROM pages WHERE filename = ?");
  query.bind(1, filename);
  if(query.executeStep()) {
    size a, b;
    a.width = query.getColumn(2).getInt();
    a.height = query.getColumn(3).getInt();
    b.width = query.getColumn(4).getInt();
    b.height = query.getColumn(5).getInt();
    Page page (questions, imread(query.getColumn(1).getText()), a, b, query.getColumn(1).getText());
    return page;
  }
  else {
    throw PAGE_NOT_FOUND;
  }
}

void Database::updatePage(Page update) {
  
}

