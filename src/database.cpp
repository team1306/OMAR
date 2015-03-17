#include "database.h"
#include "page.h"
#include "question.h"

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include "SQLiteCpp/SQLiteCpp.h"

Database::Database(std::string dbfilename, std::string posfile) : database(dbfilename, SQLITE_OPEN_READWRITE) {
  
  std::ifstream pos (posfile);
  std::vector<Question> fileQuestions;
  std::string s;
  int x, y;
  Point a, b;
  while(!pos.eof()) {
    pos >> s >> a.x >> a.y >> b.x >> b.y;
    fileQuestions.push_back(Question(a, b, s));
  }

  std::vector<Question> dbQuestions;
  SQLite::Statement query (database, "SELECT * FROM questions;");
  while(query.executeStep()) {
    dbQuestions.push_back(Question(query.getColumn(1).getInt(), query.getColumn(2).getInt(), query.getColumn(3).getInt(), query.getColumn(4).getInt(), query.getColumn(5)));
  }

  if(fileQuestions.size() == dbQuestions.size()) {
    for(int i=0; i<fileQuestions.size(); i++) {
      if(fileQuestions[i] != dbQuestions[i]) {
	updateQuestions(fileQuestions);
	break;
      }
    }
  }
  else {
    updateQuestions(fileQuestions);
  }
}

void Database::updateQuestions(std::vector<Question> fileQuestions) {
  SQLite::Transaction transaction (database);
  int rc = database.exec("DELETE FROM questions;");

  for(int i=0; i<fileQuestions.size(); i++) {
    database.exec("INSERT INTO questions VALUES (" + std::to_string(fileQuestions[i].getUR().x) + ", " + std::to_string(fileQuestions[i].getUR().y) + ", " + std::to_string(fileQuestions[i].getLL().x) + ", " + std::to_string(fileQuestions[i].getLL().y) + ");");
  }

  transaction.commit();
}

void Database::updatePage(Page update) {

  std::string filename = update.filename();
  std::string awidth = std::to_string(update.getCalibrationSize().width);
  std::string aheight = std::to_string(update.getCalibrationSize().height);
  std::string bwidth = std::to_string(update.getPageSize().width);
  std::string bheight = std::to_string(update.getPageSize().height);

  SQLite::Statement query (database, "SELECT * FROM pages WHERE filename = '" + filename + "';");
  int rc;

  if(query.executeStep()) {
    SQLite::Transaction transaction (database);

    rc = database.exec("UPDATE pages SET calrectx = " + awidth + ", calrecty = " + aheight + ", pagesizex = " + bwidth + ", pagesizey = " + bheight + " WHERE filename = '" + filename + "';");
    
    transaction.commit();
  }
  else {
    SQLite::Transaction transaction (database);
    
    rc = database.exec("INSERT INTO pages VALUES ('" + filename + "', " + awidth + ", " + aheight + ", " + bwidth + ", " + bheight + ");");

    transaction.commit();
  }

  SQLite::Transaction dataTransaction (database);
  std::vector<Question> questions = update.getQuestions();
  for(int i=0; i<questions.size(); i++) {
    SQLite::Statement qQuery (database, "SELECT rowid FROM questions WHERE question = '" + questions[i].getName() + "';");
    qQuery.executeStep();
    int qid = qQuery.getColumn(1).getInt();

    SQLite::Statement pQuery (database, "SELECT rowid FROM pages WHERE filename = '" + filename + "';");
    pQuery.executeStep();
    int pid = pQuery.getColumn(1).getInt();

    database.exec("INSERT INTO data VALUES (" + std::to_string(qid) + ", " + std::to_string(pid) + ", " + std::to_string(questions[i].getAnswer()) + ");");
  }
  dataTransaction.commit();

  // now write the image to a file
  // TODO
}

Page Database::getPage(std::string filename) {
  SQLite::Statement query (database, "SELECT rowid FROM pages WHERE filename = '" + filename + "';");
  query.executeStep();
  int pid = query.getColumn(1).getInt();

  return getPage(pid);
}

Page Database::getPage(int pageid) {
  SQLite::Statement questionsQuery (database, "SELECT *, rowid FROM questions;");
  
  std::vector<Question> questions;
  while(questionsQuery.executeStep()) {
    questions.push_back(Question(questionsQuery.getColumn(1).getInt(), questionsQuery.getColumn(2).getInt(), questionsQuery.getColumn(3).getInt(), questionsQuery.getColumn(4).getInt(), questionsQuery.getColumn(5)));
    
    SQLite::Statement dataQuery (database, "SELECT * FROM data WHERE pid = " + std::to_string(pageid) + " AND qid = " + std::to_string(questionsQuery.getColumn(6).getInt()) + ";");
    dataQuery.executeStep();

    questions[questions.size() - 1].setAnswer(dataQuery.getColumn(3).getInt());
  }

  SQLite::Statement pageQuery (database, "SELECT * FROM pages WHERE rowid = " + std::to_string(pageid) + ";");
  Size calRect (pageQuery.getColumn(2).getInt(), pageQuery.getColumn(3).getInt());
  Size pageSize (pageQuery.getColumn(4).getInt(), pageQuery.getColumn(5).getInt());
  Page page (questions, imread(pageQuery.getColumn(1)), calRect, pageSize, pageQuery.getColumn(1));

  return page;
}

std::vector<Question> Database::getQuestions() {
  std::vector<Question> questions;

  SQLite::Statement query (database, "SELECT * FROM questions;");

  while(query.executeStep()) {
    Question q (query.getColumn(1).getInt(), query.getColumn(2).getInt(), query.getColumn(3).getInt(), query.getColumn(4).getInt(), query.getColumn(5).getText());
    questions.push_back(q);
  }

  return questions;
}

std::vector<Page> Database::getPages() {
  std::vector<Page> pages;
  std::vector<Question> questions = getQuestions();

  SQLite::Statement query (database, "SELECT * FROM pages;");
  while(query.executeStep()) {
    Size a (query.getColumn(2).getInt(), query.getColumn(3).getInt());
    Size b (query.getColumn(4).getInt(), query.getColumn(5).getInt());
    Page page (questions, imread(query.getColumn(1).getText()), a, b, query.getColumn(1).getText());

    pages.push_back(page);
  }

  return pages;
}

Page Database::getPage(std::string filename, std::vector<Question> questions) {
  SQLite::Statement query (database, "SELECT * FROM pages WHERE filename = ?;");
  query.bind(1, filename);
  if(query.executeStep()) {
    Size a (query.getColumn(2).getInt(), query.getColumn(3).getInt());
    Size b (query.getColumn(4).getInt(), query.getColumn(5).getInt());
    Page page (questions, imread(query.getColumn(1).getText()), a, b, query.getColumn(1).getText());
    return page;
  }
  else {
    throw PAGE_NOT_FOUND;
  }
}

