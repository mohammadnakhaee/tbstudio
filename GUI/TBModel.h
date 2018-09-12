#ifndef TBMODEL_H
#define TBMODEL_H
#include <list>
//#include <vector>

class TBModel
{
public:
    
    double a[3],b[3],c[3];
    double a_strain,b_strain,c_strain;
    int nAtoms;
    std::list<double> AArray;
    std::list<double> BArray;
    std::list<double> CArray;
    std::list<double> XArray;
    std::list<double> YArray;
    std::list<double> ZArray;
    std::list<int> KindArray;

    TBModel();
    ~TBModel();

};

#endif // TBMODEL_H
