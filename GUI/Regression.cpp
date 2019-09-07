#include "Regression.h"


// this is a definition so can't be in a header
wxDEFINE_EVENT(RegressionEVT_OnNewData, wxCommandEvent);
wxDEFINE_EVENT(RegressionEVT_OnFinished, wxCommandEvent);
wxDEFINE_EVENT(RegressionEVT_OnStarted, wxCommandEvent);

Regression::Regression(Sec30* sec30Ref, wxWindow* ParentRef, GraphClass* graph2dRef)
{
    sec30 = sec30Ref;
    Parent = ParentRef;
    graph2d = graph2dRef;
}

Regression::~Regression()
{
    
}

void Regression::foo(long long nmax)
{ 
    wxMessageBox(_("Call"),_("yes"));
    long long i;
    double s=0;
    for(i=0; i<nmax; i++)
    {
        double d=sin(1.0*sin(1.0*i));
        if(d>0) s=d;
        if(s<10000 || s>10000)
        {
            if(i==0) wxMessageBox(_("started"),_("yes"));
            if(i==nmax-1) wxMessageBox(_("Finished"),_("yes"));
        }
    }
} 

double Regression::maxabs(double* a, int na)
{
    if (na<1) return 0.0;
    double maxval = fabs(a[0]);
    double absa;
    for(int ia=1; ia<na; ia++)
    {
        absa = fabs(a[ia]);
        if(maxval < absa) maxval = absa;
    }
    return maxval;
}

double Regression::maxdiag(double** a, int na)
{
    if (na<1) return 0.0;
    double maxval = a[0][0];
    for(int ia=1; ia<na; ia++)
    {
        if(maxval < a[ia][ia]) maxval = a[ia][ia];
    }
    return maxval;
}

double Regression::Variance(double* a, int na)
{
    if (na < 2) return 0.0;
    double a0 = 0.0;
    for(int ia=0; ia<na; ia++) a0 += a[ia];
    a0 = a0 / na;
    double var = 0.0;
    for(int ia=0; ia<na; ia++) var += pow(a[ia] - a0 , 2.0);
    return var / (na - 1);
}

void Regression::Start(double* p, int np, double* t, double* y_dat, int ny, double* weight, double* dp, double p_min, double p_max, double Mixing, double* c, lmOptions opts, bool isOneStep)
{
    SendEventRunStarted();
    myGrid* osgc = sec30->GetGridObject(_("OS"));
    myGrid* skgc = sec30->GetGridObject(_("SK"));
    myGrid* olgc = sec30->GetGridObject(_("OL"));
    sec30->OSBuffer = new double[osgc->GetNumberRows()];
    sec30->SKBuffer = new double[skgc->GetNumberRows()];
    sec30->OLBuffer = new double[olgc->GetNumberRows()];
    
    int natoms = 0;
    sec30->GetVar(_("nAtoms[0]"),natoms);
    bool isSOC;
    sec30->GetCheckVar(_("SOC[0]"), isSOC);
    bool isOverlap;
    sec30->GetCheckVar(_("Overlap[0]"), isOverlap);
    
    bool isSpin = false;
    if (isSOC) isSpin = true;
    
    int MaxIter = opts.MaxIter;          // maximum number of iterations
    double redX2;
    double* sigma_p = new double[np];
    double** cvg_hst = new double*[MaxIter];                          // convergence history
    for (int i=0; i<MaxIter; i++) cvg_hst[i] = new double[np+3];
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Allocate out side. Because func will be called a lot and it will be slow if we allocate and delete many times.
    int nHamiltonian = sec30->ArraysOf1DString[1].size();
    
    int nHamiltonianTot;
    if (isSpin)
        nHamiltonianTot = 2*nHamiltonian;
    else
        nHamiltonianTot = nHamiltonian;
        
    int nH2 = nHamiltonianTot*nHamiltonianTot;
    lapack_complex_double* LowerSymMatrixHf;
    lapack_complex_double* LowerSymMatrixSf;
    if (isOverlap)
    {
        int nAB2 = (nHamiltonianTot+nH2) + 1;
        LowerSymMatrixHf = new lapack_complex_double[nAB2];
        LowerSymMatrixSf = new lapack_complex_double[nAB2];
    }
    else
    {
        LowerSymMatrixHf = new lapack_complex_double[nH2];
    }
    //lapack_complex_double* LowerSymMatrixHf = (lapack_complex_double*)LAPACKE_malloc( sizeof(lapack_complex_double) * nH2 );
    //lapack_complex_double zero= LAPACKE_make_complex_double(0.0,0.0);
    double* eigHf = new double[nHamiltonianTot];
    for (int i=0; i<nHamiltonianTot; i++) eigHf[i] = 0.0;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    lm(p, np, t, y_dat, ny, weight, dp, p_min, p_max, Mixing, c, opts, redX2, sigma_p, cvg_hst, isOneStep, LowerSymMatrixHf, LowerSymMatrixSf, eigHf, natoms, isSOC, isOverlap);
    
    //////////////////////////////
    //Deallocate
    delete [] eigHf;
    delete [] LowerSymMatrixHf;
    if (isOverlap) delete [] LowerSymMatrixSf;
    //LAPACKE_free(LowerSymMatrixHf);
    //////////////////////////////
    
    for (int ip=0; ip<np; ip++)
    {
        int GridInd = sec30->ArraysOf2DInt[1][ip][0];
        int irow = sec30->ArraysOf2DInt[1][ip][1];
        double Value = p[ip];
        wxString val = wxString::Format(wxT("%.8f"), Value);
        if (GridInd == 1)
        {
            osgc->SetCellValue(irow, 2, val);
            if (isOneStep) osgc->SetCellValue(irow, 1, val);
        }
        else if (GridInd == 2)
        {
            skgc->SetCellValue(irow, 2, val);
            if (isOneStep) skgc->SetCellValue(irow, 1, val);
        }
        else if (GridInd == 3)
        {
            olgc->SetCellValue(irow, 2, val);
            if (isOneStep) olgc->SetCellValue(irow, 1, val);
        }
    }
    
    osgc->Refresh(false);
    skgc->Refresh(false);
    olgc->Refresh(false);
    
    //////////////////////////////Finishing///////////////////////////////////////////
    for (int i=0; i<MaxIter; i++) delete [] cvg_hst[i];
    if (MaxIter>0) delete [] cvg_hst;
    delete [] sigma_p;
    delete [] sec30->OSBuffer;
    delete [] sec30->SKBuffer;
    delete [] sec30->OLBuffer;
    /////////////////////////////////////////////////////////////////////////////////
    SendEventRunFinished();
    return;
}

void Regression::lm(double* p, int np, double* t, double* y_dat, int ny, double* weight, double* dp, double p_min, double p_max, double Mixing, double* c, lmOptions opts, double &redX2, double* sigma_p, double** cvg_hst, bool isOneStep, lapack_complex_double* LowerSymMatrixHf, lapack_complex_double* LowerSymMatrixSf, double* eigHf, int natoms, bool isSOC, bool isOverlap)
{
    wxString data;
    //global   iteration  func_calls

    //int tensor_parameter = 0;                  // set to 1 if the parameter is a tensor

    int iteration  = 0;                            // iteration counter
    int func_calls = 0;                            // running count of function evaluations

    //p = p(:); y_dat = y_dat(:);              // make column vectors
    int Npar   = np;                         // number of parameters
    int Npnt   = ny;                     // number of data points
    double* p_old  = new double[Npar];                  // previous set of parameters
    double* y_old  = new double[Npnt];                  // previous model, y_old = y_hat(t;p_old)
    double eps = 2.2204e-16;
    double X2     = 1e-3/eps;                       // a really big initial Chi-sq value
    double X2_old = 1e-3/eps;                       // a really big initial Chi-sq value
    double** J = new double*[Npnt];                          // Jacobian matrix
    for (int iy=0; iy<Npnt; iy++) J[iy] = new double[Npar];
    
    for (int iy=0; iy<ny; iy++)
        for (int ip=0; ip<np; ip++)
            J[iy][ip] = 0.0;
    
    int DoF    = Npnt - Npar + 1;                  // statistical degrees of freedom
    
    int prnt          = opts.prnt;             // >1 intermediate results; >2 plots
    int MaxIter       = opts.MaxIter;          // maximum number of iterations
    double epsilon_1     = opts.epsilon_1;        // convergence tolerance for gradient
    double epsilon_2     = opts.epsilon_2;        // convergence tolerance for parameters
    double epsilon_3     = opts.epsilon_3;        // convergence tolerance for Chi-square
    double epsilon_4     = opts.epsilon_4;        // determines acceptance of a L-M step
    double lambda_0      = opts.lambda_0;         // initial value of damping paramter, lambda
    double lambda_UP_fac = opts.lambda_UP_fac;    // factor for increasing lambda
    double lambda_DN_fac = opts.lambda_DN_fac;    // factor for decreasing lambda
    int Update_Type   = opts.Update_Type;      // 1: Levenberg-Marquardt lambda update
    
    //p_min=p_min(:); p_max=p_max(:); % make column vectors
    
    Aint0D Vidx;                              // indices of the parameters to be fit
    for (int i=0; i<Npar; i++) if(dp[i] != 0) Vidx.push_back(i);
    int Nfit = Vidx.size();                  // number of parameters to fit
    int* idx = new int[Nfit];
    for (int i=0; i<Npar; i++) idx[i] = Vidx[i];
    Vidx.clear();
    
    bool stop = false;                           // termination flag
    
    double InitializedX2 = 1.0;
    
    double** JtWJ = new double*[np];                          // Jacobian matrix
    for (int ip=0; ip<np; ip++) JtWJ[ip] = new double[np];
    for (int ip=0; ip<np; ip++)
        for (int jp=0; jp<np; jp++)
            JtWJ[ip][jp] = 0.0;
    
    double* JtWdy  = new double[np]; 
    for (int ip=0; ip<np; ip++) JtWdy[ip] = 0.0;
    
    double* y_hat  = new double[ny]; 
    for (int iy=0; iy<ny; iy++) y_hat[iy] = 0.0;
    
    lm_matx(t, p_old, np, y_old, ny, InitializedX2, J, p, y_dat, weight, dp, c, JtWJ, JtWdy, X2, y_hat, func_calls, iteration, LowerSymMatrixHf, LowerSymMatrixSf, eigHf, natoms, isSOC, isOverlap);
    
    data = _("******************** New Regression Analysis *******************\n");
    SendDataToTerminal(data);
    
    data = _("");
    double firstCheck = maxabs(JtWdy, np);
    if ( firstCheck < epsilon_1)
    {
        data.append(_("Fit parameters were not changed.\n"));
        data.append(_("Check the number of first DFT band and make sure the weight function is not zero in your favourite fitting area.\n"));
        data.append(_("********************* Regression Finished *********************\n"));
        SendDataToTerminal(data);
        stop = true;
    }
    
    double lambda  = lambda_0;
    int nu;
    if (Update_Type != 1)
    {
        lambda  = lambda_0 * maxdiag(JtWJ, np);
        nu=2;
    }
    
    X2_old = X2;                            // previous value of X2
    //cvg_hst = ones(MaxIter,Npar+3);         
    
    for (int i=0; i<MaxIter; i++)                                       // initialize convergence history
        for (int j=0; j<Npar+3; j++)
            cvg_hst[i][j] = 0.0;
    
    int np2 = np*np;
    /////////////////////////Allocate Arrays/////////////////////////////////
    double* hperP=new double[np];
    double* h = new double[np];
    double* h2 = new double[np];
    double* hInv = new double[np2];
    lapack_int* ipiv = new lapack_int[np];
    lapack_int* ipiv2 = new lapack_int[np];
    double* p_try = new double[np];
    double* y1 = new double[ny];
    double* delta_y = new double[ny];
    double* weighted_dy = new double[ny];
    double* weighted_dy2 = new double[ny];
    double* JtWJArr = new double[np2];
    double* covar_p = new double[np2];
    ////////////////////////////////////////////////////////////////////////
    bool BadCondition = false;
    while (!stop)        // --- Start Main Loop
    {
        iteration++;
        for (int ip=0; ip<np; ip++)
            for (int jp=0; jp<np; jp++)
                hInv[ip * np + jp] = JtWJ[ip][jp];
        
        for (int ip=0; ip<np; ip++) h[ip] = JtWdy[ip];
        
        // incremental change in parameters
        if (Update_Type == 1)                                   //Marquardt
        {
            for (int ip=0; ip<np; ip++)
                hInv[ip * np + ip] += lambda * JtWJ[ip][ip];
            
            
            //h = ( JtWJ + lambda*diag(diag(JtWJ)) ) \ JtWdy;
        }
        else                                                    //Quadratic and Nielsen
        {
            for (int ip=0; ip<np; ip++)
                hInv[ip * np + ip] += lambda;
            
            //h = ( JtWJ + lambda*eye(Npar) ) \ JtWdy;
        }
        
        int nrhs0 = 1;
        int info1 = LAPACKE_dgesv(LAPACK_ROW_MAJOR, np, nrhs0, hInv, np, ipiv, h, nrhs0);
        
        data = _("");
        if( info1 > 0 )
        {
            data.append(_("Lapack Error:\n"));
            data.append(_("The diagonal element of the triangular factor of A,\n"));
            data.append(wxString::Format(wxT("U(%i,%i) is zero, so that A is singular;\n"), info1, info1));
            data.append(_("The solution could not be computed.\n"));
            data.append(_("Stopped without convergence!\n"));
            SendDataToTerminal(data);
            BadCondition=true;
            break;
        }
        
        /*if (stop)                       // Lapack error; break
        {
            //wxMessageBox(wxString("1"));
            ///////////////Out of While Loop///////////
            delete [] y_hat;
            delete [] JtWdy;
            for (int ip=0; ip<np; ip++) delete [] JtWJ[ip];
            if (np>0) delete [] JtWJ;
            for (int iy=0; iy<ny; iy++) delete [] J[iy];
            if (ny>0) delete [] J;
            delete [] y_old;
            delete [] p_old;
            delete [] hperP;
            delete [] h;
            delete [] h2;
            delete [] ipiv;
            delete [] ipiv2;
            delete [] hInv;
            delete [] y1;
            delete [] delta_y;
            delete [] p_try;
            delete [] weighted_dy;
            delete [] weighted_dy2;
            delete [] JtWJArr;
            delete [] covar_p;
            delete [] idx;
            ///////////////Out of While Loop///////////
            
            return;
        }*/
        
        //  big = max(abs(h./p)) > 2;                      // this is a big step
        
        // --- Are parameters [p+h] much better than [p] ?
        
        
        for (int ip=0; ip<np; ip++) p_try[ip] = 0.0;
        
        for (int ip=0; ip<np; ip++) p_try[ip] = p[ip] + Mixing * h[idx[ip]];  // update the [idx] elements
        
        //p_try = p + h(idx);                            
        
        for (int ip=0; ip<np; ip++)                              // apply constraints
        {
            if (p_try[ip] < p_min)
                p_try[ip] = p_min;
            else if (p_try[ip] > p_max)
                p_try[ip] = p_max;
        }
        //p_try = min(max(p_min,p_try),p_max);           
        
        func(t, ny, p_try, np, c, y1, LowerSymMatrixHf, LowerSymMatrixSf, eigHf, natoms, isSOC, isOverlap);
        
        for (int iy=0; iy<ny; iy++)                    // residual error using p_try
            delta_y[iy] = y_dat[iy] - y1[iy];
        //delta_y = y_dat - func(t,p_try,c);
        
        
        bool isAllFinite = true;
        for (int iy=0; iy<ny; iy++)
            isAllFinite = isAllFinite && std::isfinite(delta_y[iy]);
        
        if (!isAllFinite) {BadCondition=true; break;}                   // floating point error; break
        /*if (!isAllFinite)                    // floating point error; break
        {
            ///////////////Out of While Loop///////////
            delete [] y_hat;
            delete [] JtWdy;
            for (int ip=0; ip<np; ip++) delete [] JtWJ[ip];
            if (np>0) delete [] JtWJ;
            for (int iy=0; iy<ny; iy++) delete [] J[iy];
            if (ny>0) delete [] J;
            delete [] y_old;
            delete [] p_old;
            delete [] hperP;
            delete [] h;
            delete [] h2;
            delete [] ipiv;
            delete [] ipiv2;
            delete [] hInv;
            delete [] y1;
            delete [] delta_y;
            delete [] p_try;
            delete [] weighted_dy;
            delete [] weighted_dy2;
            delete [] JtWJArr;
            delete [] covar_p;
            delete [] idx;
            ///////////////Out of While Loop///////////
            
            return;
        }*/
        
        func_calls = func_calls + 1;
        
        for(int iy=0; iy<ny; iy++) weighted_dy[iy] = delta_y[iy] * weight[iy];
        double X2_try = VecVec2Num(delta_y, weighted_dy, ny);              // Chi-squared error criteria
        //X2_try = delta_y' * ( delta_y .* weight );
        
        
        double alpha = 0.0;
        if ( Update_Type == 2 )                        // Quadratic
        {
            //    One step of quadratic line update in the h direction for minimum X2
            double f1 = VecVec2Num(JtWdy, h, np);
            alpha = f1 / ( (X2_try - X2)/2.0 + 2.0*f1 ) ;
            //alpha =  Transpose(JtWdy).h / ( (X2_try - X2)/2 + 2*Transpose(JtWdy).h ) ;
            //h = alpha * h;
            for (int ip=0; ip<np; ip++) h[ip] = alpha * h[ip];
            
            for (int ip=0; ip<np; ip++) p_try[ip] = p[ip] + Mixing * h[idx[ip]];           // update only [idx] elements
            
            for (int ip=0; ip<np; ip++)                              // apply constraints
            {
                if (p_try[ip] < p_min)
                    p_try[ip] = p_min;
                else if (p_try[ip] > p_max)
                    p_try[ip] = p_max;
            }
            //p_try = min(max(p_min,p_try),p_max);         // apply constraints
            
            func(t, ny, p_try, np, c, y1, LowerSymMatrixHf, LowerSymMatrixSf, eigHf, natoms, isSOC, isOverlap);
            
            for (int iy=0; iy<ny; iy++)                    // residual error using p_try
                delta_y[iy] = y_dat[iy] - y1[iy];
            
            func_calls = func_calls + 1;
            
            for(int iy=0; iy<ny; iy++) weighted_dy2[iy] = delta_y[iy] * weight[iy];
            X2_try = VecVec2Num(delta_y, weighted_dy2, ny);              // Chi-squared error criteria
        }
        
        //rho = (X2 - X2_try) / ( Transpose(h) . (lambda * h + JtWdy) );
        for (int ip=0; ip<np; ip++) h2[ip] = lambda*h[ip] + JtWdy[ip];
        double rho = VecVec2Num(h, h2, np);
        
        if ( rho > epsilon_4 )                         // it is significantly better
        {
            double dX2 = X2 - X2_old;
            X2_old = X2;
            for (int ip=0; ip<np; ip++) p_old[ip] = p[ip];
            for (int iy=0; iy<ny; iy++) y_old[iy] = y_hat[iy];
            for (int ip=0; ip<np; ip++) p[ip] = p_try[ip];
            
            lm_matx(t, p_old, np, y_old, ny, dX2, J, p, y_dat, weight, dp, c, JtWJ, JtWdy, X2, y_hat, func_calls, iteration, LowerSymMatrixHf, LowerSymMatrixSf, eigHf, natoms, isSOC, isOverlap);
            
            // decrease lambda ==> Gauss-Newton method
            switch (Update_Type)
            {
                case 1:                                   // Levenberg
                    lambda = fmax(lambda/lambda_DN_fac,1.e-7);
                    break;
                case 2:                                   // Quadratic
                    lambda = fmax( lambda/(1.0 + alpha) , 1.e-7 );
                    break;
                case 3:                                   // Nielsen
                    lambda = lambda*fmax( 1.0/3.0, 1.0-pow(2.0*rho-1.0 , 3.0) );
                    nu = 2;
                    break;
            }
            
            if ( prnt > 1 )
            {
                graph2d->Update2d();
                graph2d->Refresh(true);
                //        eval(plotcmd);
                //PlotBands(t_Complete,p,150);
                //        PlotBandsYData(t_Complete,p,c,200);
                //prnt;
                //lastp=p;
            }
        }    
        else                                           // it IS NOT better
        {   
            X2 = X2_old;                             // do not accept p_try
            
            if (remainder(iteration,2*Npar) != 0)            // rank-1 update of Jacobian
            {
                double dX2Out = 0.0;
                double minusone = -1.0;
                lm_matx(t, p_old, np, y_old, ny, minusone, J, p, y_dat, weight, dp, c, JtWJ, JtWdy, dX2Out, y_hat, func_calls, iteration, LowerSymMatrixHf, LowerSymMatrixSf, eigHf, natoms, isSOC, isOverlap);
            }
            
            // increase lambda  ==> gradient descent method
            
            switch (Update_Type)
            {
                case 1:                                   // Levenberg
                    lambda = fmin(lambda*lambda_UP_fac,1.e7);
                    break;
                case 2:                                   // Quadratic
                    lambda = lambda + fabs((X2_try - X2)/2.0/alpha);
                    break;
                case 3:                                   // Nielsen
                    lambda = lambda * nu;
                    nu = 2*nu;
                    break;
            }
            
        }
        
        if ( prnt > 1 )
        {
            data = _("");
            //data.append(wxString::Format(wxT(">it:%d: call num:%d | chi_sq=%.8f | lambda=%.8f\n"), iteration, func_calls, X2/DoF, lambda));
            data.append(wxString::Format(wxT(">Step number: %d\n"), iteration));
            data.append(_("\n"));
            data.append(_("parameters:\n"));
            for(int ip=0; ip<np; ip++) data.append(wxString::Format(wxT(" %.8f,"), p[ip]));
            data.append(_("\n"));
            data.append(_("\n"));
            data.append(_("variation of parameter:\n"));
            for(int ip=0; ip<np; ip++) data.append(wxString::Format(wxT(" %.8f,"), h[ip]/p[ip]));
            data.append(_("\n"));
            data.append(_("\n"));
            SendDataToTerminal(data);
            
            if (isOneStep)
            {
                data = _("");
                data.append(_("********************* One Step Done! *********************\n"));
                SendDataToTerminal(data);
                break;
            }
            
            if(sec30->IsStopClicked)
            {
                data = _("");
                data.append(_("******************** Regression Stoped *******************\n"));
                SendDataToTerminal(data);
                sec30->IsStopClicked = false;
                break;
            }
        }
        
        // update convergence history ... save _reduced_ Chi-square
        cvg_hst[iteration - 1][0] = func_calls;
        for (int ip=0; ip<Npar; ip++)
            cvg_hst[iteration - 1][ip + 1] = p[ip];
        cvg_hst[iteration - 1][Npar + 1] = X2/DoF;
        cvg_hst[iteration - 1][Npar + 2] = lambda;
        
        for(int ip=0; ip<np; ip++) hperP[ip] = h[ip]/p[ip];
        
        if ( maxabs(JtWdy,np) < epsilon_1  &&  iteration > 2 && !isOneStep )
        {
            data = _("");
            data.append(wxString::Format(wxT("Convergence Tolerance for Gradient = %.8f\n"),epsilon_1));
            data.append(_("********************* Convergence achieved *********************\n"));
            SendDataToTerminal(data);
            stop = true;
            break;
        }
        else if ( maxabs(hperP,np) < epsilon_2  &&  iteration > 2 && !isOneStep )
        {
            data = _("");
            data.append(wxString::Format(wxT("Convergence Tolerance for Parameters = %.8f\n"),epsilon_2));
            data.append(_("********************* Convergence achieved *********************\n"));
            SendDataToTerminal(data);
            stop = true;
            break;
        }
        else if ( X2/DoF < epsilon_3 &&  iteration > 2 && !isOneStep )
        {
            data = _("");
            data.append(wxString::Format(wxT("Convergence Tolerance for Chi-square = %.8f\n"),epsilon_3));
            data.append(_("********************* Convergence achieved *********************\n"));
            SendDataToTerminal(data);
            stop = true;
            break;
        }
        else if ( iteration == MaxIter && !isOneStep)
        {
            data = _("");
            data.append(_("Maximum number of iterations reached without convergence!\n"));
            SendDataToTerminal(data);
            stop = true;
            break;
        }
    }                                        // --- End of Main Loop
    ////////////////////////////////////////////////////////////////////////
    
    // --- convergence achieved, find covariance and confidence intervals
    
    if (!BadCondition)
    {
        // ---- Error Analysis ----

        if (Variance(weight, ny) == 0.0)   // recompute equal weights for paramter error analysis
        {
            double dydy = VecVec2Num(delta_y, delta_y, ny);
            for(int iy=0; iy<ny; iy++)
                weight[iy] = 1.0*DoF/dydy;
            //weight = DoF/(Transpose(delta_y).delta_y) * ones(Npnt,1);
        }
        
        redX2 = X2 / DoF;
        
        double minusone2 = -1.0;
        lm_matx(t, p_old, np, y_old, ny, minusone2, J, p, y_dat, weight, dp, c, JtWJ, JtWdy, X2, y_hat, func_calls, iteration, LowerSymMatrixHf, LowerSymMatrixSf, eigHf, natoms, isSOC, isOverlap);
        
        
        for (int ip=0; ip<np; ip++)
            for (int jp=0; jp<np; jp++)
                JtWJArr[ip * np + jp] = JtWJ[ip][jp];
                
        
        for (int ip=0; ip<np; ip++)
            for (int jp=0; jp<np; jp++)
                covar_p[ip * np + jp] = 0.0;
        for (int ip=0; ip<np; ip++) covar_p[ip * np + ip] = 1.0;
        
        int info2 = LAPACKE_dgesv(LAPACK_ROW_MAJOR, np, np, JtWJArr, np, ipiv2, covar_p, np);
        
        for(int ip=0; ip<np; ip++) sigma_p[ip] = sqrt(fabs(covar_p[ip * np + ip]));
    }
    // endfunction  # ---------------------------------------------------------- LM
    
    
    ///////////////Out of While Loop///////////
    delete [] y_hat;
    delete [] JtWdy;
    for (int ip=0; ip<np; ip++) delete [] JtWJ[ip];
    if (np>0) delete [] JtWJ;
    for (int iy=0; iy<ny; iy++) delete [] J[iy];
    if (ny>0) delete [] J;
    delete [] y_old;
    delete [] p_old;
    delete [] hperP;
    delete [] h;
    delete [] h2;
    delete [] ipiv;
    delete [] ipiv2;
    delete [] hInv;
    delete [] y1;
    delete [] delta_y;
    delete [] p_try;
    delete [] weighted_dy;
    delete [] weighted_dy2;
    delete [] JtWJArr;
    delete [] covar_p;
    delete [] idx;
    ///////////////Out of While Loop///////////
    
    //////////////////////////////////////////////////////////////////////
    //Strange problem. Void function without "return;" works fine through
    //codelite (Both debug and release). But does not work from explorer
    //(Both debug and release). It may come from the new thread that this
    //function is running on it.
    //Very more strange: we have crash in the case of "Maximum number of
    //iterations reached without convergence!", but not for "Convergence
    //Tolerance for Parameters = %.8f"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //so
    return;
    //////////////////////////////////////////////////////////////////////
}

void Regression::lm_FD_J(double* t, double* p, int np, double* y, int ny, double* dp, double* c, double** J, int &func_calls, lapack_complex_double* LowerSymMatrixHf, lapack_complex_double* LowerSymMatrixSf, double* eigHf, int natoms, bool isSOC, bool isOverlap)
{
    int m=ny;              // number of data points
    int n=np;              // number of parameters
    
    double* y1 = new double[ny];
    double* y2 = new double[ny];
    
    double* ps = new double[n];
    for (int ip=0; ip<np; ip++) ps[ip] = p[ip];
    
    double* del = new double[n];
    for (int ip=0; ip<np; ip++) del[ip] = 0.0;
    
    for (int iy=0; iy<ny; iy++)
        for (int ip=0; ip<np; ip++)
            J[iy][ip] = 0.0;
    
    for(int j=0; j<n; j++)                 // START --- loop over all parameters
    {
        del[j] = dp[j] * (1.0 + fabs(p[j]));   // parameter perturbation
        p[j]   = ps[j] + del[j];          // perturb parameter p(j)
        
        if (del[j] != 0)
        {
            func(t, ny, p, np, c, y1, LowerSymMatrixHf, LowerSymMatrixSf, eigHf, natoms, isSOC, isOverlap);
            func_calls = func_calls + 1;
            
            if (dp[j] < 0)                  // backwards difference
            {
                for(int iy=0; iy<ny; iy++) J[iy][j] = (y1[iy]-y[iy])/del[j];
            }
            else                            // central difference, additional func call
            {
                p[j] = ps[j] - del[j];
                func(t, ny, p, np, c, y2, LowerSymMatrixHf, LowerSymMatrixSf, eigHf, natoms, isSOC, isOverlap);
                for(int iy=0; iy<ny; iy++)
                {
                    J[iy][j] = (y1[iy]-y2[iy]) / (2.0 * del[j]);
                }
                func_calls = func_calls + 1;
            }
        }
        p[j]=ps[j];                       // restore p(j)
    }                       // END --- loop over all parameters

    // endfunction # -------------------------------------------------- LM_FD_J
    delete [] del;
    delete [] ps;
    delete [] y1;
    delete [] y2;
}

void Regression::lm_Broyden_J(double* p_old, double* y_old, double** J, double* p, int np, double* y, int ny)
{
    double* h = new double[np];
    for (int ip=0; ip<np; ip++) h[ip]  = p[ip] - p_old[ip];
    
    double* y2 = new double[ny];
    MatVec2Vec(J, ny, np, h, y2);
    
    double* y3 = new double[ny];
    for (int iy=0; iy<ny; iy++) y3[iy]  = y[iy] - y_old[iy] - y2[iy];
    
    double** A = new double*[ny];
    for (int iy=0; iy<ny; iy++) A[iy] = new double[np];
    VecVec2Mat(y3, ny, h, np, A);
    
    double A0 = VecVec2Num(h, h, np);
    
    for (int iy=0; iy<ny; iy++)
        for (int ip=0; ip<np; ip++)
            J[iy][ip] = J[iy][ip] + A[iy][ip]/A0;
    
    //J = J + (y - y_old - J*h )*h' / (h'*h);       // Broyden rank-1 update eq'n
    //J = J + (y - y_old - y2)*h / (h*h);       // Broyden rank-1 update eq'n
    //J = J + y3*h / A0;       // Broyden rank-1 update eq'n
    //J = J + A/A0;       // Broyden rank-1 update eq'n
    // endfunction # ---------------------------------------------- LM_Broyden_J
    delete [] h;
    delete [] y2;
    delete [] y3;
    for (int iy=0; iy<ny; iy++) delete [] A[iy];
    if (ny > 0) delete [] A;
}

void Regression::lm_matx(double* t,double* p_old, int np, double* y_old, int ny, double dX2, double** J, double* p, double* y_dat, double* weight, double* dp, double* c, double** JtWJ, double* JtWdy, double Chi_sq, double* y_hat, int &func_calls, int &iteration, lapack_complex_double* LowerSymMatrixHf, lapack_complex_double* LowerSymMatrixSf, double* eigHf, int natoms, bool isSOC, bool isOverlap)
{
    int Npnt = ny;               // number of data points
    int Npar = np;               // number of parameters
    
    func(t, ny, p, np, c, y_hat, LowerSymMatrixHf, LowerSymMatrixSf, eigHf, natoms, isSOC, isOverlap);          // evaluate model using parameters 'p'
    func_calls = func_calls + 1;

    if ( remainder(iteration,2*Npar) != 0 || dX2 > 0 )
    {
        lm_FD_J(t, p, np, y_hat, ny, dp, c, J, func_calls, LowerSymMatrixHf, LowerSymMatrixSf, eigHf, natoms, isSOC, isOverlap);    //finite difference
        //J = lm_FD_J(t,p,y_hat,dp,c);
    }
    else
    {
        lm_Broyden_J(p_old, y_old, J, p, np, y_hat, ny);          //rank-1 update
        //J = lm_Broyden_J(p_old,y_old,J,p,y_hat);
    }
    
    double* delta_y = new double[ny];
    
    for(int iy=0; iy<ny; iy++)
        delta_y[iy] = y_dat[iy] - y_hat[iy];            // residual error between model and data
    
    double* weighted_dy = new double[ny];
    for(int iy=0; iy<ny; iy++) weighted_dy[iy] = delta_y[iy] * weight[iy];
    Chi_sq = VecVec2Num(delta_y, weighted_dy, ny);              // Chi-squared error criteria
    //Chi_sq = delta_y' * ( delta_y .* weight );
    
    double** JT = new double*[np];
    for (int ip=0; ip<np; ip++) JT[ip] = new double[ny];
    Transpose(J, ny, np, JT);
    
    double** weighted_J = new double*[ny];
    for (int iy=0; iy<ny; iy++) weighted_J[iy] = new double[np];
    
    for (int iy=0; iy<ny; iy++)
        for (int ip=0; ip<np; ip++)
            weighted_J[iy][ip] = J[iy][ip]*weight[iy];
    
    MatMat2Mat(JT, weighted_J, np, ny, np, JtWJ);
    //JtWJ  = J' * ( J .* ( weight * ones(1,Npar) ) );
    
    MatVec2Vec(JT, np, ny, weighted_dy, JtWdy);
    //JtWdy = J' * ( weight .* delta_y );
    // endfunction  # ------------------------------------------------------ LM_MATX
    
    for (int iy=0; iy<ny; iy++) delete [] weighted_J[iy];
    if (ny > 0) delete [] weighted_J;
    
    for (int ip=0; ip<np; ip++) delete [] JT[ip];
    if (np > 0) delete [] JT;
    
    if (ny > 0) delete [] weighted_dy;
    
    if (ny > 0) delete [] delta_y;
}

void Regression::MatVec2Vec(double** a, int na, int ma, double* b, double* c)
{
    for(int ia=0; ia<na; ia++)
    {
        c[ia] = 0.0;
        for(int ja=0; ja<ma; ja++)
            c[ia] += a[ia][ja]*b[ja];
    }
}

void Regression::VecVec2Mat(double* a, int na, double* b, int nb, double** c)
{
    for(int ia=0; ia<na; ia++)
        for(int ib=0; ib<nb; ib++)
            c[ia][ib] = a[ia]*b[ib];
}

void Regression::MatMat2Mat(double** a, double** b, int na, int manb, int mb, double** c)
{
    for (int ic = 0; ic < na; ic++)
        for (int jc = 0; jc < mb; jc++)
        {
            double sum = 0;
            for (int k = 0; k < manb; k++) sum += a[ic][k]*b[k][jc];
            c[ic][jc] = sum;
        }
}

double Regression::VecVec2Num(double* a, double* b, int na)
{
    double val = 0.0;
    for(int ia=0; ia<na; ia++) val += a[ia]*b[ia];
    return val;
}

void Regression::Transpose(double** a, int na, int nb, double** aT)
{
    for(int ia=0; ia<na; ia++)
        for(int ib=0; ib<nb; ib++)
            aT[ib][ia] = a[ia][ib];
}

void Regression::func(double* t, int ny, double* p, int np, double* cnst, double* y, lapack_complex_double* LowerSymMatrixHf, lapack_complex_double* LowerSymMatrixSf, double* eigHf, int natoms, bool isSOC, bool isOverlap)
{
    bool isSpin = false;
    if (isSOC) isSpin = true;
    
    bool isBandLoaded;
    if (sec30->ArraysOf0DInt[0] != 0) isBandLoaded = true;
    if (!isBandLoaded) return;
    int nKPoint = sec30->ArraysOf0DInt[1];
    if (nKPoint < 1)  return;
    
    //myGrid* osgc = sec30->GetGridObject(_("OS"));
    //myGrid* skgc = sec30->GetGridObject(_("SK"));
    //myGrid* olgc = sec30->GetGridObject(_("OL"));
    
    for (int ip=0; ip<np; ip++)
    {
        int GridInd = sec30->ArraysOf2DInt[1][ip][0];
        int irow = sec30->ArraysOf2DInt[1][ip][1];
        //double Value = p[ip];
        //wxString val = wxString::Format(wxT("%.8f"), Value);
        if (GridInd == 1)
        {
            sec30->OSBuffer[irow] = p[ip];
            //osgc->SetCellValue(irow, 2, val);
        }
        else if (GridInd == 2)
        {
            sec30->SKBuffer[irow] = p[ip];
            //skgc->SetCellValue(irow, 2, val);
        }
        else if (GridInd == 3)
        {
            sec30->OLBuffer[irow] = p[ip];
            //olgc->SetCellValue(irow, 2, val);
        }
    }

    double a[3],b[3],c[3];
    a[0] = cnst[0];
    a[1] = cnst[1];
    a[2] = cnst[2];
    b[0] = cnst[3];
    b[1] = cnst[4];
    b[2] = cnst[5];
    c[0] = cnst[6];
    c[1] = cnst[7];
    c[2] = cnst[8];
    
    double ak[3],bk[3],ck[3];
    sec30->VecToReciprocal(a, b, c, ak, bk, ck);
    
    //int natoms = 0;
    //sec30->GetVar(_("nAtoms[0]"),natoms);
    //bool isSOC;
    //sec30->GetCheckVar(_("SOC[0]"), isSOC);
    //bool isOverlap;
    //sec30->GetCheckVar(_("Overlap[0]"), isOverlap);
    
    double** XYZCoords = new double*[natoms];
    for (int i=0; i<natoms; i++) XYZCoords[i] = new double[3];
    
    int ind=9;
    for (int i=0; i<natoms; i++)
    {
        XYZCoords[i][0] = cnst[ind++];
        XYZCoords[i][1] = cnst[ind++];
        XYZCoords[i][2] = cnst[ind++];
    }
    
    Adouble2D Hf, Sf, SOC_f;
    int nEssensialCells;
    int nHamiltonian;
    Aint1D EssCells;

    //4. It should be arrays not a vector
    if(isOverlap)
        sec30->ConstructTBHamiltonianF(a, b, c, XYZCoords, Hf, Sf, nEssensialCells, nHamiltonian, EssCells, isSOC, SOC_f);
    else
        sec30->ConstructTBHamiltonianF(a, b, c, XYZCoords, Hf, nEssensialCells, nHamiltonian, EssCells, isSOC, SOC_f);
    
    sec30->ArraysOf3DDouble[1] = Hf;
    sec30->ArraysOf3DDouble[3] = Sf;
    if (isSOC)
        sec30->ArraysOf3DDouble[5] = SOC_f;
    else
        sec30->ArraysOf3DDouble[5] = Adouble2D();
    
    for (int i=0; i<natoms; i++) delete [] XYZCoords[i];
    if (natoms>0) delete [] XYZCoords;
    
    //double** KPoints; [ka,kb,kc,kx,ky,kz,d_path]
    Adouble1D KPoints = sec30->ArraysOf2DDouble[0];
    
    //////////////////////////////Allocate all arrays//////////////////////////////////
    int** lmnEssCells = new int*[nEssensialCells];
    double*** Mf = new double**[nEssensialCells];
    
    for(int iECell = 0; iECell < nEssensialCells; iECell++)
    {
        lmnEssCells[iECell] = new int[3];
        Mf[iECell] = new double*[nHamiltonian];
        for(int i = 0; i < nHamiltonian; i++)
        {
            Mf[iECell][i] = new double[nHamiltonian];
        }
    }
    
    double*** sMf;
    if(isOverlap)
    {
        sMf = new double**[nEssensialCells];
        for(int iECell = 0; iECell < nEssensialCells; iECell++)
        {
            sMf[iECell] = new double*[nHamiltonian];
            for(int i = 0; i < nHamiltonian; i++)
            {
                sMf[iECell][i] = new double[nHamiltonian];
            }
        }
    }
    
    //////////////////////////////Fill all arrays//////////////////////////////////
    for(int iECell = 0; iECell < nEssensialCells; iECell++)
    {
        for(int i = 0; i < 3; i++) lmnEssCells[iECell][i] = EssCells[iECell][i];
        
        for(int i = 0; i < nHamiltonian; i++)
            for(int j = 0; j < nHamiltonian; j++)
            {
                Mf[iECell][i][j] = Hf[iECell][i][j];
            }
    }
    
    if(isOverlap)
    {
        for(int iECell = 0; iECell < nEssensialCells; iECell++)
        {
            for(int i = 0; i < nHamiltonian; i++)
                for(int j = 0; j < nHamiltonian; j++)
                {
                    sMf[iECell][i][j] = Sf[iECell][i][j];
                }
        }
    }
    /////////////////////////Calculate the TB Band-structure////////////////////////
    
    int nHamiltonianTot;
    if (isSpin)
        nHamiltonianTot = 2*nHamiltonian;
    else
        nHamiltonianTot = nHamiltonian;
        
    Adouble1D fTBEigVal(nKPoint,std::vector<double>(nHamiltonianTot));
    int nH2 = nHamiltonianTot*nHamiltonianTot;
    
    int nOverlapMat = (nHamiltonianTot+nH2) + 1;
    lapack_complex_double lzerocomplex = {0.0, 0.0};
    if(isOverlap)
    {
        LowerSymMatrixHf = new lapack_complex_double[nOverlapMat];
        LowerSymMatrixSf = new lapack_complex_double[nOverlapMat];
        for(int i=0; i<nOverlapMat; i++)
        {
            LowerSymMatrixHf[i] = lzerocomplex;
            LowerSymMatrixSf[i] = lzerocomplex;
        }
    }
    else
    {
        LowerSymMatrixHf = new lapack_complex_double[nH2];
        for(int i=0; i<nH2; i++)
        {
            LowerSymMatrixHf[i] = lzerocomplex;
        }
    }
    
    for (int i=0; i<nHamiltonianTot; i++) eigHf[i] = 0.0;
    
    for (int ik=0; ik<nKPoint; ik++)
    {
        double frac[3] = {KPoints[ik][0], KPoints[ik][1], KPoints[ik][2]};
        double absol[3];
        sec30->FracToAbs(ak, bk, ck, frac, absol);
        double kx = absol[0];
        double ky = absol[1];
        double kz = absol[2];
        
        //kx = KPoints[ik][3];
        //ky = KPoints[ik][4];
        //kz = KPoints[ik][5];
        
        //wxString data = wxString::Format(_("kx = %.8f ky = %.8f kz = %.8f \n"),kx,ky,kz);
        //SendDataToTerminal(data);
        if (isSpin)
        {
            lapack_complex_double cmlx;
            if(isOverlap)
            {
                for(int i=0; i<nOverlapMat; i++)
                {
                    LowerSymMatrixHf[i] = lzerocomplex;
                    LowerSymMatrixSf[i] = lzerocomplex;
                }
                
                for(int iH=0; iH<nHamiltonian; iH++)
                {
                    for(int jH=iH; jH>=0; jH--)
                    {
                        int i1 = 2*(iH - jH); // i1 = (2*iH) - (2*jH);
                        LowerSymMatrixHf[i1 * nHamiltonianTot + 2*iH] = sec30->GetHk(Mf, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                        LowerSymMatrixSf[i1 * nHamiltonianTot + 2*iH] = sec30->GetHk(sMf, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                        LowerSymMatrixHf[i1 * nHamiltonianTot + 2*iH + 1] = LowerSymMatrixHf[i1 * nHamiltonianTot + 2*iH];
                        LowerSymMatrixSf[i1 * nHamiltonianTot + 2*iH + 1] = LowerSymMatrixSf[i1 * nHamiltonianTot + 2*iH];
                    }
                }
                
                //Add SOC to Hk
                for(int iH=0; iH<nHamiltonianTot; iH++)
                {
                    eigHf[iH] = 0.0;
                    for(int jH=iH; jH>=0; jH--)
                    {
                        int i1 = iH - jH;
                        cmlx = {SOC_f[0][iH][jH], SOC_f[1][iH][jH]};// Real and Imaginary parts of SOC are [0] and [1]
                        LowerSymMatrixHf[i1 * nHamiltonianTot + iH] += cmlx;
                    }
                }
            }
            else
            {
                for(int iH=0; iH<nHamiltonian; iH++)
                {
                    for(int jH=0; jH<=iH; jH++)
                    {
                        LowerSymMatrixHf[2*iH * nHamiltonianTot + 2*jH] = sec30->GetHk(Mf, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                        LowerSymMatrixHf[2*iH * nHamiltonianTot + 2*jH + 1] = lzerocomplex;
                        LowerSymMatrixHf[(2*iH + 1) * nHamiltonianTot + 2*jH + 1] = LowerSymMatrixHf[2*iH * nHamiltonianTot + 2*jH];
                        LowerSymMatrixHf[(2*iH + 1) * nHamiltonianTot + 2*jH] = lzerocomplex;
                    }
                }
                
                //Add SOC to Hk
                for(int iH=0; iH<nHamiltonianTot; iH++)
                {
                    eigHf[iH] = 0.0;
                    for(int jH=0; jH<=iH; jH++)
                    {
                        cmlx = {SOC_f[0][iH][jH], SOC_f[1][iH][jH]};// Real and Imaginary parts of SOC are [0] and [1]
                        LowerSymMatrixHf[iH * nHamiltonianTot + jH] += cmlx;
                    }
                }
            }
        }
        else
        {
            if(isOverlap)
            {
                for(int i=0; i<nOverlapMat; i++)
                {
                    LowerSymMatrixHf[i] = lzerocomplex;
                    LowerSymMatrixSf[i] = lzerocomplex;
                }
                
                for(int iH=0; iH<nHamiltonian; iH++)
                {
                    eigHf[iH] = 0.0;
                    for(int jH=iH; jH>=0; jH--)
                    {
                        int i1 = iH - jH;
                        LowerSymMatrixHf[i1 * nHamiltonianTot + iH] = sec30->GetHk(Mf, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                        LowerSymMatrixSf[i1 * nHamiltonianTot + iH] = sec30->GetHk(sMf, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                    }
                }
            }
            else
            {
                for(int iH=0; iH<nHamiltonian; iH++)
                {
                    eigHf[iH] = 0.0;
                    for(int jH=0; jH<=iH; jH++)
                    {
                        LowerSymMatrixHf[iH * nHamiltonianTot + jH] = sec30->GetHk(Mf, kx, ky, kz, a, b, c, nEssensialCells, lmnEssCells, iH, jH);
                    }
                }
            }
        }
        
        if(isOverlap)
            sec30->SymEigenValues(LowerSymMatrixHf, LowerSymMatrixSf, nHamiltonianTot, eigHf);
        else
            sec30->SymEigenValues(LowerSymMatrixHf, nHamiltonianTot, eigHf);
        
        for(int iH=0; iH<nHamiltonianTot; iH++) fTBEigVal[ik][iH] = eigHf[iH];
    }
    
    sec30->ArraysOf2DDouble[3] = fTBEigVal;
    
    //////////////////////////////Fill the y array for fitting//////////////////////////////////
    for (int iy=0; iy<ny; iy++)
    {
        int tbband = sec30->ArraysOf2DInt[2][iy][0]; //FitPoints[iy][0]
        //int dftband = FitPoints[iy][1]; //FitPoints[iy][1]
        int ik = sec30->ArraysOf2DInt[2][iy][2]; //FitPoints[iy][2]
        y[iy] = fTBEigVal[ik][tbband - 1];
    }
    
    //////////////////////////////Deallocate all arrays//////////////////////////////////
    for(int iECell = 0; iECell < nEssensialCells; iECell++)
    {
        for(int i = 0; i < nHamiltonian; i++) delete [] Mf[iECell][i];
        delete [] Mf[iECell];
        delete [] lmnEssCells[iECell];
    }
	if (nEssensialCells>0) delete [] Mf;
    if (nEssensialCells>0) delete [] lmnEssCells;
    
    if(isOverlap)
    {
        for(int iECell = 0; iECell < nEssensialCells; iECell++)
        {
            for(int i = 0; i < nHamiltonian; i++) delete [] sMf[iECell][i];
            delete [] sMf[iECell];
        }
        if (nEssensialCells>0) delete [] sMf;
    }
}

void Regression::SendDataToTerminal(wxString data)
{
    wxCommandEvent* event = new wxCommandEvent(RegressionEVT_OnNewData);
    event->SetString(data);
    wxQueueEvent(Parent,event);
}

void Regression::SendEventRunFinished()
{
    wxCommandEvent* event = new wxCommandEvent(RegressionEVT_OnFinished);
    wxQueueEvent(Parent,event);
}

void Regression::SendEventRunStarted()
{
    wxCommandEvent* event = new wxCommandEvent(RegressionEVT_OnStarted);
    wxQueueEvent(Parent,event);
}
