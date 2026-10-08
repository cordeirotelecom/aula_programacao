# Elaborado pelo Prof. Vagner Cordeiro
# PREPARAR AMBIENTE DO ALUNO: instala ferramentas e cria as pastas e arquivos VAZIOS (so com cabecalho)
# para o aluno escrever o codigo em sala. NAO baixa o conteudo pronto do curso.
# Nao precisa de administrador.
$ErrorActionPreference = 'Stop'
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
$ProgressPreference = 'SilentlyContinue'

$Docs  = [Environment]::GetFolderPath('MyDocuments')
$Aluno = Join-Path $Docs 'programacao\aluno'
$Tools = Join-Path $HOME 'tools'
$Autor = 'Aluno: escreva seu nome aqui'

function AdicionarAoPath($pasta) {
    $atual = @([Environment]::GetEnvironmentVariable('Path', 'User') -split ';' | Where-Object { $_ -and $_.TrimEnd('\') -ine $pasta.TrimEnd('\') })
    [Environment]::SetEnvironmentVariable('Path', (($atual + $pasta) -join ';'), 'User')
    $env:Path = "$pasta;$env:Path"
}
function Escrever($caminho, $texto) {
    New-Item -ItemType Directory -Path (Split-Path $caminho) -Force | Out-Null
    if (-not (Test-Path $caminho)) { Set-Content -Path $caminho -Value $texto -Encoding UTF8 }
}

Write-Host '== 1/3 Compilador GCC (C e C++) ==' -ForegroundColor Cyan
New-Item -ItemType Directory -Path $Tools -Force | Out-Null
if (Get-Command gcc -ErrorAction SilentlyContinue) {
    Write-Host 'GCC ja instalado.'
} else {
    $rel = Invoke-RestMethod -Uri 'https://api.github.com/repos/brechtsanders/winlibs_mingw/releases/latest' -Headers @{ 'User-Agent' = 'curso-setup' }
    $pac = $rel.assets | Where-Object { $_.name -match '^winlibs-x86_64-posix-seh-.*\.zip$' } | Select-Object -First 1
    if (-not $pac) { throw 'Nao encontrei o pacote do GCC. Tente de novo mais tarde.' }
    $arq = Join-Path $env:TEMP $pac.name
    Invoke-WebRequest -Uri $pac.browser_download_url -OutFile $arq
    $pastaGcc = Join-Path $Tools "winlibs-$($rel.tag_name)"
    Expand-Archive -Path $arq -DestinationPath $pastaGcc -Force
    Remove-Item $arq
    $exe = Get-ChildItem $pastaGcc -Filter gcc.exe -Recurse | Select-Object -First 1
    AdicionarAoPath $exe.DirectoryName
}

Write-Host '== 2/3 Node.js ==' -ForegroundColor Cyan
if (Get-Command node -ErrorAction SilentlyContinue) {
    Write-Host 'Node.js ja instalado.'
} else {
    $lts = (Invoke-RestMethod -Uri 'https://nodejs.org/dist/index.json' | Where-Object { $_.lts -and $_.version -like 'v22.*' } | Select-Object -First 1).version
    $arq = Join-Path $env:TEMP "node-$lts.zip"
    Invoke-WebRequest -Uri "https://nodejs.org/dist/$lts/node-$lts-win-x64.zip" -OutFile $arq
    Expand-Archive -Path $arq -DestinationPath $Tools -Force
    Remove-Item $arq
    AdicionarAoPath (Join-Path $Tools "node-$lts-win-x64")
}

Write-Host '== 3/3 Criando suas pastas e arquivos em branco ==' -ForegroundColor Cyan

for ($i = 1; $i -le 10; $i++) {
    $n = '{0:00}' -f $i
    Escrever "$Aluno\c\exercicio_$n.c" "/* Elaborado por: $Autor */`r`n#include <stdio.h>`r`n`r`nint main(void) {`r`n    /* escreva seu codigo aqui */`r`n    return 0;`r`n}`r`n/* Executar: powershell -ExecutionPolicy Bypass -File `"`$([Environment]::GetFolderPath('MyDocuments'))\programacao\aluno\executar.ps1`" c exercicio_$n */"
    Escrever "$Aluno\cpp\exercicio_$n.cpp" "// Elaborado por: $Autor`r`n#include <iostream>`r`n`r`nint main() {`r`n    // escreva seu codigo aqui`r`n    return 0;`r`n}`r`n// Executar: powershell -ExecutionPolicy Bypass -File `"`$([Environment]::GetFolderPath('MyDocuments'))\programacao\aluno\executar.ps1`" cpp exercicio_$n"
}

Escrever "$Aluno\web\index.html" "<!DOCTYPE html>`r`n<!-- Elaborado por: $Autor -->`r`n<html lang=`"pt-BR`">`r`n<head>`r`n<meta charset=`"utf-8`">`r`n<title>Minha pagina</title>`r`n<link rel=`"stylesheet`" href=`"estilo.css`">`r`n</head>`r`n<body>`r`n<!-- escreva seu HTML aqui -->`r`n<script src=`"script.js`"></script>`r`n</body>`r`n</html>"
Escrever "$Aluno\web\estilo.css" "/* Elaborado por: $Autor */`r`n/* escreva seu CSS aqui */"
Escrever "$Aluno\web\script.js" "// Elaborado por: $Autor`r`n// escreva seu JavaScript aqui"

foreach ($p in 'arduino_01_piscar_led', 'arduino_02_botao', 'esp32_01_hello_serial', 'esp32_02_wifi') {
    Escrever "$Aluno\arduino_esp32\$p\$p.ino" "// Elaborado por: $Autor`r`n`r`nvoid setup() {`r`n  // roda uma vez`r`n}`r`n`r`nvoid loop() {`r`n  // roda sem parar`r`n}"
}

Escrever "$Aluno\redes\calculos.c" "/* Elaborado por: $Autor */`r`n/* Exercicio de redes: calcule rede, broadcast e mascara. */`r`n#include <stdio.h>`r`n`r`nint main(void) {`r`n    return 0;`r`n}"
Escrever "$Aluno\sistemas_embarcados\simulacao_01.c" "/* Elaborado por: $Autor */`r`n#include <stdio.h>`r`n`r`nint main(void) {`r`n    return 0;`r`n}"
Escrever "$Aluno\sistemas_embarcados\vhdl\aula_01.vhd" "-- Elaborado por: $Autor`r`n-- escreva seu VHDL aqui"

$exec = @'
# Compila e executa um arquivo seu pelo nome. Uso: executar.ps1 c exercicio_01
param([Parameter(Mandatory=$true,Position=0)][ValidateSet('c','cpp')][string]$Linguagem,[Parameter(Mandatory=$true,Position=1)][string]$Nome)
$ErrorActionPreference = 'Stop'
$f = Get-ChildItem -Path $PSScriptRoot -Recurse -File | Where-Object { $_.BaseName -eq $Nome -and $_.Extension -eq ".$Linguagem" } | Select-Object -First 1
if (-not $f) { throw "Nao encontrei $Nome.$Linguagem" }
$exe = [IO.Path]::ChangeExtension($f.FullName, '.exe')
if ($Linguagem -eq 'c') { gcc -std=c11 -Wall -Wextra $f.FullName -o $exe } else { g++ -std=c++17 -Wall -Wextra $f.FullName -o $exe }
if ($LASTEXITCODE -ne 0) { throw 'Erro de compilacao. Leia a mensagem acima.' }
Write-Host "--- Executando $($f.Name) ---"
& $exe
'@
Escrever "$Aluno\executar.ps1" $exec

Write-Host ''
Write-Host "PRONTO! Suas pastas estao em: $Aluno" -ForegroundColor Green
Write-Host 'Abra a pasta no VS Code:   code "$([Environment]::GetFolderPath(''MyDocuments''))\programacao\aluno"'
Write-Host 'Teste (depois de escrever o codigo):'
Write-Host 'powershell -ExecutionPolicy Bypass -File "$([Environment]::GetFolderPath(''MyDocuments''))\programacao\aluno\executar.ps1" c exercicio_01'
# Executar: irm https://raw.githubusercontent.com/cordeirotelecom/aula_programacao/main/preparar_aluno.ps1 | iex
