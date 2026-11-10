@echo off
chcp 65001 >nul
set CLI="D:\STM32CubeProgrammer\bin\STM32_Programmer_CLI.exe"
set HEX="D:\STM32_PROJECTS\F103_WaterDAQ\MDK-ARM\F103_WaterDAQ\F103_WaterDAQ.hex"
echo [1/2] flash: %HEX%
%CLI% -c port=SWD -w %HEX% -v -rst
echo [2/2] done - press any key
pause >nul