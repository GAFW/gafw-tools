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

#include "FrequencyQuantity.h"
using namespace GAFW::Tools::CPPParameters;

std::vector<SimpleDimensionedValue<double,false,true,FrequencyQuantity>::Conv> FrequencyQuantity::createConversion() const
{
    const SimpleDimensionedValue<double,false,true,FrequencyQuantity>::Conv myConv[]={ 
        {1.0, "hertz"} , {1.0,"Hz"},
        {1e-1,"dHz"} , { 1e-1,"decihertz"},
        {1e-2,"cHz"} , { 1e-2,"centihertz"},
        {1e-3,"mHz"} , { 1e-3,"millihertz"},
        {1e-6,"uHz"} , { 1e-6,"microhertz"},
        {1e-9,"nHz"} , { 1e-9,"nanohertz"},
        {1e-12,"pHz"} , { 1e-12,"picohertz"},
        {1e-15,"fHz"} , { 1e-15,"femtohertz"},
        {1e-18,"aHz"} , { 1e-18,"attohertz"},
        {1e-21,"zHz"} , { 1e-21,"zeptohertz"},
        {1e-24,"yHz"} , { 1e-24,"yoctohertz"},
        {1e1,"daHz"} , { 1e1,"decahertz"},
        {1e2,"hHz"} , { 1e2,"hectohertz"},
        {1e3,"kHz"} , { 1e3,"kilohertz"},
        {1e6,"MHz"} , { 1e6,"megahertz"},
        {1e9,"GHz"} , { 1e9,"gigahertz"},
        {1e12,"THz"} , { 1e12,"terahertz"},
        {1e15,"PHz"} , { 1e15,"petahertz"},
        {1e18,"EHz"} , { 1e18,"exahertz"},
        {1e21,"ZHz"} , { 1e21,"zettahertz"},
        {1e24,"YHz"} , { 1e24,"	yottahertz"}
    };
        

    const int noOfConvs=42;
    
    std::vector<SimpleDimensionedValue<double,false,true,FrequencyQuantity>::Conv> c;
    for (int x=0;x<noOfConvs;x++) c.push_back(myConv[x]);
    return c;
}
FrequencyQuantity::FrequencyQuantity():SimpleDimensionedValue<double,false,true,FrequencyQuantity>("Time",this->createConversion())
{
    
}
FrequencyQuantity::FrequencyQuantity(const double &magnitude,const std::string &unit):SimpleDimensionedValue<double,false,true,FrequencyQuantity>("Frequency",this->createConversion(),magnitude,unit)
{
}

FrequencyQuantity::~FrequencyQuantity()
{
    
}
