# Elaborado pelo Prof. Vagner Cordeiro
# Compila e executa um exemplo pelo nome, de qualquer pasta.
# Uso: executar.ps1 c 01_ola_mundo
#      executar.ps1 cpp ex_01_led_sos
param(
    [Parameter(Mandatory = $true, Position = 0)]
    [ValidateSet('c', 'cpp')]
    [string]$Linguagem,

    [Parameter(Mandatory = $true, Position = 1)]
    [string]$Nome
)

$ErrorActionPreference = 'Stop'

$Raiz = Join-Path $PSScriptRoot $Linguagem
$Pastas = @($Raiz)
if ($Linguagem -eq 'c') { $Pastas += Join-Path $PSScriptRoot 'redes' }   # programas de redes em C
if ($Linguagem -eq 'c') { $Pastas += Join-Path $PSScriptRoot 'sistemas_embarcados' }   # simulacoes em C
$Fonte = Get-ChildItem -Path $Pastas -Recurse -File |
    Where-Object { $_.BaseName -eq $Nome -and $_.Extension -eq ".$Linguagem" } |
    Select-Object -First 1

if (-not $Fonte) {
    throw "Nao encontrei '$Nome.$Linguagem' dentro de $Raiz"
}

if (-not (Get-Command gcc -ErrorAction SilentlyContinue)) {
    throw 'GCC nao encontrado. Execute o passo 1 do README e abra um PowerShell novo.'
}

$Executavel = [System.IO.Path]::ChangeExtension($Fonte.FullName, '.exe')

if ($Linguagem -eq 'c') {
    gcc -std=c11 -Wall -Wextra $Fonte.FullName -o $Executavel
} else {
    g++ -std=c++17 -Wall -Wextra $Fonte.FullName -o $Executavel
}
if ($LASTEXITCODE -ne 0) {
    throw 'A compilacao falhou. Leia a mensagem de erro acima.'
}

Write-Host "--- Executando $($Fonte.Name) ---"
& $Executavel
