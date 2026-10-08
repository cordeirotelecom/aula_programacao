@echo off
rem Elaborado pelo Prof. Vagner Cordeiro
rem DUPLO CLIQUE: instala o que faltar, coloca o curso em Documentos\programacao e abre a pagina inicial.
title Curso de Programacao - Instalacao automatica
cd /d "%~dp0"
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0instalar_professor.ps1"
if errorlevel 1 (
  echo.
  echo ERRO na instalacao. Tire uma foto desta tela e envie ao professor.
  pause
  exit /b 1
)
for /f "delims=" %%D in ('powershell -NoProfile -Command "[Environment]::GetFolderPath('MyDocuments')"') do set DOCS=%%D
start "" "%DOCS%\programacao\curso_programacao\index.html"
echo.
echo PRONTO! A pagina do curso foi aberta no navegador.
pause
