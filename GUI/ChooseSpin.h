#ifndef CHOOSESPIN_H
#define CHOOSESPIN_H
#include "wxcrafter.h"
#include "Sec30.h"

class ChooseSpin : public ChooseSpinBase
{
public:
    ChooseSpin(wxWindow* parent, int ndatasets, wxString filetype);
    virtual ~ChooseSpin();
};
#endif // CHOOSESPIN_H
