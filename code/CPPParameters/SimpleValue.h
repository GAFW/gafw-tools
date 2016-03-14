/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimpleValues.h
 * Author: daniel
 *
 * Created on 07 March 2016, 17:05
 */

#ifndef __SIMPLEVALUE_H__
#define __SIMPLEVALUE_H__
#include "Value.h"
#include "boost/lexical_cast.hpp"
namespace GAFW {  namespace Tools { namespace CPPParameters {
    template <class Type>
    class SimpleValue: public Value {
        protected:
            static const char * myType;
            Type myValue;
    public:
        SimpleValue();
        SimpleValue(const Type &value);
        virtual ~SimpleValue();
        virtual std::string getType();
        virtual void setFromString(const std::string &value);
        virtual std::string toString();
        virtual SimpleValue<Type> * clone() const; 
        virtual void deleteClone();
        virtual void set(const Type &value);
        virtual Type get();
        virtual void getValue(Value &v);
        virtual void setValue(const Value &v);
    };
    template <class Type>
    SimpleValue<Type>::SimpleValue()
    {
        
    }
    template <class Type>
    SimpleValue<Type>::SimpleValue(const Type &value)
    {
        this->myValue=value;
    }
    template <class Type>
    SimpleValue<Type>::~SimpleValue()
    {
        
    }
    template <class Type>
    std::string SimpleValue<Type>::getType()
    {
        return this->myType;
    }
    template <class Type>
    void SimpleValue<Type>::setFromString(const std::string &value) 
    {
        try
        {
            this->myValue=boost::lexical_cast<Type>(value);
        }
        catch (const boost::bad_lexical_cast&)
        {
            throw std::exception();  //TODO
        }
    }
    template <class Type>
    std::string SimpleValue<Type>::toString()
    {
        return boost::lexical_cast<std::string>(this->myValue);
    }
    template <class Type>
    void SimpleValue<Type>::set(const Type &value)
    {
        this->myValue=value;
    }
    template <class Type>
    Type SimpleValue<Type>::get()
    {
        return this->myValue;
    }
    template <class Type>
    SimpleValue<Type>  * SimpleValue<Type>::clone() const
    {
        return new SimpleValue<Type>(this->myValue);
    }
    template <class Type>
    void SimpleValue<Type>::deleteClone()
    {
        delete this;
    }
    template <>
    void SimpleValue<std::string>::getValue(Value &v);
    
    template <class Type>
    void SimpleValue<Type>::getValue( Value &v) 
    {
        Value *va=&v;
        SimpleValue<Type> *sva=NULL;
        sva=dynamic_cast<SimpleValue<Type> *>(va);
        if (sva==NULL) throw std::exception();
        sva->myValue=this->myValue;
    }
    template <class Type>
    void SimpleValue<Type>::setValue(const Value &v) 
    {
        const Value *va=&v;
        SimpleValue<Type> *sva=NULL;
        sva=dynamic_cast< SimpleValue<Type> *>(const_cast<Value *>(va));
        if (sva==NULL) throw std::exception();
        this->myValue=sva->myValue;
    }
    template <>
    void SimpleValue<bool>::setFromString(const std::string &value);
    template <>
    std::string SimpleValue<bool>::toString();
    
    
    
    
   
    
    
    
}}}


#endif /* SIMPLEVALUES_H */

