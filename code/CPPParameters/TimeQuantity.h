/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimeQuantity.h
 * Author: daniel
 *
 * Created on 14 March 2016, 21:16
 */

#ifndef __TIMEQUANTITY_H__
#define __TIMEQUANTITY_H__
#include "SimpleDimensionedValue.h"
namespace GAFW { namespace Tools { namespace CPPParameters {
    class TimeQuantity :public SimpleDimensionedValue<double,false,false>{
    protected:
         std::vector<SimpleDimensionedValue<double,false,false>::Conv> createConversion() const;
    public:
        TimeQuantity();
        TimeQuantity(const double &magnitude,const std::string &unit=std::string(""));
        virtual ~TimeQuantity();
    };
}}}

#endif /* TIMEQUANTITY_H */

