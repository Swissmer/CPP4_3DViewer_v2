#include <QApplication>

#include "./pattern/pattern_facade.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Facade app;
  app.build();
  return a.exec();
}
