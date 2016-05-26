/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AngleQuantity.cpp
 * Author: daniel
 * 
 * Created on 17 March 2016, 19:46
 */

#include "AngleQuantity.h"
using namespace GAFW::Tools::CPPParameters;
#define PI 3.14159265358979323846264338327950288419716939937510
std::vector<SimpleDimensionedValue<double,false,false,AngleQuantity>::Conv> AngleQuantity::createConversion() const
{
    const SimpleDimensionedValue<double,false,false,AngleQuantity>::Conv myConv[]={ 
        {(180.0/PI), "rad"} , {(180.0/PI), "radian"} , {(180.0/PI), "radians"},
        {1.0,"deg"},{(1.0),"degrees"},{(1.0),"degree"},
        {1.0/60.0, "arcminute"}, {1.0/60.0,"arcmin"},{1.0/60.0, "arcminutes"},{1.0/60.0, "amin"}, {1.0/60.0,"am"},{1.0/60.0, "amin"},{1.0/60.0, "MOA"},
        {1.0/3600.0, "arcsecond"}, {1.0/3600.0,"arcsec"},{1.0/3600.0, "arcseconds"},{1.0/3600.0, "asec"}, {1.0/3600.0,"as"},
        {1.0/3600000.0, "milliarcsecond"}, {1.0/3600000.0,"milliarcsec"},{1.0/3600000.0, "milliarcseconds"},{1.0/3600000.0, "mas"}, 
        {1.0/3600000000.0, "microarcsecond"}, {1.0/3600000000.0,"microarcsec"},{1.0/3600000000.0, "microarcseconds"},{0.0,""}
    };
        

    
    std::vector<SimpleDimensionedValue<double,false,false,AngleQuantity>::Conv> c;
    for (int x=0;myConv[x].unit!="";x++) c.push_back(myConv[x]);
    return c;
}
AngleQuantity::AngleQuantity():SimpleDimensionedValue<double,false,false,AngleQuantity>("Angle",this->createConversion())
{
    
}
AngleQuantity::AngleQuantity(const double &magnitude,const std::string &unit):SimpleDimensionedValue<double,false,false,AngleQuantity>("Angle",this->createConversion(),magnitude,unit)
{
}

AngleQuantity::~AngleQuantity()
{
    
}
