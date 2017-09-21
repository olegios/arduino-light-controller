The controller count visitors 
for light and fan control in a bathroom
=====================================================================

> Author: olegios
> Date: 2017  
> Revision: version 1
> License: Public Domain

INSTALLATION
------------

Please make sure the release file is unpacked under a Web-accessible
directory. You shall see the following files and directories:

    duino-light-controller                      arduino sketch folder
      ├── light-controller-visitor-counter.ino  main arduino file
      ├── DelayOn.h                             h file class for delay
      ├── DelayOn.cpp                           cpp file class for delay
      ├── Schematic.svg                         (optional) an image of the required schematics       
      └── README.md                             this file

BOM
----

ID     |Part name      		      |Name 					                |Quantity
-------|------------------------|-------------------------------|-----------
U1, U2 | E18-D80NK Resistor     | Infrared Sensor Switch 	      | 2       
U3	   | Arduino NANO			      | Controller				            | 1       
U4, U5 | OMRON G3MB-202P		    | Solid State Relay Module 	    | 1       
U6	   | AC 220V to DC 5V 500mA | Step-Down Power Supply Module | 1 	
SW1 	 |    					          | Reed Switch    				        | 1       
S1 	   | 						            | Switch   					            | 1        
R1, R2 | 10k   				          | Resistor    				          | 2        
C1     | 100nF   				        | Capasitor    				          | 2        

SCHEMATIC
---------
![schematic](https://github.com/olegios/arduino-light-controller/blob/master/Schematic.svg)
