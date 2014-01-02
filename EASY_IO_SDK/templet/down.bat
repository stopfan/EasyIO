@ECHO OFF
ECHO Open a project and data file, start auto processing and exit
"C:\Program Files\SEGGER\JLinkARM_V420p\jflasharm.exe" -openprjrbt6.jflash -openeasyio.bin,0x8000000 -auto -exit
IF ERRORLEVEL 1 goto ERROR
  goto END
:ERROR
ECHO J-Flash ARM: Error!
pause
:END
