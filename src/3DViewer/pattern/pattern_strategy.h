#ifndef CPP4_SRC_PATTERN_PATTERN_STRATEGY_H
#define CPP4_SRC_PATTERN_PATTERN_STRATEGY_H

#include <sstream>

#include "../model/helpinfo.h"

namespace s21 {
class Strategy {
 public:
  virtual ~Strategy() {}
  virtual void fill(std::string line, Data &data) = 0;
};

class StrategyInvoker {
 public:
  void run(Strategy *strategy, std::string line, Data &data);
};

class FillVertex : public Strategy {
 public:
  void fill(std::string line, Data &data) override;
};

class FillFacete : public Strategy {
 public:
  void fill(std::string, Data &data) override;
  inline void PushFirst(std::vector<int> &facetes, const std::string &line,
                        int &firstValue, int vertex_count);
  inline void PushNext(std::vector<int> &facetes, const std::string &line,
                       int vertex_count);

 private:
  std::string num_ = "0123456789-";
};
}  // namespace s21

#endif  // CPP4_SRC_PATTERN_PATTERN_STRATEGY_H