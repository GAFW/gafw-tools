/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CommonException.h
 * Author: daniel
 *
 * Created on 05 June 2016, 21:21
 */

#ifndef __COMMONEXCEPTION_H__
#define __COMMONEXCEPTION_H__
#include <sstream>
#include <string>
#include <exception>
#define GAFWToolsException(description) GAFW::Tools::CommonException(description,__FILE__,__LINE__); 
#define GAFWToolsExceptionWithCause(description,cause) GAFW::Tools::CommonException(description,__FILE__,__LINE__,cause); 

namespace GAFW { namespace Tools {

    class CommonException: public std::exception 
    {
    protected:
        const std::string description;
        const int linenumber;
        const std::string file;
        const std::exception * causeException;
        std::stringstream buffer;
    public:
        CommonException(const std::string & description,const std::string &file="",const int &linenumber=-1,const std::exception * cause_exception=NULL) throw();
        CommonException(const CommonException &) throw();
        virtual const char* what() const throw();
        virtual ~CommonException() throw();
        
    };
}}
#endif /* COMMONEXCEPTION_H */

