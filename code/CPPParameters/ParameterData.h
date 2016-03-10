/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParameterData.h
 * Author: daniel
 *
 * Created on 10 March 2016, 20:05
 */

#ifndef PARAMETERDATA_H
#define PARAMETERDATA_H
#include <string>
namespace GAFW { namespace Tools { namespace  CPPParameters {
    struct ParameterData
    {
        std::string name;
        std::string value;
        std::string type;
        std::string comment;
    };
}}}
#endif /* PARAMETERDATA_H */

