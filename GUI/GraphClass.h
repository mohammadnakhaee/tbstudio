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
    void DiscardAtomicStructure();
    
protected:
    std::list<int> EssentialListi;
    std::list<int> EssentialListj;
    std::list<int> EssentialListk;
    virtual bool isItNew(int i,int j,int k);
    virtual void graph_OnPaint(wxPaintEvent& event);
    
};
#endif // GRAPHCLASS_H
