#pragma once

#include <iostream>
#include <map> // we want an ordered map
#include <string>

class Parser {
private:
  static constexpr char delimeters[] = " \".,:;!?<>{}[]()_=+^%*&#";
  std::string outputFilePath;
  std::string inputFilePath;
  std::map<std::string, size_t> localFreqencyMap;
  static std::map<std::string, size_t> globalFreqencyMap;
  void addToMap(std::string word, std::map<std::string, size_t> &freqencyMap);
  void addToMap(std::string word);
  void parseLine(const std::string &line);

public:
  Parser(const std::string &path);
  bool parse();
  static void exportGlobal(std::ostream &out = std::cout);
  void exportToFile();
  friend std::ostream &operator<<(std::ostream &out, const Parser &aDis);
};

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
  out << parser.localFreqencyMap << std::endl;
  return out;
}