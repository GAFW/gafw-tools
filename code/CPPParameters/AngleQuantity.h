/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AngleQuantity.h
 * Author: daniel
 *
 * Created on 17 March 2016, 19:46
 */

#ifndef __ANGLEQUANTITY_H__
#define __ANGLEQUANTITY_H__
#include "SimpleDimensionedValue.h"
namespace GAFW { namespace Tools { namespace CPPParameters {
    class AngleQuantity :public SimpleDimensionedValue<double,false,false,AngleQuantity>{
    protected:
         std::vector<SimpleDimensionedValue<double,false,false,AngleQuantity>::Conv> createConversion() const;
    public:
        AngleQuantity();
        AngleQuantity(const double &magnitude,const std::string &unit=std::string(""));
        virtual ~AngleQuantity();
       
    };
}}}

#endif /* ANGLEQUANTITY_H */

