/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parameter.h
 * Author: daniel
 *
 * Created on 04 March 2016, 21:40
 */

#ifndef PARAMETER_H
#define PARAMETER_H
#include "Value.h"
#include "ParameterName.h"

namespace GAFW { namespace Tools    { namespace CPPParameters {
class ParameterRegistry;
class Parameter {
    ParameterName * name;
    Value * value;
    void setParameterName(const std::string & parName);
    
    friend class ParameterRegistry;
public:
    Parameter(std::string fullName="",Value * value=NULL);
    Parameter(const Parameter& orig);
    virtual ~Parameter();
    ParameterName getParameterName();
    void getValue(Value &value);
    std::string getValue() const;
    std::string getValueType() const;
    void setValue(const Value &value);
    void setValue(std::string value);
    bool isValueSet();
    Parameter& operator=(Parameter && orig );
    Parameter& operator=(const Parameter & orig );
    
};
}}}
#endif /* PARAMETER_H */

