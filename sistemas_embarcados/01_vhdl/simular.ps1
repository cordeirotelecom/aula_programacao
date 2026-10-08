# Elaborado pelo Prof. Vagner Cordeiro
# Simula uma aula de VHDL pelo nome, de qualquer pasta. Nao precisa de administrador.
# Se o GHDL (simulador gratuito) nao existir, ele e baixado para a sua pasta de usuario.
# Uso: simular.ps1 01_porta_and
param([Parameter(Mandatory = $true, Position = 0)][string]$Nome)

$ErrorActionPreference = 'Stop'
$Versao = '6.0.0'
$Destino = Join-Path $env:LOCALAPPDATA 'ghdl'

function Achar-Ghdl {
    $cmd = Get-Command ghdl -ErrorAction SilentlyContinue
    if ($cmd) { return $cmd.Source }
    $p = Join-Path $Destino 'bin\ghdl.exe'
    if (Test-Path $p) { return $p }
    return $null
}

$ghdl = Achar-Ghdl
if (-not $ghdl) {
    Write-Host 'Baixando o simulador GHDL (uma vez so, ~23 MB)...'
    $zip = Join-Path $env:TEMP 'ghdl.zip'
    Invoke-WebRequest "https://github.com/ghdl/ghdl/releases/download/v$Versao/ghdl-mcode-$Versao-mingw64.zip" -OutFile $zip
    Expand-Archive $zip $Destino -Force
    Remove-Item $zip
    $ghdl = Achar-Ghdl
    if (-not $ghdl) { throw 'Nao consegui instalar o GHDL. Veja o README.' }
}

$Fonte = Get-ChildItem -Path $PSScriptRoot -Recurse -File -Filter "$Nome.vhd" | Select-Object -First 1
if (-not $Fonte) { throw "Nao encontrei '$Nome.vhd' dentro de $PSScriptRoot" }

# Area de trabalho temporaria: nao suja a pasta do curso
$Work = Join-Path $env:TEMP ("vhdl_" + $Nome)
New-Item -ItemType Directory -Force $Work | Out-Null

Write-Host "--- Simulando $($Fonte.Name) ---"
& $ghdl -a --std=08 --workdir=$Work $Fonte.FullName
if ($LASTEXITCODE -ne 0) { throw 'Erro de sintaxe no VHDL. Leia a mensagem acima.' }
& $ghdl -e --std=08 --workdir=$Work tb
if ($LASTEXITCODE -ne 0) { throw 'Nao consegui montar a simulacao (a entidade de teste deve se chamar tb).' }
& $ghdl -r --std=08 --workdir=$Work tb --stop-time=100ms 2>&1 |
    ForEach-Object { ($_ -replace '^.*?:(\d+):\d+:@', 'linha $1 @') -replace '\(report note\):', '' }
Remove-Item $Work -Recurse -Force -ErrorAction SilentlyContinue
