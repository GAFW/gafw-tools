/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test.cpp
 * Author: daniel
 *
 * Created on 07 March 2016, 17:49
 */

#include <cstdlib>
#include <iostream>
#include "ParameterName.h"
#include "CPPParams.h"
#include "SimpleValue.h"
#include "boost/regex.hpp"
#include "ListValue.h"
#include "TimeQuantity.h"
#include <sstream>
using namespace std;
using namespace GAFW::Tools::CPPParameters;
/*
 * 
 */
int __main(int argc, char** argv) 
{
    TimeQuantity a(60);
    a.changeUnits("m");
    cout << a.toString()<<endl;
    
    
}

