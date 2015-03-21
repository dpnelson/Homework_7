//
//  station.h
//  Homework_7
//
//  Created by Darin Nelson on 3/20/15.
//  Copyright (c) 2015 The University of Memphis. All rights reserved.
//

#ifndef __Homework_7__station__
#define __Homework_7__station__

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

using namespace std;

#endif /* defined(__Homework_7__station__) */

enum NetworkCode {
    CE,
    CI,
    FA,
    NP,
    WR
};

enum BandTypes {
    LONGPERIOD,
    SHORTPERIOD,
    BROADBAND
};

enum InstrumentTypes {
    HIGHGAIN,
    LOWGAIN,
    ACCELEROMETER
};

class Station
{
public:
    void changetoupper(string &temp2);
    void BadEntry(ofstream &LF, int z, int &change, string errortype);
    bool CheckNC(int k, string check);
    void SetNC(string check);
    bool CheckSC(int k, string StatCode);
    void SetSC(string check);
    bool CheckBT(int k, string TB);
    void SetBT(string TB);
    bool CheckIT(int k, string INST);
    void SetIT(string INST);
    bool CheckOR(int k, string ORE);
    void SetOR(string check);
    void Remove_Invalid_Chars(string &BandInst);
    string getNC();
    string getBT();
    string getIT();
    string getOR(int b);
    string getSN();
    int NumSigs();
    
private:
    NetworkCode NC;
    string SN;
    BandTypes BT;
    InstrumentTypes IT;
    string OR;
};