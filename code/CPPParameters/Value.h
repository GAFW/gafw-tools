/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Value.h
 * Author: daniel
 *
 * Created on 05 March 2016, 20:38
 */

#ifndef __VALUE_H__
#define __VALUE_H__
#include <string>
namespace GAFW {  namespace Tools { namespace CPPParameters {
    
    class Value
    {
    
        
    public:
        virtual std::string getType()=0;
        virtual void setFromString(const std::string &value)=0;
        virtual std::string toString()=0;
        virtual Value * clone() const=0; 
        virtual void deleteClone()=0;
        virtual void getValue(Value &v)=0;
        virtual void setValue(const Value &v)=0;
    };
    
    
}}}

#endif /* VALUE_H */

