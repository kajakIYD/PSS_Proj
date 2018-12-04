#ifndef REGULATIONLOOP_H
#define REGULATIONLOOP_H
#include "siso.h"
#include "regulator.h"
#include "subject.h"
#include <typeinfo>
#include "p.h"
#include "pid.h"
#include "gpc.h"
#include "Xgenerator.h"
#include "identify.h"
#include "identifyuber.h"
#include <QString>


//SISO inheritance removed
class RegulationLoop : public Subject
{
public:
    /*!
     * \brief Constructor
     */
    RegulationLoop(){}
    /*!
     * \brief Constructoor used in flow of aapplication
     * it receives pointer to SISO - object to simulate
     * Regulator - pointer to regulator object
     * Generator -  pointer to generator that generates set point value
     * Identify - pointer to identification object
     * QString - current regulator type
     */
    RegulationLoop(SISO *siso, Regulator *regulator, Generator *generator, SISO* paralel_Siso, QString currentRegType="PID");
    /*!
     * \brief Destructor
     */
    ~RegulationLoop();
    /*!
     * \brief simulate_step
     * perform one simulation step
     * double - input of the simulation (current output of the simulation)
     * time - time passed from the beginning of the simulation
     */
    double Simulate_step(double input);
    /*!
     * \brief Method to notify plot to update it
     */
    void UpdatePlot();
    /*!
     * \brief Method that allowss to save measurements
     * to *.txt file
     */
    void SaveToFile();
    /*!
     * \brief Simple getter of an simulation output
     */
    double GetOutput();

    /*!
     * \brief Simple getter of an simulation set point
     */
    double GetSP();
    /*!
     * \brief Simple getter of an simulation output vector
     */
    std::vector<double> GetYVector();
    /*!
     * \brief Simple getter of a regulator pointer
     */
    Regulator* GetRegulator();
    /*!
     * \brief Simple getter of a regulator name
     */
    QString GetRegulatorType();
    /*!
     * \brief Method that allows to change regulator parameters,
     * naturally depending on regulator type
     * kr - gain, Ti - integration time, Td-derivation time
     * alpha -GPC regulator parameter
     */
    void ChangeRegParameters(double kr, double Ti, double Td, double N, double b, double max_u, double min_u, double alpha, double H, double L, double ro);
    /*!
     * \brief Method that allows to change regulator type
     * QString - value from GUI, name of proper regulator
     */
    void ChangeRegulator(QString regType);
    /*!
     * \brief Simulation time for loop
     *
     */
    int time=0;
private:
    Regulator *s_reg;
    SISO *s_siso;
    SISO *s_paralelSiso;
    Generator *s_generator;
    IdentifyUber *s_identify;

    double s_output;
    double s_input;
    std::fstream s_file;
    QString s_currentRegType = "PID";
    std::vector<double> s_y;
};

#endif // REGULATIONLOOP_H
