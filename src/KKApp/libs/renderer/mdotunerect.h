#ifndef _MDOTUNERECT_H_
#define _MDOTUNERECT_H_

#include "leobase/mdobject.h"

class MdoTuneRect
{
public:
    MdoTuneRect();
    ~MdoTuneRect();

    void init();
    void create(float blankw, float blankh);

    VertexBlock vb;
    IndexBlock ib;
};

#endif // MDOTUNERECT_H
