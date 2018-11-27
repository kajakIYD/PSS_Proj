#include "identifyzp.h"

IdentifyZP::IdentifyZP(int s_dR, int s_dS, int s_dT, int s_k):
    s_dR(s_dR),
    s_dS(s_dS),
    s_dT(s_dT),
    s_k(s_k)
{
    // lambda 1 - metoda bez ważenia (w przypadku o. stacj. ustawia się mniej np. 0.99
    //lambda = 0.99;
    // beta musi być stosunkowo duża
    beta = 1000;
    // Wywołanie funkcji inicjującej macierze i wektory
    Identify_initialization();
}

void IdentifyZP::Identify_step(std::vector<double> args)
{
    double new_u = args[0];
    double new_y = args[1];
    double new_w = args[2];
    // krok 1 aktualizacja wektora danych

    u.push_front(new_u);
    u.pop_back();

    y.push_front(new_y);
    y.pop_back();

    w.push_front(new_w);
    w.pop_back();
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
        phi(phi_it,0) = *it;
        phi_it++;
    }

    it = w.begin();
    advance(it, 1);
    for(it; it!=w.end(); ++it)
    {
        std::vector<double> temp;
        phi(phi_it,0) = (-(*it));
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
    //eps = new_y - tmp(0,0);
    gamma = new_y - w.at(s_k-1);
    eps = gamma - tmp(0,0);
    // krok 5

    // krok aktualizacja wektora estymowanych parametrów
    theta = theta + k * eps;


}

deque<vector<double>> IdentifyZP::Get_param()
{
    vector<double> tmp;
    deque<vector<double>> out;
    for(int i=0; i < s_dR; i++)
    {
        tmp.push_back(theta(i,0));
    }
    out.push_back(tmp);
    tmp.clear();
    for(int i=s_dR; i < s_dR+s_dS+1; i++)
    {
        tmp.push_back(theta(i,0));
    }
    out.push_back(tmp);
    tmp.clear();
    for(int i=s_dR+s_dS+1; i < s_dR+s_dS+s_dT+2; i++)
    {
        tmp.push_back(theta(i,0));
    }
    out.push_back(tmp);
    return out;
}

void IdentifyZP::Identify_initialization()
{
    // U
    for(int i=0; i < (s_dR+s_k); i++)
        u.push_back(0.0);

    // Y
    for(int i=0; i < (s_dS+s_k+1); i++)
        y.push_back(0.0);

    // W
    for(int i=0; i < (s_dT+s_k+1); i++)
        w.push_back(0.0);

    // R,S,T
    for(int i=0; i < s_dR; i++)
        R.push_back(0.0);

    for(int i=0; i < (s_dS+1); i++)
        S.push_back(0.0);

    for(int i=0; i < (s_dT+1); i++)
        T.push_back(0.0);

    // P
    p.resize(s_dR+s_dS+s_dT+2,s_dR+s_dS+s_dT+2);

    for(int i=0; i < (s_dR+s_dS+s_dT+2); i++)
    {
        for(int j=0; j < (s_dR+s_dS+s_dT+2); j++)
        {
            if(j==i)
                p(i,j) = 1.0 * beta;
            else
                p(i,j) = 0.0;
        }
    }

    // Diag
    diag.resize(s_dR+s_dS+s_dT+2,s_dR+s_dS+s_dT+2);

    for(int i=0; i < (s_dR+s_dS+s_dT+2); i++)
    {
        for(int j=0; j < (s_dR+s_dS+s_dT+2); j++)
        {
            if(j==i)
                diag(i,j) = 1.0 * (1/lambda_zap);
            else
                diag(i,j) = 0.0;
        }
    }

    // Theta
    theta.resize(s_dR+s_dS+s_dT+2,1);
    for(int i=0; i< s_dR+s_dS+s_dT+2; i++ )
        theta(i,0) = 0.0;

    // Phi
    phi.resize(s_dR+s_dS+s_dT+2,1);
    for(int i=0; i< s_dR+s_dS+s_dT+2; i++ )
        phi(i,0) = 0.0;

}
