makesrc directory
------------------

--> scripts to help building source distributions of the EE
    Enterprise Source Code.




Abstract
--------

This directory simply contains a set of scripts and files that should
help making a source distribution of EE Enterprise, that is a
distribution that only includes a subset of the ee source tree




What is a source distribution for EE Enterprise
--------------------------------------------------

A source distribution for EE is a set of directories that includes
only a subsetof the distribution, useful to distribute only part of
the source code to selected people.

Source distributions include CVS directory to make possible to these
people to commit changes.






The makedist directory
----------------------

Here are the contents of the makedist directory:

readme.txt - this file
makefile   - the main makefile that is used to generate the binary package
config     - various configuration files. In particular, conf.in contains
             the list of all configurations that have been used for
             building
out        - (temp directory) contains intermediate results that are used for
             the binary distribution
ee_*       - (temp directory) contains a given binary distribution












How to make a distribution
--------------------------

To make a given source distribution, just type:

make DIST=<name>

where <name> is a prefix of the available names thar are listed into conf.in

At the end of the process, a set of ee_<name>* directories will
contain the distributions for the configuration chosen.

for the usage of the makefile see the binary distribution page :-)






Source distribution creation process
------------------------------------

1) Understanding which are the targets to be done

the DIST value identifies a set of {set of libraries} that have to be
built. The following steps applies for each given {set of libraries}

2) Creation of the distribution directory

Suppose D is a given distribution.
- the directory ee_D is created.
- a basic directory structure is also created (pkg, lib directories)

3) Creation of the include files

Distribution D includes a set of different configurations C that are
made of a set of parameters that are usually expressed in the EEOPT
variable in just-in-time compilations.

- collect all the EEOPT variables from all the configurations C of
  distribution D. this collection of variables is helpful to
  understand which are the files and directories of the include tree
  that must be part of the distribution D

- copy a given subdirectory structure ONLY if the relative EEOPT
  Configuration is present in one of the configurations C

For example, suppose that a distribution D includes a set of
configurations that at the end melts up in this set of EEOPT
configurations: __ARM7GNU__ __EVALUATOR7T__ __OO_BCC1__ . That
means that only the directories include/arm7gnu,
include/arm7gnu/evaluator7T, include/oo will be considered in the
copying process.
