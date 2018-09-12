#ifndef GRAPHCLASS_H
#define GRAPHCLASS_H
#include "wxcrafter.h"
#include "MyOpenGL.h"
#include "TBModel.h"

class GraphClass : public GraphBaseClass
{
public:
    TBModel* tbmodel;
    MyGLCanvas* glc;
    GraphClass(wxWindow* parent, int Dim);
    virtual ~GraphClass();
    
    void CreateAtomicStructure(TBModel* tbmodelvar);
    void DiscardAtomicStructure();
    
protected:
    virtual void graph_OnPaint(wxPaintEvent& event);
};
#endif // GRAPHCLASS_H
