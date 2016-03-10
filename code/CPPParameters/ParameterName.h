/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParameterName.h
 * Author: daniel
 *
 * Created on 07 March 2016, 19:27
 */

#ifndef PARAMETERNAME_H
#define PARAMETERNAME_H
#include <string>
#include <vector>

namespace GAFW { namespace Tools { namespace CPPParameters { 
    class ParameterName {
        std::string fullName;
        std::vector<std::string> hierarchy;
        std::string lowestSubordinate;
    public:
        ParameterName(std::string fullName);
        std::string getFullName(); 
        std::vector<std::string> getHierarchy();
        std::string getLowestSubordinate();
        static bool check(std:: string fullName);
        virtual ~ParameterName();
    };
}}}
#endif /* PARAMETERNAME_H */

