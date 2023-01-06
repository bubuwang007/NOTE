@echo off

cd /d %~dp0
git add .
@REM 提交的时候，可以在后面加上 -m "提交的时间"
git commit -m "2023.1.7 7.38"
git push