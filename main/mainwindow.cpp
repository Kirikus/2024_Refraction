#include "mainwindow.h"

#include "./ui_mainwindow.h"

void setValidators(Ui::MainWindow *ui)
{
    ui->line_Ha_common->setValidator(new QIntValidator(-1000, 27000));
    ui->line_hs_common->setValidator(new QIntValidator(-1000, 27000));
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QScreen *screen = QGuiApplication::primaryScreen();
  QRect  screenGeometry = screen->geometry();
  this->resize(screenGeometry.width() * 0.75, screenGeometry.height() * 0.95);

  setValidators(ui);

  connect(ui->main_launch_button, &QPushButton::clicked, this, &MainWindow::launchCalculation);
  connect(ui->action_run_calculate, &QAction::triggered, this, &MainWindow::launchCalculation);
  connect(ui->file_dialog_button_gost, &QPushButton::clicked, this, &MainWindow::stateStandartHandler);
  connect(ui->file_gialog_button_gost_4, &QPushButton::clicked, this, &MainWindow::stateStandartHandlerRev);

  ui->graph->hide();
}

void MainWindow::extractDataFromGui()
{
    h_a = ui->line_Ha_common->text().toDouble();
    h_s = ui->line_hs_common->text().toDouble();
    r_refr_dir = ui->line_r_refr->text().toDouble();
    ns_unite = ui->line_Ns_unite->text().toDouble();
    ns_unite_rev = ui->line_Ns_unite_rev->text().toDouble();
    ns_segm = ui->line_Ns_segm->text().toDouble();
    ns_segm_rev = ui->line_Ns_segm_rev->text().toDouble();


    refraction_model = ui->comboBox->currentText();
    refraction_model_reverse = ui->comboBox_7->currentText();
    atmosphere_model = ui->comboBox_2->currentText();
    atmosphere_model_reverse = ui->comboBox_8->currentText();
    std::cout<<"extracting: OK\n";

};


void MainWindow::loggingDataFromGui()
{
    ui->LogText->append("---------------\n---------------");
    ui->LogText->append(QString("refraction_model: " + refraction_model));
    ui->LogText->append(QString("refraction_model_reverse: " + refraction_model_reverse));
    ui->LogText->append(QString("ratmosphere_model: " + atmosphere_model));
    ui->LogText->append(QString("atmosphere_model_reverse: " + atmosphere_model_reverse + "\n"));
    ui->LogText->append(QString("h_a: " + QString::number(h_a, 'f', 1)));
    ui->LogText->append(QString("h_s: " + QString::number(h_s, 'f', 1)));
    ui->LogText->append(QString("r_refr_dir: " + QString::number(r_refr_dir, 'f', 1)));
    ui->LogText->append(QString("ns_unite: " + QString::number(ns_unite, 'f', 1)));
    ui->LogText->append(QString("ns_unite_rev: " + QString::number(ns_unite_rev, 'f', 1)));
    ui->LogText->append(QString("ns_segm: " + QString::number(ns_segm, 'f', 1)));
    ui->LogText->append(QString("ns_segm_rev: " + QString::number(ns_segm_rev, 'f', 1)));
    std::cout<<"logging: OK\n";
};


void MainWindow::drawGraph(calculate_answer resultCalculationDirect, float h_s_guess)
{
    // Получаем указатель на QCustomPlot
    QCustomPlot *customPlot = ui->graph;

    // Очищаем предыдущие графики
    customPlot->clearGraphs();

    double x_rls = 0;
    double d = resultCalculationDirect.d;
    double x_target = qSqrt(d*d - (h_a-h_s)*(h_a-h_s)); // Координата цели

    // Устанавливаем область отображения графика
    customPlot->xAxis->setRange(x_rls - std::max(x_rls, x_target)/5 - 1,
                                x_target + std::max(x_rls, x_target)/5 +1); // Учитываем отступы
    customPlot->yAxis->setRange(std::min(h_a, h_s) - 0.5*fabs(std::min(h_a, h_s)), 1.25 * std::max(h_a, h_s) + 1); // Выбираем максимальное значение по высоте

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

    // Находим координаты конечной точки отрезка с длиной 0.1 d и углом psi_d от точки РЛС
    double dx_rls = x_target - x_rls;
    double dy_rls = h_s - h_a;
    double x_rls_end = x_rls + 0.1*(dx_rls*std::cos(resultCalculationDirect.psi_d) - dy_rls * std::sin(resultCalculationDirect.psi_d));
    double h_a_end = h_a + 0.1*(dx_rls*std::sin(resultCalculationDirect.psi_d) + dy_rls * std::cos(resultCalculationDirect.psi_d));
    ui->LogText->append(QString::number(dx_rls) + " " + QString::number(dy_rls));
    ui->LogText->append(QString::number(resultCalculationDirect.d));

    // Находим координаты конечной точки отрезка с длиной 0.1 d и углом psi_g от точки цели
    double dx_target = x_rls - x_target;
    double dy_target = h_a - h_s;
    double x_target_end = x_target + 0.1*(dx_target*std::cos(resultCalculationDirect.psi_g) + dy_target * std::sin(resultCalculationDirect.psi_g));
    double h_s_end = h_s + 0.1*(-dx_target*std::sin(resultCalculationDirect.psi_g) + dy_target * std::cos(resultCalculationDirect.psi_g));
    ui->LogText->append(QString::number(dx_target) + " " + QString::number(dy_target));

    // Создаем график для отрезков с углами psi_d и psi_g
    customPlot->addGraph();
    customPlot->graph(3)->setPen(QPen(Qt::green));
    customPlot->graph(3)->setLineStyle(QCPGraph::lsLine);
    customPlot->graph(3)->addData(QVector<double>() << x_rls << x_rls_end, QVector<double>() << h_a << h_a_end);

    customPlot->addGraph();
    customPlot->graph(4)->setPen(QPen(Qt::black));
    customPlot->graph(4)->setLineStyle(QCPGraph::lsLine);
    customPlot->graph(4)->addData(QVector<double>() << x_target << x_target_end, QVector<double>() << h_s << h_s_end);


    // Создаем график для расчётных точек цели
    customPlot->addGraph();
    customPlot->graph(5)->setPen(QPen(Qt::blue));
    customPlot->graph(5)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(5)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 8));
    customPlot->graph(5)->addData(x_target, h_s_guess);

    // Перерисовываем график
    customPlot->replot();

    customPlot->setVisible(true);

    QList sizes = {1, 1};
    ui->splitter_2->setSizes(sizes);
}


void MainWindow::launchCalculation()
{
    extractDataFromGui();
    loggingDataFromGui();

    RefractionModel* refractionModel_dir=chooseRefractionModelDir();
    RefractionModel* refractionModel_rev=chooseRefractionModelRev();


    calculate_answer resultCalculationDirect = refractionModel_dir->calculate(h_a, h_s, r_refr_dir);
    float d = resultCalculationDirect.d;
    float psi_d = resultCalculationDirect.psi_d;
    std::cout<<h_a<<" "<<h_s<<" "<<d<<" "<<psi_d<<"\n";
    float h_s_guess = refractionModel_rev->reverse(h_a, h_s, d, psi_d);
    ui->ResultsText->clear();
    ui->ResultsText->append("Input data: \n    h_a = " + QString::number(h_a) +
                            "\n    h_s = " + QString::number(h_s) +
                            "\n    R = " + QString::number(r_refr_dir));
    ui->ResultsText->append("Direct task result: \n    psi_d = " +
                         QString::number(resultCalculationDirect.psi_d) + "\n    d = " +
                         QString::number(resultCalculationDirect.d) + "\n    psi_g = " +
                         QString::number(resultCalculationDirect.psi_g) + "\n" +
                         "Reversed task result: \n    h_guess = " +
                         QString::number(h_s_guess)
                        );
    drawGraph(resultCalculationDirect, h_s_guess);

    ui->VerdictLine->setText("OK");

};

std::unique_ptr<AtmosphericModel> MainWindow::chooseAtmosphericModelDir()
{
    if(atmosphere_model == "сегментированная модель")
    {
        if(ns_segm<50)
        {
        SegmentedModel* model = new SegmentedModel(324.8, h_s);
        std::unique_ptr<AtmosphericModel> atmosphereModel(model);
        return atmosphereModel;
        }

        else
        {
        SegmentedModel* model = new SegmentedModel(ns_segm, h_s);
        std::unique_ptr<AtmosphericModel> atmosphereModel(model);
        return atmosphereModel;
        }
    }
    else if(atmosphere_model_reverse == "модель ГОСТ 4401-81")
    {
        CubicSpline cs_p = CubicSpline(ssm_direct.Heights, ssm_direct.Pressures);
        Linear l_t = Linear(ssm_direct.Heights, ssm_direct.Temperatures);
        std::unique_ptr<AtmosphericModel> atmosphereModel(new GOSTModel<CubicSpline, Linear>(cs_p, l_t));
        return atmosphereModel;
    }
    else
    {
        ExponentialModel* model = new ExponentialModel(ns_unite, h_s);
        if(ns_unite<50)
            model->Ns = 324.8;
        std::unique_ptr<AtmosphericModel> atmosphereModel(model);
        return atmosphereModel;
    }
};

std::unique_ptr<AtmosphericModel> MainWindow::chooseAtmosphericModelRev()
{
    if(atmosphere_model_reverse == "сегментированная модель")
    {
        if(ns_segm_rev<50)
        {
        SegmentedModel* model = new SegmentedModel(324.8, h_s);
        std::unique_ptr<AtmosphericModel> atmosphereModel_rev(model);
        return atmosphereModel_rev;
        }

        else
        {
        SegmentedModel* model = new SegmentedModel(ns_segm_rev, h_s);
        std::unique_ptr<AtmosphericModel> atmosphereModel_rev(model);
        return atmosphereModel_rev;
        }
    }
    else if(atmosphere_model_reverse == "модель ГОСТ 4401-81")
    {
        if (!ssm_reversed.Heights[0])
            ssm_reversed=ssm_direct;
        CubicSpline cs_p = CubicSpline(ssm_reversed.Heights, ssm_reversed.Pressures);
        Linear l_t = Linear(ssm_reversed.Heights, ssm_reversed.Temperatures);
        std::unique_ptr<AtmosphericModel> atmosphereModel_rev(new GOSTModel<CubicSpline, Linear>(cs_p, l_t));
        return atmosphereModel_rev;
    }
    else
    {
        ExponentialModel* model = new ExponentialModel(ns_unite_rev, h_s);
        if(ns_unite_rev<50)
            model->Ns = 324.8;
        std::unique_ptr<AtmosphericModel> atmosphereModel_rev(model);
        return atmosphereModel_rev;
    }
};

RefractionModel* MainWindow::chooseRefractionModelDir()
{
    if(refraction_model == "эфф.радиус 4/3 (прямая)")
    {
        FourThirds* refractionModel_dir = new FourThirds;
        return refractionModel_dir;
    }
    else if(refraction_model == "ср.знач. k (прямая)")
    {
        AverageK* refractionModel_dir = new AverageK;
        refractionModel_dir->SetAtmosphere(chooseAtmosphericModelDir());
        return refractionModel_dir;
    }
    else if(refraction_model == "ср.зн. R кривизны (прямая)")
    {
        AverageP* refractionModel_dir = new AverageP;
        refractionModel_dir->SetAtmosphere(chooseAtmosphericModelDir());
        return refractionModel_dir;
    }
    else
    {
        GeometricLine* refractionModel_dir = new GeometricLine;
        return refractionModel_dir;
    }
};

RefractionModel* MainWindow::chooseRefractionModelRev()
{
    if(refraction_model_reverse == "эфф.радиус 4/3 (прямая)")
    {
        FourThirds* refractionModel_rev = new FourThirds;
        return refractionModel_rev;
    }
    else if(refraction_model_reverse == "ср.знач. k (прямая)")
    {
        AverageK* refractionModel_rev = new AverageK;
        refractionModel_rev->SetAtmosphere(chooseAtmosphericModelRev());
        return refractionModel_rev;
    }
    else if(refraction_model_reverse == "ср.зн. R кривизны (прямая)")
    {
        AverageP* refractionModel_rev = new AverageP;
        refractionModel_rev->SetAtmosphere(chooseAtmosphericModelRev());
        return refractionModel_rev;
    }
    else
    {
        GeometricLine* refractionModel_rev = new GeometricLine;
        return refractionModel_rev;
    }
};

stateStandartModelData MainWindow::fillFromFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error opening file" << filename;
        ui->VerdictLine->setText("Error opening file");
    }

    stateStandartModelData data;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        qDebug()<<"line"<<line;
        QStringList values = line.split(",");

        if (values.size() == 3)
        {
            data.Heights.push_back(values[0].toDouble());
            data.Pressures.push_back(values[1].toDouble());
            data.Temperatures.push_back(values[2].toDouble());
            qDebug()<<"here"<<'\n';
        }
        else if(line!="")
        {
            qDebug() << "Invalid format in file" << filename <<values.size()<<"\n";
            ui->VerdictLine->setText("Invalid format in file");
        }
    }

    file.close();
    return data;
}

void MainWindow::stateStandartHandler()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Table"), "/home/", tr("Text Files (*.txt *.csv *.xlsx, *.odf)"));
    ui->LogText->append("Direct task state standart model file: "+ fileName);
    ui->file_dialog_gost->setText(fileName);
    stateStandartModelData ssm_direct = fillFromFile(fileName);
    ui->LogText->append("first line of direct file: "
                      + QString::number(ssm_direct.Heights[0]) + ", "
                      + QString::number(ssm_direct.Pressures[0]) + ", "
                      + QString::number(ssm_direct.Temperatures[0]));
};

void MainWindow::stateStandartHandlerRev()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Table"), "/home/", tr("Text Files (*.txt *.csv *.xlsx, *.odf)"));
    ui->LogText->append("Reversed task state standart model file: "+ fileName);
    ui->file_dialog_gost_4->setText(fileName);
    stateStandartModelData ssm_reversed = fillFromFile(fileName);
    ui->LogText->append("first line of reversed file: "
                      + QString::number(ssm_reversed.Heights[0]) + ", "
                      + QString::number(ssm_reversed.Pressures[0]) + ", "
                      + QString::number(ssm_reversed.Temperatures[0]));
};


MainWindow::~MainWindow() { delete ui; }

