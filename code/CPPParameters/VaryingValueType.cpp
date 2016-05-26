/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VaryingValueType.cpp
 * Author: daniel
 * 
 * Created on 28 March 2016, 19:14
 */

#include "VaryingValueType.h"
using namespace GAFW::Tools::CPPParameters;
VaryingValueType::VaryingValueType(const std::vector<Value *> &vec,const std::string & v):whichValueOk(-1)
{
    for (int x=0;x<vec.size();x++)
    {
        this->values.push_back(vec[x]->clone());
    }
    if (v=="")
    {
        try {
            this->setFromString(v);
        }
        catch (const std::exception &)
        {
            
        }
    }
    else this->setFromString(v);
}
VaryingValueType::~VaryingValueType()
{
    for (int x=0;x<this->values.size();x++)
    {
        this->values[x]->deleteClone();
    }
}
std::string VaryingValueType::getType()
{
    std::stringstream ss;
    ss<< "Varying Type (";
    for (int x=0;x<this->values.size();x++)
    {
        if (x!=0) ss<<";";
        ss<< this->values[x]->getType();
    }
    ss << ")";
    return ss.str();
}
void VaryingValueType::setFromString(const std::string &value)
{
    int x;
    for (x=0;x<this->values.size();x++)
    {
        try {
            this->values[x]->setFromString(value);
            break;
        } catch (const std::exception&)
        {
                
        }
    }
    if (x==this->values.size()) throw std::exception();
    this->whichValueOk=x;
}
std::string VaryingValueType::toString()
{
    if (this->whichValueOk==-1) throw std::exception();
    return this->values[this->whichValueOk]->toString();
}
Value * VaryingValueType::clone() const
{
    VaryingValueType * newType=new VaryingValueType(this->values);
    newType->whichValueOk=this->whichValueOk;
}
void VaryingValueType::deleteClone()
{
    delete this;
}
void VaryingValueType::getValue(Value &v)
{
    VaryingValueType * value=dynamic_cast<VaryingValueType *>(&v);
    if (value==NULL) throw std::exception();
    if (value->values.size()!=this->values.size())
        throw std::exception();
    value->whichValueOk=this->whichValueOk;
    if (value->whichValueOk!=-1) this->values[this->whichValueOk]->getValue(*value->values[this->whichValueOk]);
}
void VaryingValueType::setValue(const Value &v)
{
    const VaryingValueType * value=dynamic_cast<const VaryingValueType *>(&v);
    if (value==NULL) throw std::exception();
    if (value->values.size()!=this->values.size())
        throw std::exception();
    this->whichValueOk=value->whichValueOk;
    if (value->whichValueOk!=-1) this->values[this->whichValueOk]->setValue(*value->values[this->whichValueOk]);

}
Value& VaryingValueType::getSelectedValue()
{
    if (this->whichValueOk==-1) throw std::exception();
    return *this->values[this->whichValueOk];
    
}
int VaryingValueType::getWhichValueSelected()
{
    return this->whichValueOk;
}
void VaryingValueType::setSelectedValue(int select,const Value &v)
{
    if ((select <0)||(select>=this->values.size())) throw std::exception();
    this->values[select]->setValue(v);
    this->whichValueOk=select;
}