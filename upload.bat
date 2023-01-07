@echo off

cd /d %~dp0
git add .
git commit -m "%date:~0,10%%time:~0,8%"
git pull
git push

pause
@echo on