#ifndef GRAPHCLASS_H
#define GRAPHCLASS_H
#include "wxcrafter.h"
#include "MyOpenGL.h"
#include "Sec30.h"

class GraphClass : public GraphBaseClass
{
public:
    Sec30* sec30;
    MyGLCanvas* glc;
    GraphClass(wxWindow* parent, int Dim);
    virtual ~GraphClass();
    
    void CreateAtomicStructure(Sec30* sec30var);
    int GetShowingBondCount(int lmin, int lmax, int mmin, int mmax, int nmin, int nmax, int nUnitcellAtoms);
    void GetBondInfo(const wxString& bondtextvar, int& i, int& n, int& j, int& m, int& bondtype);
    void GetUnitcellInfo(const wxString& unitcelltextvar, int& l, int& m, int& n);
    void FindEssentials();
    void DiscardAtomicStructure();
    double GetAtomRadius(int kind);
    
protected:
    std::list<int> EssentialListi;
    std::list<int> EssentialListj;
    std::list<int> EssentialListk;
    std::list<int> AtomIndexListi;
    std::list<int> AtomIndexListj;
    virtual bool isItNew(int i,int j,int k);
    virtual bool isAtomIndexNew(int i,int j);
    virtual void graph_OnPaint(wxPaintEvent& event);
    
};
#endif // GRAPHCLASS_H
