#include "identifyarmax.h"

IdentifyARMAX::IdentifyARMAX(int dA, int dB, int dC, int k):
s_dA(dA),
s_dB(dB),
s_dC(dC),
s_k(k)
{
    // lambda 1 - metoda bez ważenia (w przypadku o. stacj. ustawia się mniej np. 0.99
    //lambda = 0.99;
    // beta musi być stosunkowo duża
    beta = 1000;
    // Wywołanie funkcji inicjującej macierze i wektory
    Identify_initialization();

}

IdentifyARMAX::~IdentifyARMAX()
{}

void IdentifyARMAX::Identify_step(double new_u, double new_y)
{

    // krok 1 aktualizacja wektora danych

    u.push_front(new_u);
    u.pop_back();

    y.push_front(new_y);
    y.pop_back();

    //TODO: zrobić ładnie bo jesr brzydko
    MatrixXd aaa;
    aaa.resize(1,1);
    aaa = (phi.transpose() * theta);
    double e_dashed_current = new_y - aaa(0,0);

    e_dashed.push_front(e_dashed_current);
    e_dashed.pop_back();

    // krok 2 wyznaczenie nowego phi

    int phi_it = 0;

    auto it = u.begin();
    advance(it, s_k);
    for(it; it!=u.end(); ++it)
    {
        std::vector<double> temp;
        phi(phi_it,0) = *it;
        phi_it++;
    }

    it = y.begin();
    advance(it, 1);
    for(it; it!=y.end(); ++it)
    {
        std::vector<double> temp;
        phi(phi_it,0) = (-(*it));
        phi_it++;
    }

    it = e_dashed.begin();
    advance(it, 1);
    for(it; it != e_dashed.end(); ++it)
    {
        std::vector<double> temp;
        phi(phi_it, 0) = (*it);
        phi_it++;
    }

    MatrixXd tmp_lambda;
    tmp_lambda.resize(1,1);
    tmp_lambda(0,0) = lambda;
    // krok 3 aktualizacja macierzy kowariancji (32.8 str.523)
    MatrixXd licznik;
    licznik = ((p*phi)*(phi.transpose()))*p;
    MatrixXd mianownik;
    mianownik = tmp_lambda + (phi.transpose()*p*phi);
    p = 1/lambda*(p - licznik / mianownik(0,0));// / tmp_lambda(0,0);

    //p = (p - (((p*phi)*(phi.transpose()))*p)/(tmp + (((phi.transpose())*p)*phi))) / tmp;


    // Zapobiegnięcie wybuchowi estymatora
    // RMNK z macierzowym zapominaniem  (32.16-32.18 str. 525)
    // W miarę potrzeb dodać aktualizację macierzy diag
    p = (diag * p) * diag;

    // krok 4 obliczenie wektora wzmocnień i eps
    k = p * phi;
    MatrixXd tmp;
    tmp = (phi.transpose()) * theta;
    eps = new_y - tmp(0,0);
    // krok 5

    // krok aktualizacja wektora estymowanych parametrów
    theta = theta + k * eps;


}

deque<double> IdentifyARMAX::Get_param()
{
    deque<double> tmp;
    for(int i=0; i < s_dA+s_dB+s_dC+1; i++)
    {
        tmp.push_back(theta(i,0));
    }
    return tmp;
}

vector<double> IdentifyARMAX::Get_A()
{   A.clear();
    for(int i=s_dB+1; i<s_dA+s_dB+1; i++)
        A.push_back(theta(i,0));
    return A;
}

vector<double> IdentifyARMAX::Get_B()
{
    B.clear();
    for(int i=0; i<s_dB+1; i++)
        B.push_back(theta(i,0));
    return B;
}

vector<double> IdentifyARMAX::Get_C()
{
    C.clear();
    for(int i=0; i<s_dC+1; i++)
        C.push_back(theta(i,0));
    return C;
}

void IdentifyARMAX::Identify_initialization()
{
    // input
    for(int i=0; i < (s_dB+s_k+1); i++)
        u.push_back(0.0);

    // output
    for(int i=0; i < (s_dA+1); i++)
        y.push_back(0.0);

    //estimated e
    for(int i=0; i < s_dC; i++)
        e_dashed.push_back(0.0);

    // A and B and C
    for(int i=0; i < s_dA; i++)
        A.push_back(0.0);

    for(int i=0; i < (s_dB+1); i++)
        B.push_back(0.0);

    for(int i=0; i < (s_dC+1); i++)
        C.push_back(0.0);

    // P
    p.resize(s_dA + s_dB + s_dC + 1, s_dA + s_dB + s_dC + 1);

    for(int i=0; i < (s_dA+s_dB+1); i++)
    {
        for(int j=0; j < (s_dA+s_dB+1); j++)
        {
            if(j==i)
                p(i,j) = 1.0 * beta;
            else
                p(i,j) = 0.0;
        }
    }

    // Diag
    diag.resize(s_dA + s_dB + s_dC + 1, s_dA + s_dB + s_dC + 1);

    for(int i=0; i < (s_dA + s_dB + s_dC + 1); i++)
    {
        for(int j=0; j < (s_dA + s_dB + s_dC + 1); j++)
        {
            if(j==i)
                diag(i,j) = 1.0 * (1/lambda_zap);
            else
                diag(i,j) = 0.0;
        }
    }

    // Theta
    theta.resize(s_dA + s_dB + s_dC + 1, 1);
    for(int i=0; i< s_dA + s_dB + s_dC + 1; i++ )
        theta(i,0) = 0.0;

    // Phi
    phi.resize(s_dA + s_dB + s_dC + 1, 1);
    for(int i=0; i< s_dA + s_dB + 1; i++ )
        phi(i,0) = 0.0;
}
