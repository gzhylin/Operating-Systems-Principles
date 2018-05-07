#ifndef PROC_H
#define PROC_H

/****************************************************************
   Processor header

   Author:    George Zhylin
   Z-number:  z1810327

   Description: Store data from the /proc/cpuinfo file

****************************************************************/

using namespace std;
#include <string>

class Processor
{

	private:
	  int    processorId;   //Processor ID
	  int    physicalId;    //CPU ID
	  bool   fpu;           //floating num unit
	  int    cacheSize;     //Cache size
	  int    addressP;      //Physical Address size
	  int    addressV;      //Virtual Address size

	public:
	  Processor();

	  int get_processorId();
	  void set_processorId(int input_processorId);
	  int get_physicalId();
	  void set_physicalId(int input_physicalId);
	  bool get_fpu();
	  void set_fpu(bool input_fpu);
	  int get_cacheSize();
	  void set_cacheSize(int input_cacheSize);
	  int get_addressP();
	  void set_addressP(int input_addressP);
	  int get_addressV();
	  void set_addressV(int input_addressV);
};

#endif /* PROC_H */

