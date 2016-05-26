/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vector.h
 * Author: daniel
 *
 * Created on 17 March 2016, 20:30
 */

#ifndef VECTOR_H
#define VECTOR_H
#include "Value.h"
#include <string>
#include <vector>
#include "SimpleValue.h"
namespace GAFW { namespace Tools { namespace CPPParameters {
    template<class ElementValue=SimpleValue<std::string>,char del=','> 
    class VectorValue: public Value {
    protected:
        std::vector<ElementValue *> values;
        std::vector<std::string> vectorize(const std::string & str);
    public:
        VectorValue(const std::string &value="");
        virtual ~VectorValue();
        virtual std::string getType();
        virtual void setFromString(const std::string &value);
        virtual std::string toString();
        virtual VectorValue<ElementValue,del> * clone() const; 
        virtual void deleteClone();
        virtual void getValue(Value &v);
        virtual void setValue(const Value &v);
        virtual int getVectorSize();
        virtual ElementValue & getElementNo(unsigned int elNo);
};
    template<class ElementValue,char del>
    std::vector<std::string> VectorValue<ElementValue,del>::vectorize(const std::string & str)
    {
        std::vector<std::string> toReturn;
        std::stringstream ss;
        for (int x=0;x<str.size();x++)
        {
            if (str[x]!=del)
                ss<<str[x];
            else
            {
                toReturn.push_back(ss.str());
                ss.str("");
                ss.seekg(0);
            }
        }
        toReturn.push_back(ss.str());
        return toReturn;

    }
    template<class ElementValue,char del>
    VectorValue<ElementValue,del>::VectorValue(const std::string &value)
    {
        this->setFromString(value);
    }
    template<class ElementValue,char del>
    VectorValue<ElementValue,del>::~VectorValue()
    {
        for (int x=0;x<this->values.size();x++)
        {
            this->values[x]->deleteClone();
        }

    }
    template<class ElementValue,char del>
    std::string VectorValue<ElementValue,del>::getType()
    {
        std::stringstream ss;
        ss<< "Vector of "<<ElementValue().getType();
        return ss.str();
    }
    template<class ElementValue,char del>
    void VectorValue<ElementValue,del>::setFromString(const std::string &value)
    {
        std::vector<std::string> vec;
        if (value!="") vec=this->vectorize(value);
        std::vector<ElementValue *> newVec;
        ElementValue v;
        for (int x=0;x<vec.size();x++)
        {
            newVec.push_back(dynamic_cast<ElementValue*> (v.clone()));
            newVec[x]->setFromString(vec[x]);
        }
        std::vector<ElementValue *> oldVec=this->values;
        this->values=newVec;
        for (int x=0;x<oldVec.size();x++)
        {
            oldVec[x]->deleteClone();
        }
    }
    template<class ElementValue,char del>
    std::string VectorValue<ElementValue,del>::toString()
    {
        std::stringstream ss;
        for (int x=0;x<this->values.size();x++)
        {
            if (x!=0) ss<< del;
            ss<<this->values[x]->toString();
        }
        return ss.str();
    }
    template<class ElementValue,char del>
    VectorValue<ElementValue,del> * VectorValue<ElementValue,del>::clone() const
    {
        VectorValue<ElementValue,del> *toReturn=new VectorValue<ElementValue,del>();
        for (int x=0;x<this->values.size();x++)
        {
            toReturn->values.push_back(dynamic_cast<ElementValue *>(this->values[x]->clone()));
        }
        return toReturn;
    }
    template<class ElementValue,char del>
    void VectorValue<ElementValue,del>::deleteClone()
    {
        delete this;
    }
    template<class ElementValue,char del>
    void VectorValue<ElementValue,del>::getValue(Value &v)
    {
        VectorValue *vecValue=dynamic_cast<VectorValue<ElementValue,del> *>(&v);
        if (vecValue==NULL) throw std::exception();
        std::vector<ElementValue *> vec;
        for (int x=0;x<this->values.size();x++)
        {
            vec.push_back(dynamic_cast<ElementValue *>(this->values[x]->clone()));
        }
        std::vector<ElementValue *> toDelVec=vecValue->values;
        vecValue->values=vec;
        for (int x=0;x<toDelVec.size();x++)
        {
            toDelVec[x]->deleteClone();
        }
    }
    template<class ElementValue,char del>
    void VectorValue<ElementValue,del>::setValue(const Value &v)
    {
        const VectorValue<ElementValue,del> *vecValue=dynamic_cast<const VectorValue<ElementValue,del> *>(&v);
        if (vecValue==NULL) throw std::exception();
        std::vector<ElementValue *> vec;
        for (int x=0;x<vecValue->values.size();x++)
        {
            vec.push_back(dynamic_cast<ElementValue *>(vecValue->values[x]->clone()));
        }
        std::vector<ElementValue *> toDelVec=this->values;
        this->values=vec;
        for (int x=0;x<toDelVec.size();x++)
        {
            toDelVec[x]->deleteClone();
        }
    }
    template<class ElementValue,char del>
    int VectorValue<ElementValue,del>::getVectorSize()
    {
        return this->values.size();
    }
    template<class ElementValue,char del>
    ElementValue & VectorValue<ElementValue,del>::getElementNo(unsigned int elNo)
    {
        return *this->values[elNo];
    }


}}}

#endif /* VECTOR_H */

