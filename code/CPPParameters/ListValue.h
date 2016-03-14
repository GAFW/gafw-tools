/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListValue.h
 * Author: daniel
 *
 * Created on 14 March 2016, 20:00
 */

#ifndef LISTVALUE_H
#define LISTVALUE_H
#include "Value.h"
#include <vector>

namespace GAFW { namespace Tools { namespace CPPParameters {
    class ListValue:public Value {
    protected:
        const std::vector<std::string> regexList;
        int choice;

    public:
        ListValue(const std::vector<std::string> &regexList,const std::string &value);
        ListValue(const std::vector<std::string> &regexList,const int &value=-1);
        virtual ~ListValue();
        virtual std::string getType();
        virtual void setFromString(const std::string &value);
        virtual std::string toString();
        virtual Value * clone() const; 
        virtual void deleteClone();
        virtual void getValue(Value &v);
        virtual void setValue(const Value &v);
        int getValue();
        void setValue(int choice);

    };
}}}

#endif /* LISTVALUE_H */

