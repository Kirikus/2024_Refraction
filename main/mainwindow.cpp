#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setValidators(ui);

  connect(ui->main_launch_button, &QPushButton::clicked, this, &MainWindow::launchCalculation);
  connect(ui->action_run_calculate, &QAction::triggered, this, &MainWindow::launchCalculation);
}

void MainWindow::launchCalculation()
{
    QString radius_earth = ui->line_rad_earth_common->text();
    QString integr_step = ui->line_stepintegr_common->text();
    QString h_a = ui->line_Ha_common->text();
    QString h_s = ui->line_hs_common->text();
    QString r_refr_dir = ui->line_r_refr->text();
    QString r_refr_rev = ui->line_r_refr_rev->text();
    QString psi_d_refr_rev = ui->line_psid_refr_rev->text();
    QString ns_unite = ui->line_Ns_unite->text();
    QString ns_unite_rev = ui->line_Ns_unite_rev->text();
    QString ns_segm = ui->line_Ns_segm->text();
    QString ns_segm_rev = ui->line_Ns_segm_rev->text();
    QString n1_segm = ui->line_N1_segm->text();
    QString n1_segm_rev = ui->line_N1_segm_rev->text();
    QString nb_unite = ui->line_Nb_unite->text();
    QString nb_unite_rev = ui->line_Nb_unite_rev->text();
    QString hb_unite = ui->line_Hb_unite->text();
    QString hb_unite_rev = ui->line_Hb_unite_rev->text();
    QString hlayer_unite = ui->line_Hlayer_unite->text();
    QString hlayer_unite_rev = ui->line_Hlayer_unite_rev->text();

    QString refraction_model = ui->comboBox->currentText();
    QString refraction_model_reverse = ui->comboBox_7->currentText();
    QString atmosphere_model = ui->comboBox_2->currentText();
    QString atmosphere_model_reverse = ui->comboBox_8->currentText();

    ui->LogText->append("---------------\n---------------");
    ui->LogText->append(QString("refraction_model: " + refraction_model));
    ui->LogText->append(QString("refraction_model_reverse: " + refraction_model_reverse));
    ui->LogText->append(QString("ratmosphere_model: " + atmosphere_model));
    ui->LogText->append(QString("atmosphere_model_reverse: " + atmosphere_model_reverse + "\n"));
    ui->LogText->append(QString("radius_earth: " + radius_earth));
    ui->LogText->append(QString("integr_step: " + integr_step));
    ui->LogText->append(QString("h_a: " + h_a));
    ui->LogText->append(QString("h_s: " + h_s));
    ui->LogText->append(QString("r_refr_dir: " + r_refr_dir));
    ui->LogText->append(QString("r_refr_rev: " + r_refr_rev));
    ui->LogText->append(QString("psi_d_refr_rev: " + psi_d_refr_rev));
    ui->LogText->append(QString("ns_unite: " + ns_unite));
    ui->LogText->append(QString("ns_unite_rev: " + ns_unite_rev));
    ui->LogText->append(QString("ns_segm: " + ns_segm));
    ui->LogText->append(QString("ns_segm_rev: " + ns_segm_rev));
    ui->LogText->append(QString("n1_segm: " + n1_segm));
    ui->LogText->append(QString("n1_segm_rev: " + n1_segm_rev));
    ui->LogText->append(QString("nb_unite: " + nb_unite));
    ui->LogText->append(QString("nb_unite_rev: " + nb_unite_rev));
    ui->LogText->append(QString("hb_unite: " + nb_unite));
    ui->LogText->append(QString("hb_unite_rev: " + nb_unite_rev));
    ui->LogText->append(QString("hlayer_unite: " + nb_unite));
    ui->LogText->append(QString("hlayer_unite_rev: " + nb_unite_rev));
};


MainWindow::~MainWindow() { delete ui; }


void setValidators(Ui::MainWindow * ui)
{
    ui->line_rad_earth_common->setValidator(new QIntValidator(5000000, 7000000));
    ui->line_Ha_common->setValidator(new QIntValidator(-1000, 27000));
    ui->line_hs_common->setValidator(new QIntValidator(-1000, 27000));
    ui->line_stepintegr_common->setValidator(new QDoubleValidator(0, 100, 2));
};
