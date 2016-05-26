/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParameterRegistry.cpp
 * Author: daniel
 * 
 * Created on 07 March 2016, 21:16
 */

#include "ParameterRegistry.h"
#include "CPPParams.h"
#include <sstream>
using namespace GAFW::Tools::CPPParameters;
ParameterRegistry::ParameterRegistry()
{
    this->allParametersFreezed=false;
}
ParameterRegistry::~ParameterRegistry()
{
    
}
void ParameterRegistry::freezeAllParameters()
{
    this->allParametersFreezed=true;
}
ParameterRegistry::Entry& ParameterRegistry::findEntry(const std::string &fullName,bool &freezed)
{
    freezed=this->allParametersFreezed;
    ParameterName p(fullName);
    std::vector<std::string> h=p.getHierarchy();
    std::map<std::string,Entry> *currentNode=&this->registry;
    Entry * currentEntry=NULL;
    for (int x=0;x<h.size();x++)
    {
        if (!currentNode->count(h[x]))
        {
            throw std::exception();
        }
        else
        {    
            currentEntry=&((*currentNode)[h[x]]);
            currentNode=&currentEntry->nodeData;
            freezed=freezed||currentEntry->freezed;
        }
        
    }
    return *currentEntry;
}
void ParameterRegistry::freezeParameterAndChilds(const std::string & parent)
{
    bool freezed;
    this->findEntry(parent,freezed).freezed=true;
}
void ParameterRegistry::unfreezeAllParameters()
{
    this->allParametersFreezed=false;
}
void ParameterRegistry::unfreezeParametersAndChild(const std::string &parent)
{
    bool freezed;
    this->findEntry(parent,freezed).freezed=false;
}
void ParameterRegistry::setParameter(const std::string & name, const Value & val, std::string comment)
{
    Entry & entry=searchAndCreateEntry(name);
    entry.par.setValue(val);
    if (comment!="")
        entry.comment=comment;
}
ParameterRegistry::Entry& ParameterRegistry::searchAndCreateEntry(const std::string &fullName)
{
    bool freeze=this->allParametersFreezed;
    std::vector<std::string> h=ParameterName(fullName).getHierarchy();
    std::map<std::string,Entry> *currentNode=&this->registry;
    Entry * currentEntry=NULL;
    std::stringstream currentFullName;
    for (int x=0;x<h.size();x++)
    {
        if (x!=0) currentFullName << ".";
        currentFullName << h[x];
        if (!currentNode->count(h[x]))
        {
            if (freeze) throw std::exception();
            Entry newEntry;
            newEntry.comment="";
            newEntry.freezed=false;
            newEntry.par.setParameterName(currentFullName.str());
            newEntry.registeredInNode=currentNode;
            (*currentNode)[h[x]]=newEntry;
            
        }
        currentEntry=&(*currentNode)[h[x]];
        freeze=freeze||currentEntry->freezed;
        currentNode=&currentEntry->nodeData;
    }
    return *currentEntry;
}
void ParameterRegistry::setParameter(const std::string & name, const std::string & val, std::string comment)
{
    Entry & entry=searchAndCreateEntry(name);
    entry.par.setValue(val);
    if (comment!="")
        entry.comment=comment;

}
void ParameterRegistry::deleteParameter(const std::string & name)
{
    bool freeze=false;
    Entry & entry=this->findEntry(name,freeze);
    if (freeze) std::exception();
    if (this->checkIfSubOrdinatesArefreezed(entry)) std::exception();
    //No freezing
    std::string lastSubOrdinate=ParameterName(name).getLowestSubordinate();
    entry.registeredInNode->erase(lastSubOrdinate);
    //everything should be deleted automatically
}

bool ParameterRegistry::checkIfSubOrdinatesArefreezed(Entry& entry)
{
    for (std::map<std::string,Entry>::iterator i=entry.nodeData.begin();i!=entry.nodeData.end();i++)
    {
        if (i->second.freezed)
            return true;
        if (this->checkIfSubOrdinatesArefreezed(i->second)) return true;
    }
    return false;
}

void ParameterRegistry::setComment(const std::string & name, const std::string & comment)
{
    bool freeze;
    this->findEntry(name,freeze).comment=comment;
}
Parameter & ParameterRegistry::getParameter(const std::string &name)
{
    bool freeze;
    return this->findEntry(name,freeze).par;
}
std::string  ParameterRegistry::getComment(const std::string & name)
{
    bool freeze;
    return this->findEntry(name,freeze).comment;
}
bool ParameterRegistry::isParameterSet(const std::string &name)
{
    bool freeze;
    try {
        Parameter &p= this->findEntry(name,freeze).par;
        p.getValueType(); //Will throw exception if not valued yet
    }
    catch (const std::exception &)
    {
        
        return false;
    }
    return true;
}
void ParameterRegistry::getParameterData(std::vector<ParameterData> &tofill)
{
    this->dumpMap("",tofill,this->registry);
}
void ParameterRegistry::dumpMap(const std::string& parent,std::vector<ParameterData> &tofill, const std::map<std::string,ParameterRegistry::Entry> & node)
{
    for (std::map<std::string,ParameterRegistry::Entry>::const_iterator x=node.begin();x!=node.end();x++)
    {
        std::stringstream ss;
        if (parent!="")
            ss<<parent <<".";
        try {
            
            
            ParameterData data;
            ss<<x->first;
            data.name=ss.str();
            data.comment=x->second.comment;
            //below code can throw exception
            data.type=x->second.par.getValueType();
            data.value=x->second.par.getStringValue();
            tofill.push_back(data);
        } catch (const std::exception &)
        {}
        dumpMap(ss.str(),tofill,x->second.nodeData);
    }
}
