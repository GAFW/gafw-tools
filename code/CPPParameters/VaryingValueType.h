/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VaryingValueType.h
 * Author: daniel
 *
 * Created on 28 March 2016, 19:14
 */

#ifndef __VARYINGVALUETYPE_H__
#define __VARYINGVALUETYPE_H__
#include <vector>
#include <sstream>
#include "Value.h"
namespace GAFW {namespace Tools { namespace CPPParameters {
    class VaryingValueType: public Value {
    private:
        VaryingValueType(const VaryingValueType& orig){};
    protected:
        std::vector<Value *> values;
        int whichValueOk;
        
    public:
        VaryingValueType(const std::vector<Value *> &vec,const std::string & v="");
        virtual ~VaryingValueType();
        virtual std::string getType();
        virtual void setFromString(const std::string &value);
        virtual std::string toString();
        virtual Value * clone() const; 
        virtual void deleteClone();
        virtual void getValue(Value &v);
        virtual void setValue(const Value &v);
        virtual void setSelectedValue(int select,const Value &v);
        virtual Value& getSelectedValue();
        virtual int getWhichValueSelected();
    };
}}}
#endif /* VARYINGVALUETYPE_H */

