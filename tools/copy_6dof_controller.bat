@echo off
REM =========================================================
REM Batch File for Relative File Copy and Overwrite
REM =========================================================

REM %~dp0 returns the drive and path of the batch file itself, regardless of
REM where the script is executed from.
set "SCRIPT_DIR=%~dp0"

REM --- Configuration (Relative Paths) ---
REM NOTE: Paths are relative to the folder where this batch file is located.
set "SOURCE_REL=..\model\controller_6dof_container_ert_rtw"
set "DEST_REL=..\src\components\controller_6dof_container"

REM Calculate the absolute paths
set "SOURCE_DIR=%SCRIPT_DIR%%SOURCE_REL%"
set "DEST_DIR=%SCRIPT_DIR%%DEST_REL%"

REM List of the 4 specific files to copy
set "FILE1=controller_6dof_container.cpp"
set "FILE2=controller_6dof_container.h"
set "FILE3=controller_6dof_container_data.cpp"
set "FILE4=rtwtypes.h"
REM ---------------------------------------

echo Starte Kopiervorgang...
echo Quelle: %SOURCE_DIR%
echo Ziel:   %DEST_DIR%
echo ---------------------------------------

REM Check if the destination directory exists. If it does not, the COPY command will fail.
if not exist "%DEST_DIR%\" (
    echo.
    echo FEHLER: Zielordner "%DEST_DIR%" existiert nicht.
    echo.
    goto :eof
)

REM --- Copy Operations ---
REM The /Y flag forces the overwrite of the destination file without prompting.

call :CopyFile "%FILE1%"
call :CopyFile "%FILE2%"
call :CopyFile "%FILE3%"
call :CopyFile "%FILE4%"

echo ---------------------------------------
echo Kopiervorgang abgeschlossen.
pause
goto :eof

:CopyFile
REM Subroutine to handle copying and error checking for a single file.
set "FILENAME=%~1"

echo Kopiere %FILENAME%...
copy /Y "%SOURCE_DIR%\%FILENAME%" "%DEST_DIR%\" > nul

REM Check ERRORLEVEL: 0 indicates success, non-zero indicates failure.
if ERRORLEVEL 1 (
    echo FEHLER beim Kopieren von %FILENAME%
) else (
    echo SUCCESS
)
goto :eof