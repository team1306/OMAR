#include "report.h"
#include "database.h"
#include "checkbox.h"
#include "multiplechoice.h"
#include "number.h"
#include <algorithm>
#include <fstream>

Report::Report(Database *db) {
  database = db;
}

Report::~Report() {
  for(int i=0; i<fields.size(); i++) {
    for(int j=0; j<fields[i].size(); j++) {
      delete fields[i][j];
    }
  }
}

void Report::initialize() {
  std::vector<Question> questions = database->getQuestions();
  for(int i=0; i<questions.size(); i++) {
    std::string tag = questions[i].getName();
    if(std::find(tags.begin(), tags.end(), tag) == tags.end()) {
      tags.push_back(tag);
      int dots = std::count(tag.begin(), tag.end(), '.');
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
    std::vector<Field*> fs;
    std::vector<Question> pageQs = pages[i].getQuestions();

    // sort checkbox tags
    for(int j=0; j<CBTags.size(); j++) {
      std::vector<Question> qs;
      for(int k=0; k<pageQs.size(); k++) {
	if(getTag(pageQs[k].getName()) == CBTags[j]) {
	  qs.push_back(pageQs[k]);
	}
      }
      CheckBox *cb = new CheckBox(qs);
      cb->parse();
      fs.push_back(cb);
    }

    for(int j=0; j<NumTags.size(); j++) {
      std::vector<Question> qs;
      for(int k=0; k<pageQs.size(); k++) {
	if(getTag(pageQs[k].getName()) == NumTags[j]) {
	  qs.push_back(pageQs[k]);
	}
      }
      Number *num = new Number(qs);
      num->parse();
      fs.push_back(num);
    }

    for(int j=0; j<MCTags.size(); j++) {
      std::vector<Question> qs;
      for(int k=0; k<pageQs.size(); k++) {
	if(getTag(pageQs[k].getName()) == MCTags[j]) {
	  qs.push_back(pageQs[k]);
	}
      }
      MultipleChoice *mc = new MultipleChoice(qs);
      mc->parse();
      fs.push_back(mc);
    }

    fields.push_back(fs);
  }
}

void Report::writeToFile(std::string reportFile) {
  std::ofstream fout (reportFile);

  for(int i=0; i<tags.size(); i++) {
    fout << tags[i] << ";";
  }
  fout << std::endl;

  for(int i=0; i<fields.size(); i++) {
    for(int j=0; j<fields[i].size(); j++) {
      fout << fields[i][j]->getValue() << ";";
    }
    fout << std::endl;
  }
  
  fout.close();
}

 std::string Report::getTag(std::string s) {
  std::string tag = ""; // should reimplement with string stream
  int i = 0;
  while(s[i] != '.' && i != s.size()) {
    tag += s[i];
    i++;
  }

  return tag;
}
