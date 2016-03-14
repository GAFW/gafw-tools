/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "SimpleValue.h"
#include <boost/algorithm/string/case_conv.hpp>
using namespace GAFW::Tools::CPPParameters;
template <>
const char * SimpleValue<bool>::myType="Boolean";
template <>
const char * SimpleValue<int>::myType="Integer";
template <>
const char * SimpleValue<float>::myType="Float";
template <>
const char * SimpleValue<double>::myType="Double";
template <>
const char * SimpleValue<long int>::myType="Long Integer";
template <>
const char * SimpleValue<long long int>::myType="Very Long Integer";
template <>
const char * SimpleValue<unsigned int>::myType="Unsigned Integer";
template <>
const char * SimpleValue<unsigned long int>::myType="Unsigned Long Integer";
template <>
const char * SimpleValue<unsigned long long int>::myType="Unsigned Very Long Integer";
template <>
const char * SimpleValue<std::string>::myType="String";
template <>
void SimpleValue<std::string>::getValue(Value &v)
{
     v.setFromString(this->myValue);
}
template <>
void SimpleValue<bool>::setFromString(const std::string &value)
{
    std::stringstream ss;
    for (int x=0;x<value.size();x++)
    {
        ss<<(char)tolower(value[x]);
    }
    std::string v=ss.str();
    if ((v=="0")||(v=="false"))
    {
        this->myValue=false;
    }
    else if (((v=="1")||(v=="true")))
    {
        this->myValue=true;
    }
    else
    {
        throw std::exception();
    }
        
}
template <>
std::string SimpleValue<bool>::toString()
{
    if (this->myValue) return std::string("true");
    else return std::string("false");
    
}
    
    