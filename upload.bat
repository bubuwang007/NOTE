@echo off

cd /d %~dp0
git add .
@REM 提交的时候，可以在后面加上 -m "提交的时间"
git commit -m "%date:~0,10%%time:~0,8%"
git push

pause
@echo on