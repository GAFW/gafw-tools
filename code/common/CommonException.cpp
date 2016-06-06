/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CommonException.cpp
 * Author: daniel
 * 
 * Created on 05 June 2016, 21:21
 */

#include "CommonException.h"
using namespace GAFW::Tools;
CommonException::CommonException(const std::string & description,const std::string &file,const int &linenumber,const std::exception * cause_exception) throw()
        :description(description),linenumber(linenumber),file(file),causeException(cause_exception)
{
    this->buffer.str("");
    if (file!="") this->buffer<<file;
    if (linenumber!=-1) this->buffer<<":"<< linenumber;
    if ((file!="")||(linenumber!=-1)) this->buffer<<":";
    this->buffer<< this->description<<std::endl;
    if (this->causeException!=NULL)
    {
        this->buffer<<"Caused by:"<<std::endl;
        this->buffer<<causeException->what();
    }
    
}
CommonException::CommonException(const CommonException &orig) throw()
        :description(orig.description),linenumber(orig.linenumber),file(orig.file),causeException(orig.causeException)
{
    buffer<<orig.buffer.str(); 
}
        
const char* CommonException::what() const throw()
{
    return this->buffer.str().c_str();
    
            
}
CommonException::~CommonException() throw()
{
    
}

