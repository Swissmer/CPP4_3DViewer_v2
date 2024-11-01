#ifndef OPENGL_H
#define OPENGL_H

#define GL_SILENCE_DEPRECATION

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <QWidget>
#include <QtOpenGL>

#include "../controller/controller.h"
#include "../model/helpinfo.h"
#include "../pattern/pattern_command.h"

namespace s21 {
class OpenGL : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit OpenGL(QWidget *parent = nullptr);
  // settor
  void setController(s21::Controller *controller);
  void loadSettings();
  void saveSettings();

  // public main variables
  Data data_;
  //  MovementCoords move_;
  QSettings *settings_;

  // for color
  double redBack_ = 0.0, greenBack_ = 0.0, blueBack_ = 0.0, opacity_ = 1.0;
  double redLine_ = 1, greenLine_ = 1, blueLine_ = 1;
  double redDot_ = 1.0, greenDot_ = 1, blueDot_ = 1;

  // for style
  int projType_ = 0, dotType_ = 1, lineType_ = 0;
  int dotSize_ = 1, lineSize_ = 1;

 private:
  // private main variables
  QPoint lastMousePosition;
  s21::Controller *controller_;

  // other methods
  void SetLineColor();
  void SetDotColor();
  void mouseMoveEvent(QMouseEvent *) override;
  void mousePressEvent(QMouseEvent *) override;
  void wheelEvent(QWheelEvent *) override;

 protected:
  // base methods
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;
};
}  // namespace s21

#endif  // OPENGL_H
