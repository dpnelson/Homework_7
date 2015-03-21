//
//  earthquake.cpp
//  Homework_7
//
//  Created by Darin Nelson on 3/20/15.
//  Copyright (c) 2015 The University of Memphis. All rights reserved.
//

#include "earthquake.h"

void Earthquake::set_id(ifstream &IF)
{
    IF >> id;
}

string Earthquake::GetDateSubStr(int ii, string &tempS)     // Used to ensure only numbers are used in the data
{
    tempS = date.substr(ii,1);
    return tempS;
}

bool Earthquake::CheckDateLength()
{
    if (date.length() != 10) return false;
    return true;
}

bool Earthquake::CheckMonthRange(int mon)
{
    if (mon < 1 || mon > 12) return false;
    return true;
}

bool Earthquake::CheckDayRange(int day)
{
    if (day < 1 || day > 31) return false;
    return true;
}

bool Earthquake::CheckYearRange(int year)        // This can obviously be changed, but I created this limit
{                                    // because it was the last full year
    if (year > 2014) return false;
    return true;
}

bool Earthquake::MonthDayComboCheck(int day, int month)    // Ensure the day of month/month of year combo is valid
{
    switch (month)
    {
        case 2:
            if (day > 28)
            {
                return false;
                break;
            }
        case 4: case 6: case 9: case 11:
            if (day == 31)
            {
                return false;
                break;
            }
        default:
            return true;
    }
}

void Earthquake::MDY(string &MM, string &DD, string &YY)     // Acquires month, day, and year from earthquake date
{
    MM = date.substr(0,2);
    DD = date.substr(3,2);
    YY = date.substr(6,4);
}

bool Earthquake::CheckDateSeperators(string tempS)     // Checks that date seperators are individually valid
{
    if (tempS.compare("/") != 0 && tempS.compare("-") != 0) return false;
    return true;
}

bool Earthquake::CheckDateValidity(int place)    // Checks that only numbers are used in the date
{
    if (!isdigit(date[place])) return false;
    return true;
}

bool Earthquake::CheckDateSeperators2(int aa, int bb)     // Checks that date seperators are the same
{
    if (date[aa] != date[bb]) return false;
    return true;
}

void Earthquake::set_date(ifstream &IF)
{
    IF >> date;
}

void Earthquake::GetTimeSubStr(int ii, string &tempS)     // Used to ensure only numbers are used in the data
{
    tempS = time.substr(ii,1);
}

bool Earthquake::CheckTimeLength()
{
    if (time.length() != 12) return false;
    return true;
}

bool Earthquake::CheckHourRange(int h)
{
    if (h > 23) return false;
    return true;
}

bool Earthquake::CheckMinuteRange(int m)
{
    if (m > 59) return false;
    return true;
}

bool Earthquake::CheckSecondRange(int s)
{
    if (s > 59) return false;
    return true;
}

bool Earthquake::CheckTimeSeperators(string tempS, string VarExp)     // Checks that time seperators are individually valid
{
    if (tempS.compare(VarExp) != 0) return false;
    return true;
}

bool Earthquake::CheckTimeValidity(int place)     // Checks that only numbers are used in the time
{
    if (!isdigit(time[place])) return false;
    return true;
}

void Earthquake::set_time(ifstream &IF)
{
    IF >> time;
    
}

bool Earthquake::CheckTimeZoneLength()
{
    if (timezone.length() != 3) return false;
    return true;
}

bool Earthquake::CheckTimeZoneEntries()     // Checks that only letters are used in the time zone
{
    for (int i = 0; i < 3; i++)
    {
        if(!isalpha(timezone[i])) return false;
    }
    return true;
}

void Earthquake::HMS(string &H, string &M, string &S)     // Acquires hour, minute, and second from earthquake time
{
    H = time.substr(0,2);
    M = time.substr(3,2);
    S = time.substr(6,2);
}

void Earthquake::set_time_zone(ifstream &IF)
{
    IF >> timezone;
}

void Earthquake::set_eq_name(ifstream &IF)
{
    int check = 1, check2 = 1;
    string Name = "", Ename;
    while(check == 1)
    {
        IF >> Name;
        if (check2 == 1)
        {
            Ename = Name;
            check2 = 0;
        } else
        {
            Ename = Ename + " " + Name;
        }
        if(IF.peek() == '\n') check = 0;
    }
    earthquake_name = Ename;
}

double Earthquake::set_longitude(ifstream &IF)
{
    IF >> longitude;
    return longitude;
}

double Earthquake::set_latitude(ifstream &IF)
{
    IF >> latitude;
    return latitude;
}

double Earthquake::set_depth(ifstream &IF)
{
    IF >> depth;
    return depth;
}

bool Earthquake::CheckLongRange(double Long)
{
    if(Long < -180 || Long > 180) return false;
    return true;
}

bool Earthquake::CheckLatRange(double Lat)
{
    if(Lat < -180 || Lat > 180) return false;
    return true;
}

bool Earthquake::CheckDepth(double d)
{
    if(d < 0) return false;
    return true;
}

bool Earthquake::Check_MagTypeLength(string MT)
{
    if (MT.length() != 2) return false;
    return true;
}

void Earthquake::changetoupper(string &temp2)
{
    for (unsigned i = 0; i < temp2.length(); i++)
    {
        if (isalpha(temp2[i]))
        {
            temp2[i] = toupper(temp2[i]);
        }
    }
}

bool Earthquake::set_mag_type(string MT)     // checks for valid magnitude type
{
    changetoupper(MT);
    if(MT == "ML")
    {
        magnitude_type = ML;
        return true;
    } else if (MT == "MS")
    {
        magnitude_type = MS;
        return true;
    } else if (MT == "MB")
    {
        magnitude_type = MB;
        return true;
    } else if (MT == "MW")
    {
        magnitude_type = MW;
        return true;
    } else
    {
        return false;
    }
}

string Earthquake::getMagType()     // gets abbreviation of the earthquake magnitude type to output
{
    if (magnitude_type == ML) return "ML";
    if (magnitude_type == MS) return "MS";
    if (magnitude_type == MB) return "MB";
    if (magnitude_type == MW) return "MW";
    exit(EXIT_FAILURE);
}

bool Earthquake::Check_Mag()
{
    if (magnitude < 0) return false;
    return true;
};

float Earthquake::set_mag(ifstream &IF)
{
    IF >> magnitude;
    return magnitude;
}

void Earthquake::HeaderOutput(ofstream &OF, string DD, string MM, string YY)
{
    string StrMagType = getMagType();
    OF <<  "# " << DD << " " << MM << " " << YY << " " << time << " " << timezone << " ";
    OF << StrMagType << " " << magnitude << " " << earthquake_name << " ";
    OF << "[" << id << "] " << "(" << longitude << ", " << latitude << ", " << depth << ")\n";
}

void Earthquake::printout(ofstream &OF, string SN, string NetC, string SCab, string ITab, string O)
{
    OF << id << "." << NetC << "." << SN << "." << SCab << ITab << O << "\n";
}




