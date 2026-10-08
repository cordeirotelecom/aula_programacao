@echo off
title Portal do Curso - Programacao
cd /d "%~dp0"
where node >nul 2>nul
if errorlevel 1 (
  echo Node.js nao encontrado. Execute instalar_professor.ps1 primeiro.
  pause
  exit /b 1
)
node "%~dp0laboratorio\server.js"
echo.
echo O laboratorio foi encerrado.
pause
