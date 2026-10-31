@echo off
title Starting Server...
color B

cd ac_dbagentsvr
start dbagent.bat
timeout 1 > nul
cd ..

cd ac_dbagentsvr
start dbagent_log.bat
timeout 1 > nul
cd ..

cd ac_billingsvr
start billing.bat
timeout 1 > nul
cd ..


cd ac_mainsvr
start main.bat
timeout 1 > nul
cd ..

cd ac_gamesvr
start game.bat
timeout 1 > nul
cd ..

PAUSE