#define CATCH_CONFIG_MAIN

#include "parser.h"
#include <catch2/catch.hpp>
#include <map>
#include <sstream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <Windows.h>
std::string getDirectory() {
  char buffer[MAX_PATH];
  GetModuleFileNameA(nullptr, buffer, MAX_PATH);
  std::string fullpath(buffer);
  size_t beginIdx = fullpath.rfind('\\');
  std::string dirPath = fullpath.substr(0, beginIdx);
  beginIdx = dirPath.rfind('\\');
  dirPath = dirPath.substr(0, beginIdx + 1);
  return dirPath;
}
#elif __APPLE__
#include <mach-o/dyld.h>
std::string getDirectory() {
  uint32_t bufSize = PATH_MAX + 1;
  char dirNameBuffer[bufSize];
  if (_NSGetExecutablePath(dirNameBuffer, &bufSize) == 0) {
    // Buffer size is too small.
    std::string fullpath(dirNameBuffer);
    int beginIdx = fullpath.rfind('/');
    std::string dirPath = fullpath.substr(0, beginIdx + 1);
    return dirPath;
  }
  return "";
}
#elif __linux__
#include <unistd.h>
std::string getDirectory() {
  char abs_path[1024];
  int cnt = readlink("/proc/self/exe", abs_path, 1024);
  // Get the absolute path of the executable program
  if (cnt < 0 || cnt >= 1024) {
    return "";
  }

  // The last '/' is followed by the executable name, remove devel/lib/m100/exe,
  // and only keep the previous part of the path.
  for (int i = cnt; i >= 0; --i) {
    if (abs_path[i] == '/') {
      abs_path[i + 1] = '\0';
      break;
    }
  }

  std::string path(abs_path);

  return path;
}

#endif

TEST_CASE("Test One Parser", "[Parser]") {
  Parser parser(getDirectory() + "files/dickens.txt");
  std::map<std::string, int> baselineMap = {
      {"best", 1},  {"it", 2},  {"of", 2},   {"the", 2},
      {"times", 2}, {"was", 2}, {"worst", 1}};
  std::stringstream ssBaseline;
  ssBaseline << baselineMap;
  std::stringstream ss;
  REQUIRE(parser.parse());
  ss << parser;
  REQUIRE(ssBaseline.str() == ss.str());
}

TEST_CASE("Test One Parser with ParserCollection",
          "[Parser][ParserCollection]") {
  ParserCollection parserCollection;
  Parser parser(getDirectory() + "files/fox.txt",
                &parserCollection.globalFreqencyMap);

  std::map<std::string, int> baselineMap = {
      {"brown", 1}, {"dog", 1},  {"fox", 1},   {"jumps", 1},
      {"lazy", 1},  {"over", 1}, {"quick", 1}, {"the", 2}};

  std::stringstream ssBaseline;
  ssBaseline << baselineMap;
  std::stringstream ss;
  REQUIRE(parser.parse());
  parserCollection.exportGlobal(ss);
  REQUIRE(ssBaseline.str() == ss.str());
}

TEST_CASE("Test Multiple Parser", "[Parser][ParserCollection]") {
  ParserCollection parserCollection;
  parserCollection.parsers = {Parser(getDirectory() + "files/churchill.txt",
                                     &parserCollection.globalFreqencyMap),
                              Parser(getDirectory() + "files/beastie.txt",
                                     &parserCollection.globalFreqencyMap),
                              Parser(getDirectory() + "files/iverson.txt",
                                     &parserCollection.globalFreqencyMap)};

  std::map<std::string, int> baselineMap = {
      {"beaches", 1}, {"fight", 4}, {"for", 2},   {"gotta", 1}, {"grounds", 1},
      {"landing", 1}, {"on", 2},    {"party", 1}, {"right", 1}, {"shall", 2},
      {"the", 2},     {"to", 1},    {"want", 1},  {"we", 2},    {"what", 1},
      {"you", 3},     {"your", 1}};
  std::stringstream ssBaseline;
  ssBaseline << baselineMap;

  for (int i = 0; i < parserCollection.parsers.size(); i++) {
    REQUIRE(parserCollection.parsers[i].parse());
  }
  std::stringstream ss;
  parserCollection.exportGlobal(ss);
  REQUIRE(ssBaseline.str() == ss.str());
}