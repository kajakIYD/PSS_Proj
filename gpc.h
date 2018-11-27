#ifndef GPC_H
#define GPC_H
#include "regulator.h"
#include "Xgenerator.h"
#include "identify.h"
#include <vector>
#include <deque>
#include <arx.h>
#include <siso.h>
#include <Eigen/Dense>
#include <boost/numeric/ublas/lu.hpp>


using namespace Eigen;
using namespace boost::numeric::ublas;

class GPC : public Regulator
{
public:
    /*!
     * \brief Constructor that construct regulator GPC with specified GPC-parameters:
     * H, L, alpha, ro
     * upper (max_u) and lower (min_u) bound of control signal and
     * signal generator (generator) that helps to generate SetPoint signal
     * and two arx's -> one for real time simulation, second for model prediction
     */
    GPC(double H, double L, double alpha, double ro, double max_u, double min_u, Generator *generator, ARX *arx, int time, std::vector<double>sisoOutput, double control, ARX* paralel_ARX);
    GPC(){}
    /*!
     * \brief Destructor
     */
    ~GPC();

    /*!
     * \brief Method updating plots
     */
    void Update(double y1, double y2, double y3){}
    void Update(double x, double y){}
    void Update(double y);
    /*!
     * \brief simulate_step
     * perform one simulation step
     * give an output depending on input
     */
    double Simulate_step(double input);
    /*!
     * \brief Simple getter for regulation control (double u)
     */
    double GetU();
    /*!
     * \brief Simple getter for regulation setPoint
     */
    double GetSP();
    /*!
     * \brief Simple getter for Identify object pointer
     */
    IdentifyUber* GetId();
    /*!
     * \brief Setter for Simulation time for regulator (in case of resetting simulation)
     */
    void SetTime(int time);
    /*!
     * \brief Setter for vector containing output from siso model
     */
    void SetSisoOutput(std::vector<double> sisoOutput);

private:
    double s_H;
    double s_L;
    double s_alpha;
    double s_ro;
    double s_u;
    double s_SP;
    double s_currentControl;
    int s_dA;
    int s_dB;
    int s_dAm = 1;
    int s_time;

    //mat s_Q;
    MatrixXd s_Q;
    MatrixXd s_Aeq;
    VectorXd s_Beq;
    MatrixXd s_I;
    VectorXd s_X;
    VectorXd s_q;
    VectorXd s_controlVector; //Series of L-long new controls
    VectorXd s_referenceTrajectory; //Series of H-long reference trajectory vector
    VectorXd s_predictiveSisoOutput;

//    mat s_Aeq;
//    mat s_Beq;
//    mat s_I;
    //std::vector<vector<double>> s_Q;
    std::vector<double> s_parA;
    std::vector<double> s_parB;
    std::vector<double> s_hVec;
    std::deque<double> s_sisoOutput;
    std::deque<double> u;
    std::deque<double> y;

    ARX* s_arx;
    ARX* s_paralelARX;
    Generator* s_generator;
    Identify* s_identify;

    std::vector<double> GetStepResponse();
    VectorXd SetInitialConditions();
    double SimulateStepResponse(int i);
    void ClearAndInitializeVectors();
    double SimulateStepReferenceTrajectory(int j);


};

#endif // GPC_H
