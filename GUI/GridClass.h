#ifndef GRIDCLASS_H
#define GRIDCLASS_H
#include "wxcrafter.h"
#include <wx/grid.h>

class GridClass : public GridBaseClass
{
public:
    GridClass(wxWindow* parent);
    virtual ~GridClass();
};
#endif // GRIDCLASS_H
