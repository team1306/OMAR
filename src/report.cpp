#include "report.h"
#include "database.h"
#include "checkbox.h"
#include "multiplechoice.h"
#include "number.h"
#include <algorithm>

Report::Report(Database *db) {
  database = db;
}

void Report::initialize() {
  std::vector<Question> questions = database->getQuestions();
  for(int i=0; i<questions.size(); i++) {
    std::string tag = getTag(questions[i].getName());
    if(std::find(tags.begin(), tags.end(), tag) == tags.end()) {
      tags.push_back(tag);
      int dots = countDots(tag);
      if(dots == 0) {
	CBTags.push_back(tag);
      }
      else if(dots == 2) {
	MCTags.push_back(tag);
      }
      else if(dots == 3) {
	NumTags.push_back(tag);
      }
    }
  }

  // TODO this all needs to be optimized
  std::vector<Page> pages = database->getPages();
  for(int i=0; i<pages.size(); i++) {
    std::vector<Field> fs;
    std::vector<Question> pageQs = pages[i].getQuestions();

    // sort checkbox tags
    for(int j=0; j<CBTags.size(); j++) {
      std::vector<Question> qs;
      for(int k=0; k<pageQs.size(); k++) {
	if(getTag(pageQs[k].getName()) == CBTags[j]) {
	  qs.push_back(pageQs[k]);
	}
      }
      fs.push_back(CheckBox(qs));
    }

    for(int j=0; j<NumTags.size(); j++) {
      std::vector<Question> qs;
      for(int k=0; k<pageQs.size(); k++) {
	if(getTag(pageQs[k].getName()) == NumTags[j]) {
	  qs.push_back(pageQs[k]);
	}
      }
      fs.push_back(Number(qs));
    }

    for(int j=0; j<MCTags.size(); j++) {
      std::vector<Question> qs;
      for(int k=0; k<pageQs.size(); k++) {
	if(getTag(pageQs[k].getName()) == MCTags[j]) {
	  qs.push_back(pageQs[k]);
	}
      }
      fs.push_back(MultipleChoice(qs));
    }

    fields.push_back(fs);
  }
}

void Report::parse() {
  for(int i=0; i<fields.size(); i++) {
    for(int j=0; j<fields[i].size(); j++) {
      fields[i][j].parse();
    }
  }
}

void Report::writeToFile(std::string reportFile) {
  // dear lord
}

int Report::countDots(std::string s) {
  int total = 0;
  for(int i=0; i<s.size(); i++) {
    if(s[i] == '.') {
      total++;
    }
  }
  return total;
}

 std::string Report::getTag(std::string s) {
  std::string tag = ""; // should reimplement with 
  int i = 0;
  while(s[i] != '.' && i != s.size()) {
    tag += s[i];
  }

  return tag;
}
