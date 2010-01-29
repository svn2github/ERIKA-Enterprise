@echo off

echo ****************************************************************
echo * MODISTARC OSEK/VDX Conformance Testing Methodology           *
echo * Operating System: Erika Enterprise                           *
echo * Examples:                                                    *
echo *          - to run hiwave:                                    *
echo *              modistarc_regression_test.bat hivawe            *
echo *          - to make all and run hiwave:                       *
echo *              modistarc_regression_test.bat all               *
echo *              modistarc_regression_test.bat                   *
echo *          - to clean testcases:                               *
echo *              modistarc_regression_test.bat clean             *
echo *          - to make only one test and run hiwave:             *
echo *              modistarc_regression_test.bat modistarc_alarm_1 *
echo ****************************************************************

rem ***************************************************************

rem Are you here because the script can not find the bash shell?
rem Please change the following line!
set EE_BASH_PATH=C:\cygwin\bin\bash.exe
set TESTCASE_PATH=C:\cygwin\home\user\repos\ee\trunk\ee\testcase
if not exist %EE_BASH_PATH% goto error

rem ***************************************************************

::goto end

IF "%1" EQU "hiwave" goto hiwave

:ok
set OLDDIR=%CD%
cd %TESTCASE_PATH%
echo ...wait a moment, please, the selected operation is in progress...
set SHELLOPTS=igncr
%EE_BASH_PATH% -c "/bin/bash --login -c \"cd `/bin/cygpath/ -ms \"$PWD\"`; ./common/s12xs/modistarc_compile.sh %1 \""
cd /d %OLDDIR%  

IF "%1" EQU "clean" goto end

goto hiwave

rem ***************************************************************

:error
echo *** ERROR:
echo ***  The compile.bat script can not find the Cygwin BASH shell.
echo ***  Please change the EE_BASH_PATH environment variable inside compile.bat
pause
goto end

rem ***************************************************************

:hiwave
::C:\Programmi\Freescale\CodeWarriorHCS12V4_7\Prog\hiwave.exe -Prod=%TESTCASE_PATH%\common\s12xs\Full_Chip_Simulation.ini -c %TESTCASE_PATH%\tmp\s12xs.cmd
C:\Programmi\Freescale\CodeWarriorHCS12V4_7\Prog\hiwave.exe -Prod=%TESTCASE_PATH%\common\s12xs\SofTec_HCS12.ini -c %TESTCASE_PATH%\tmp\s12xs.cmd -instance=softec

rem ***************************************************************

:end
