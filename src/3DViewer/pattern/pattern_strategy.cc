#include "pattern_strategy.h"

namespace s21 {
void StrategyInvoker::run(Strategy *strategy, std::string line, Data &data) {
  strategy->fill(line, data);
}

void FillVertex::fill(std::string line, Data &data) {
  double x, y, z;
  std::istringstream iss(line);
  std::string str;
  iss >> str >> x >> y >> z;
  data.vertex_.push_back(x);
  data.vertex_.push_back(y);
  data.vertex_.push_back(z);
}

void FillFacete::fill(std::string line, Data &data) {
  std::vector<int> facetes;
  int vertex_count = data.vertex_.size() / 3;
  int len = line.size();
  int firstValue = 0;
  for (int i = 1; i < len; ++i) {
    if (line[i] == ' ' && num_.find(line[i + 1]) != std::string::npos) {
      ++i;
      if (i == 2)
        PushFirst(facetes, &line[i], firstValue, vertex_count);
      else
        PushNext(facetes, &line[i], vertex_count);
    }
  }
  facetes.push_back(firstValue);
  data.polygons_.push_back(facetes);
}

inline void FillFacete::PushFirst(std::vector<int> &facetes,
                                  const std::string &line, int &firstValue,
                                  int vertex_count) {
  std::istringstream iss(line);
  int value;
  iss >> value;
  value = value > 0 ? value - 1 : value + vertex_count;
  firstValue = value;
  facetes.push_back(value);
}

inline void FillFacete::PushNext(std::vector<int> &facetes,
                                 const std::string &line, int vertex_count) {
  std::istringstream iss(line);
  int value;
  iss >> value;
  value = value > 0 ? value - 1 : value + vertex_count;
  facetes.push_back(value);
  facetes.push_back(value);
}
}  // namespace s21