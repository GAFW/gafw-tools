/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPPParams.h
 * Author: daniel
 *
 * Created on 08 March 2016, 21:09
 */

#ifndef __CPPPARAMS_H__
#define __CPPPARAMS_H__
#include "ParameterData.h"
#include "ParameterRegistry.h"
#include <utility>
namespace GAFW { namespace Tools { namespace CPPParameters {
    
    class CPPParams {
    protected:
        ParameterRegistry registry;
        std::pair<std::string,std::string> translateLine(const std::string &line);
    public:
        CPPParams();
        virtual ~CPPParams();
        void setParameter(const std::string &name, const Value &value,const std::string comment="");
        void setParameter(const std::string &name, std::string &value,const std::string comment="");
        void setComment(const std::string &name,const std::string & comment);
        std::string getComment(const std::string &name);
        Parameter& getParameter(const std::string & name);
        void freezeParameters();
        void unFreezeParameters();
        void freezeParameterAndChildren(const std::string &name);
        void unfreezeParameterAndChildren(const std::string &name);
        void loadFromFile(const std::string &fileName);
        void loadFromArgs(int argc, char** argv);
        bool isParameterSet(const std::string &name);
        void getParameterData(std::vector<ParameterData> &tofill);
    };
}}}
#endif /* CPPPARAMS_H */

