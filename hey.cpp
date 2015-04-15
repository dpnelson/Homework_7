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

int MonthtoInteger(string MM)
{
    if (MM == "01") return 1;
    if (MM == "02") return 2;
    if (MM == "03") return 3;
    if (MM == "04") return 4;
    if (MM == "05") return 5;
    if (MM == "06") return 6;
    if (MM == "07") return 7;
    if (MM == "08") return 8;
    if (MM == "09") return 9;
    if (MM == "10") return 10;
    if (MM == "11") return 11;
    if (MM == "12") return 12;
    exit(EXIT_FAILURE);
}

enum months {
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

string monthtostring(months M)
{
    if (M == January  )  return  "January";
    if (M == February )  return  "February";
    if (M == March    )  return  "March";
    if (M == April    )  return  "April";
    if (M == May      )  return  "May";
    if (M == June     )  return  "June";
    if (M == July     )  return  "July";
    if (M == August   )  return  "August";
    if (M == September)  return  "September";
    if (M == October  )  return  "October";
    if (M == November )  return  "November";
    if (M == December )  return  "December";
    exit(EXIT_FAILURE);
}

void print2(ofstream &LF, string texty, int n)
{
    cout << texty << n << "\n";
    LF   << texty << n << "\n";
}

void printheader(ofstream &LF, string top)
{
    cout << top;
    LF   << top;
}

void backslash(ofstream &LF, string ret)
{
    cout << ret;
    LF   << ret;
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
    eq.set_date(inputfile);
    
    string temp = "Invalid Data Length";
    if (eq.CheckDateLength() == false) Fail(logfile, temp);
    
    string tempstring;
    for (int i = 0; i <= 9; i++)    // Checks each position in the data for correct variable type
    {
        if (i == 2 || i == 5)
        {
            temp = "Invalid Date Separators";
            string temp2 = eq.GetDateSubStr(i, temp) ;
            if(eq.CheckDateSeperators(temp2)== false) Fail(logfile, temp);
        } else
        {
            temp = "Non-Number in Date";
            if(eq.CheckDateValidity(i) == false) Fail(logfile, temp);
        }
    }
    
    temp = "Date Seperators are not the same";
    if(eq.CheckDateSeperators2(2,5) == false) Fail(logfile, temp);
    
    string M, D, Y;
    eq.MDY(M,D,Y);
    int intmonth = atoi(M.c_str());
    int intday = atoi(D.c_str());
    int intyear = atoi(Y.c_str());
    
    months month;
    month = (months)intmonth;
    
    temp = "Invalid Month";
    if (eq.CheckMonthRange(intmonth) == false) Fail(logfile, temp);
    
    temp = "Invalid Day";
    if (eq.CheckDayRange(intday) == false) Fail(logfile, temp);
    
    temp = "Invalid Year";
    if (eq.CheckYearRange(intyear) == false) Fail(logfile, temp);
    
    string monthstring = monthtostring(month);
    
    temp = "Invalid Day/Month Combination";
    if (eq.MonthDayComboCheck(intday, intmonth) == false) Fail(logfile, temp);
    
    eq.set_time(inputfile);
    
    temp = "Invalid Time Length";
    if (eq.CheckTimeLength() == false) Fail(logfile, temp);
    
    string expVar;
    for (int i = 0; i <= 11; i++)     // Checks each position in the time for correct variable type
    {
        if (i == 2 || i == 5)
        {
            temp = "Invalid Time Seperator";
            eq.GetTimeSubStr(i, tempstring);
            expVar = ":";
            if(eq.CheckTimeSeperators(tempstring, expVar) == false) Fail(logfile, temp);
        } else if (i == 8)
        {
            temp = "Invalid Time Seperator";
            eq.GetTimeSubStr(i, tempstring);
            expVar = ".";
            if(eq.CheckTimeSeperators(tempstring, expVar) == false) Fail(logfile, temp);
        } else
        {
            temp = "Non-Number in Time";
            if(eq.CheckTimeValidity(i) == false) Fail(logfile, temp);
        }
    }
    
    temp = "Time Seperators are not the same";
    if (eq.CheckDateSeperators2(2,5) == false) Fail(logfile, temp);
    
    temp = "Invalid Time Zone Length";
    eq.set_time_zone(inputfile);
    if (eq.CheckTimeZoneLength() == false) Fail(logfile, temp);
    
    string HH, MM, SS;
    eq.HMS(HH,MM,SS);
    int inthour = atoi(HH.c_str());
    int intminute = atoi(MM.c_str());
    int intsecond = atoi(SS.c_str());
    
    temp = "Invalid Hour";
    if (eq.CheckHourRange(inthour) == false) Fail(logfile, temp);
    
    temp = "Invalid Minute";
    if (eq.CheckMinuteRange(intminute) == false) Fail(logfile, temp);
    
    temp = "Invalid Second";
    if (eq.CheckSecondRange(intsecond) == false) Fail(logfile, temp);
    
    temp = "Invalid Day/Month Combination";
    if (eq.MonthDayComboCheck(intday, intmonth) == false) Fail(logfile, temp);
    
    temp = "Invalid Time Zone Entry";
    if (eq.CheckTimeZoneEntries() == false) Fail(logfile, temp);
    
    eq.set_eq_name(inputfile);
    
    double Longitude, Latitude, Depth;
    
    Longitude = eq.set_longitude(inputfile);
    Latitude = eq.set_latitude(inputfile);
    Depth = eq.set_depth(inputfile);
    
    temp = "Longitude out of Range";
    if (eq.CheckLongRange(Longitude) == false) Fail(logfile, temp);
    temp = "Latitude out of Range";
    if (eq.CheckLatRange(Latitude) == false) Fail(logfile, temp);
    temp = "Negative depth";
    if (eq.CheckDepth(Depth) == false) Fail(logfile, temp);
    
    string magtype;
    inputfile >> magtype;
    temp = "Invalid Magnitude Type Length";
    if(eq.Check_MagTypeLength(magtype) == false) Fail(logfile, temp);
    
    temp = "Invalid Magnitude Type";
    if (eq.set_mag_type(magtype) == false) Fail(logfile, temp);
    
    temp = "Negative Magnitude";
    if (eq.set_mag(inputfile) == false) Fail(logfile, temp);
    
    printheader(logfile, "Header read correctly!\n");
    
    eq.HeaderOutput(outputfile, D, monthstring, Y);
    
    Station st;
    Station NC[300];
    Station SN[300];
    Station BT[300];
    Station IT[300];
    Station OR[300];
    int countbad = 0;
    int totsignals = 0;
    int validentries = 0, numentries = 0, newsignals, changer;
    string NetCode, StatCode, TypeBand, TypeInst, Orient;
    string NetworkCode[900], StationName[900], NCabbrev[900], ITabbrev[900], ORspot[900];
    while (inputfile >> NetCode)
    {
        inputfile >> StatCode;
        inputfile >> TypeBand;
        inputfile >> TypeInst;
        inputfile >> Orient;

        numentries++;
        changer = 0;
        
        if(st.CheckNC(validentries, NetCode) == false)    // Checks if Network Code is valid
        {
            st.BadEntry(logfile, numentries, changer, "Network Code.");
        }
        
        if(st.CheckSC(validentries, StatCode) == false)     // Checks if Station Name is valid
        {
            st.BadEntry(logfile, numentries, changer, "Station Name.");
        }
        
        st.Remove_Invalid_Chars(TypeBand);     // Remove
        
        if(st.CheckBT(validentries, TypeBand) == false)     // Checks if Band Type is valid
        {
            st.BadEntry(logfile, numentries, changer, "Band Type.");
        }
        
        st.Remove_Invalid_Chars(TypeInst);
        
        if(st.CheckIT(validentries, TypeInst) == false)     // Checks if Instrument Type is valid
        {
            st.BadEntry(logfile, numentries, changer, "Instrument Type.");
        }
        
        if(st.CheckOR(validentries, Orient) == false)     // Checks if Orientation is valid
        {
            st.BadEntry(logfile, numentries, changer, "Orientation.");
        }
        
        if (changer !=0)
        {
            backslash(logfile, "\n");
            countbad++;
        } else
        {
            NC[validentries].SetNC(NetCode);
            SN[validentries].SetSC(StatCode);
            BT[validentries].SetBT(TypeBand);
            IT[validentries].SetIT(TypeInst);
            OR[validentries].SetOR(Orient);
            
            newsignals = st.NumSigs();
            for (int i = 0; i < newsignals ; i++)
            {
                NetworkCode[totsignals+i] = NC[validentries].getNC();   // Stores valid station readings into these array
                StationName[totsignals+i] = SN[validentries].getSN();
                NCabbrev[totsignals+i]    = BT[validentries].getBT();     // Get necessary abreviations for intstrument and band
                ITabbrev[totsignals+i]    = IT[validentries].getIT();
                ORspot[totsignals+i]      = OR[validentries].getOR(i);
            }
            validentries++;
            totsignals += newsignals;
        }
    }
    
    outputfile << totsignals << "\n";
    
    for (int i = 0; i < totsignals; i++)
    {
        eq.printout(outputfile, StationName[i], NetworkCode[i], NCabbrev[i], ITabbrev[i], ORspot[i]);
    }
    
    int countgood = numentries - countbad;
    
    print2(logfile, "Total invalid entries ignored: ", countbad);
    print2(logfile, "Total valid entries read: ", countgood);
    print2(logfile, "Total signal names processed: ", totsignals);

    return 0;

}