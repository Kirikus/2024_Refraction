#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "RefractionModel.h"


struct stateStandartModelData
{
    std::vector<double> Heights;
    std::vector<double> Pressures;
    std::vector<double> Temperatures;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void launchCalculation();
  void stateStandartHandler();
  void stateStandartHandlerRev();

 private:
  Ui::MainWindow *ui;
  double h_a;
  double h_s;
  double r_refr_dir;
  double ns_unite;
  double ns_unite_rev;
  double ns_segm;
  double ns_segm_rev;
  QString refraction_model;
  QString refraction_model_reverse;
  QString atmosphere_model;
  QString atmosphere_model_reverse;

  stateStandartModelData ssm_direct;
  stateStandartModelData ssm_reversed;

  void extractDataFromGui();
  void loggingDataFromGui();
  void drawGraph(calculate_answer resultCalculation, float h_s_guess);
  stateStandartModelData fillFromFile(const QString &fileName);
  std::unique_ptr<AtmosphericModel> chooseAtmosphericModelDir ();
  std::unique_ptr<AtmosphericModel> chooseAtmosphericModelRev ();
  RefractionModel* chooseRefractionModelDir ();
  RefractionModel* chooseRefractionModelRev ();

};
#endif  // MAINWINDOW_H
