/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parameter.cpp
 * Author: daniel
 * 
 * Created on 04 March 2016, 21:40
 */

#include "Parameter.h"
#include "SimpleValue.h"
using namespace GAFW::Tools::CPPParameters;
Parameter::Parameter(std::string fullName,Value * val)
{
    if (fullName!="") this->name=new ParameterName(fullName);
    else this->name=NULL;
    if (val!=NULL)
        this->value=val->clone();
    else 
        this->value=NULL;
}
Parameter::Parameter(const Parameter& orig)
{
    if (orig.name!=NULL)
        this->name=new ParameterName(orig.name->getFullName());
    else this->name=NULL;
    if (orig.value!=NULL)
        this->value=orig.value->clone();
    else 
        this->value=NULL;

}
Parameter::~Parameter()
{
    if (this->name!=NULL)
        delete(this->name);
    if (this->value!=NULL)
        this->value->deleteClone();
}
ParameterName Parameter::getParameterName()
{
    if (this->name!=NULL)
        return *this->name;
    else
        throw std::exception();
}
void Parameter::getValue( Value &value)
{
    if (this->value!=NULL)
        this->value->getValue(value);
    else
        throw std::exception();
}
void Parameter::setParameterName(const std::string & parName)
{
    if (this->name!=NULL) delete this->name;
    this->name=new ParameterName(parName);
}
std::string Parameter::getValueType() const
{
   if (this->value!=NULL)
        return this->value->getType();
   else
       throw std::exception();
}
void Parameter::setValue(const Value& val) 
{
    if (this->value!=NULL)
        this->value->setValue(val);
    else
        this->value=val.clone();
}
void Parameter::setValue(std::string value)
{
    if (this->value!=NULL)
        this->value->setFromString(value);
    else
        this->value=SimpleValue<std::string>(value).clone();
}
Parameter& Parameter::operator=(Parameter && orig )
{
    if (orig.name!=NULL)
        this->name=new ParameterName(orig.name->getFullName());
    else this->name=NULL;
    if (orig.value!=NULL)
        this->value=orig.value->clone();
    else 
        this->value=NULL;
    return *this;
}
Parameter& Parameter::operator=(const Parameter & orig )
{
    if (orig.name!=NULL)
        this->name=new ParameterName(orig.name->getFullName());
    else this->name=NULL;
    if (orig.value!=NULL)
        this->value=orig.value->clone();
    else 
        this->value=NULL;
    return *this;
}
bool Parameter::isValueSet()
{
    return bool(this->value);
}
std::string Parameter::getStringValue() const
{
    if (this->value!=NULL)
        return this->value->toString();
   else
       throw std::exception();
}
Value & Parameter::getValue() const
{
    if (this->value!=NULL)
        return *this->value;
}