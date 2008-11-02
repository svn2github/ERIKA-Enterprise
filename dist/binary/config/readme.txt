This directory contains a set of files used during the script
generation. These files are:

- erikacfg.mk
  This file contains the rules to generate the template for the
  eecfg.h included in the binary distribution

- conf.mk
  This file contains the list of configuration supported by each
  binary generation. For each distribution, a set of libraries are
  described in terms of a set of EEOPT options.

- compile.mk
  This file contains the rules, for each compiler/architecture/BSP,
  that have to be used to compile the library that will be used for
  the binary distribution.

- distrib.mk
  This files contains the associations between each meaningful
  EEOPT options and the include files that have to be copied in the
  include tree of the binary distribution

- make_makefile.mk
  This file contains the rules used to generate the makefile structure
  from the available templates.
