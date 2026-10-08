@echo off
rem Elaborado pelo Prof. Vagner Cordeiro
rem DUPLO CLIQUE: abre a pasta do curso no VS Code e a pagina inicial no navegador.
cd /d "%~dp0"
where code >nul 2>nul
if %errorlevel%==0 (
  start "" code "%~dp0"
) else if exist "%LOCALAPPDATA%\Programs\Microsoft VS Code\bin\code.cmd" (
  start "" "%LOCALAPPDATA%\Programs\Microsoft VS Code\bin\code.cmd" "%~dp0"
) else (
  echo VS Code nao encontrado. Instale em https://code.visualstudio.com
  pause
)
start "" "%~dp0index.html"
