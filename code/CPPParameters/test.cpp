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
#include "AngleQuantity.h"
#include "VectorValue.h"
#include <sstream>
using namespace std;
using namespace GAFW::Tools::CPPParameters;
/*
 * 
 */
int notmain(int argc, char** argv) 
{
    VectorValue<AngleQuantity > a;
    a.setFromString("1arcsec,2arcsec");
    for (int x=0;x<a.getVectorSize();x++)
    {
        a.getElementNo(x).changeUnits("rad");
        cout << x<< endl;
    }
    cout << a.toString()<<endl;
}

