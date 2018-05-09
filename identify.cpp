#include "identify.h"

Identify::Identify()
{
    //Init P with beta
    s_q = (s_lambda_max-s_lambda_min)/s_lambda_max;
    s_r = s_lambda_min;

}

double Identify::Calculate_P(double u, double y)
{
    ///Iterate through each element of u and y vector (measurements)
    for(int i=0; i<N; i++)
    {
        //Pseudocode:
        //P(i) = 1/lambda*(P(i-1) - phi(i-1)*phi_t(i-1)*P(i-1)/(lambda + phi_t(i-1)*P(i-1)*phi(i-1)));

        // RMNK z regularyzacja?
        // P_tmp(i)(-1) =P_tmp(i-1)(-1)+phi(i-1)*phi_t(i-1)...
        // P(i) = q*P_tmp(i) + r*I;

    }
    return 3;//s_P;
}
