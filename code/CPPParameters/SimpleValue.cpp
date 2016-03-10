/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "SimpleValue.h"
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
    