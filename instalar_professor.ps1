# Elaborado pelo Prof. Vagner Cordeiro
# INSTALADOR DO PROFESSOR: baixa o curso completo do GitHub e instala as dependencias.
# Nao precisa de administrador. Pode ser executado quantas vezes quiser (atualiza tudo).
$ErrorActionPreference = 'Stop'
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
$ProgressPreference = 'SilentlyContinue'

$Repo    = 'cordeirotelecom/aula_programacao'
$Docs    = [Environment]::GetFolderPath('MyDocuments')
$Base    = Join-Path $Docs 'programacao'
$Destino = Join-Path $Base 'curso_programacao'
$Tools   = Join-Path $HOME 'tools'

function AdicionarAoPath($pasta) {
    $atual = @([Environment]::GetEnvironmentVariable('Path', 'User') -split ';' | Where-Object { $_ -and $_.TrimEnd('\') -ine $pasta.TrimEnd('\') })
    [Environment]::SetEnvironmentVariable('Path', (($atual + $pasta) -join ';'), 'User')
    $env:Path = "$pasta;$env:Path"
}

New-Item -ItemType Directory -Path $Base, $Tools -Force | Out-Null
New-Item -ItemType Directory -Path $Destino -Force | Out-Null
$local = $PSScriptRoot -and (Test-Path (Join-Path $PSScriptRoot 'executar.ps1'))
if ($local) {
    Write-Host '== 1/4 Copiando o curso (a partir do ZIP, sem internet) ==' -ForegroundColor Cyan
    if ((Resolve-Path $PSScriptRoot).Path.TrimEnd('\') -ine (Resolve-Path $Destino).Path.TrimEnd('\')) {
        Copy-Item -Path (Join-Path $PSScriptRoot '*') -Destination $Destino -Recurse -Force
    }
} else {
    Write-Host '== 1/4 Baixando o curso do GitHub ==' -ForegroundColor Cyan
    $zip = Join-Path $env:TEMP 'curso.zip'
    $tmp = Join-Path $env:TEMP 'curso_extraido'
    Invoke-WebRequest -Uri "https://github.com/$Repo/archive/refs/heads/main.zip" -OutFile $zip
    if (Test-Path $tmp) { Remove-Item $tmp -Recurse -Force }
    Expand-Archive -Path $zip -DestinationPath $tmp -Force
    $origem = Get-ChildItem $tmp -Directory | Select-Object -First 1
    Copy-Item -Path (Join-Path $origem.FullName '*') -Destination $Destino -Recurse -Force
    Remove-Item $zip, $tmp -Recurse -Force
}
Write-Host "Curso em: $Destino"

Write-Host '== 2/4 Compilador GCC (C e C++) ==' -ForegroundColor Cyan
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

Write-Host '== 3/4 Node.js (web, mobile e integracao) ==' -ForegroundColor Cyan
if (Get-Command node -ErrorAction SilentlyContinue) {
    Write-Host 'Node.js ja instalado.'
} else {
    $lts = (Invoke-RestMethod -Uri 'https://nodejs.org/dist/index.json' | Where-Object { $_.lts -and $_.version -like 'v22.*' } | Select-Object -First 1).version
    if (-not $lts) { throw 'Nao encontrei a versao do Node.js.' }
    $arq = Join-Path $env:TEMP "node-$lts.zip"
    Invoke-WebRequest -Uri "https://nodejs.org/dist/$lts/node-$lts-win-x64.zip" -OutFile $arq
    Expand-Archive -Path $arq -DestinationPath $Tools -Force
    Remove-Item $arq
    AdicionarAoPath (Join-Path $Tools "node-$lts-win-x64")
}

Write-Host '== 4/4 Bibliotecas do projeto de integracao (npm install) ==' -ForegroundColor Cyan
Push-Location (Join-Path $Destino 'integracao\02_projeto')
npm install
Pop-Location

Write-Host ''
Write-Host '== Python ==' -ForegroundColor Cyan
if ((Get-Command python -ErrorAction SilentlyContinue) -or (Get-Command py -ErrorAction SilentlyContinue)) {
    Write-Host 'Python ja instalado.'
} elseif (Get-Command winget -ErrorAction SilentlyContinue) {
    winget install --id Python.Python.3.12 -e --silent --accept-package-agreements --accept-source-agreements
} else {
    Write-Host 'Instale o Python em https://www.python.org/downloads (marque "Add python.exe to PATH").' -ForegroundColor Yellow
}

Write-Host ''
Write-Host 'PRONTO! Feche e abra o PowerShell e execute o primeiro programa:' -ForegroundColor Green
Write-Host 'cd "$([Environment]::GetFolderPath(''MyDocuments''))\programacao\curso_programacao"; .\rodar.ps1 01_ola_mundo'
Write-Host 'Para o VHDL, o simulador GHDL e baixado sozinho no primeiro uso.'
Write-Host 'Para Arduino/ESP32, instale a Arduino IDE: https://www.arduino.cc/en/software'
# Executar: irm https://raw.githubusercontent.com/cordeirotelecom/aula_programacao/main/instalar_professor.ps1 | iex
