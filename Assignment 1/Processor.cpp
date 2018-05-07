/****************************************************************
   Processor

   Author:    George Zhylin
   Z-number:  z1810327

   Description: Processor Class Method files

****************************************************************/

#include "Processor.h"

/***************************************************************

Class initialization for Processor

***************************************************************/

Processor::Processor()
{
  processorId = 0;
  physicalId = 0;
  fpu = false;
  cacheSize = 0;
  addressP = 0;
  addressV = 0;
}

/***************************************************************

Getters for Processor class

***************************************************************/

int Processor::get_processorId()
{
  return processorId;
}

int Processor::get_physicalId()
{
  return physicalId;
}

bool Processor::get_fpu()
{
  return fpu;
}

int Processor::get_cacheSize()
{
  return cacheSize;
}

int Processor::get_addressP()
{
  return addressP;
}

int Processor::get_addressV()
{
  return addressV;
}

/***************************************************************

Setters for Processor class

***************************************************************/

void Processor::set_processorId (int input_processorId)
{
  processorId = input_processorId;
}

void Processor::set_physicalId (int input_physicalId)
{
  physicalId = input_physicalId;
}

void Processor::set_fpu (bool input_fpu)
{
  fpu = input_fpu;
}

void Processor::set_cacheSize (int input_cacheSize)
{
  cacheSize = input_cacheSize;
}

void Processor::set_addressP (int input_addressP)
{
  addressP = input_addressP;
}

void Processor::set_addressV (int input_addressV)
{
  addressV = input_addressV;
}
