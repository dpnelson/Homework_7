//
//  Darin Nelson
//  Homework #6
//  3/26/15
//  CIVL 7903
//  Github URL: https://github.com/dpnelson/Homework_7
//

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

#include "earthquake.h"
#include "station.h"

using namespace std;

void open_input(ifstream &IF, string IF2)      // Opening input file
{
    IF.open(IF2.c_str());
    if ( !IF.is_open() )
    {
        cout << "Cannot open input file: "
        << IF2
        << endl;
        exit(EXIT_FAILURE);
    }
}

void open_outputfiles(ofstream &file, string file2, string file3)      // Opens log and output files
{
    file.open(file3.c_str());
    if ( !file.is_open() )
    {
        cout << "Cannot open " << file2 << "file: " << file3;
        file.flush();
        exit(EXIT_FAILURE);
    }
}

void Fail(ofstream &logfile, string failtype)     // Handles any error in the header
{
    cout    << "Error: " << failtype << "\n";
    logfile << "Error: " << failtype << "\n";
    logfile.flush();
    exit(EXIT_FAILURE);
}

void printheader(ofstream &LF, string text)
{
    cout << text;
    LF   << text;
}


int main()
{
    
    string   inputfilename, outputfilename, logfilename;
    ifstream inputfile;
    ofstream logfile, outputfile;
    
    cout << "Enter inputfile name: ";
    cin  >> inputfilename;
    cout << "\n";
    open_input(inputfile, inputfilename);
    open_outputfiles(logfile, "log file", "darin.log");
    open_outputfiles(outputfile, "output file", "darin.out");
    
    printheader(logfile, "Opening file: darin.in\n");
    printheader(logfile, "Processing input...\n");
    
    Earthquake eq; 
    
    eq.set_id(inputfile);
    eq.set_data(inputfile);
    
    string temp = "Invalid Data Length";
    if (CheckDateLength(eq) == false) Fail(logfile, temp);
    
    string tempstring;
    for (int i = 0; i <= 9; i++)    // Checks each position in the data for correct variable type
    {
        if (i == 2 || i == 5)
        {
            temp = "Invalid Date Separators";
            GetDateSubStr(eq, i, tempstring);
            if(CheckDateSeperators(tempstring) == false) Fail(logfile, temp);
        } else
        {
            temp = "Non-Number in Date";
            if(CheckDateValidity(eq, i) == false) Fail(logfile, temp);
        }
    }
    
    temp = "Date Seperators are not the same";
    if(CheckDateSeperators2(eq, 2,5) == false) Fail(logfile, temp);
    
    string M, D, Y;
    MDY(eq, M,D,Y);
    int intmonth = atoi(M.c_str());
    int intday = atoi(D.c_str());
    int intyear = atoi(Y.c_str());
    
    months month;
    month = (months)intmonth;
    
    temp = "Invalid Month";
    if (CheckMonthRange(intmonth) == false) Fail(logfile, temp);
    
    temp = "Invalid Day";
    if (CheckDayRange(intday) == false) Fail(logfile, temp);
    
    temp = "Invalid Year";
    if (CheckYearRange(intyear) == false) Fail(logfile, temp);
    
    string monthstring = monthtostring(month);
    
    temp = "Invalid Day/Month Combination";
    if (MonthDayComboCheck(intday, intmonth) == false) Fail(logfile, temp);
    
    get_eqTime(inputfile, eq);
    
    temp = "Invalid Time Length";
    if (CheckTimeLength(eq) == false) Fail(logfile, temp);
    
    string expVar;
    for (int i = 0; i <= 11; i++)     // Checks each position in the time for correct variable type
    {
        if (i == 2 || i == 5)
        {
            temp = "Invalid Time Seperator";
            GetTimeSubStr(eq, i, tempstring);
            expVar = ":";
            if(CheckTimeSeperators(tempstring, expVar) == false) Fail(logfile, temp);
        } else if (i == 8)
        {
            temp = "Invalid Time Seperator";
            GetTimeSubStr(eq, i, tempstring);
            expVar = ".";
            if(CheckTimeSeperators(tempstring, expVar) == false) Fail(logfile, temp);
        } else
        {
            temp = "Non-Number in Time";
            if(CheckTimeValidity(eq, i) == false) Fail(logfile, temp);
        }
    }
    
    temp = "Time Seperators are not the same";
    if (CheckDateSeperators2(eq, 2,5) == false) Fail(logfile, temp);
    
    temp = "Invalid Time Zone Length";
    get_eqTimeZone(inputfile, eq);
    if (CheckTimeZoneLength(eq) == false) Fail(logfile, temp);
    
    string HH, MM, SS;
    HMS(eq, HH,MM,SS);
    int inthour = atoi(HH.c_str());
    int intminute = atoi(MM.c_str());
    int intsecond = atoi(SS.c_str());
    
    temp = "Invalid Hour";
    if (CheckHourRange(inthour) == false) Fail(logfile, temp);
    
    temp = "Invalid Minute";
    if (CheckMinuteRange(intminute) == false) Fail(logfile, temp);
    
    temp = "Invalid Second";
    if (CheckSecondRange(intsecond) == false) Fail(logfile, temp);
    
    temp = "Invalid Day/Month Combination";
    if (MonthDayComboCheck(intday, intmonth) == false) Fail(logfile, temp);
    
    temp = "Invalid Time Zone Entry";
    if (CheckTimeZoneEntries(eq) == false) Fail(logfile, temp);
    
    string Name, Ename;
    int check = 1, check2 = 1;
    
    set_eqName(inputfile, eq, Name, Ename, check, check2);
    
    double Longitude, Latitude, Depth;
    
    Longitude = set_eqLongitude(inputfile, eq);
    Latitude = set_eqLatitude(inputfile, eq);
    Depth = set_eqDepth(inputfile, eq);
    
    temp = "Longitude out of Range";
    if (CheckLongRange(Longitude) == false) Fail(logfile, temp);
    temp = "Latitude out of Range";
    if (CheckLatRange(Latitude) == false) Fail(logfile, temp);
    temp = "Negative depth";
    if (CheckDepth(Depth) == false) Fail(logfile, temp);
    
    string magtype;
    inputfile >> magtype;
    temp = "Invalid Magnitude Type Length";
    if(Check_MagTypeLength(magtype) == false) Fail(logfile, temp);
    
    temp = "Invalid Magnitude Type";
    if (set_MagType(eq, magtype) == false) Fail(logfile, temp);
    
    set_Mag(inputfile, eq);
    temp = "Negative Magnitude";
    if (Check_Mag(eq) == false) Fail(logfile, temp);
    
    printheader(logfile, "Header read correctly!\n")
    
    
    
    
    
    
    Station st;
    

    return 0;

}