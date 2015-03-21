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
  fileQuestions.erase(fileQuestions.end() - 1);

  std::vector<Question> dbQuestions;
  SQLite::Statement query (database, "SELECT * FROM questions;");
  while(query.executeStep()) {
    dbQuestions.push_back(Question(query.getColumn(0).getInt(), query.getColumn(1).getInt(), query.getColumn(2).getInt(), query.getColumn(3).getInt(), query.getColumn(4)));
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
    database.exec("INSERT INTO questions VALUES (" + std::to_string(fileQuestions[i].getUR().x) + ", " + std::to_string(fileQuestions[i].getUR().y) + ", " + std::to_string(fileQuestions[i].getLL().x) + ", " + std::to_string(fileQuestions[i].getLL().y) + ", '" + fileQuestions[i].getName() + "');");
  }

  transaction.commit();
}

void Database::updatePage(Page update) {
  std::string filename = update.filename();
  filename = filename.substr(0, filename.size() - 3) + "good.jpg";
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
    int qid = qQuery.getColumn(0).getInt();

    SQLite::Statement pQuery (database, "SELECT rowid FROM pages WHERE filename = '" + filename + "';");
    pQuery.executeStep();
    int pid = pQuery.getColumn(0).getInt();

    database.exec("INSERT INTO data VALUES (" + std::to_string(qid) + ", " + std::to_string(pid) + ", " + std::to_string(questions[i].getAnswer()) + ");");
  }
  dataTransaction.commit();

  // now write the image to a file
  imwrite(filename, update.getImage());
}

Page Database::getPage(std::string filename) {
  SQLite::Statement query (database, "SELECT rowid FROM pages WHERE filename = '" + filename + "';");
  if(query.executeStep()) {
    int pid = query.getColumn(0).getInt();
    
    return getPage(pid);
  }
  else {
    throw 20; // TODO
  }
}

Page Database::getPage(int pageid) {
  SQLite::Statement questionsQuery (database, "SELECT *, rowid FROM questions;");
  
  std::vector<Question> questions;
  while(questionsQuery.executeStep()) {
    questions.push_back(Question(questionsQuery.getColumn(0).getInt(), questionsQuery.getColumn(1).getInt(), questionsQuery.getColumn(2).getInt(), questionsQuery.getColumn(3).getInt(), questionsQuery.getColumn(4)));
    
    SQLite::Statement dataQuery (database, "SELECT * FROM data WHERE pid = " + std::to_string(pageid) + " AND qid = " + std::to_string(questionsQuery.getColumn(5).getInt()) + ";");
    dataQuery.executeStep();

    questions[questions.size() - 1].setAnswer(dataQuery.getColumn(2).getInt());
  }

  SQLite::Statement pageQuery (database, "SELECT * FROM pages WHERE rowid = " + std::to_string(pageid) + ";");
  pageQuery.executeStep();
  Size calRect (pageQuery.getColumn(1).getInt(), pageQuery.getColumn(2).getInt());
  Size pageSize (pageQuery.getColumn(3).getInt(), pageQuery.getColumn(4).getInt());
  Page page (questions, imread(pageQuery.getColumn(0)), calRect, pageSize, pageQuery.getColumn(0));

  return page;
}

std::vector<Page> Database::getPages() {
  SQLite::Statement pagesQuery (database, "SELECT rowid FROM pages;");

  std::vector<Page> pages;
  while(pagesQuery.executeStep()) {
    pages.push_back(getPage(pagesQuery.getColumn(0).getInt()));
  }

  return pages;
}

std::vector<Question> Database::getQuestions() {
  SQLite::Statement qQuery (database, "SELECT * FROM questions;");

  std::vector<Question> questions;
  while(qQuery.executeStep()) {
    questions.push_back(Question(qQuery.getColumn(0).getInt(), qQuery.getColumn(1).getInt(), qQuery.getColumn(2).getInt(), qQuery.getColumn(3).getInt(), qQuery.getColumn(4)));
  }

  return questions;
}
