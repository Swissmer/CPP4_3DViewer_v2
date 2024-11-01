#ifndef VIEW_H
#define VIEW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QTime>
#include <QTimer>

#include "../QtGifImage/src/gifimage/qgifimage.h"
#include "../controller/controller.h"
#include "../pattern/pattern_command.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT

 public:
  // main methods
  View(QWidget *parent = nullptr, Controller *controller = nullptr);
  ~View();

 private slots:
  // style
  void on_ScrollBarDotSize_valueChanged(int value);
  void on_ScrollBarLineSize_valueChanged(int value);
  void on_radioButtonOrtho_clicked();
  void on_radioButtonPerspective_clicked();
  void on_pushButtonLineColor_clicked();
  void on_pushButtonDotColor_clicked();
  void on_pushButtonBackgroundColor_clicked();
  void on_radioButtonSolid_clicked();
  void on_radioButtonDotted_clicked();
  void on_radioButtonWIthoutDot_clicked();
  void on_radioButtonRoundDot_clicked();
  void on_radioButtonSquareDot_clicked();

  // transform
  void on_pushButtonScaleMinus_clicked();
  void on_pushButtonScalePlus_clicked();
  void on_pushButtonMoveXMinus_clicked();
  void on_pushButtonMoveXPlus_clicked();
  void on_pushButtonMoveYMinus_clicked();
  void on_pushButtonMoveYPlus_clicked();
  void on_pushButtonMoveZMinus_clicked();
  void on_pushButtonMoveZPlus_clicked();
  void on_pushButtonRotateXMinus_clicked();
  void on_pushButtonRotateXPlus_clicked();
  void on_pushButtonRotateYMinus_clicked();
  void on_pushButtonRotateYPlus_clicked();
  void on_pushButtonRotateZMinus_clicked();
  void on_pushButtonRotateZPlus_clicked();
  //  void on_ScrollBarRotateX_valueChanged(int value);
  //  void on_ScrollBarRotateY_valueChanged(int value);
  //  void on_ScrollBarRotateZ_valueChanged(int value);

  // other
  void on_uploadObjFile_clicked();
  void CreateGifFrame();
  void StopGifRecord();
  bool ModelSelected();
  void WriteError(Errors err);
  void on_pushButtonPng_clicked();
  void on_pushButtonGif_clicked();

 private:
  // main variables
  Ui::View *ui;
  Controller *controller_;
  //  PathInvoker invoker_;
  //  MoveInvoker moveInvoker_;

  // other variables
  QGifImage *gif_;
  QString path_;
  QTimer timer_;
  QTime time_;
  QString gifName_;
  QString screenName_;
};
}  // namespace s21

#endif  // VIEW_H
