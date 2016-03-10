/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParameterRegistry.h
 * Author: daniel
 *
 * Created on 07 March 2016, 21:16
 */

#ifndef PARAMETERREGISTRY_H
#define PARAMETERREGISTRY_H
#include <map>
#include <string>
#include "Parameter.h"
#include "ParameterData.h"


namespace GAFW { namespace Tools { namespace CPPParameters {
    
    
    class ParameterRegistry {
    protected:
        struct Entry {
            Parameter par;
            std::map<std::string,Entry> nodeData;
            std::map<std::string,Entry> *registeredInNode;
            std::string comment;
            bool freezed;
            
        };
        std::map<std::string,Entry> registry;
        bool allParametersFreezed;
        Entry& findEntry(const std::string &fullName,bool &freezed);
        Entry& searchAndCreateEntry(const std::string &fullName);
        bool checkIfSubOrdinatesArefreezed(Entry& entry);
        void dumpMap(const std::string& parent, std::vector<ParameterData> &tofill, const std::map<std::string,Entry> & node);
    public:
        ParameterRegistry();
        virtual ~ParameterRegistry();
        void freezeAllParameters();
        void freezeParameterAndChilds(const std::string &  parent);
        void unfreezeAllParameters();
        void unfreezeParametersAndChild(const std::string &  parent);
        void setParameter(const std::string & name, const Value & val, std::string comment="");
        void setParameter(const std::string & name, const std::string & val, std::string comment="");
        void setComment(const std::string & name, const std::string & comment);
        Parameter & getParameter(const std::string &name);
        std::string getComment(const std::string & name);
        void deleteParameter(const std::string & name);
        bool isParameterSet(const std::string & name);
        void getParameterData(std::vector<ParameterData> &tofill);
    };

}}}

#endif /* PARAMETERREGISTRY_H */

