/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParameterName.cpp
 * Author: daniel
 * 
 * Created on 07 March 2016, 19:27
 */

#include <vector>
#include <sstream>

#include "ParameterName.h"
#include <boost/regex.hpp>
using namespace GAFW::Tools::CPPParameters;

ParameterName::ParameterName(std::string fullName)
{
    if (ParameterName::check(fullName)) this->fullName=fullName;
    else throw std::exception();
    std::stringstream name; 
    for (int x=0;x<fullName.size();x++)
    {
        if (fullName[x]=='.')
        {
            this->hierarchy.push_back(name.str());
            name.str("");
        }
        else
            name <<fullName[x];
    }
    this->hierarchy.push_back(name.str());
    this->lowestSubordinate=name.str();
}
ParameterName::~ParameterName()
{
    
}
std::vector<std::string> ParameterName::getHierarchy()
{
    return this->hierarchy;
}
std::string ParameterName::getLowestSubordinate()
{
    return this->lowestSubordinate;
}
 bool ParameterName::check(std:: string fullName)
{
    const char * wrongsRegex[6]={
        "^$",           //has nothing
        "[[:space:]]" ,  // has whitespace 
        "\\.\\.",       // Two or more dots neighbour to each other
        "^\\.",           //Dot at the beginning
        "\\.$",           //Dot at the end
        "[#\\$\\^\\=]"     //Prohibited characters
    };
    
    for (int x=0;x<6;x++)
    {
        boost::regex r(wrongsRegex[x]);
        if (boost::regex_search(fullName.c_str(),r)) return false;
    }
    return true;
}
 
std::string ParameterName::getFullName()
{
    return this->fullName;
}