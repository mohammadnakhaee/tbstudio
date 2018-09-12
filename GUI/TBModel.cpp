#include "TBModel.h"

TBModel::TBModel()
{
    a[0]=1.0; a[1]=0.0; a[2]=0.0;
    b[0]=0.0; b[1]=1.0; b[2]=0.0;
    c[0]=0.0; c[1]=0.0; c[2]=1.0;
    
    a_strain = 1.0; b_strain = 1.0; c_strain = 1.0;
    
    nAtoms = 0;
}

TBModel::~TBModel()
{
}

