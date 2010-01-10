#!/usr/bin/python
# coding=UTF-8

import os, os.path
import re
import subprocess
import sys

class data_section:
    def __init__( self, textlines, startname ):
        self.table = dict()
        for line in textlines:
            entry = parse_line( line )
            if entry:
                # print "Found %s (%s,%d)" % \
                #       (entry[0], hex(entry[1].addr), entry[1].length)
                if entry[0] == startname:
                    self.section_start = entry[1].addr
                elif entry[1].type == st_entry.TYPE_OBJECT:
                    self.table[entry[0]] = entry[1]
                    # print "Added %s" % entry[0]
    
    def out_object( self, name, entry_data=None ):
        if not entry_data:
            entry_data = self.table[name]
        length = entry_data.length
        offs = entry_data.addr - self.section_start
        if length <= 4:
            out_word( name, offs, length )
        else:
            print >>sys.stderr, "Warning: object %s of length %d > 4 not handled and ignored" % (name, length)

    def out_all_objects( self ):
        for entry in self.table.items():
            if entry[1].type == st_entry.TYPE_OBJECT and \
                   entry[1].length > 0:
                self.out_object( entry[0], entry[1] )

MEMENTITY = "onchipramtimer_tb/UUT/LM32/cpu/load_store_unit/ram/mem"
def out_word( name, offset, length ):
    start = offset* 8;
    end = start + length * 8 - 1;
    print "add wave -vbus {%s} -noreg {%s(%d downto %d)}" % \
          (name, MEMENTITY, end, start)

class st_entry:
    TYPE_OBJECT = "O"
    TYPE_FUNCTION = "F"
    TYPE_OTHER = " "
    def __init__( self, addr, length, etype ):
        self.addr = addr
        self.length = length
        self.type = etype

# Parse a line of objdump and return an entry for the symbol table
entryre = re.compile( "^([0-9a-fA-F]+) [lgu!][w ][C ][W ][Ii ] ([OF ]) [^\t]+\t([0-9a-fA-F]+) (.+)$" )
def parse_line( line ):
    global entryre
    m = entryre.match( line )
    if not m:
        return None
    addr = eval( "0x" + m.groups()[0] )
    length = eval( "0x" + m.groups()[2] )
    etype = m.groups()[1]
    name = m.groups()[3]
    return ( name, st_entry( addr, length, etype ) )


#
# Main
#
OBJDUMPCMD = "lm32-elf-objdump"
STARTSYMBOL = "_frodata"
if len( sys.argv ) < 2:
    sys.exit( "usage wavesymbol <elf_object> [<symbol1> [<symbol2> ...]]" )

elfobject = sys.argv[1]
pipe = subprocess.Popen( (OBJDUMPCMD, "-t", elfobject), shell=False, \
                         stdout=subprocess.PIPE ).stdout
table = data_section( pipe, STARTSYMBOL )
if len(sys.argv) > 2:
    for sym in sys.argv[2:]:
        table.out_object( sym )
else:
    table.out_all_objects()
