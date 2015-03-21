//
//  station.cpp
//  Homework_7
//
//  Created by Darin Nelson on 3/20/15.
//  Copyright (c) 2015 The University of Memphis. All rights reserved.
//

#include "station.h"

void Station::changetoupper(string &temp2)
{
    for (unsigned i = 0; i < temp2.length(); i++)
    {
        if (isalpha(temp2[i]))
        {
            temp2[i] = toupper(temp2[i]);
        }
    }
}

void Station::BadEntry(ofstream &LF, int z, int &change, string errortype)    // Prints error in entries to log file and terminal
{
    if (change == 0)
    {
        change++;
        cout << "Entry # " << right << setw(3) << z << " ignored.";
        LF   << "Entry # " << right << setw(3) << z << " ignored.";
    }
    cout << " Invalid " << errortype;
    LF   << " Invalid " << errortype;
}

bool Station::CheckNC(int k, string check)
{
    if(check == "CE")
    {
        return true;
    } else if (check == "CI")
    {
        return true;
    } else if (check == "FA")
    {
        return true;
    } else if (check == "NP")
    {
        return true;
    } else if (check == "WR")
    {
        return true;
    } else
    {
        return false;
    }
}

void Station::SetNC(string check)
{
    if(check == "CE")
    {
        NC = CE;
    } else if (check == "CI")
    {
        NC = CI;
    } else if (check == "FA")
    {
        NC = FA;
    } else if (check == "NP")
    {
        NC = NP;
    } else if (check == "WR")
    {
        NC = WR;
    }
}

bool Station::CheckSC(int k, string StatCode)
{
    int check = 0;
    if(StatCode.length() != 3 && StatCode.length() != 5)    // Ensures Station code is either 3 or 5 characters long
    {
        check = 1;
    } else
    {
        if (StatCode.length() == 5)     // Ensures code is all numbers if 5 characters long
        {
            int num = 4;
            for (int w = 0; w <= num; w++)
            {
                if(!isdigit(StatCode[w]))
                {
                    check = 1;
                }
            }
        } else            //// Ensures code is all letters if 3 characters long
        {
            int num = 2;
            for (int w = 0; w <= num; w++)
            {
                if(!isalpha(StatCode[w]))
                {
                    check = 1;
                }
                
                string temp = StatCode;
                string temp1 = temp;
                changetoupper(temp);
                
                if (temp != temp1)
                {
                    check = 1;
                }
            }
        }
    }
    if (check == 1)
    {
        return false;
    } else
    {
        return true;
    }
}

void Station::SetSC(string check)
{
    SN = check;
}

bool Station::CheckBT(int k, string TB)
{
    if(TB == "LONG-PERIOD" || TB == "LONGPERIOD")
    {
        return true;
    } else if (TB == "SHORT-PERIOD" || TB == "SHORTPERIOD")
    {
        return true;
    } else if (TB == "BROADBAND")
    {
        return true;
    } else
    {
        return false;
    }
}

void Station::SetBT(string TB)
{
    if(TB == "LONG-PERIOD" || TB == "LONGPERIOD" )
    {
        BT = LONGPERIOD;
    } else if (TB == "SHORT-PERIOD" || TB == "SHORTPERIOD")
    {
        BT = SHORTPERIOD;
    } else if (TB == "BROADBAND")
    {
        BT = BROADBAND;
    }
}

bool Station::CheckIT(int k, string INST)
{
    if(INST == "HIGH-GAIN" || INST == "HIGHGAIN")
    {
        return true;
    } else if (INST == "LOW-GAIN" || INST == "LOWGAIN")
    {
        return true;
    } else if (INST == "ACCELEROMETER")
    {
        return true;
    } else
    {
        return false;
    }
}

void Station::SetIT(string INST)
{
    if(INST == "HIGH-GAIN" || INST == "HIGHGAIN")
    {
        IT = HIGHGAIN;
    } else if (INST == "LOW-GAIN" || INST == "LOWGAIN")
    {
        IT = LOWGAIN;
    } else if (INST == "ACCELEROMETER")
    {
        IT = ACCELEROMETER;
    }
}

bool Station::CheckOR(int k, string ORE)
{
    int check = 0, x = 0, length = 0;
    while (isalpha(ORE[x]) || isdigit(ORE[x]))
    {
        length++;
        x++;
    }
    if(length < 1 || length > 3)    // Ensures orientation  is between 1 and 3 characters long
    {
        check = 1;
    }
    int alphacount = 0, numbercount = 0;
    for (int g = 1; g <= length; g++)
    {
        if (isalpha(ORE[g-1]))
        {
            alphacount++;
        } else if (isdigit(ORE[g-1]))
        {
            numbercount++;
        } else
        {
            check = 1;
        }
    }
    
    if (alphacount != length && numbercount != length)
    {
        check = 1;
    }
    
    if (alphacount != 0)    // Ensures Orientation is all letters
    {
        changetoupper(ORE);
        for (int c = 1; c <= length; c++)
        {
            string tempString = ORE.substr(c-1,1);
            if (tempString.compare("N") && tempString.compare("E") && tempString.compare("Z"))
            {
                check = 1;
            }
        }
    }
    
    if (numbercount != 0)    // Ensures Orientation is all numbers
    {
        for (int c = 1; c <= length; c++)
        {
            string tempString = ORE.substr(c-1,1);
            if (tempString.compare("1") && tempString.compare("2") && tempString.compare("3"))
            {
                check = 1;
            }
        }
    }
    if (check == 1)
    {
        return false;
    } else
    {
        return true;
    }
}

void Station::SetOR(string check)
{
    OR = check;
}

void Station::Remove_Invalid_Chars(string &BandInst)    // Removes dashs from Instrument type and Band type
{
    string Altered;
    for (unsigned i = 0; i < BandInst.length(); i++)
    {
        string temp = BandInst.substr(i);
        if (isalpha(BandInst[i]) || temp.compare("-"))
        {
            Altered += BandInst[i];
        }
    }
    BandInst = Altered;
    changetoupper(BandInst);
}

string Station::getNC()
{
    if (NC == CE )  return  "CE";
    if (NC == CI )  return  "CI";
    if (NC == FA )  return  "FA";
    if (NC == NP )  return  "NP";
    if (NC == WR )  return  "WR";
    exit(EXIT_FAILURE);
}

string Station::getOR(int b)
{
    string end = OR.substr(b,1);
    return end;
}

string Station::getSN()
{
    string last = SN;
    return last;
}

int Station::NumSigs()
{
    int i = 0;
    while (isalpha(OR[i]) || isdigit(OR[i]))
    {
        i++;
    }
    return i;
}

string Station::getBT()
{
    if (BT == LONGPERIOD)  return "L";
    if (BT == SHORTPERIOD) return "B";
    if (BT == BROADBAND)   return "H";
    exit(EXIT_FAILURE);
}

string Station::getIT()
{
    if (IT == HIGHGAIN)       return "H";
    if (IT == LOWGAIN)        return "L";
    if (IT == ACCELEROMETER)  return "N";
    exit(EXIT_FAILURE);
}