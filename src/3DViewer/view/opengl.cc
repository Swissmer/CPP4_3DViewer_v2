#include "opengl.h"

#include <QDebug>

namespace s21 {

////////////
// settor //
////////////

void OpenGL::setController(s21::Controller *controller) {
  controller_ = controller;
}

void OpenGL::loadSettings() {
  if (settings_->value("are_settings").toInt() == 1) {
    projType_ = settings_->value("projection_type").toInt();
    dotType_ = settings_->value("dot_type").toInt();
    lineType_ = settings_->value("line_type").toInt();
    dotSize_ = settings_->value("dot_size").toInt();
    lineSize_ = settings_->value("live_size").toInt();
    redBack_ = settings_->value("red_back").toInt();
    greenBack_ = settings_->value("green_back").toInt();
    blueBack_ = settings_->value("blue_back").toInt();
    redLine_ = settings_->value("red_line").toInt();
    greenLine_ = settings_->value("green_line").toInt();
    blueLine_ = settings_->value("blue_line").toInt();
    redDot_ = settings_->value("red_dot").toInt();
    greenDot_ = settings_->value("green_dot").toInt();
    blueDot_ = settings_->value("blue_dot").toInt();
  }
}

void OpenGL::saveSettings() {
  settings_->setValue("are_settings", 1);
  settings_->setValue("projection_type", projType_);
  settings_->setValue("dot_type", dotType_);
  settings_->setValue("line_type", lineType_);
  settings_->setValue("dot_size", dotSize_);
  settings_->setValue("line_size", lineSize_);
  settings_->setValue("red_back", redBack_);
  settings_->setValue("green_back", greenBack_);
  settings_->setValue("blue_back", blueBack_);
  settings_->setValue("red_line", redLine_);
  settings_->setValue("green_line", greenLine_);
  settings_->setValue("blue_line", blueLine_);
  settings_->setValue("red_dot", redDot_);
  settings_->setValue("green_dot", greenDot_);
  settings_->setValue("blue_dot", blueDot_);
}

///////////////////
// other methods //
///////////////////

void OpenGL::SetLineColor() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  if (lineType_ == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }

  glColor3f(redLine_, greenLine_, blueLine_);
  glLineWidth(lineSize_);

  glVertexPointer(3, GL_DOUBLE, 0, data_.vertex_.data());

  for (std::vector<int> facete : data_.polygons_) {
    glDrawElements(GL_LINES, facete.size(), GL_UNSIGNED_INT, facete.data());
  }

  glDisable(GL_LINE_STIPPLE);
}

void OpenGL::SetDotColor() {
  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
  if (dotType_ == 1) glEnable(GL_POINT_SMOOTH);
  if (dotType_ == 2) glDisable(GL_POINT_SMOOTH);

  if (dotType_) {
    glPointSize(dotSize_);
    glColor3f(redDot_, greenDot_, blueDot_);
    glDrawArrays(GL_POINTS, 0, data_.vertex_.size() / 3);
  }

  glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void OpenGL::mouseMoveEvent(QMouseEvent *mouseEvent) {
  if (mouseEvent->buttons() == Qt::LeftButton) {
    Rotater rotater;
    controller_->Transformate(
        &rotater, 'y', data_,
        static_cast<double>(mouseEvent->pos().y() - lastMousePosition.y()));
    controller_->Transformate(
        &rotater, 'x', data_,
        static_cast<double>(lastMousePosition.x() - mouseEvent->pos().x()));
  }
  lastMousePosition = mouseEvent->pos();
  update();
}

void OpenGL::mousePressEvent(QMouseEvent *mouseEvent) {
  lastMousePosition = mouseEvent->pos();
}

void OpenGL::wheelEvent(QWheelEvent *wheelEvent) {
  int step = wheelEvent->angleDelta().y();
  if (step > 0) {
    controller_->Scale(data_, 1.05);
  } else {
    controller_->Scale(data_, 0.95);
  }
  update();
}

//////////////////
// base methods //
//////////////////

OpenGL::OpenGL(QWidget *parent) : QOpenGLWidget(parent) {}

void OpenGL::initializeGL() {
  initializeOpenGLFunctions();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
}

void OpenGL::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}

void OpenGL::paintGL() {
  glClearColor(redBack_, greenBack_, blueBack_, opacity_);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (projType_ == 0) {
    glOrtho(-3, 3, -3, 3, -100, 100);
  } else {
    glFrustum(-3, 3, -3, 3, 1, 100);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -3);

  glEnableClientState(GL_VERTEX_ARRAY);

  SetLineColor();
  SetDotColor();

  glDisableClientState(GL_VERTEX_ARRAY);
}

}  // namespace s21
