xmlbus
======

Welcome.

In order to build the sources:

Make sure you have the required software
- check (unit testing for C) (http://check.sourceforge.net/ )
- log4c (http://log4c.sourceforge.net)
- libxml2 (most of the times already on your system but available via http://xmlsoft.org)
- python with the lxml library (python is mostly available, lxml is easily installed by easy_install lxml


Step 1

make -f Makefile.cvs 
This make sure that you have the right configure script

Step 2
Create a directory (optional) like 'debug' 
and run inside the directory '../configure'
Have a look at the options (configure --help) for details

Step 3
Run 'make' 

Step 4 
Run 'make install'

NOTE ON MESSAGES TO console:
Logging is implemented based on Log4c, you need to set 2 env variables to get logging to
the console:
LOG4C_APPENDER=stdout
LOG4C_PRIORITY=debug

