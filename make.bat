@REM you should pass --debug to frontend (Wf--debug)
@REM you should pass -y to the linker to make it create a CDB file used for debugging (Wl-y)
@REM and also pass -m -w to the linker to produce "wide maps" that are useful for emulicious (Wl-m)
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -c -o main.o main.c
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -o main.gb main.o