#include "parser.h"
#include <algorithm>
#include <fstream>
#include <sstream>

std::map<std::string, size_t> Parser::globalFreqencyMap;

Parser::Parser(const std::string &path) : inputFilePath(path) {
  outputFilePath = inputFilePath.substr(0, inputFilePath.find(".")) + ".out";
}

bool Parser::parse() {
  std::ifstream file(inputFilePath);
  if (!file.is_open()) {
    // Error couldn't open the file
    return false;
  }

  std::string line;
  while (getline(file, line)) {
    parseLine(line);
  }

  file.close();
  return file.eof() && !file.bad();
}

void Parser::parseLine(const std::string &line) {
  size_t startPos = 0, endpos = 0;
  while ((startPos = line.find_first_not_of(Parser::delimeters, endpos)) !=
         std::string::npos) {
    endpos = line.find_first_of(Parser::delimeters, startPos + 1);
    std::string word = line.substr(startPos, endpos - startPos);
    StringHelper::toLower(word);
    addToMap(word);
  }
}

void StringHelper::toLower(std::string &word) {
  std::transform(word.begin(), word.end(), word.begin(),
                 [](unsigned char c) { return std::tolower(c); });
}

void Parser::addToMap(std::string word) {
  addToMap(word, localFreqencyMap);
  // We have a choice here we can merge the
  // localFreqencyMaps in post or we can just
  // have a global one.
  addToMap(word, globalFreqencyMap);
}

void Parser::addToMap(std::string word,
                      std::map<std::string, size_t> &freqencyMap) {
  if (freqencyMap.find(word) == freqencyMap.end()) {
    freqencyMap[word] = 1;
  } else {
    freqencyMap[word] = freqencyMap[word] + 1;
  }
}

void Parser::exportGlobal(std::ostream &out) { out << globalFreqencyMap; }

void Parser::exportToFile() {
  std::ofstream ofs(outputFilePath, std::ios_base::out);
  ofs << *this;
  ofs.close();
}