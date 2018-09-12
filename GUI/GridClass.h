#ifndef GRIDCLASS_H
#define GRIDCLASS_H
#include "wxcrafter.h"
#include <wx/grid.h>
#include "mygrid.h"
#include "TBModel.h"

class GridClass : public GridBaseClass
{
public:
    TBModel* tbmodel;
    GridClass(wxWindow* parent);
    virtual ~GridClass();
};
#endif // GRIDCLASS_H
