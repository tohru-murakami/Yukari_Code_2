@echo off
REM This script generates 50 optimized team assignment results.

REM grouping_ils.exe : team assignment optimization program.
REM data.txt : student data of properties and peer compatibility.
REM results.txt : optimized team assignments.

REM README for details.
(for /f %%a in ('date /t') do set d=%%a)
(for /f %%a in ('time /t') do set t=%%a)
echo %d% %t% > results.txt
for /l %%i in (0, 1, 49) do (
    grouping_ils.exe data.txt >> results.txt
    (for /f %%a in ('date /t') do set d=%%a)
    (for /f %%a in ('time /t') do set t=%%a)
    echo %d% %t% >> results.txt
    echo ----- >> results.txt
)
