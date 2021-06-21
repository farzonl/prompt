#pragma once

#include <iostream>
#include <map> // we want an ordered map
#include <string>
#include <vector>

/*!
\brief   Parser class that tokenizes words and removes special characters.
\details This class tokenizes words, counts word frequency and stores them
          alphabetically in an in-memory data store.
*/
class Parser {
private:
  static constexpr char delimeters[] = " \".,:;!?<>{}[]()_=+^%*&#";
  std::string mOutputFilePath;
  std::string mInputFilePath;
  std::map<std::string, size_t> *mGlobalFreqencyMap;
  std::map<std::string, size_t> mLocalFreqencyMap;
  void addToMap(std::string word, std::map<std::string, size_t> &freqencyMap);
  void addToMap(std::string word);
  void parseLine(const std::string &line);

public:
  Parser(const std::string &path,
         std::map<std::string, size_t> *globalFreqencyMap = nullptr);
  bool parse();
  void exportToFile();
  friend std::ostream &operator<<(std::ostream &out, const Parser &aDis);
};

/*!
\brief  Common data structures needed to support cross file frequency analysis.
\details Note: No effort was taken to make globalFreqencyMap thread safe.
         Parsers are intended to run sequentially.
*/
struct ParserCollection {
  std::map<std::string, size_t> globalFreqencyMap;
  std::vector<Parser> parsers;
  void exportGlobal(std::ostream &out = std::cout);
};

/*!
\brief   StringHelper provides static helper functions to manipulate strings.
*/
class StringHelper {
  StringHelper() = delete;

public:
  static void toLower(std::string &word);
};

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const std::map<K, V> &m) {
  for (const std::pair<K, V> &p : m) {
    os << "{" << p.first << ": " << p.second << "}\n";
  }
  return os;
}

inline std::ostream &operator<<(std::ostream &out, const Parser &parser) {
  out << parser.mLocalFreqencyMap;
  return out;
}