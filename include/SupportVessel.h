// AUTORE FILE: Chinello Alessandro

#ifndef SUPPORT_VESSEL_H
#define SUPPORT_VESSEL_H

#include "NavalUnit.h"

class SupportVessel : public NavalUnit{
public:
    SupportVessel();
    void action(Battlefield& to_defend, Battlefield& to_attack, const Coordinate& t);
};

#endif
