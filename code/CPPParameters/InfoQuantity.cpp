/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InfoQuantity.cpp
 * Author: daniel
 * 
 * Created on 13 March 2016, 21:45
 */

#include "InfoQuantity.h"
using namespace GAFW::Tools::CPPParameters;

std::vector<SimpleDimensionedValue<double,false,false,InfoQuantity>::Conv> InfoQuantity::createConversion() const
{
    const SimpleDimensionedValue<double,false,false,InfoQuantity>::Conv myConv[]={ 
        {1.0, "bytes"} , {1.0,"b"}, {1.0, "byte"} ,
        {1e3, "kilobytes"}, {1e3,"kB"},{1e3, "kilobyte"},
        {1e6, "megabytes"}, {1e6,"MB"},{1e6, "megabyte"},
        {1e9, "gigabytes"}, {1e9,"GB"},{1e9, "gigabyte"},
        {1e12, "terabytes"}, {1e12,"TB"},{1e12, "terabyte"},
        {1e15, "petabytes"}, {1e15,"PB"},{1e15, "petabyte"},
        {1e18, "exabytes"}, {1e18,"EB"},{1e18, "exabyte"},
        {1e21, "zettabytes"}, {1e21,"ZB"},{1e21, "zettabyte"},
        {1e24, "yottabytes"}, {1e24,"YB"},{1e24, "yottabyte"},
        {pow(1024,1), "kibibytes"}, {pow(1024,1),"KiB"},{pow(1024,1), "kibibyte"},
        {pow(1024,2), "mebibytes"}, {pow(1024,2),"MiB"},{pow(1024,2), "mebibyte"},
        {pow(1024,3), "gibibytes"}, {pow(1024,3),"GiB"},{pow(1024,3), "gibibyte"},
        {pow(1024,4), "tebibytes"}, {pow(1024,4),"TiB"},{pow(1024,4), "tebibyte"},
        {pow(1024,5), "pebibytes"}, {pow(1024,5),"PiB"},{pow(1024,5), "pebibyte"},
        {pow(1024,6), "exbiytes"}, {pow(1024,6),"EiB"},{pow(1024,6), "exbibyte"},
        {pow(1024,7), "zebibytes"}, {pow(1024,7),"ZiB"},{pow(1024,7), "zebibyte"},
        {pow(1024,8), "yobibytes"}, {pow(1024,8),"YiB"},{pow(1024,8), "yobibyte"}
        
    };
        

    const int noOfConvs=51;
    
    std::vector<SimpleDimensionedValue<double,false,false,InfoQuantity>::Conv> c;
    for (int x=0;x<noOfConvs;x++) c.push_back(myConv[x]);
    return c;
}

InfoQuantity::InfoQuantity():SimpleDimensionedValue<double,false,false,InfoQuantity>("Information Units",this->createConversion())
{
    
}

InfoQuantity::InfoQuantity(const double &magnitude,const std::string &unit):SimpleDimensionedValue<double,false,false,InfoQuantity>("Information Units",this->createConversion(),magnitude,unit)
{
    
}


