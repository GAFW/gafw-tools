/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPPParams.cpp
 * Author: daniel
 * 
 * Created on 08 March 2016, 21:09
 */

#include "CPPParams.h"
#include "SimpleValue.h"
#include <boost/regex.hpp>
#include <fstream>
using namespace GAFW::Tools::CPPParameters;
CPPParams::CPPParams()
{
    
}
CPPParams::~CPPParams()
{
    
}
void CPPParams::setParameter(const std::string &name, const Value &value,const std::string comment)
{
    this->registry.setParameter(name,value,comment);
}
void CPPParams::setParameter(const char * name, const Value &value,const char * comment)
{
    this->registry.setParameter(std::string(name),value,std::string(comment));
}

void CPPParams::setParameter(const std::string &name, const std::string &value,const std::string comment)
{
    this->registry.setParameter(name,value,comment);
}
void CPPParams::setParameter(const  char *name, const char *value,const char * comment)
{
    this->registry.setParameter(std::string(name),std::string(value),std::string(comment));
}

void CPPParams::setComment(const std::string &name,const std::string & comment)
{
    this->registry.setComment(name,comment);
}
void CPPParams::setComment(const char *name,const char * comment)
{
    this->registry.setComment(std::string(name),std::string(comment));
}
std::string CPPParams::getComment(const std::string &name)
{
    return this->getComment(name);
}
std::string CPPParams::getComment(const  char *name)
{
    return this->getComment(std::string(name));
}
Parameter& CPPParams::getParameter(const std::string & name)
{
    return this->registry.getParameter(name);
}
Parameter& CPPParams::getParameter(const char * name)
{
    return this->registry.getParameter(std::string(name));
}
void CPPParams::freezeParameters()
{
    this->registry.freezeAllParameters();
}
void CPPParams::unFreezeParameters()
{
    this->registry.unfreezeAllParameters();
}
void CPPParams::freezeParameterAndChildren(const std::string &name)
{
    this->registry.freezeParameterAndChilds(name);
}
void CPPParams::unfreezeParameterAndChildren(const std::string &name)
{
    this->registry.unfreezeParametersAndChild(name);
}
void CPPParams::freezeParameterAndChildren(const  char *name)
{
    this->registry.freezeParameterAndChilds(std::string(name));
}
void CPPParams::unfreezeParameterAndChildren(const  char *name)
{
    this->registry.unfreezeParametersAndChild(std::string(name));
}
void CPPParams::loadFromFile(const char * fileName)
{
    this->loadFromFile(std::string(fileName));
}
void CPPParams::loadFromFile(const std::string &fileName)
{
    boost::regex onlyspace("^[[:space:]]*$");
    boost::regex reg_comment("^[[:space:]]*[#!].*$");
    boost::regex prop_genformat("^[[:space:]]*([^[:space:]\\=]+)[[:space:]]*=[[:space:]]*([^[:space:]]*)$");
    boost::regex change_parent("^[[:space:]]*\\[[[:space:]]*([^[:space:]\\]]*)[[:space:]]*\\][[:space:]]*");
    std::string parent(""); 
    
    std::ifstream in;
    in.open(fileName.c_str());
    if (!in)
        throw std::exception();
    std::string line;
    do
    {
        getline(in,line);
       
        //is this a comment?? or just white space
        if (regex_match(line,reg_comment)||regex_match(line,onlyspace))
        {
            continue;
        }
        //Check general format
        boost::match_results<std::string::const_iterator> what;
        if (regex_match(line,what,change_parent))
        {
            if (what[1]==std::string(""))
            {
                parent="";
                continue;
            }
            else
            {
                ParameterName p(what[1]); //Checks proper format
                parent=p.getFullName();
            }
        }
        else
        {
            std::pair<std::string,std::string> r=this->translateLine(line);
            if (r.first==".")
            {
                if (parent!="")
                    this->setParameter(parent,r.second);
                else
                    throw std::exception();
            }
            std::stringstream ss;
            if (parent!="")
                ss<< parent<< "."<< r.first;
            else
                ss << r.first;
            this->setParameter(ss.str(),r.second);
        }
        
        
    } while(!in.eof());
    
}
void CPPParams::loadFromArgs(int argc, char** argv)
{
    //We always assume that this are directly form main.. show argv[0] is tpo be ignored
    for (int x=1;x<argc;x++)
    {
        //Args have special feature... if no = exist and begins with - then it is a boolean property
        boost::regex bool_genformat("^-([^=]+)$");
        boost::cmatch what;
        if (boost::regex_match(argv[x],what,bool_genformat))
        {
            //Yep it is bool
            std::string parName=std::string(what[1]);
            this->setParameter(parName,SimpleValue<bool>(true));
        }
        else
        {
            //Normal translation
            std::pair<std::string,std::string> p=this->translateLine(argv[1]);
            this->setParameter(p.first,p.second);
        }
    }
}

std::pair<std::string,std::string> CPPParams::translateLine(const std::string& line)
{
    boost::regex prop_genformat("^[[:space:]]*([^[:space:]\\=]+)[[:space:]]*=[[:space:]]*([^[#!]*)[#!]?.*$");
    boost::match_results<std::string::const_iterator> what;
    if (!regex_search(line,what,prop_genformat))
        throw std::exception();
    //Remove any whitespace at the end of string for what[2]
    boost::regex w_remove("^(.*[^[:space:]])[[:space:]]+$");
    boost::match_results<std::string::const_iterator> what2;
    std::pair<std::string,std::string> toReturn;
    toReturn.first=what[1];
    if (regex_match(std::string(what[2]),what2,w_remove))
        toReturn.second=what2[1];
    else
        toReturn.second=what[2];
    return toReturn;
}
bool CPPParams::isParameterSet(const std::string &name)
{
    return this->registry.isParameterSet(name);
}
bool CPPParams::isParameterSet(const char *name)
{
    return this->registry.isParameterSet(std::string(name));
}

void CPPParams::getParameterData(std::vector<ParameterData> &tofill)
{
    this->registry.getParameterData(tofill);
}
