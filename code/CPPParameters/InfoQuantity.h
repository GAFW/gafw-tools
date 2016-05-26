/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InfoQuantity.h
 * Author: daniel
 *
 * Created on 13 March 2016, 21:45
 */

#ifndef __INFOQUANTITY_H__
#define __INFOQUANTITY_H__

#include "SimpleDimensionedValue.h"
namespace GAFW { namespace Tools { namespace CPPParameters {
    class InfoQuantity :public SimpleDimensionedValue<double,false,false,InfoQuantity>
    {
        std::vector<SimpleDimensionedValue<double,false,false,InfoQuantity>::Conv> createConversion() const;
    public:
        InfoQuantity();
        InfoQuantity(const double &magnitude,const std::string &unit=std::string(""));
        
    };
}}}
#endif /* INFOQUANTITY_H */

