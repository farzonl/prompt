#include "lib/parser.h"
#include <vector>

void printUsage() {
  std::cout << "usage: ./WordFreq [...<string| filepath>]\n";
  std::cout << "       ./WordFreq -l [...<string| filepath>]\n";
  std::cout << "       ./WordFreq -h\n";
}

int main(int argc, char *argv[]) {
  const std::string localFlag("-l");
  const std::string helpFlag("-h");
  bool isLocalFlag = false;

  if (argc == 1) {
    printUsage();
    return 0;
  }

  ParserCollection parserCollection;
  for (int i = 1; i < argc; i++) {
    if (localFlag == argv[i]) {
      isLocalFlag = true;
      continue;
    }
    if (helpFlag == argv[i]) {
      printUsage();
      return 0;
    }
    Parser parser(argv[i], &parserCollection.globalFreqencyMap);
    if (parser.parse()) {
      parserCollection.parsers.push_back(parser);
    } else {
      std::cerr << "failed to parse file: " << argv[i] << std::endl;
      printUsage();
      return -1;
    }
  }
  if (isLocalFlag) {
    for (auto parser : parserCollection.parsers) {
      parser.exportToFile();
    }
  } else {
    parserCollection.exportGlobal();
  }
  return 0;
}