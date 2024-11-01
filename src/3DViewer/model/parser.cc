#include "parser.h"

namespace s21 {
void Parser::ParseObjFile(std::string path, Data &data, Errors &err) {
  std::ifstream file(path);
  if (file.is_open() && file.peek() != std::ifstream::traits_type::eof()) {
    std::string line;
    while (std::getline(file, line)) {
      if (!line.compare(0, 2, "v ")) {
        FillVertex fillv;
        strategy_.run(&fillv, line, data);
      } else if (!line.compare(0, 2, "f ")) {
        data.vertex_in_facete_count_ += CalculateSpaces(line);
        FillFacete fillf;
        strategy_.run(&fillf, line, data);
      }
    }
    if ((data.vertex_.size() / 3) < 3)
      err.err_ = ErrorCodes::kWrongCountOfCoords;
    else
      data.edges_ = data.vertex_.size() / 3 + data.polygons_.size() - 2;
  } else {
    err.err_ = ErrorCodes::kEmptyFile;
  }
}

int Parser::CalculateSpaces(const std::string &line) {
  int spaces = 0;
  int len = line.size();
  for (int i = 0; i < len; ++i) {
    if (line[i] == ' ') ++spaces;
  }
  return spaces;
}

}  // namespace s21
