#include "gpc.h"

GPC::GPC(double H, double L, double alpha, double ro, double max_u, double min_u, Generator *generator, ARX *arx, int time, std::vector<double>sisoOutput, double control, ARX *paralelARX)
{
    s_arx = arx;
    s_H = H;
    s_L = L;
    s_ro = ro;
    s_alpha = alpha;
    s_parA = s_arx->GetA();
    s_parB = s_arx->GetB();
    s_generator = generator;
    s_paralelARX = paralelARX;
    s_time = time;
    s_sisoOutput = sisoOutput;
    s_currentControl = control;

    if (s_time>=H-s_dA)
    {
        s_referenceTrajectory = SetInitialConditions();
    }
    else
    {
        s_referenceTrajectory = VectorXd::Zero(1000*s_H+1);
        s_predictiveSisoOutput = VectorXd::Zero(1000*s_H+1);
    }

    // stopnie wielomianów
    s_dA = s_parA.size();
    s_dB = s_parB.size()-1;

    // wstępne zerowanie wektorów
    for(int i=0; i < s_dA;i++)
    y.push_back(0);

    for(int i=0;i < s_dB+1 ;i++)
    u.push_back(0);

    //s_Q(s_H, s_L);
    s_Q = MatrixXd::Zero(s_H, s_L);// zeros();

    //s_Beq.set_size(s_L);
    s_Beq = VectorXd::Zero(s_L);//zeros();
    s_Beq(0)=1;

    //s_I.eye(s_L, s_L);
    s_I = MatrixXd::Identity(s_L, s_L);
    s_I = s_ro*s_I;


}

GPC::~GPC()
{

}

VectorXd GPC::SetInitialConditions()
{
    VectorXd temp;
    for(int i=s_H;i>=0;i--)
    {
        temp(i)=s_sisoOutput.size()-1-i;
    }
    return temp;
}


double GPC::SimulateStepReferenceTrajectory(int j)
{
    //Changes of SP -> calculate signal from generator for proper simulation time
    return (s_time<s_H) ? 0.0 : (1-s_alpha)*s_generator->CalculateSignal(s_time+j)+s_alpha*s_referenceTrajectory(s_time+j-1);
}


double GPC::Simulate_step(double input)
{
    //Acquire Step Response vector from object
    GetStepResponse();
    //Organize Q matrix
    for(int i =0; i<s_H; i++)
    {
        int k=i;
        for(int j=0; j<s_L; j++)
        {
            if (i >=s_L)
            {
                //1-st row put 1 element, 2-nd row put 2 elements and so on...
                //But maximum is L-elements (0 to L-1)
                //h0 is the very first step response value, but in hVec it is the last value
                s_Q(i,j) = s_hVec.at(k);
                k--;
            }
            else
            {
                if (j<=i)
                {
                    //1-st row put 1 element, 2-nd row put 2 elements and so on...
                    //But maximum is L-elements (0 to L-1)
                    //h0 is the very first step response value
                    s_Q(i,j) = s_hVec.at(k);
                    k--;
                }
                else
                {
                    s_Q(i,j) = 0;
                }
            }
        }
    }
    //We have Q-matrix
    //Now solve linear equations system: Ax = b;
    s_Aeq = s_Q.transpose()*s_Q+s_I;
    s_X = s_Aeq.colPivHouseholderQr().solve(s_Beq);
    s_q = s_X.transpose()*s_Q.transpose();
    s_q = s_q.transpose();
    //Calculate reference trajectory and model response
    for (int j=0; j<s_H; j++)
    {
        s_referenceTrajectory(s_time+j) = SimulateStepReferenceTrajectory(j);
        s_predictiveSisoOutput(s_time+j) = s_paralelARX->Simulate_step(s_currentControl);
    }
    s_paralelARX->SetY(s_arx->GetY());
    s_paralelARX->SetU(s_arx->GetU());
    //Calculate control
    VectorXd tempRefTr = VectorXd::Zero(s_H);
    VectorXd tempPredOut = VectorXd::Zero(s_H);
    for(int k=0; k<s_H; k++)
    {
        tempRefTr(k) = s_referenceTrajectory(s_time+k);
        tempPredOut(k) = s_predictiveSisoOutput(s_time+k);
    }
    auto tmp = s_q.transpose()*(tempRefTr-tempPredOut);
    return s_currentControl + s_q.transpose()*(tempRefTr-tempPredOut);
}

void GPC::Update(double y)
{
    this->Simulate_step(y);
}

void GPC::SetTime(int time)
{
    s_time = time;
}

double GPC::GetU()
{
    return s_u;
}

double GPC::GetSP()
{
    return s_SP;
}


void GPC::ClearAndInitializeVectors()
{
    y.clear();
    u.clear();
    // wstępne zerowanie wektorów
    for(int i=0; i < s_dA;i++)
    y.push_back(0);

    for(int i=0;i < s_dB+1 ;i++)
    u.push_back(0);
}

double GPC::SimulateStepResponse(int i)
{
    static std::deque<double> subY;

    static std::deque<double> subU;

    //ClearAndInitializeVectors();

    // delete oldest value and push newest
    u.pop_back();
    u.push_front(1);

    // copy u vector with k offset
    auto it = u.begin();
    advance(it, 0);
    std::copy(it, u.end(), std::front_inserter(subU));//std::back_inserter(subU));

    // copy y vector with dA offset
    it = y.begin();
    advance(it, this->s_dA);
    std::copy(y.begin(), it, std::front_inserter(subY));

    double output1, output2;

    output1 = inner_product(s_parB.begin(), s_parB.end(), subU.begin(), 0.0);
    output2 = - inner_product(s_parA.begin(), s_parA.end(), subY.begin(), 0.0);

    this->y.pop_back();
    this->y.push_front(output1 + output2);
    double output = output1 + output2;

    //Powiadom wykres
    //Notify(input, output);

    //Powiadom regulator
    //Notify(output);

    return output;
}

std::vector<double> GPC::GetStepResponse()
{
    s_hVec.clear();
    for(int i=0; i<s_H; i++)
    {
        s_hVec.push_back(SimulateStepResponse(i));
    }
    return s_hVec;
}
