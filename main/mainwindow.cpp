#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->line_rad_earth_common->setValidator(new QIntValidator(5000000, 7000000, this));
  ui->line_Ha_common->setValidator(new QIntValidator(-1000, 27000, this));
  ui->line_hs_common->setValidator(new QIntValidator(-1000, 27000, this));
  ui->line_stepintegr_common->setValidator(new QDoubleValidator(0, 100, 2, this));
}

MainWindow::~MainWindow() { delete ui; }
