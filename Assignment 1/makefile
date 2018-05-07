#
# PROGRAM:    hw1
# PROGRAMMER: George Zhylin
# LOGON ID:   z1810327
# DATE:   2/18/2018
#

# Rule to link object code files to create executable file
hw1.exe: hw1.o Processor.o
	g++ hw1.o Processor.o -o hw1.exe

# Rules to compile source code files to object code
Processor.o: Processor.cpp Processor.h
	g++ -c Processor.cpp -o Processor.o

hw1.o: hw1.cpp Processor.h
	g++ -c hw1.cpp -o hw1.o

# Pseudo-target to remove object code and executable files
clean :
	rm hw1.o Processor.o


