#ifndef PASSCLASS_H
#define PASSCLASS_H
#include "wxcrafter.h"

class PassClass : public PassClassBase
{
public:
    PassClass(wxWindow* parent, int mode);
    virtual ~PassClass();
};
#endif // PASSCLASS_H
