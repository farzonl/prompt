#include "parser.h"
#include <algorithm>
#include <fstream>
#include <sstream>

// clang-format off
/*!
\brief   Initializes a Parser with an input and export file.
*/
// clang-format on
Parser::Parser(const std::string &path,
               std::map<std::string, size_t> *globalFreqencyMap)
    : mInputFilePath(path), mGlobalFreqencyMap(globalFreqencyMap) {
  mOutputFilePath = mInputFilePath.substr(0, mInputFilePath.find(".")) + ".out";
}

// clang-format off
/*!
\brief A function that creates a file stream from a path and parses it for word frequency.
\return	 the status of whether parsing was successful.  
*/
// clang-format on
bool Parser::parse() {
  std::ifstream file(mInputFilePath);
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

// clang-format off
/*!
\brief   A function that tokenizes a line into words split by a list of special charactered delimiters.
\param	 [in] line The line we want to split into words to track for analytics.
*/
// clang-format on
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

// clang-format off
/*!
\brief   A function that lowers all characters in a string.
\details This is used b\c when tracking word frequency there is no 
         difference between a capitalized and lowercase version of a word.
*/
// clang-format on
void StringHelper::toLower(std::string &word) {
  std::transform(word.begin(), word.end(), word.begin(),
                 [](unsigned char c) { return std::tolower(c); });
}

// clang-format off
/*!
\brief   A function that increments word frequency both per parser and across parsers.
\param	 [in] word The  string whos frequency we want to keep track of. 
*/
// clang-format on
void Parser::addToMap(std::string word) {
  addToMap(word, mLocalFreqencyMap);
  // We have a choice here we can merge the
  // localFreqencyMaps in post or we can just
  // have a global one.
  if (mGlobalFreqencyMap != nullptr) {
    addToMap(word, *mGlobalFreqencyMap);
  }
}

// clang-format off
/*!
\brief   A function that increments word frequency.
\param	 [in] word The  string whos frequency we want to keep track of.
\param	 [in] freqencyMap the map we want to increment.
\details This function abstracts which frequency map we use and increments word frequency.
*/
// clang-format on
void Parser::addToMap(std::string word,
                      std::map<std::string, size_t> &freqencyMap) {
  if (freqencyMap.find(word) == freqencyMap.end()) {
    freqencyMap[word] = 1;
  } else {
    freqencyMap[word] = freqencyMap[word] + 1;
  }
}

// clang-format off
/*!
\brief    A function that exports the per parser frequency map.
*/
// clang-format on
void Parser::exportToFile() {
  std::ofstream ofs(mOutputFilePath, std::ios_base::out);
  ofs << *this;
  ofs.close();
}

// clang-format off
/*!
\brief   A function that exports the combined frequency map.
\param	 [in] out The out stream we want to export the global frequency map. 
          This parameter allows one to use a file stream instead of the default iostream. 
*/
// clang-format on
void ParserCollection::exportGlobal(std::ostream &out) {
  out << globalFreqencyMap;
}