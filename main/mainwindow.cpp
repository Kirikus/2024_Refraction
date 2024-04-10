#include "mainwindow.h"

#include "./ui_mainwindow.h"

void setValidators(Ui::MainWindow *ui)
{
    ui->line_rad_earth_common->setValidator(new QIntValidator(5000000, 7000000));
    ui->line_Ha_common->setValidator(new QIntValidator(-1000, 27000));
    ui->line_hs_common->setValidator(new QIntValidator(-1000, 27000));
    ui->line_stepintegr_common->setValidator(new QDoubleValidator(0, 100, 2));
};



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->resize(900, this->height());

  setValidators(ui);

  connect(ui->main_launch_button, &QPushButton::clicked, this, &MainWindow::launchCalculation);
  connect(ui->action_run_calculate, &QAction::triggered, this, &MainWindow::launchCalculation);

  ui->graph->hide();
}

void MainWindow::extractDataFromGui()
{
    radius_earth = ui->line_rad_earth_common->text().toDouble();
    integr_step = ui->line_stepintegr_common->text().toDouble();
    h_a = ui->line_Ha_common->text().toDouble();
    h_s = ui->line_hs_common->text().toDouble();
    r_refr_dir = ui->line_r_refr->text().toDouble();
    r_refr_rev = ui->line_r_refr_rev->text().toDouble();
    psi_d_refr_rev = ui->line_psid_refr_rev->text().toDouble();
    ns_unite = ui->line_Ns_unite->text().toDouble();
    ns_unite_rev = ui->line_Ns_unite_rev->text().toDouble();
    ns_segm = ui->line_Ns_segm->text().toDouble();
    ns_segm_rev = ui->line_Ns_segm_rev->text().toDouble();
    n1_segm = ui->line_N1_segm->text().toDouble();
    n1_segm_rev = ui->line_N1_segm_rev->text().toDouble();
    nb_unite = ui->line_Nb_unite->text().toDouble();
    nb_unite_rev = ui->line_Nb_unite_rev->text().toDouble();
    hb_unite = ui->line_Hb_unite->text().toDouble();
    hb_unite_rev = ui->line_Hb_unite_rev->text().toDouble();
    hlayer_unite = ui->line_Hlayer_unite->text().toDouble();
    hlayer_unite_rev = ui->line_Hlayer_unite_rev->text().toDouble();


    refraction_model = ui->comboBox->currentText();
    refraction_model_reverse = ui->comboBox_7->currentText();
    atmosphere_model = ui->comboBox_2->currentText();
    atmosphere_model_reverse = ui->comboBox_8->currentText();

};


void MainWindow::loggingDataFromGui()
{
    ui->LogText->append("---------------\n---------------");
    ui->LogText->append(QString("refraction_model: " + refraction_model));
    ui->LogText->append(QString("refraction_model_reverse: " + refraction_model_reverse));
    ui->LogText->append(QString("ratmosphere_model: " + atmosphere_model));
    ui->LogText->append(QString("atmosphere_model_reverse: " + atmosphere_model_reverse + "\n"));
    ui->LogText->append(QString("radius_earth: " + QString::number(radius_earth, 'f', 1)));
    ui->LogText->append(QString("integr_step: " + QString::number(integr_step, 'f', 1)));
    ui->LogText->append(QString("h_a: " + QString::number(h_a, 'f', 1)));
    ui->LogText->append(QString("h_s: " + QString::number(h_s, 'f', 1)));
    ui->LogText->append(QString("r_refr_dir: " + QString::number(r_refr_dir, 'f', 1)));
    ui->LogText->append(QString("r_refr_rev: " + QString::number(r_refr_rev, 'f', 1)));
    ui->LogText->append(QString("psi_d_refr_rev: " + QString::number(psi_d_refr_rev, 'f', 1)));
    ui->LogText->append(QString("ns_unite: " + QString::number(ns_unite, 'f', 1)));
    ui->LogText->append(QString("ns_unite_rev: " + QString::number(ns_unite_rev, 'f', 1)));
    ui->LogText->append(QString("ns_segm: " + QString::number(ns_segm, 'f', 1)));
    ui->LogText->append(QString("ns_segm_rev: " + QString::number(ns_segm_rev, 'f', 1)));
    ui->LogText->append(QString("n1_segm: " + QString::number(n1_segm, 'f', 1)));
    ui->LogText->append(QString("n1_segm_rev: " + QString::number(n1_segm_rev, 'f', 1)));
    ui->LogText->append(QString("nb_unite: " + QString::number(nb_unite, 'f', 1)));
    ui->LogText->append(QString("nb_unite_rev: " + QString::number(nb_unite_rev, 'f', 1)));
    ui->LogText->append(QString("hb_unite: " + QString::number(hb_unite, 'f', 1)));
    ui->LogText->append(QString("hb_unite_rev: " + QString::number(hb_unite_rev, 'f', 1)));
    ui->LogText->append(QString("hlayer_unite: " + QString::number(hlayer_unite, 'f', 1)));
    ui->LogText->append(QString("hlayer_unite_rev: " + QString::number(hlayer_unite_rev, 'f', 1)));
};


void MainWindow::drawGraph()
{
    // Получаем указатель на QCustomPlot
    QCustomPlot *customPlot = ui->graph;

    // Очищаем предыдущие графики
    customPlot->clearGraphs();

    double x_rls = 0;
    double x_target = qSqrt(r_refr_dir*r_refr_dir - (h_a-h_s)*(h_a-h_s)); // Координата цели

    // Устанавливаем область отображения графика
    customPlot->xAxis->setRange(x_rls - std::max(x_rls, x_target)/5 - 1,
                                x_target + std::max(x_rls, x_target)/5 +1); // Учитываем отступы
    customPlot->yAxis->setRange(0, 1.25 * std::max(h_a, h_s) + 1); // Выбираем максимальное значение по высоте

    // Создаем график для точек РЛС
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::black));
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 8));
    customPlot->graph(0)->addData(x_rls, h_a);

    // Создаем график для точек цели
    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red));
    customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 8));
    customPlot->graph(1)->addData(x_target, h_s);

    // Создаем график для отрезка между точками
    customPlot->addGraph();
    customPlot->graph(2)->setPen(QPen(Qt::blue));
    customPlot->graph(2)->setLineStyle(QCPGraph::lsLine);
    customPlot->graph(2)->addData(QVector<double>() << x_rls << x_target, QVector<double>() << h_a << h_s);

    // Перерисовываем график
    customPlot->replot();

    customPlot->setVisible(true);
    customPlot->resize(80, customPlot->height());
}


void MainWindow::launchCalculation()
{
    extractDataFromGui();
    loggingDataFromGui();
    drawGraph();

};


MainWindow::~MainWindow() { delete ui; }

