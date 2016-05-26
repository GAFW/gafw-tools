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

#ifndef __FREQUENCYQUANTITY_H__
#define __FREQUENCYQUANTITY_H__
#include "SimpleDimensionedValue.h"
namespace GAFW { namespace Tools { namespace CPPParameters {
    class FrequencyQuantity :public SimpleDimensionedValue<double,false,true,FrequencyQuantity>{
    protected:
         std::vector<SimpleDimensionedValue<double,false,true,FrequencyQuantity>::Conv> createConversion() const;
    public:
        FrequencyQuantity();
        FrequencyQuantity(const double &magnitude,const std::string &unit=std::string(""));
        virtual ~FrequencyQuantity();
       
    };
}}}

#endif /* TIMEQUANTITY_H */

