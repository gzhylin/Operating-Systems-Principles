/********************************************************************
Class:     CSCI 480-2
Program:   Assignment 1
Author:    George Zhylin
Z-number:  z1810327
Date Due:  2/20/18

Purpose:   Read and format relevant data from /proc file.

Execution: ./hw1.exe [filename]
           If filename is omitted, /proc/xxx is used.

Notes:     Program opens a file to read cpu info, gets useful information
           and stores it in a Processor objects that stored by the pointers
		   in a vector records. Then programs displays output that is computed 
		   from the data in vector of pointers to the Processor objects.

*********************************************************************/

#include "Processor.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <math.h>       /* pow */
using namespace std;

//function prototypes
int cpuCount (vector<Processor*> records);
string cpuCountDisp (vector<Processor*> records);
string cacheShare (vector<Processor*> records);
string fpuCheck (vector<Processor*> records);
int sysUpTime();
string sysUpTimeA();

int  main(int argc, char *argv[])
{
 //declare vector of pointers and iterator for it.
 vector <Processor*> records;
 vector <Processor*> :: iterator it;

 //declare some variables 
 Processor* temp;                      // Temp processor object 
 bool newRecerdFlag = true;            // Flag to see if we read new processor record
 string output;                        // String to hold output
 int recordCounter = 0;                // Line counter
 int charCounter = 0;                  // Char counter
 string fileName = "/proc/cpuinfo";    // Default file name
 
 // if file name specified, use it. 
 if (argc == 2)
		 fileName = argv[1];
	  
	 //create stream object ant open a file
	 ifstream readf;
	 readf.open(fileName);

 // try to read i file
 if (readf.is_open())
	 {
	 while (!readf.eof())
		 {
		 //work with one line at a time
		 getline(readf,output);
		 //increment line counter & char counter
		 recordCounter++;
		 charCounter = charCounter + output.length();
		 
		 //if start reading new processor info, create new processor object
		 if (newRecerdFlag == true)
			temp = new Processor();

		 //below is functions to retrieve useful information from the file

		 //search for processor field
		 size_t foundPr = output.find("processor");
			if (foundPr!=string::npos)
				{
					//search for processor value
				   size_t found = output.find_first_of("0123456789");
						if (found!=string::npos)
						{
							// get value, convert, store in object
							string value = output.substr (found);
							int ivalue = stoi (value);
							temp->set_processorId(ivalue);
							newRecerdFlag = false;
						}
				}
		 //search for physical id field
		 size_t foundPh = output.find("physical id");
			if (foundPh!=string::npos)
				{
					//search for physical id value
				   size_t found = output.find_first_of("0123456789");
						if (found!=string::npos)
						{
							// get value, convert, store in object
							string value = output.substr (found);
							int ivalue = stoi (value);
							temp->set_physicalId(ivalue);
						}
				}
		//search for fpu field
		 size_t foundFp = output.find("fpu");
			if (foundFp!=string::npos)
				{
					//search for fpu value
				   size_t found = output.find_first_of("yes");
						if (found!=string::npos)
						{
							temp->set_fpu(true);
						}
				}
		//search for cacheSize field
		 size_t foundCs = output.find("cache size");
			if (foundCs!=string::npos)
				{
					//search for cacheSize value
				   size_t found = output.find_first_of("0123456789");
						if (found!=string::npos)
						{
							// get value,convert, store in object
							string value = output.substr (found);
							int ivalue = stoi (value);
							temp->set_cacheSize(ivalue);
						}
				}
		//search for address size field
		 size_t foundAd = output.find("address sizes");
			if (foundAd!=string::npos)
				{
					//search for addressP value
				   size_t found = output.find_first_of("0123456789");
						if (found!=string::npos)
						{
							// get value,convert, store in object
							string value = output.substr((found),2);
							int ivalue = stoi (value);
							temp->set_addressP(ivalue);
						}
						
									//search for addressP value
				   size_t foundA = output.find_last_of("0123456789");
						if (foundA!=string::npos)
						{
							// get value,convert, store in object
							string value = output.substr((foundA-1),2);
							int ivalue = stoi (value);
							temp->set_addressV(ivalue);
						}	
				}
		//search for end record field
		 size_t foundPm = output.find("power management");
			if (foundPm!=string::npos)
				{
					//end of record reached, push object to vector and reset flag
					newRecerdFlag = true;
					//push object to the vector
					records.push_back(temp);
				}		
	 }
	  //close the stream 
	  readf.close();
 }
 else
	 {
		 // if cannot open the file,print msg and exit
		  cout << "Can't open the file :" << argv[1] << endl;
		  return 0;
	 }


 
     // program output
	 cout << endl;
	 cout << "A: Question about the cpuinfo file" << endl;
	 cout << "1. File name is : " << fileName << endl;
	 cout << "2. File contains : " << recordCounter - 1  << " records. (including white space)" << endl;
	 cout << "3. File contains : " << (charCounter + recordCounter) - 1 << " chars in this file." << endl;
	 cout << "4. Used  wc /proc/cpuinfo." << endl;
	 cout << endl;
	 
 //if no CPU info, print error msg and exit.
 if (records.size() == 0)
	 {
		 cout << "This file does not contain any useful information on CPU Info." << endl;
		 cout << "Skipping part B and C." << endl << endl;
	 }
 else 
	 {
		 cout << "B: Question about the configuration" << endl;
		 cout << "1. This machine has " << records.size() << " processors. " << endl;
		 cout << "2. This machine has " << cpuCount(records) << " physical CPUs." << endl;
		 cout << "3. This machine has " << cpuCountDisp(records) << "physical ids." << endl;
		 cout << "4. This machine has processors that " << cacheShare(records) << " L2 cache." <<endl;
		 cout << endl;
		 cout << "C: Question about first processor in the file." << endl;
		 cout << "1. Physical address size is " << records[0]->get_addressP()  << " bits." << endl;
		 cout << "2. Virtual address size is " << records[0]->get_addressV()  << " bits." << endl;
		 cout << "3. Ratio size is " <<(pow(2.0,((records[0]->get_addressV())-(records[0]->get_addressP()))))<<"."<<endl;
		 cout << "4. Processor " << fpuCheck(records) << " floating point unit." << endl;
		 cout << "5. Lvl 2 cache is " << records[0]->get_cacheSize() << " KB." << endl;
		 cout << "6. Lvl 2 cache is " << (records[0]->get_cacheSize())*100 << " Bytes." << endl;
		 cout << endl;
	 }
 	 cout << "D: Question about uptime" << endl;
	 cout << "1. System uptime is " << sysUpTime() << " seconds." << endl;
	 cout << "2. System uptime in D-H-M-S format is " << sysUpTimeA() << endl; 
 //exit
 return 0;
}


/***************************************************************
Function finds a number of distinct CPU's in a vector

Arguments: vector of pointers to the Processor objects

Returns:   (int) number of distinct CPU's in a vector

***************************************************************/
int cpuCount (vector<Processor*> records)
{
	vector <Processor*> :: iterator it;
	int numOfCPU = 0;
	int tempCPU;
	for (it = records.begin(); it != records.end(); it++)
		{
			if ( tempCPU != ((*it)->get_physicalId()))
			{
				tempCPU = (*it)->get_physicalId();
				numOfCPU++;
			}
		}
	return numOfCPU;
}

/***************************************************************
Function finds id's of all CPU's in a vector and displays them

Arguments: vector of pointers to the Processor objects

Returns:  (string) id's of distinct CPU's in a vector

***************************************************************/
string cpuCountDisp (vector<Processor*> records)
{
	vector <Processor*> :: iterator it;
	string CPUString;
	int tempCPU = 999999;
	for (it = records.begin(); it != records.end(); it++)
		{
			if ( tempCPU != ((*it)->get_physicalId()))
			{
				tempCPU = (*it)->get_physicalId();
				CPUString.append(to_string(tempCPU));
				CPUString.append(" ");
			}
		}
	return CPUString;
}

/***************************************************************
Function finds if a num of Processors is > then num of CPU's

Arguments: vector of pointers to the Processor objects

Returns:  (string) that states is Processor share cache or not

Notes:  Function counts distinct CPU's and compares it to # of 
        Processors in a vector.If number is greater then CPU's
		are multi-core CPU's so function returns string stating 
		that CPU's in this vector share cache. If # of CPU's not\
		> then #Processor's then CPU's are single core and they 
		do not share cache so function returns default string 
		that states "do not share".

***************************************************************/
string cacheShare (vector<Processor*> records)
{
	vector <Processor*> :: iterator it;
	string CPUString = "do not share";
	int tempCPU;
	int numOfCPU;
	for (it = records.begin(); it != records.end(); it++)
		{
			if ( tempCPU != ((*it)->get_physicalId()))
			{
				tempCPU = (*it)->get_physicalId();
				numOfCPU++;
			}
		}
	if ((records.size()) > numOfCPU)
		CPUString = "share";
	
	return CPUString;
}

/***************************************************************
Function checks firs object from the vector to see if FPU is T\F

Arguments: vector of pointers to the Processor objects

Returns:   (string)that states if Processor has FPU or not

***************************************************************/
string fpuCheck (vector<Processor*> records)
{
	string ans = "don't have";
	if ( records[0]->get_fpu() == true )
		ans = "have";
	return ans;
}

/***************************************************************
Function gets sys uptime from /proc/uptime and returns it as int

Arguments: none

Returns:   (int) sys uptime in seconds
Notes:     Function opens virtual file /proc/uptime and reads it
           as a the stream, gets first value from the stream, stores
		   it is a string, then converts a string to int with stod.

***************************************************************/
int sysUpTime()
{
	 int upTime = 0;
	 string output;
	 ifstream readf;
     readf.open("/proc/uptime");
	 getline(readf,output);
	 size_t space = output.find_first_of(" ");
	 size_t found = output.find_first_of("0123456789");
				if (found!=string::npos)
				{
					// get value, convert, store in int
					string value = output.substr (found,space);
					upTime = stod (value);
				}
				 readf.close();
	return upTime;
}

/***************************************************************
Function gets int value from sysUpTime() converts it to a string

Arguments: none

Returns:  (string) 

Notes:    Function gets int Uptime in seconds, then converts it to
          D-H-M-S format and stores it as a string. returns it.

***************************************************************/
string sysUpTimeA()
{
	int total = sysUpTime();
	int days;
	int hour;
	int min;
	int sec;
	string ans;
	
	days = total / 86400;
	total = total % 86400;
	hour = total / 3600;
	total = total % 3600;
	min = total / 60;
	sec = total % 60;
	
	ans=to_string(days)+"days, "+to_string(hour)+"hour, "+to_string(min)+"minutes, and "+to_string(sec)+"seconds.";
	
	return ans;
}







