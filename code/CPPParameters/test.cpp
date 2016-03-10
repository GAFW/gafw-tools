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
using namespace std;
using namespace GAFW::Tools::CPPParameters;
/*
 * 
 */
int main(int argc, char** argv) {

        
    
    
    CPPParams params;
    params.loadFromFile(std::string("//tmp//a"));
    SimpleValue<bool> b(false);
    params.getParameter("test1").getValue(b);
    cout << b.get()<<endl;
    params.getParameter("testing.test2").getValue(b);
    cout << b.get()<<endl;
    std::vector<ParameterData> data;
    params.setComment("test1", "I am a comment");
    params.getParameterData(data);
    
    for (int x=0;x<data.size();x++)
    {
        cout << data[x].name << " " << data[x].type << " " << data[x].value << " "  << data[x].comment<< endl;
    }
    return 0;
}

