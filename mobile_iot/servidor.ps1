# Elaborado pelo Prof. Vagner Cordeiro
# Servidor web simples (sem instalar nada, sem administrador).
# Serve a pasta mobile_iot para voce testar no PC e no celular (mesmo Wi-Fi).
# Uso: servidor.ps1            (porta 8080)   |   servidor.ps1 -Porta 9000
param([int]$Porta = 8080)

$raiz = $PSScriptRoot
$tipos = @{
    '.html' = 'text/html; charset=utf-8'; '.css' = 'text/css; charset=utf-8'
    '.js' = 'text/javascript; charset=utf-8'; '.json' = 'application/json; charset=utf-8'
    '.svg' = 'image/svg+xml'; '.png' = 'image/png'; '.ico' = 'image/x-icon'
}

$servidor = New-Object System.Net.Sockets.TcpListener([System.Net.IPAddress]::Any, $Porta)
try { $servidor.Start() } catch { Write-Host "Nao consegui usar a porta $Porta. Tente: servidor.ps1 -Porta 9000" -ForegroundColor Red; exit 1 }

Write-Host "Servidor ligado. Pare com Ctrl+C." -ForegroundColor Green
Write-Host "No PC:      http://localhost:$Porta/"
Get-NetIPAddress -AddressFamily IPv4 -ErrorAction SilentlyContinue |
    Where-Object { $_.IPAddress -notlike '127.*' -and $_.IPAddress -notlike '169.254.*' } |
    ForEach-Object { Write-Host "No celular: http://$($_.IPAddress):$Porta/" }
Write-Host "Exemplo:    http://localhost:$Porta/03_projetos/painel_sensores/index.html"

try {
    while ($true) {
        $cliente = $servidor.AcceptTcpClient()
        try {
            $fluxo = $cliente.GetStream()
            $leitor = New-Object System.IO.StreamReader($fluxo)
            $linha = $leitor.ReadLine()
            while ($true) { $h = $leitor.ReadLine(); if ([string]::IsNullOrEmpty($h)) { break } }

            $caminho = '/'
            if ($linha -match '^GET\s+(\S+)') { $caminho = [Uri]::UnescapeDataString(($Matches[1] -split '\?')[0]) }
            if ($caminho.EndsWith('/')) { $caminho += 'index.html' }

            $arquivo = [System.IO.Path]::GetFullPath((Join-Path $raiz ($caminho.TrimStart('/') -replace '/', '\')))
            if ($arquivo.StartsWith($raiz) -and (Test-Path -LiteralPath $arquivo -PathType Leaf)) {
                $corpo = [System.IO.File]::ReadAllBytes($arquivo)
                $tipo = $tipos[[System.IO.Path]::GetExtension($arquivo).ToLower()]
                if (-not $tipo) { $tipo = 'application/octet-stream' }
                $status = '200 OK'
            } else {
                $corpo = [System.Text.Encoding]::UTF8.GetBytes('404 - nao encontrado')
                $tipo = 'text/plain; charset=utf-8'; $status = '404 Not Found'
            }
            $cab = "HTTP/1.1 $status`r`nContent-Type: $tipo`r`nContent-Length: $($corpo.Length)`r`nCache-Control: no-cache`r`nConnection: close`r`n`r`n"
            $bytes = [System.Text.Encoding]::ASCII.GetBytes($cab)
            $fluxo.Write($bytes, 0, $bytes.Length)
            $fluxo.Write($corpo, 0, $corpo.Length)
            Write-Host "$status $caminho"
        } catch { } finally { $cliente.Close() }
    }
} finally { $servidor.Stop() }
