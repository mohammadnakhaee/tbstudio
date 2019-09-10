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
    int ObjectID = -1;
    GraphClass(wxWindow* parent, int Dim, Sec30* sec30Var, int MyID);
    virtual ~GraphClass();
    
    //wxColourPickerCtrl* AColorCtrl[118];
    wxColourPickerCtrl* BColorCtrl[50];
    //wxColour BondColors[50];
    int nShowingUnitcell = -1;
    int nShowingAtoms = -1;
    int nShowingBonds = -1;
    void CreateAtomicStructure(Sec30* sec30var, bool IsNewAllocate = true);
    void Update2d0();
    void Update2d();
    void GetBondInfo(const wxString& bondtextvar, int& i, int& n, int& j, int& m, int& bondtype);
    void GetUnitcellInfo(const wxString& unitcelltextvar, int& l, int& m, int& n);
    void FindEssentials();
    void SetWorkingList(int l, int m, int n);
    void DiscardAtomicStructure();
    double GetAtomRadius(int kind);
    void SetLeftMouseMode(int mouseEventMode);
    int GetSelectedCount();
    int GetShowingAtomsCount();
    int GetShowingBondsCount();
    int GetShowingUnitcellCount();
    void GetAtoms_Selection(int* &Atoms);
    void SetCamDir(wxString direction);
    void RotateCam(wxString direction);
    
protected:
    std::list<int> EssentialListi;
    std::list<int> EssentialListj;
    std::list<int> EssentialListk;
    std::list<int> WorkingListi;
    std::list<int> WorkingListj;
    std::list<int> WorkingListk;
    std::list<int> AtomIndexListi;
    std::list<int> AtomIndexListj;
    virtual bool isItNew(int i,int j,int k);
    virtual bool isAtomIndexNew(int i,int j);
    virtual void graph_OnPaint(wxPaintEvent& event);
    
};
#endif // GRAPHCLASS_H
