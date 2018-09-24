#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(ARX *arx, PID *pid, Generator *generator, Config *conf, ARX *paralelArx, QWidget *parent) :
    s_arx(arx),
    s_pid(pid),
    s_generator(generator),
    s_conf(conf),
    s_paralelArx(paralelArx),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    s_dA = s_arx->GetAdegree();
    s_dB = s_arx->GetBdegree();
    int k = s_arx->Getk();

    s_id = new Identify(s_dA,s_dB,k);
    s_regLoop = new RegulationLoop(s_arx, s_pid, s_generator, s_paralelArx, s_id, "PID" );


    s_plot1Delegate = new PlotDelegate(ui, this);
    s_plot2Delegate = new PlotDelegate(ui, this);
    s_plot3Delegate = new PlotDelegate(ui, this);


    s_arx->RegisterObserver(s_plot1Delegate);
    //s_arx->RegisterObserver(s_p);
    s_regLoop->RegisterObserver(s_plot3Delegate);

    ui->w_changeKr->setValue(s_conf->kr);
    ui->w_changeTi->setValue(s_conf->Ti);
    ui->w_changeTd->setValue(s_conf->Td);
    ui->w_changeN->setValue(s_conf->N);
    ui->w_changeb->setValue(s_conf->b);
    ui->w_changeH->setValue(s_conf->H);
    ui->w_changeL->setValue(s_conf->L);
    ui->w_changeAlpha->setValue(s_conf->alpha);
    ui->w_changeRo->setValue(s_conf->ro);
    ui->w_changeMax_u->setValue(conf->max_u);
    ui->w_changeMin_u->setValue(conf->min_u);

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateView()));
    timer->start(1000);
    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(on_startButton_clicked(bool)));
    connect(ui->stepButton, SIGNAL(clicked(bool)), this, SLOT(on_stepButton_clicked(bool)));
    connect(ui->stopButton, SIGNAL(clicked(bool)), this, SLOT(on_stopButton_clicked(bool)));
    connect(ui->addStep, SIGNAL(clicked(bool)), this, SLOT(on_addStep_clicked()));
    connect(ui->addRectangle, SIGNAL(clicked(bool)), this, SLOT(on_addRectangle_clicked()));
    connect(ui->addSine, SIGNAL(clicked(bool)), this, SLOT(on_addSine_clicked()));
    connect(ui->addTriangle, SIGNAL(clicked(bool)), this, SLOT(on_addTriangle_clicked()));
    connect(ui->addNoise, SIGNAL(clicked(bool)), this, SLOT(on_addNoise_clicked(bool)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalSlider_valueChanged(int)));
    //connect(ui->w_changeKr, SIGNAL(valueChanged(double)), this, SLOT(on_w_changeKr_valueChanged(double)));
    connect(ui->changeRegulatorButton, SIGNAL(clicked(bool)), this, SLOT(on_changeRegulatorButton_clicked(bool)));
    connect(ui->changeRegulatorParametersButton, SIGNAL(clicked(bool)), this, SLOT(on_changeRegulatorParametersButton_clicked(bool)));
    connect(ui->restartButton, SIGNAL(clicked(bool)), this, SLOT(on_restartButton_clicked(bool)));
    connect(ui->resetSetPoint, SIGNAL(clicked(bool)), this, SLOT(on_resetSetPoint_clicked(bool)));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete s_arx;
    delete s_generator;
    delete s_plot1Delegate;
    delete s_plot2Delegate;
    delete s_plot3Delegate;
    delete ui;
    delete s_id;
}

void MainWindow::updateView()
{
    //s_p->time=time;

    if (MainWindow::time>s_arx->GetSwitchTime())
    {
        s_arx->UpdateParameters();
        s_paralelArx->UpdateParameters();
    }
    if (restarted)
    {
        s_arx->ResetParameters();
        s_paralelArx->ResetParameters();
        restarted = false;
        ui->Plot1->yAxis->setRange(-10, 10);
        ui->Plot1->replot();
    }
    if (!step && start)
    {
        if (MainWindow::time ==0)
        {
            currentOutput=s_arx->Simulate_step(0);
            //s_paralelArx->Simulate_step(0);
        }
        else
        {
            //s_arx->Simulate_step(0); //0 because all logic is present inside Simulate_step()

            currentOutput = s_regLoop -> Simulate_step(currentOutput);
            deque<double> U = s_arx->GetU();
            deque<double> Y = s_arx->GetNewestY();

            s_id->Identify_step(U[0],Y[0]);
            A = s_id->Get_A();
            B = s_id->Get_B();

            theta = s_id->Get_param();
        }
        if (time>0) DisplayIdentParams();
        //PlotSP();
        MainWindow::time++;
        s_regLoop->time = time;
    }
}

void MainWindow::updateViewStep()
{
    //s_p->time=time;
    if (MainWindow::time>s_arx->GetSwitchTime())
        s_arx->UpdateParameters();
    if (restarted)
    {
        s_arx->ResetParameters();
        restarted = false;
        ui->Plot1->yAxis->setRange(-10, 10);
        ui->Plot1->replot();
    }
    currentOutput = s_regLoop -> Simulate_step(currentOutput);
    deque<double> U = s_arx->GetU();
    deque<double> Y = s_arx->GetNewestY();

    s_id->Identify_step(U[0],Y[0]);
    //theta = s_id->Get_param();
    if (time>0) DisplayIdentParams();
    //PlotSP();
    MainWindow::time++;
    s_regLoop->time = MainWindow::time;
}

void MainWindow::PlotSP()
{
    this->s_TimeVec.push_back(time);
    this->s_SPVec.push_back(s_regLoop->GetSP());
    this->ui->Plot1->graph(1)->setData(this->s_TimeVec,this->s_SPVec);
    this->ui->Plot1->yAxis->rescale();

    if (s_TimeVec.size()>50)
    {
        this->ui->Plot1->xAxis->setRange(s_TimeVec.size()-50, s_TimeVec.size());
    }

    this->ui->Plot1->replot();
    return;
}

void MainWindow::DisplayIdentParams()
{
    QString idParams = "";
    for (int i=0; i<=s_dB;i++)
    {
        idParams = idParams.append(stringToQString(doubleToString(theta.at(i))) + " ");
    }
    ui->textBrowser_B_ident_coeffs->setText(idParams);
    idParams = "";
    for (int i=s_dB+1; i<=s_dA+s_dB;i++)
    {
        idParams = idParams.append(stringToQString(doubleToString(theta.at(i))) + " ");
    }
    ui->textBrowser_A_ident_coeffs->setText(idParams);
}


void MainWindow::on_startButton_clicked(bool checked)
{
    start = true;
    step = false;
}

void MainWindow::on_stepButton_clicked(bool checked)
{
    start = true;
    step = true;
    updateViewStep();
}

void MainWindow::on_stopButton_clicked(bool checked)
{
    start = false;
    step = false;
    currentOutput = 0;
    //time = 0;
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    MainWindow::timer->start(value);
}

QString MainWindow::stringToQString(string str)
{
    return QString::fromStdString(str);
}

string MainWindow::doubleToString(double val)
{
    std::ostringstream strs;
    strs << val;
    std::string str = strs.str();
    return str;
}

void MainWindow::on_addStep_clicked()
{
    s_generator->RegisterSignal(new Step(ui->w_stepChangeA->value()));
    string str = doubleToString(ui->w_stepChangeA->value());
    s_generator->crp->WriteToFile("<step><value>" + str + "</value></step>\n");// + ui->w_stepChangeA->value() +
}

void MainWindow::on_addRectangle_clicked()
{
    ui->w_rectangleChangeA->value();
    s_generator->RegisterSignal(new RectWave(ui->w_rectangleChangeA->value(), ui->w_rectangleChangeInterval->value(),ui->w_rectangleChangeInterval->value()));
    string str = doubleToString(ui->w_rectangleChangeA->value());
    s_generator->crp->WriteToFile("<rectangle><value>" + str + "</value></rectangle>\n");
}

void MainWindow::on_addSine_clicked()
{
    s_generator->RegisterSignal(new SineWave(ui->w_sineChangeA->value(), ui->w_sineChangeInterval->value()));
    string str = doubleToString(ui->w_sineChangeA->value());
    s_generator->crp->WriteToFile("<sine><value>" + str + "</value></sine>\n");
}

void MainWindow::on_addTriangle_clicked()
{
    s_generator->RegisterSignal(new TriaWave(ui->w_triangleChangeA->value(), ui->w_triangleChangeInterval->value()));
    string str = doubleToString(ui->w_triangleChangeA->value());
    s_generator->crp->WriteToFile("<triangle><value>" + str + "</value></triangle>\n");
}

void MainWindow::on_addNoise_clicked(bool checked)
{
    s_generator->RegisterSignal(new NoiseWave(ui->w_noiseChangeVariance->value()));
    string str = doubleToString(ui->w_noiseChangeVariance->value());
    s_generator->crp->WriteToFile("<noise><value>" + str + "</value></noise>\n");
}




void MainWindow::on_changeRegulatorParametersButton_clicked(bool checked)
{
    timer->start(10000);
    s_regLoop->ChangeRegParameters(ui->w_changeKr->value(),ui->w_changeTi->value(),ui->w_changeTd->value(),
                                   ui->w_changeN->value(), ui->w_changeb->value(), ui->w_changeMax_u->value(),
                                   ui->w_changeMin_u->value(), ui->w_changeAlpha->value(), ui->w_changeH->value(), ui->w_changeL->value(), ui->w_changeRo->value());
    timer->start(1000);
}



void MainWindow::on_changeRegulatorButton_clicked(bool checked)
{
     timer->start(10000);
    try
    {
        s_regLoop->ChangeRegulator(ui->regType->currentText());
        on_changeRegulatorParametersButton_clicked(true);
        ui->currentRegulator->setText(ui->regType->currentText());
    }
    catch (...)
    {
        //Exception handling
    }
    timer->start(1000);
}

void MainWindow::on_restartButton_clicked(bool checked)
{
    delete s_arx;
    delete s_conf;
    delete s_generator;
    delete s_pid;
    s_arx = new ARX();
    s_paralelArx = new ARX();
    s_conf = new Config("E:\\Polibuda\\!VIII Sem\\PSS\\Laboratorium\\PSS_Proj\\Config\\PSS_Config.xml");
    s_generator = new Generator("E:\\Polibuda\\!VIII Sem\PSS\\Laboratorium\\PSS_Proj\\Config\\PSS2_Config.xml");
    s_pid =  new PID(s_conf->kr, s_conf->Ti, s_conf->Td, s_conf->N, s_conf->b, s_conf->max_u, s_conf->min_u, s_generator);

    s_regLoop->UnregisterObserver(s_plot3Delegate);
    //MainWindow(s_arx, s_pid, s_generator, s_conf, s_paralelArx);
    ui->setupUi(this);



    s_dA = s_arx->GetAdegree();
    s_dB = s_arx->GetBdegree();
    int k = s_arx->Getk();

    delete s_id;
    s_id = new Identify(s_dA,s_dB,k);
    //delete s_regLoop;
    s_regLoop = new RegulationLoop(s_arx, s_pid, s_generator, s_paralelArx, s_id, "PID" );


    delete s_plot1Delegate;
    s_plot1Delegate = new PlotDelegate(ui, this);
    delete s_plot2Delegate;
    s_plot2Delegate = new PlotDelegate(ui, this);
    delete s_plot3Delegate;
    s_plot3Delegate = new PlotDelegate(ui, this);


    s_arx->RegisterObserver(s_plot1Delegate);
    //s_arx->RegisterObserver(s_p);
    s_regLoop->RegisterObserver(s_plot3Delegate);

    ui->w_changeKr->setValue(s_conf->kr);
    ui->w_changeTi->setValue(s_conf->Ti);
    ui->w_changeTd->setValue(s_conf->Td);
    ui->w_changeN->setValue(s_conf->N);
    ui->w_changeb->setValue(s_conf->b);
    ui->w_changeH->setValue(s_conf->H);
    ui->w_changeL->setValue(s_conf->L);
    ui->w_changeAlpha->setValue(s_conf->alpha);
    ui->w_changeRo->setValue(s_conf->ro);
    ui->w_changeMax_u->setValue(s_conf->max_u);
    ui->w_changeMin_u->setValue(s_conf->min_u);
    MainWindow::time = 0;
    restarted = true;
    delete this->timer;
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateView()));
    timer->start(1000);
    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(on_startButton_clicked(bool)));
    connect(ui->stepButton, SIGNAL(clicked(bool)), this, SLOT(on_stepButton_clicked(bool)));
    connect(ui->stopButton, SIGNAL(clicked(bool)), this, SLOT(on_stopButton_clicked(bool)));
    connect(ui->addStep, SIGNAL(clicked(bool)), this, SLOT(on_addStep_clicked()));
    connect(ui->addRectangle, SIGNAL(clicked(bool)), this, SLOT(on_addRectangle_clicked()));
    connect(ui->addSine, SIGNAL(clicked(bool)), this, SLOT(on_addSine_clicked()));
    connect(ui->addTriangle, SIGNAL(clicked(bool)), this, SLOT(on_addTriangle_clicked()));
    connect(ui->addNoise, SIGNAL(clicked(bool)), this, SLOT(on_addNoise_clicked(bool)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalSlider_valueChanged(int)));
    //connect(ui->w_changeKr, SIGNAL(valueChanged(double)), this, SLOT(on_w_changeKr_valueChanged(double)));
    connect(ui->changeRegulatorButton, SIGNAL(clicked(bool)), this, SLOT(on_changeRegulatorButton_clicked(bool)));
    connect(ui->changeRegulatorParametersButton, SIGNAL(clicked(bool)), this, SLOT(on_changeRegulatorParametersButton_clicked(bool)));
    connect(ui->restartButton, SIGNAL(clicked(bool)), this, SLOT(on_restartButton_clicked(bool)));
    connect(ui->resetSetPoint, SIGNAL(clicked(bool)), this, SLOT(on_resetSetPoint_clicked(bool)));
}

void MainWindow::on_resetSetPoint_clicked(bool checked)
{
    s_generator->UnregisterSignals();
}

