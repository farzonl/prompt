#include "lib/parser.h"
#include <vector>

int main(int argc, char *argv[]) {
  const std::string localFlag("-l");
  bool isLocalFlag = false;
  std::vector<Parser> parsers;
  for (int i = 1; i < argc; i++) {
    if (localFlag == argv[i]) {
      isLocalFlag = true;
      continue;
    }
    Parser parser(argv[i]);
    if (parser.parse()) {
      parsers.push_back(parser);
    } else {
      std::cerr << "failed to parse file: " << argv[i] << std::endl;
    }
  }
  if (isLocalFlag) {
    for (auto parser : parsers) {
      parser.exportToFile();
    }
  } else {
    Parser::exportGlobal();
  }
  return 0;
}