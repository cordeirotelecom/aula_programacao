# Elaborado pelo Prof. Vagner Cordeiro
# Abre uma aula ou projeto da pasta web no navegador padrao.
# Uso: abrir.ps1 NOME_DA_AULA   (ex: abrir.ps1 01_primeira_pagina)
param([Parameter(Mandatory = $true)][string]$Nome)

$pasta = $PSScriptRoot
$arquivo = Get-ChildItem -Path $pasta -Recurse -Filter "$Nome.html" | Select-Object -First 1
if (-not $arquivo) {
    $projeto = Get-ChildItem -Path $pasta -Recurse -Directory -Filter $Nome | Select-Object -First 1
    if ($projeto) { $arquivo = Get-Item (Join-Path $projeto.FullName 'index.html') -ErrorAction SilentlyContinue }
}
if (-not $arquivo) {
    Write-Host "Nao encontrei '$Nome'. Confira o nome na tabela do README." -ForegroundColor Red
    exit 1
}
Write-Host "Abrindo $($arquivo.FullName)"
Start-Process $arquivo.FullName
$code = Get-Command code -ErrorAction SilentlyContinue
if (-not $code) {
    $local = Join-Path $env:LOCALAPPDATA 'Programs\Microsoft VS Code\bin\code.cmd'
    if (Test-Path $local) { $code = $local }
}
if ($code) { & $code --reuse-window $arquivo.FullName } else { Write-Host 'VS Code nao encontrado; abrindo so no navegador.' -ForegroundColor Yellow }
