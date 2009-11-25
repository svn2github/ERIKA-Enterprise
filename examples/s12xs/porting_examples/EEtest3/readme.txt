test3

 A minimal EE demo that demostrates how to create two TASKs with different priorities.
 This demo can be used to test the preemption mechanism. In this case Task2 preempts Task1.
 The compilation chain can start outside Eclipse environment from the Cygwin shell with the "make" 
 command inside the Debug folder of the project.
 The Debug folder can be created manually if you don't have the oil-based generator. 
 The Debug folder must contain at least the following files (suitably modified...):
 ee_hs12xsregs.h, eecfg.h, eecfg.c and the makefile (see the examples of different architectures to begin...) 
