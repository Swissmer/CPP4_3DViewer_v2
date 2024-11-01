#include "view.h"

#include <QDebug>

#include "ui_view.h"

namespace s21 {

//////////////////
// main methods //
//////////////////

View::View(QWidget *parent, Controller *controller)
    : QMainWindow(parent), ui(new Ui::View), controller_(controller) {
  ui->setupUi(this);
  ui->openGLWidget->setController(controller_);

  ui->openGLWidget->settings_ =
      new QSettings("School 21", "3DViewer_Settings", this);
  ui->openGLWidget->loadSettings();

  ui->labelPath->setText("");
  ui->Vertex->setText("");
  ui->Edge->setText("");
  ui->gifScreen->setText("");
}

View::~View() {
  ui->openGLWidget->saveSettings();
  delete ui->openGLWidget->settings_;
  delete ui;
}

///////////
// style //
///////////

void View::on_ScrollBarDotSize_valueChanged(int value) {
  ui->openGLWidget->dotSize_ = value;
  ui->openGLWidget->update();
}

void View::on_ScrollBarLineSize_valueChanged(int value) {
  ui->openGLWidget->lineSize_ = value;
  ui->openGLWidget->update();
}

void View::on_radioButtonOrtho_clicked() {
  ui->openGLWidget->projType_ = 0;
  ui->openGLWidget->update();
}

void View::on_radioButtonPerspective_clicked() {
  ui->openGLWidget->projType_ = 1;
  ui->openGLWidget->update();
}

void View::on_pushButtonLineColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white).toRgb();
  ui->openGLWidget->redLine_ = color.redF();
  ui->openGLWidget->greenLine_ = color.greenF();
  ui->openGLWidget->blueLine_ = color.blueF();
  ui->openGLWidget->opacity_ = color.alphaF();
  ui->openGLWidget->update();
}

void View::on_pushButtonDotColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white).toRgb();
  ui->openGLWidget->redDot_ = color.redF();
  ui->openGLWidget->greenDot_ = color.greenF();
  ui->openGLWidget->blueDot_ = color.blueF();
  ui->openGLWidget->update();
}

void View::on_pushButtonBackgroundColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white).toRgb();
  ui->openGLWidget->redBack_ = color.redF();
  ui->openGLWidget->greenBack_ = color.greenF();
  ui->openGLWidget->blueBack_ = color.blueF();
  ui->openGLWidget->update();
}

void View::on_radioButtonSolid_clicked() {
  ui->openGLWidget->lineType_ = 0;
  ui->openGLWidget->update();
}

void View::on_radioButtonDotted_clicked() {
  ui->openGLWidget->lineType_ = 1;
  ui->openGLWidget->update();
}

void View::on_radioButtonWIthoutDot_clicked() {
  ui->openGLWidget->dotType_ = 0;
  ui->openGLWidget->update();
}

void View::on_radioButtonRoundDot_clicked() {
  ui->openGLWidget->dotType_ = 1;
  ui->openGLWidget->update();
}

void View::on_radioButtonSquareDot_clicked() {
  ui->openGLWidget->dotType_ = 2;
  ui->openGLWidget->update();
}

///////////////
// transform //
///////////////

void View::on_pushButtonMoveXMinus_clicked() {
  Mover mover;
  controller_->Transformate(&mover, 'x', ui->openGLWidget->data_, -10.0);
  ui->openGLWidget->update();
}

void View::on_pushButtonMoveXPlus_clicked() {
  Mover mover;
  controller_->Transformate(&mover, 'x', ui->openGLWidget->data_, 10.0);
  ui->openGLWidget->update();
}

void View::on_pushButtonMoveYMinus_clicked() {
  Mover mover;
  controller_->Transformate(&mover, 'y', ui->openGLWidget->data_, -10.0);
  ui->openGLWidget->update();
}

void View::on_pushButtonMoveYPlus_clicked() {
  Mover mover;
  controller_->Transformate(&mover, 'y', ui->openGLWidget->data_, 10.0);
  ui->openGLWidget->update();
}

void View::on_pushButtonMoveZMinus_clicked() {
  Mover mover;
  controller_->Transformate(&mover, 'z', ui->openGLWidget->data_, -10.0);
  ui->openGLWidget->update();
}

void View::on_pushButtonMoveZPlus_clicked() {
  Mover mover;
  controller_->Transformate(&mover, 'z', ui->openGLWidget->data_, 10.0);
  ui->openGLWidget->update();
}

void View::on_pushButtonRotateXMinus_clicked() {
  Rotater rotater;
  controller_->Transformate(&rotater, 'x', ui->openGLWidget->data_, -10.0);
  ui->openGLWidget->update();
}

void View::on_pushButtonRotateXPlus_clicked() {
  Rotater rotater;
  controller_->Transformate(&rotater, 'x', ui->openGLWidget->data_, 10.0);
  ui->openGLWidget->update();
}

void View::on_pushButtonRotateYMinus_clicked() {
  Rotater rotater;
  controller_->Transformate(&rotater, 'y', ui->openGLWidget->data_, -10.0);
  ui->openGLWidget->update();
}

void View::on_pushButtonRotateYPlus_clicked() {
  Rotater rotater;
  controller_->Transformate(&rotater, 'y', ui->openGLWidget->data_, 10.0);
  ui->openGLWidget->update();
}

void View::on_pushButtonRotateZMinus_clicked() {
  Rotater rotater;
  controller_->Transformate(&rotater, 'z', ui->openGLWidget->data_, -10.0);
  ui->openGLWidget->update();
}

void View::on_pushButtonRotateZPlus_clicked() {
  Rotater rotater;
  controller_->Transformate(&rotater, 'z', ui->openGLWidget->data_, 10.0);
  ui->openGLWidget->update();
}

void View::on_pushButtonScaleMinus_clicked() {
  controller_->Scale(ui->openGLWidget->data_, 0.95);
  ui->openGLWidget->update();
}

void View::on_pushButtonScalePlus_clicked() {
  controller_->Scale(ui->openGLWidget->data_, 1.05);
  ui->openGLWidget->update();
}

///////////
// other //
///////////

void View::on_uploadObjFile_clicked() {
  ui->gifScreen->setText("");
  Data data;
  path_ = QFileDialog::getOpenFileName(nullptr, "Choose .obj", "../pics/",
                                       "OBJ (*.obj)");
  Errors err;
  if (!path_.isEmpty()) {
    ui->labelPath->setText(path_);
    controller_->InitData(data);
    std::string stdpath_ = path_.toStdString();
    controller_->ParseObjFile(stdpath_, data, err);
    if (err.err_ == ErrorCodes::kOk) {
      controller_->Normalize(data);
      ui->openGLWidget->data_ = data;
      ui->Vertex->setText(QString::number(data.vertex_.size() / 3));
      ui->Edge->setText(QString::number(data.edges_));
      ui->openGLWidget->update();
    } else {
      WriteError(err);
    }
  } else {
    err.err_ = ErrorCodes::kEmptyFile;
    WriteError(err);
  }
}

void View::on_pushButtonGif_clicked() {
  if (ModelSelected()) {
    gifName_ = QFileDialog::getSaveFileName(
        nullptr, "Сохранить gif", QDir::currentPath(), "Gif Files (*.gif)");
    if (!gifName_.isEmpty()) {
      ui->pushButtonGif->setDisabled(true);
      gif_ = new QGifImage;
      gif_->setDefaultDelay(100);
      timer_.setInterval(100);
      connect(&timer_, &QTimer::timeout, this, &View::CreateGifFrame);
      time_ = QTime::currentTime();
      timer_.start();
    }
  }
}

void View::CreateGifFrame() {
  QImage image = ui->openGLWidget->grabFramebuffer();
  gif_->addFrame(image);

  if (time_.msecsTo(QTime::currentTime()) >= 5000) {
    StopGifRecord();
  }
}

void View::StopGifRecord() {
  timer_.stop();
  gif_->save(gifName_);
  delete gif_;
  ui->pushButtonGif->setEnabled(true);
  ui->pushButtonGif->setText("GIF");
}

bool View::ModelSelected() {
  return (!ui->labelPath->text().isEmpty() && !ui->Edge->text().isEmpty());
}

void View::WriteError(Errors err) {
  if (err.err_ == ErrorCodes::kEmptyFile) {
    ui->labelPath->setText("Empty file");
  } else if (err.err_ == ErrorCodes::kWrongCountOfCoords) {
    ui->labelPath->setText("Wrong count of vertexes. Can't draw this obj");
  }
  ui->Edge->setText("");
  ui->Vertex->setText("");
}

void View::on_pushButtonPng_clicked() {
  if (ModelSelected()) {
    screenName_ = QFileDialog::getSaveFileName(
        nullptr, "Сохранить скриншот как ...", QDir::currentPath(),
        "*.bmp;; *.jpeg;; *.png");
    if (!screenName_.isEmpty()) {
      ui->openGLWidget->grabFramebuffer().save(screenName_);
    }
  }
}

}  // namespace s21
