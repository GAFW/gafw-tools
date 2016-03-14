/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimpleDimensionedValue.h
 * Author: daniel
 *
 * Created on 12 March 2016, 17:24
 */

#ifndef __SIMPLEDIMENSIONEDVALUE_H__
#define __SIMPLEDIMENSIONEDVALUE_H__
#include "Value.h"
#include <sstream>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
namespace GAFW { namespace Tools { namespace CPPParameters {
    template <class Type,bool isInteger,bool caseSensitive>
    class SimpleDimensionedValue: public Value
    {
        private:
            SimpleDimensionedValue(const SimpleDimensionedValue& orig){};
        
        protected:
            Type magnitude;
            std::string unit; 
            struct Conv
            {
                Type relValue;
                std::string unit;
            };
            bool showUnits;
            const std::string valueType;
            const std::vector<struct Conv> conversion;
            Type getUnitRelValue(const std::string &value);
            void compareConversions(SimpleDimensionedValue<Type,isInteger,caseSensitive>&);
        public:
            SimpleDimensionedValue();
            SimpleDimensionedValue(const std::string &valueType,const std::vector<struct Conv> &conversion);
            SimpleDimensionedValue(const Type &magnitude,const std::string &unit);
            SimpleDimensionedValue(const std::string &valueType,const std::vector<struct Conv> &conversion,const Type &magnitude,const std::string &unit);
            SimpleDimensionedValue(const std::string &value);
            SimpleDimensionedValue(const std::string &valueType,const std::vector<struct Conv> &conversion,const std::string &value);
            
            virtual ~SimpleDimensionedValue();
            virtual std::string getType();
            virtual void setFromString(const std::string &value);
            virtual std::string toString();
            virtual Value * clone() const; 
            virtual void deleteClone();
            virtual void getValue(Value &v);
            virtual void setValue(const Value &v);
            virtual Type getMagnitude();
            virtual std::string getUnits();
            virtual Type getMagnitude(const std::string &units);
            virtual Type getMagnitude(const char * units);
            virtual void set(Type magnitude,const std::string &units);
            virtual void set(Type magnitude,const char * units);
            virtual void changeUnits(const std::string &units);
            virtual void changeUnits(const char * units);
            virtual void toStringShowUnits(bool show=true);

    };
    template <class Type,bool isInteger,bool caseSensitive>
    SimpleDimensionedValue<Type,isInteger,caseSensitive>::SimpleDimensionedValue():valueType("Simple Dimensioned Value"),conversion(std::vector<struct Conv>())
    {
        showUnits=true;
        this->unit="";
        this->magnitude=0;
    }
    template <class Type,bool isInteger,bool caseSensitive>
    SimpleDimensionedValue<Type,isInteger,caseSensitive>::SimpleDimensionedValue(const std::string &valueType,const std::vector<struct Conv> &conversion):valueType(valueType),conversion(conversion)
    {
        showUnits=true;
        this->unit="";
        this->magnitude=0;
    
    }
    template <class Type,bool isInteger,bool caseSensitive>
    SimpleDimensionedValue<Type,isInteger,caseSensitive>::SimpleDimensionedValue(const Type &magnitude,const std::string &unit):valueType("Simple Dimensioned Value"),conversion(std::vector<struct Conv>())
    {
        showUnits=true;
        this->set(magnitude,unit);
    }
    
    template <class Type,bool isInteger,bool caseSensitive>
    SimpleDimensionedValue<Type,isInteger,caseSensitive>::SimpleDimensionedValue(const std::string &valueType,const std::vector<struct Conv> &conversion,const Type &magnitude,const std::string &unit):valueType(valueType),conversion(conversion)
    {
        showUnits=true;
        this->set(magnitude,unit);
    }
    template <class Type,bool isInteger,bool caseSensitive>
    SimpleDimensionedValue<Type,isInteger,caseSensitive>::SimpleDimensionedValue(const std::string &value):valueType("Simple Dimensioned Value"),conversion(std::vector<struct Conv>())
    {
        showUnits=true;
        this->setFromString(value);
    }
    template <class Type,bool isInteger,bool caseSensitive>
    SimpleDimensionedValue<Type,isInteger,caseSensitive>::SimpleDimensionedValue(const std::string &valueType,const std::vector<struct Conv> &conversion,const std::string &value):valueType(valueType),conversion(conversion)
    {
        showUnits=true;
        this->setFromString(value);
    }
    template <class Type,bool isInteger,bool caseSensitive>
    SimpleDimensionedValue<Type,isInteger,caseSensitive>::~SimpleDimensionedValue()
    {
        
    }       
    template <class Type,bool isInteger,bool caseSensitive>
    std::string SimpleDimensionedValue<Type,isInteger,caseSensitive>::getType()
    {
        return valueType;
    }
    template <class Type,bool isInteger,bool caseSensitive>
    void SimpleDimensionedValue<Type,isInteger,caseSensitive>::setFromString(const std::string &value)
    {
        boost::regex base10integer_withexponent("^([\\+-]?[[:digit:]]+)e([\\+-]?[[:digit:]]+)[[:space:]]*([^[:space:]]*)$");
        boost::regex base10integer_noexponenet("^([\\+-]?[[:digit:]]+)[[:space:]]*([^[:space:]]*)$");
        boost::regex octalinteger("^([\\+-]?0[01234567]+)[[:space:]]*([^[:space:]]*)$");
        boost::regex hexinteger("^([\\+-]?0[xX][0123456789ABCDEF]+)[[:space:]]*([^[:space:]]*)$");
        
        boost::regex float_withexponent("^([\\+-]?[[:digit:]]+\\.?[[:digit:]]*e[\\+-]?[[:digit:]]+)[[:space:]]*([^[:space:]]*)$");
        boost::regex float_noexponent("^([\\+-]?[[:digit:]]+\\.?[[:digit:]]*)[[:space:]]*([^[:space:]]*)$");
        
        boost::smatch what;
        enum {
            HEX,
            OCT,
            DEC_NOEXP,
            DEC_EXP
        } formatType;
        if (isInteger)
        {
            
            bool patternFound;
            patternFound=boost::regex_search(value,what,octalinteger);
            if (patternFound) formatType=OCT;
            else 
            {
                patternFound=boost::regex_search(value,what,hexinteger);
                if (patternFound) formatType=HEX;
                else
                {
                    patternFound=boost::regex_search(value,what,base10integer_withexponent);
                    if (patternFound) formatType=DEC_EXP;
                    else
                    {
                        patternFound=boost::regex_search(value,what,base10integer_noexponenet);
                        if (patternFound) formatType=DEC_NOEXP;
                        else
                            throw std::exception();
                    }
                }
            }
        }
        
        else //!isInteger
        {
            
            bool patternFound;
            patternFound=boost::regex_search(value,what,float_withexponent);
            if (patternFound) formatType=DEC_EXP;
            else
            {
                 patternFound=patternFound?1:boost::regex_search(value,what,float_noexponent);
                 if (patternFound) formatType=DEC_NOEXP;
                 else
                     throw std::exception();
            }
        }
        Type mag;
        std::string proposed_unit;
        if (isInteger&&(formatType==DEC_EXP)) 
        {
            
            //Special case ..need special code
            std::string ss1=what[1];
            std::stringstream ss(ss1);
            Type v;
            ss >> v;
            Type p;
            std::string ss21=what[2];
            
            std::stringstream ss2(ss21);
            ss2 >> p;
            mag=(int)v*pow10(p);
            if ((errno==EDOM)||(errno==ERANGE))
            {
                throw std::exception();
            }
            proposed_unit=std::string(what[3]);

        }
        else
        {
        
            std::stringstream ss(what[1]);
            switch (formatType)
            {
                case DEC_EXP:
                    ss >> std::scientific;
                    break;
                case HEX:
                    ss >> std::hex;
                    break;
                case OCT:
                    ss >> std::oct;
                    break;
                case DEC_NOEXP:
                    ss >> std::dec;
            }
            ss>> mag;
            
            proposed_unit=std::string(what[2]);
        }
       
        this->set(mag,proposed_unit);
        
        
    }
    template <class Type,bool isInteger,bool caseSensitive>
    std::string SimpleDimensionedValue<Type,isInteger,caseSensitive>::toString()
    {
        std::stringstream ss;
        ss<<this->magnitude;
        if (this->showUnits) ss<<unit;
        return ss.str();
    }
    template <class Type,bool isInteger,bool caseSensitive>
    Value * SimpleDimensionedValue<Type,isInteger,caseSensitive>::clone() const
    {
        return new SimpleDimensionedValue<Type,isInteger,caseSensitive>(magnitude,unit);
    }
    template <class Type,bool isInteger,bool caseSensitive>
    void SimpleDimensionedValue<Type,isInteger,caseSensitive>::deleteClone()
    {
        delete this;
    }
    template <class Type,bool isInteger,bool caseSensitive>
    void SimpleDimensionedValue<Type,isInteger,caseSensitive>::getValue(Value &v)
    {
        SimpleDimensionedValue<Type,isInteger,caseSensitive> *ret=dynamic_cast<SimpleDimensionedValue<Type,isInteger,caseSensitive> *>(const_cast<Value *>(&v));
        if (ret==NULL) throw std::exception();
        //Check if this is same units
        if (ret->conversion.size()!=0)
        {
            this->compareConversions(*ret); 
        }
        ret->unit=this->unit;
        ret->magnitude=this->magnitude;
    }
    template <class Type,bool isInteger,bool caseSensitive>
    void SimpleDimensionedValue<Type,isInteger,caseSensitive>::setValue(const Value &v)
    {
        SimpleDimensionedValue<Type,isInteger,caseSensitive> *ret=dynamic_cast<SimpleDimensionedValue<Type,isInteger,caseSensitive> *>(const_cast<Value *>(&v));
        if (ret==NULL) throw std::exception();
        //Check if this is same units
        if (this->conversion.size()!=0)
        {
            this->compareConversions(*ret);
        }
        this->unit=ret->unit;
        this->magnitude=ret->magnitude;
    }
    template <class Type,bool isInteger,bool caseSensitive>
    Type SimpleDimensionedValue<Type,isInteger,caseSensitive>::getMagnitude()
    {
        return this->magnitude;
    }
    template <class Type,bool isInteger,bool caseSensitive>
    std::string SimpleDimensionedValue<Type,isInteger,caseSensitive>::getUnits()
    {
        return this->unit;
    }
    template <class Type,bool isInteger,bool caseSensitive>
    Type SimpleDimensionedValue<Type,isInteger,caseSensitive>::getMagnitude(const std::string &units)
    {
        Type myRel=this->getUnitRelValue(this->unit);
        Type reqRel=this->getUnitRelValue(units);
        Type ratio;
        if (reqRel>myRel) //needed when integers
        {
            ratio=reqRel/myRel;
            return this->magnitude/ratio;
        }
        else
        {
            ratio=myRel/reqRel;
            return this->magnitude*ratio;
        }
            
    }
    template <class Type,bool isInteger,bool caseSensitive>
    void SimpleDimensionedValue<Type,isInteger,caseSensitive>::set(Type mag,const std::string &p_units)
    {
        std::string proposed_unit=p_units;
        if (this->conversion.size()!=0)
        {
            if (proposed_unit=="") proposed_unit=this->conversion[0].unit;
            else
                this->getUnitRelValue(proposed_unit); //This will check if unit is known
        }
        this->magnitude=mag;
        this->unit=proposed_unit;

    }
    template <class Type,bool isInteger,bool caseSensitive>
    Type SimpleDimensionedValue<Type,isInteger,caseSensitive>::getMagnitude(const char * units)
    {
        return this->getMagnitude(std::string(units));
    }
    template <class Type,bool isInteger,bool caseSensitive>
    void SimpleDimensionedValue<Type,isInteger,caseSensitive>::set(Type magnitude,const char *units)
    {
        this->set(magnitude, std::string(units));
    }
    template <class Type,bool isInteger,bool caseSensitive>
    void SimpleDimensionedValue<Type,isInteger,caseSensitive>::changeUnits(const std::string &units)
    {
        Type newMag=this->getMagnitude(units);
        this->magnitude=newMag;
        this->unit=units;
    }
    template <class Type,bool isInteger,bool caseSensitive>
    void SimpleDimensionedValue<Type,isInteger,caseSensitive>::changeUnits(const char * units)
    {
        this->changeUnits(std::string(units));
    }
    template <class Type,bool isInteger,bool caseSensitive>
    void SimpleDimensionedValue<Type,isInteger,caseSensitive>::toStringShowUnits(bool show)
    {
        this->showUnits=show;
    }
    template <class Type,bool isInteger,bool caseSensitive>
    Type SimpleDimensionedValue<Type,isInteger,caseSensitive>::getUnitRelValue(const std::string &value)
    {
        std::string myValue=value;
        if (!caseSensitive)
        {
            std::stringstream ss;
            for (int x=0;x<value.size();x++)
            {
                ss<<(char)tolower(value[x]);
            }
            myValue=ss.str();
        }        
        
        for (int x=0;x<this->conversion.size();x++)
        {
            Conv cv=this->conversion[x];
            std::string toComp=cv.unit;
            if (!caseSensitive)
            {   
                std::stringstream ss;
                for (int x=0;x<cv.unit.size();x++)
                {
                    ss<<(char)tolower(cv.unit[x]);
                }
                toComp=ss.str();
            }
            if (toComp==myValue) return cv.relValue;
        }        
        throw std::exception();
    }
    template <class Type,bool isInteger,bool caseSensitive>
    void SimpleDimensionedValue<Type,isInteger,caseSensitive>::compareConversions(SimpleDimensionedValue<Type,isInteger,caseSensitive>& toCheck)
    {
        if (toCheck.conversion.size()!=this->conversion.size()) throw std::exception();
        for (int x=0;x<toCheck.conversion.size();x++)
        {
            if (toCheck.conversion[x].relValue!=this->conversion[x].relValue) throw std::exception();
            if (toCheck.conversion[x].unit!=this->conversion[x].unit) throw std::exception();
        }
    }
}}}

#endif /* SIMPLEDIMENSIONEDVALUE_H */

