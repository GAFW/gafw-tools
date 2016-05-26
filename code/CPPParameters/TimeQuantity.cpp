/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimeQuantity.cpp
 * Author: daniel
 * 
 * Created on 14 March 2016, 21:16
 */

#include "TimeQuantity.h"
using namespace GAFW::Tools::CPPParameters;

std::vector<SimpleDimensionedValue<double,false,false,TimeQuantity>::Conv> TimeQuantity::createConversion() const
{
    const SimpleDimensionedValue<double,false,false,TimeQuantity>::Conv myConv[]={ 
        {1.0, "seconds"} , {1.0,"s"}, {1.0, "sec"} ,
        {60, "minute"}, {60,"m"},{60, "minutes"},{60,"min"},
        {3600, "hour"}, {3600,"hours"},{3600, "h"},
        {86400, "days"}, {86400,"d"},{86400, "day"}
    };
        

    const int noOfConvs=13;
    
    std::vector<SimpleDimensionedValue<double,false,false,TimeQuantity>::Conv> c;
    for (int x=0;x<noOfConvs;x++) c.push_back(myConv[x]);
    return c;
}
TimeQuantity::TimeQuantity():SimpleDimensionedValue<double,false,false,TimeQuantity>("Time",this->createConversion())
{
    
}
TimeQuantity::TimeQuantity(const double &magnitude,const std::string &unit):SimpleDimensionedValue<double,false,false,TimeQuantity>("Time",this->createConversion(),magnitude,unit)
{
}

TimeQuantity::~TimeQuantity()
{
    
}
