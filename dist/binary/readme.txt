makedist directory
------------------

--> scripts to help building binary distributions of the EE
    Enterprise Source Code.




Abstract
--------

This directory simply contains a set of scripts and files that should
help making a binary distribution of EE Enterprise, that is a
distribution that only includes compiled libraries, and include files
with the external interfaces.





What is a binary distribution for EE Enterprise
--------------------------------------------------

A binary distribution for EE is a set of scripts, include files and
libraries that can be used to create an application based on EE.

EE Enterprise is highly configurable using the EEOPT
variable. To retain such configurability in a binary distribution, a
SUBSET of all the possible EEOPT setups have to be considered when
compiling the binary distribution. Basically, a binary distribution
is a set of different EEOPT configurations with their
relative libraries and include files.

In general, the binary distribution can be generated from the source
code expressly for a given customer with a given configuration.

A binary distribution contains the following directories:

include - all the include files that are needed to properly CONFIGURE
and LINK the source code that is present into the libraries.

lib - the set of libraries that are included in the distribution.








Changes that have to be made to the EE Enterprise tree
---------------------------------------------------------

Currently (2004/02/03), the EE Enterprise source code has been
designed for configurability and for just-in-time compilation. That
is, each application can specify its own EEOPT parameters, and the
kernel source code is compiled against these options to create a
customized kernel version that will express maximum performance.

Moreover, the actual structure of the include files mixes together the
interface that the user can call, and the internal functions, that the
user should NOT call.

This way of doing things is not the best one if we have to create a
binary distribution. For these reasons, the following modifications
have to be made to the current EE Enterprise source tree:

- Symbols: __BIN_DISTR_LIMITED__ and __BIN_DISTR_FULL__ can be used to
  discriminate if we are compiling to make a just-in-time compilation
  or a binary library.

- Constants: many constants (related with application configuration,
  e.g., the number of tasks) are currently implemented as
  #defines. That works as long the kernel can be compiled considering,
  for example, a fixed number of tasks. When making a library, the
  library cannot change, and in this sense it MUST be independent from
  constants that are present in the source code. For this reason,
  these constants will have to be referred as "external const" in the
  include files, but ONLY when libraries are compiled.

- Include files: 
  - application contines to include the ee.h file.
  - the files included by ee.h will remain the same.
  - the INTERNAL data structures will be moved away from the tree of
    files included by ee.h. These data will be declared into
    internal.h. internal.h SHOULD NOT NEED the inclusion of ee.h.

- Source files:
  - should include internal.h and NOT ee.h






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
erika_*    - (temp directory) contains a given binary distribution







Types of binary distributions
-----------------------------

There are two types of binary distributions:

- Evaluation libraries
  These libraries are limited versions of the real libraries. In
  practice, the code is compiled with fixed values (#defines) for the
  different main symbols (like EE_MAX_TASK)

  To create Evaluation libraries, add the symbol
  __BIN_DISTR_LIMITED__. The limited distribution adds some checks in
  the code to limit its usage.
  
  These checks have only sense if setup values are generated for the 
  main symbols. Note that if an evaluation library is selected, the 
  user MUST specify the limits for the main symbols...

- Production libraries
  These are full-fledged libraries that are distributed to the
  companies that do not have permission to use the source code.

  To create Production Libraries, add the symbol
  __BIN_DISTR_FULL__. No additional code is added to limit the use of
  the primitives. The main symbols can appear both as #defines
  (unusual choice) or like extern values.






Ways to access the main configuration symbols
---------------------------------------------

The main configuration symbols are the symbols like: EE_MAX_TASK,
EE_MAX_RESOURCE, ... that is, the symbols that controls the
cardinality of the system. When distributing the source code of the
system, these values are leaved unspecified in the source code. Their
value will be then specified inside the eecfg.h as #defines.

When distributing a binary image, such values have either to be 

- defined as #defines, to limit the numbers of objects the customer
  can use.

- defined as extern const values to give the possibility to tune the
  number of objects (tasks, resources, ...) in the system, or

The generation scripts of the binary image give both possibilities:

- definition as #define
  the symbols should be listed inside the config/conf.in file like
  make's environment variables in the form 
  DISTRIBUTIONNAME_SYMBOLNAME = VALUE.

- definition as extern values
  if a symbol is not specified as #define, the extern const
  specification is automatically generated.

The complete list of available main configuration symbols are listed
inside config/conf.in in the define ALL_SYMBOLS








How to make a binary distribution
---------------------------------

To make a given binary distribution, just type:

make DIST=<name>

where <name> is a prefix of the available names thar are listed into conf.in

At the end of the process, a set of erika_<name>* directories will
contain the binary distributions for the configuration chosen.

For example, suppose that customer C bought two sets of EE
Enterprise libraries, called a and b. Suppose that the conf.in file
lists both C_a and C_b. here are some meaningful commands:

make DIST=C_a
- makes the set of libraries "a" for customer "C". 
- results in the directory erika_C_a

make DIST=C_b
- makes the set of libraries "b" for customer "C". 
- results in the directory erika_C_b

make DIST=C
make DIST=C_
- makes the set of libraries "a" and "b" for customer "C".
- results in the directories erika_C_a and erika_C_b

make clean
- cleans all the directories out and erika_*







Binary distribution creation process
------------------------------------

1) Understanding which are the targets to be done

the DIST value identifies a set of {set of libraries} that have to be
built. The following steps applies for each given {set of libraries}

2) Creation of the distribution directory

Suppose D is a given distribution.
- the directory erika_D is created.
- a basic directory structure is also created (include, lib directories)

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

4) Library creation

Just-in-time compilation for EE already internally uses a library
usually called out/liberika.a . In this case, FOR each configuration,
the script have to perform a standard just-in-time compilation to
create a particular out/liberika.a . Once created, that library will
be moved in erika_D/lib/liberikaC.a

DEBUG support when compiling the libraries should be disabled.

5) eecfg.h generation

standard include files will need in any case the specification of the
EEOPT defines that where used when compiling. That is done using a
custom eecfg.h that will have to be created and put into the main
include diretory.

The right set of parameters that have to be used can be selected using
a define __CONFIG_configname__. a template can be found in the version
that is generated by the script. if the distribution is a limited
distribution, values of the main symbols appear in the form of
defines.

6) makefile generation

Finally, a makefile should be generated, that must be able, given a
particular distribution/compiler, to use the libraries to compile a
given application.

I do not know how to do that yet, the thing that I know is that there
will be for sure some parts that will depend on architecture/compiler
issues, plus some parts that depend on the particular configurations.
