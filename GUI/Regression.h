#ifndef REGRESSION_H
#define REGRESSION_H

/**********************************************************************************/
#include "wxcrafter.h"
#include <Sec30.h>
#include <math.h>
#include <wx/msgdlg.h>
#include "GraphClass.h"
/**********************************************************************************/

// It just declares MY_EVENT event type
/******************************************************************************/
wxDECLARE_EVENT(RegressionEVT_OnNewData, wxCommandEvent);
wxDECLARE_EVENT(RegressionEVT_OnFinished, wxCommandEvent);
/******************************************************************************/

struct lmOptions
{
    int prnt;            //   3        >1 intermediate results; >2 plots
    int MaxIter;         //   10*Npar     maximum number of iterations
    double epsilon_1;    //   1e-3     convergence tolerance for gradient
    double epsilon_2;    //   1e-3     convergence tolerance for parameters
    double epsilon_3;    //   1e-1     convergence tolerance for red. Chi-square
    double epsilon_4;    //   1e-1     determines acceptance of a L-M step
    double lambda_0;     //   1e-2     initial value of L-M paramter
    double lambda_UP_fac;   //   11       factor for increasing lambda
    double lambda_DN_fac;   //   9       factor for decreasing lambda
    int Update_Type;     //   1       1: Levenberg-Marquardt lambda update      2: Quadratic update           3: Nielsen's lambda update equations
};

class Regression
{
public:
    Sec30* sec30;
    wxWindow* Parent;
    GraphClass* graph2d;
    
    Regression(Sec30* sec30Ref, wxWindow* ParentRef, GraphClass* graph2dRef);
    ~Regression();
    void foo(long long nmax);
    double maxabs(double* a, int na);
    double maxdiag(double** a, int na);
    double Variance(double* a, int na);
    void Start(double* p, int np, double* t, double* y_dat, int ny, double* weight, double* dp, double p_min, double p_max, double* c, lmOptions opts);
    void lm(double* p, int np, double* t, double* y_dat, int ny, double* weight, double* dp, double p_min, double p_max, double* c, lmOptions opts, double &redX2, double* sigma_p, double** cvg_hst);
    void lm_FD_J(double* t, double* p, int np, double* y, int ny, double* dp, double* c, double** J, int &func_calls);
    void lm_Broyden_J(double* p_old, double* y_old, double** J, double* p, int np, double* y, int ny);
    void lm_matx(double* t,double* p_old, int np, double* y_old, int ny, double dX2, double** J, double* p, double* y_dat, double* weight, double* dp, double* c, double** JtWJ, double* JtWdy, double Chi_sq, double* y_hat, int &func_calls, int &iteration);
    void MatVec2Vec(double** a, int na, int ma, double* b, double* c);
    void VecVec2Mat(double* a, int na, double* b, int nb, double** c);
    void MatMat2Mat(double** a, double** b, int na, int manb, int mb, double** c);
    double VecVec2Num(double* a, double* b, int na);
    void Transpose(double** a, int na, int nb, double** aT);
    void func(double* t,  int ny, double* p, int np, double* cnst, double* y);

};

#endif // REGRESSION_H
