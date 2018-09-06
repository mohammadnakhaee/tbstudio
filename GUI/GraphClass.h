#ifndef GRAPHCLASS_H
#define GRAPHCLASS_H
#include "wxcrafter.h"

class GraphClass : public GraphBaseClass
{
public:
    GraphClass(wxWindow* parent, int Dim);
    virtual ~GraphClass();
protected:
    virtual void graph_OnPaint(wxPaintEvent& event);
};
#endif // GRAPHCLASS_H
