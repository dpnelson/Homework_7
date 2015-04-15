//
//  earthquake.h
//  Homework_7
//
//  Created by Darin Nelson on 3/20/15.
//  Copyright (c) 2015 The University of Memphis. All rights reserved.
//

#ifndef __Homework_7__earthquake__
#define __Homework_7__earthquake__

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

using namespace std;

#endif /* defined(__Homework_7__earthquake__) */

enum TypeofMag {
    ML,
    MS,
    MB,
    MW
};

class Earthquake
{
public:
    void set_id(ifstream &IF);
    void set_date(ifstream &IF);
    string GetDateSubStr(int ii, string &tempS);
    bool CheckDateLength();
    bool CheckMonthRange(int mon);
    bool CheckDayRange(int day);
    bool CheckYearRange(int year);
    bool MonthDayComboCheck(int day, int month);
    bool CheckDateSeperators(string tempS);
    bool CheckDateValidity(int place);
    bool CheckDateSeperators2(int aa, int bb);
    void set_time(ifstream &IF);
    void GetTimeSubStr(int ii, string &tempS);
    bool CheckTimeLength();
    bool CheckHourRange(int h);
    bool CheckMinuteRange(int m);
    bool CheckSecondRange(int s);
    bool CheckTimeSeperators(string tempS, string VarExp);
    bool CheckTimeValidity(int place);
    void set_time_zone(ifstream &IF);
    bool CheckTimeZoneLength();
    bool CheckTimeZoneEntries();
    void get_eqTimeZone(ifstream &IF);
    void set_eq_name(ifstream &IF);
    double set_longitude(ifstream &IF);
    double set_latitude(ifstream &IF);
    double set_depth(ifstream &IF);
    bool CheckLongRange(double Long);
    bool CheckLatRange(double Lat);
    bool CheckDepth(double d);
    bool set_mag_type(ifstream &IF);
    bool Check_MagTypeLength(string MT);
    void changetoupper(string &temp2);
    float set_mag(ifstream &IF);
private:
    string id;
    string date;
    string time;
    string timezone;
    string earthquake_name;
    double longitude;
    double latitude;
    double depth;
    TypeofMag magnitude_type;
    float magnitude;
};
