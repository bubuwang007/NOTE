@echo off

set here=%~dp0
set build=%here%build
if not exist "%build%" mkdir %build%

cd %build%
cmake ../
cmake --build . --config Release