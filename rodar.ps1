# Elaborado pelo Prof. Vagner Cordeiro
# Comando unico do curso: roda ou abre QUALQUER arquivo, so pelo nome ou pelo caminho.
#   .c / .cpp  -> compila e executa
#   .py        -> executa com Python
#   .html      -> abre no navegador E no VS Code
#   outros     -> abre no VS Code
# Uso: rodar.ps1 01_ola_mundo | rodar.ps1 03_enderecos_ip | rodar.ps1 "C:\caminho\arquivo.c"
param([Parameter(Mandatory = $true, Position = 0)][string]$Alvo)

$Raiz = $PSScriptRoot
$Ignorar = '\\(node_modules|\.git|\.vscode)\\'

if (Test-Path -LiteralPath $Alvo -PathType Leaf) {
    $Arquivo = Get-Item -LiteralPath $Alvo
} else {
    $nome = [IO.Path]::GetFileNameWithoutExtension($Alvo)
    $ext = [IO.Path]::GetExtension($Alvo)
    $achados = Get-ChildItem -Path $Raiz -Recurse -File |
        Where-Object { $_.FullName -notmatch $Ignorar -and $_.BaseName -eq $nome -and $_.Extension -ne '.exe' -and (-not $ext -or $_.Extension -eq $ext) }
    $ordem = '.c', '.cpp', '.py', '.html', '.ino', '.vhd'
    $Arquivo = $achados | Sort-Object { $i = $ordem.IndexOf($_.Extension.ToLower()); if ($i -lt 0) { 99 } else { $i } } | Select-Object -First 1
    if (-not $Arquivo) {
        Write-Host "Nao encontrei '$Alvo' dentro de $Raiz" -ForegroundColor Red
        exit 1
    }
}

function AbrirNoVSCode($caminho) {
    $code = Get-Command code -ErrorAction SilentlyContinue
    if (-not $code) {
        $local = Join-Path $env:LOCALAPPDATA 'Programs\Microsoft VS Code\bin\code.cmd'
        if (Test-Path $local) { $code = $local }
    }
    if ($code) { & $code --reuse-window $caminho } else { Write-Host 'VS Code nao encontrado.' -ForegroundColor Yellow }
}

function AcharCompilador($exe) {
    if (Get-Command $exe -ErrorAction SilentlyContinue) { return }
    $tools = Join-Path $HOME 'tools'
    $bin = Get-ChildItem -Path $tools -Recurse -Filter "$exe.exe" -ErrorAction SilentlyContinue | Select-Object -First 1
    if ($bin) { $env:Path = "$($bin.DirectoryName);$env:Path" }
    if (-not (Get-Command $exe -ErrorAction SilentlyContinue)) {
        Write-Host "$exe nao encontrado. De duplo clique em COMECE_AQUI.bat para instalar." -ForegroundColor Red
        exit 1
    }
}

Write-Host "Arquivo: $($Arquivo.FullName)"
switch ($Arquivo.Extension.ToLower()) {
    { $_ -in '.c', '.cpp' } {
        $comp = if ($_ -eq '.c') { 'gcc' } else { 'g++' }
        $padrao = if ($_ -eq '.c') { '-std=c11' } else { '-std=c++17' }
        AcharCompilador $comp
        $saida = [IO.Path]::ChangeExtension($Arquivo.FullName, '.exe')
        & $comp $padrao -Wall -Wextra $Arquivo.FullName -o $saida
        if ($LASTEXITCODE -ne 0) { Write-Host 'A compilacao falhou. Leia a mensagem acima.' -ForegroundColor Red; exit 1 }
        Write-Host "--- Executando $($Arquivo.Name) ---"
        & $saida
    }
    '.py' {
        $py = Get-Command python -ErrorAction SilentlyContinue
        if (-not $py) { $py = Get-Command py -ErrorAction SilentlyContinue }
        if (-not $py) {
            Write-Host 'Python nao encontrado. De duplo clique em COMECE_AQUI.bat ou instale em https://www.python.org/downloads' -ForegroundColor Red
            exit 1
        }
        Write-Host "--- Executando $($Arquivo.Name) ---"
        & $py.Source $Arquivo.FullName
    }
    '.html' {
        Start-Process $Arquivo.FullName
        AbrirNoVSCode $Arquivo.FullName
    }
    default { AbrirNoVSCode $Arquivo.FullName }
}
