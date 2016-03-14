/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListValue.cpp
 * Author: daniel
 * 
 * Created on 14 March 2016, 20:00
 */

#include <sstream>
#include <boost/regex.hpp>
#include "ListValue.h"
using namespace GAFW::Tools::CPPParameters;

ListValue::ListValue(const std::vector<std::string> &regexList,const std::string &value):regexList(regexList)
{
    this->choice=-1;
    this->setFromString(value);
}
ListValue::ListValue(const std::vector<std::string> &regexList,const int &value):regexList(regexList)
{
    this->choice=-1;
    this->setValue(value);
    
}
ListValue::~ListValue()
{
    
}
std::string ListValue::getType()
{
    return "String List";
}
void ListValue::setFromString(const std::string &value)
{
    for (int x=0;x<this->regexList.size();x++)
    {
        boost::regex reg(this->regexList[x].c_str());
        boost::smatch what;
        if (boost::regex_search(value,what,reg))
        {
            this->choice=x;
            return;
        }
    }
    throw std::exception();
}
std::string ListValue::toString()
{
    if (this->choice==-1) throw std::exception();
    std::stringstream ss;
    ss << this->choice;
    return ss.str();
}
Value * ListValue::clone() const
{
    return new ListValue(this->regexList,this->choice);
}
void ListValue::deleteClone()
{
    delete this;
}
void ListValue::getValue(Value &v)
{
    ListValue * cast=dynamic_cast<ListValue *>(&v);
    if (cast==NULL) throw std::exception();
    //Let's compare vectors
    if (this->regexList.size()!=cast->regexList.size())
        throw std::exception();
    for (int x=0;x<this->regexList.size();x++)
        if (this->regexList[x]!=cast->regexList[x])
            throw std::exception();
    cast->choice=this->choice;
}
    
void ListValue::setValue(const Value &v)
{
    const ListValue * cast=dynamic_cast<const ListValue *>(&v);
    if (cast==NULL) throw std::exception();
    //Let's compare vectors
    if (this->regexList.size()!=cast->regexList.size())
        throw std::exception();
    for (int x=0;x<this->regexList.size();x++)
        if (this->regexList[x]!=cast->regexList[x])
            throw std::exception();
    this->choice=cast->choice;
}
int ListValue::getValue()
{
    if (choice==-1) throw std::exception();
    else
        return this->choice;
}
void ListValue::setValue(int _choice)
{
    if (choice<-1) throw std::exception();
    if (choice>=regexList.size()) throw std::exception();
    this->choice=_choice;
}
