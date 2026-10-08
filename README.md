<!-- Elaborado pelo Prof. Vagner Cordeiro -->
# Curso de programacao em C e C++ (Windows)

Aprenda C passo a passo, avance para conteudos intermediarios e aplicacoes praticas, depois pratique com sistemas embarcados, **Arduino** e **desenvolvimento web (HTML, CSS e JavaScript)**. O mesmo conteudo existe em **C** e em **C++**.

Todos os comandos abaixo sao para **Windows PowerShell**. Nao precisa abrir como administrador, editar o PATH na mao nem digitar seu nome de usuario: apenas **copie, cole e pressione Enter**.

## Baixar, executar e entender (inicio rapido)

| Passo | O que fazer |
|---|---|
| 1. Baixar | [**Baixar o curso (ZIP)**](https://github.com/cordeirotelecom/aula_programacao/archive/refs/heads/main.zip) e extrair (botao direito > Extrair tudo) |
| 2. Instalar | Duplo clique em `COMECE_AQUI.bat` (instala GCC e Node.js se faltarem e abre o curso) |
| 3. Abrir no VS Code | Duplo clique em `ABRIR_NO_VSCODE.bat` |
| 4. Executar | Abra um `.c`, `.cpp` ou `.html` e aperte **Ctrl+Shift+B** |

Pelo terminal, dentro da pasta do curso, um comando serve para tudo: `.\rodar.ps1 01_ola_mundo` (C/C++ compila e roda; `.html` abre no navegador e no VS Code).

Outros links: [Pagina do curso online](https://cordeirotelecom.github.io/aula_programacao/) | [Abrir no VS Code online](https://vscode.dev/github/cordeirotelecom/aula_programacao) | [Clonar no VS Code](vscode://vscode.git/clone?url=https://github.com/cordeirotelecom/aula_programacao.git)

Para clonar com Git: `git clone https://github.com/cordeirotelecom/aula_programacao.git`

## Portal visual do curso

Com o GCC (incluindo G++) e o Node.js instalados, de duplo clique em `abrir_laboratorio.bat`. O portal local reune os programas C/C++, as aulas HTML e os exemplos de Arduino, ESP32 e VHDL. Clique em **Executar** para compilar e rodar C ou C++; se o programa pedir dados, digite no terminal visual. O arquivo `.exe` fica junto do codigo-fonte. O portal tambem tem as abas **Teoria**, **Redes**, **Plataformas** (9 sites complementares do Prof. Vagner Cordeiro), **Referencias** (guia ABNT NBR 6023 com gerador) e **Como usar** (passo a passo e downloads).

Na aba **Projeto IoT**, **Iniciar simulacao** sobe o broker MQTT, a API, o ingestor e o simulador de sensores. O dashboard fica disponivel na propria pagina. Arduino e ESP32 podem ser consultados no portal, mas enviar codigo a uma placa requer a placa conectada e configuracao local da Arduino IDE/CLI. A simulacao VHDL requer GHDL.

Deixe a janela do terminal aberta enquanto usa o laboratorio. Para encerra-lo, volte a essa janela e pressione **Ctrl+C**. O servidor fica somente no computador local; nao abra a porta `47831` para a rede.

## Organizacao das pastas

```text
curso_programacao
|-- executar.ps1                  (compila e executa qualquer exemplo)
|-- abrir_laboratorio.bat         (abre o portal visual do curso)
|-- laboratorio                  (portal, servidor local e terminal de execucao)
|-- c                             (linguagem C)
|   |-- 01_fundamentos            (8 aulas: basico de C)
|   |-- 02_intermediario          (10 aulas: ponteiros, structs, arquivos...)
|   |-- 03_aplicacoes_praticas    (10 programas uteis)
|   `-- 04_sistemas_embarcados    (10 aulas + pasta exercicios)
|-- cpp                           (os mesmos temas em C++)
|   |-- 01_fundamentos
|   |-- 02_intermediario
|   |-- 03_aplicacoes_praticas
|   `-- 04_sistemas_embarcados
|-- arduino                       (15 exemplos .ino, cada um na sua pasta)
|-- web                           (HTML, CSS e JavaScript)
|   |-- abrir.ps1                 (abre qualquer aula no navegador)
|   |-- 01_html                   (8 aulas)
|   |-- 02_css                    (8 aulas)
|   |-- 03_javascript             (10 aulas)
|   `-- 04_projetos               (3 projetos completos)
|-- redes                         (redes de computadores)
|   |-- abrir.ps1                 (abre aula no navegador)
|   |-- 01_teoria                 (11 aulas em HTML)
|   |-- 02_calculos_em_c          (8 programas em C)
|   |-- 03_calculadora_web        (calculadora de redes)
|   `-- 04_exercicios             (exercicios com respostas)
|-- ux_design                     (conceitos, pratica, exercicios)
|-- mobile_iot                    (apps PWA para IoT)
|-- esp32                         (ESP32 e ESP32-S3)
|-- sistemas_embarcados           (simulacoes em C, VHDL, conceitos)
|-- integracao                    (ESP32 + MQTT + Node-RED + banco + app)
|-- index.html                    (pagina com botoes Professor e Aluno)
|-- instalar_professor.ps1        (baixa tudo e instala dependencias)
`-- preparar_aluno.ps1            (cria pastas e arquivos em branco para o aluno)
```

Siga a ordem das pastas numeradas. Cada aula termina com **EXERCICIOS** em comentario: edite o arquivo, salve e execute de novo. As pastas `arduino` e `web` sao independentes (veja as secoes Arduino e Web).

## 1. Instalar o GCC (compilador de C e C++)

Copie o bloco inteiro, cole no PowerShell e pressione Enter. Ele baixa a versao 64 bits mais recente do GCC WinLibs, instala na sua pasta de usuario e configura o PATH apenas para sua conta. Requer internet. O pacote inclui `gcc` (C) e `g++` (C++).

```powershell
$ErrorActionPreference = 'Stop'
$Release = Invoke-RestMethod `
    -Uri 'https://api.github.com/repos/brechtsanders/winlibs_mingw/releases/latest' `
    -Headers @{ 'User-Agent' = 'PowerShell-C-Setup' }
$Pacote = $Release.assets |
    Where-Object { $_.name -match '^winlibs-x86_64-posix-seh-.*\.zip$' } |
    Select-Object -First 1
if (-not $Pacote) { throw 'Nao encontrei o pacote 64 bits do GCC. Tente novamente mais tarde.' }

$PastaFerramentas = Join-Path $HOME 'tools'
$PastaGcc = Join-Path $PastaFerramentas "winlibs-$($Release.tag_name)"
$ArquivoZip = Join-Path $env:TEMP $Pacote.name
New-Item -ItemType Directory -Path $PastaFerramentas -Force | Out-Null
Write-Host "Baixando $($Pacote.name)..."
Invoke-WebRequest -Uri $Pacote.browser_download_url -OutFile $ArquivoZip
Write-Host 'Extraindo o compilador...'
Expand-Archive -Path $ArquivoZip -DestinationPath $PastaGcc -Force
Remove-Item $ArquivoZip

$GccExe = Get-ChildItem -Path $PastaGcc -Filter gcc.exe -Recurse |
    Select-Object -First 1
if (-not $GccExe) { throw "Nao encontrei gcc.exe dentro de $PastaGcc" }
$GccBin = $GccExe.DirectoryName

$EntradasPath = @(
    [Environment]::GetEnvironmentVariable('Path', 'User') -split ';' |
    Where-Object { $_ -and $_.TrimEnd('\') -ine $GccBin.TrimEnd('\') }
)
[Environment]::SetEnvironmentVariable(
    'Path',
    (($EntradasPath + $GccBin) -join ';'),
    'User'
)
$env:Path = "$GccBin;$env:Path"

Write-Host ''
Write-Host 'GCC instalado. Versao:'
gcc --version
```

## 2. Colocar a pasta do curso no lugar certo

Copie a pasta `curso_programacao` para dentro da pasta `programacao` em **Documentos**:

```text
Documentos\programacao\curso_programacao
```

Se a pasta `programacao` nao existir, crie-a. Nao precisa alterar nenhum comando: o PowerShell encontra a pasta Documentos da sua conta automaticamente.

## 3. Executar uma aula (de qualquer pasta)

Copie o bloco, cole no PowerShell e pressione Enter. Ele compila e executa a primeira aula em C:

```powershell
powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 01_ola_mundo
```

Para escolher outra aula, troque apenas o final do comando: a linguagem (`c` ou `cpp`) e o nome da aula (veja as tabelas abaixo). Exemplo em C++:

```powershell
powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 01_ola_mundo
```

O comando pode ser colado com o PowerShell aberto em qualquer pasta. Tambem aparece como comentario na **ultima linha** de cada arquivo `.c` e `.cpp`.

### Fundamentos (`01_fundamentos`)

| Nome da aula | Assunto |
|---|---|
| `01_ola_mundo` | Mostrar uma mensagem |
| `02_variaveis` | Variaveis e tipos |
| `03_operacoes` | Operacoes matematicas |
| `04_entrada_dados` | Ler um numero digitado |
| `05_decisoes` | `if` e `else` |
| `06_repeticoes` | Repeticao com `for` |
| `07_vetores` | Vetores |
| `08_funcoes` | Funcoes |

### Intermediario (`02_intermediario`)

| Aula em C | Aula em C++ | Assunto |
|---|---|---|
| `01_while_dowhile` | `01_while_dowhile` | `while` e `do-while` |
| `02_strings` | `02_strings` | Textos |
| `03_ponteiros` | `03_ponteiros_referencias` | Ponteiros (e referencias em C++) |
| `04_matrizes` | `04_array_vector` | Matrizes (e `array`/`vector` em C++) |
| `05_structs` | `05_structs` | Estruturas |
| `06_enum_typedef` | `06_enum_class` | `enum` e apelidos de tipo |
| `07_recursao` | `07_recursao` | Funcoes recursivas |
| `08_alocacao_dinamica` | `08_memoria_dinamica` | `malloc`/`free` (e `vector` em C++) |
| `09_arquivos` | `09_arquivos` | Ler e gravar arquivos |
| `10_macros_constantes` | `10_classes` | Macros e constantes (e classes em C++) |

### Aplicacoes praticas (`03_aplicacoes_praticas`)

Mesmos nomes em C e C++ (exceto `09`: em C `09_ordenacao_bolha`, em C++ `09_ordenacao`). Alguns programas pedem que voce digite algo: siga a mensagem na tela.

| Nome | Programa |
|---|---|
| `01_calculadora` | Calculadora (digite, por exemplo, `8 * 3`) |
| `02_media_notas` | Media de 4 notas e aprovacao |
| `03_conversor_temperatura` | Celsius para Fahrenheit e Kelvin |
| `04_tabuada` | Tabuada de um numero |
| `05_numeros_primos` | Primos ate um limite |
| `06_fibonacci` | Sequencia de Fibonacci |
| `07_cadastro_alunos` | Cadastro com estruturas |
| `08_jogo_adivinhacao` | Jogo de adivinhar o numero |
| `09_ordenacao_bolha` / `09_ordenacao` | Ordenar numeros |
| `10_contar_vogais` | Contar vogais de uma frase |

### Sistemas embarcados (`04_sistemas_embarcados`)

Os programas simulam o hardware na tela; nao precisa de placa.

| Nome da aula | Assunto |
|---|---|
| `01_led_blink` | Saida digital: piscar LED |
| `02_entrada_digital` | Entrada digital: botao |
| `03_alarme_temperatura` | Sensor de temperatura |
| `04_leitura_adc` | Conversor analogico-digital |
| `05_pwm_led` | PWM: brilho do LED |
| `06_comunicacao_uart` | Comunicacao serial |
| `07_temporizador` | Temporizador |
| `08_maquina_estados` | Estados com `switch` |
| `09_leituras_sensor` | Vetor de leituras e media |
| `10_operacoes_bits` | Bits de um registrador |

### Exercicios praticos de embarcados (pasta `exercicios`)

Cada arquivo traz um problema e trechos marcados com `TODO` para voce completar. Abra o arquivo, complete, salve e execute com o mesmo comando.

| Nome do exercicio | Desafio |
|---|---|
| `ex_01_led_sos` | Piscar o codigo SOS |
| `ex_02_botao_contador` | Contar cliques de um botao |
| `ex_03_ventilador` | Controlar ventilador pela temperatura |
| `ex_04_bateria` | Calcular o nivel da bateria com ADC |
| `ex_05_pwm_rampa` | Rampa de brilho com PWM |

## 4. Arduino (pasta `arduino`)

Os exemplos Arduino usam a linguagem C/C++ do Arduino e **nao** usam o `executar.ps1`. Escolha uma das duas formas:

**A) Sem placa, direto no navegador (mais facil):** abra https://wokwi.com, crie um projeto **Arduino Uno**, cole o conteudo do arquivo `.ino` e clique em Play. Adicione os componentes citados nos comentarios do exemplo.

**B) Com placa Arduino:** instale o Arduino IDE colando este comando no PowerShell (se o `winget` nao existir, baixe em https://www.arduino.cc/en/software):

```powershell
winget install --id ArduinoSA.IDE.stable -e
```

Depois abra o Arduino IDE, use **Arquivo > Abrir** e escolha um arquivo `.ino`, selecione a placa (**Ferramentas > Placa > Arduino Uno**) e a porta COM, e clique em **Carregar**. O Monitor Serial usa **9600 baud**.

Abra sempre o `.ino` dentro da propria pasta (o nome da pasta precisa ser igual ao do arquivo).

| Pasta | Assunto |
|---|---|
| `01_blink_led` | Piscar o LED da placa |
| `02_botao_led` | Botao liga o LED |
| `03_semaforo` | Semaforo com 3 LEDs |
| `04_pwm_fade` | Brilho suave com PWM |
| `05_potenciometro` | Potenciometro controla o brilho |
| `06_serial_monitor` | Comandos pelo Monitor Serial |
| `07_sensor_ldr` | Sensor de luz |
| `08_sensor_temperatura_lm35` | Termometro LM35 |
| `09_buzzer_melodia` | Melodia com buzzer |
| `10_ultrassonico_hcsr04` | Medir distancia |
| `11_servo_motor` | Servo motor |
| `12_millis_sem_delay` | Tarefas sem `delay()` |
| `13_interrupcao_botao` | Interrupcoes |
| `14_eeprom_contador` | Memoria EEPROM |
| `15_projeto_alarme` | Projeto final: alarme de presenca |

## 5. Web: HTML, CSS e JavaScript (pasta `web`)

Nao precisa instalar nada: basta ter um navegador (Edge, Chrome ou Firefox). Cada aula e um arquivo `.html` que abre no navegador. Para **editar**, abra o arquivo no Bloco de Notas, salve (Ctrl+S) e atualize o navegador (F5).

Para abrir uma aula, cole no PowerShell (troque o nome no final do comando):

```powershell
powershell -ExecutionPolicy Bypass -File ".\web\abrir.ps1" 01_primeira_pagina
```

O comando tambem aparece como comentario na **ultima linha** de cada arquivo. Nas aulas de JavaScript, aperte **F12** para ver o console do navegador.

Siga a ordem: HTML (estrutura), CSS (visual), JavaScript (comportamento) e, por fim, os projetos.

| Pasta | Nome da aula | Assunto |
|---|---|---|
| `01_html` | `01_primeira_pagina` | Estrutura basica |
| `01_html` | `02_textos_titulos` | Titulos e textos |
| `01_html` | `03_links_imagens` | Links e imagens |
| `01_html` | `04_listas` | Listas |
| `01_html` | `05_tabelas` | Tabelas |
| `01_html` | `06_formularios` | Formularios |
| `01_html` | `07_semantica` | Tags semanticas |
| `01_html` | `08_pagina_completa` | Pagina completa |
| `02_css` | `01_cores_fontes` | Cores e fontes |
| `02_css` | `02_seletores` | Seletores |
| `02_css` | `03_caixa_margens` | Caixa, margens e bordas |
| `02_css` | `04_display_posicao` | `display` e `position` |
| `02_css` | `05_flexbox` | Flexbox |
| `02_css` | `06_grid` | Grid |
| `02_css` | `07_responsivo` | Design responsivo |
| `02_css` | `08_animacoes` | Transicoes e animacoes |
| `03_javascript` | `01_variaveis` | Variaveis e tipos |
| `03_javascript` | `02_operadores_condicoes` | Operadores e `if` |
| `03_javascript` | `03_repeticoes` | `for` e `while` |
| `03_javascript` | `04_funcoes` | Funcoes |
| `03_javascript` | `05_arrays_objetos` | Arrays e objetos |
| `03_javascript` | `06_dom` | Alterar a pagina (DOM) |
| `03_javascript` | `07_eventos` | Eventos |
| `03_javascript` | `08_formulario_validacao` | Validar formularios |
| `03_javascript` | `09_temporizador` | `setInterval` e `setTimeout` |
| `03_javascript` | `10_localstorage` | Guardar dados no navegador |
| `04_projetos` | `lista_tarefas` | Projeto: lista de tarefas |
| `04_projetos` | `calculadora_web` | Projeto: calculadora |
| `04_projetos` | `relogio_digital` | Projeto: relogio digital |

Os projetos tem tres arquivos (`index.html`, `estilo.css`, `script.js`): abra-os no Bloco de Notas para estudar e editar.

## 6. Redes de computadores (pasta `redes`)

Ensina IP, mascara, CIDR, rede, broadcast, faixa de hosts, classes, sub-redes e VLSM. **Comece pela aula `00_para_que_serve`** e depois `10_passo_a_passo_calculo` (metodo no papel).

**Aulas e exercicios (abrem no navegador)** - copie e cole (troque o nome final):

```powershell
powershell -ExecutionPolicy Bypass -File ".\redes\abrir.ps1" 00_para_que_serve
```

| Nome para abrir | Assunto |
|---|---|
| `00_para_que_serve` | Para que serve IP, mascara, classe, faixa |
| `01_modelo_osi_tcpip` | Camadas OSI e TCP/IP |
| `02_binario_decimal` | Binario e decimal (conversor) |
| `03_enderecos_ip` | Classes, privados, loopback |
| `04_mascara_cidr` | Mascara e CIDR |
| `05_rede_broadcast` | Rede e broadcast (interativo) |
| `06_subredes` | Sub-redes |
| `07_vlsm` | VLSM |
| `08_portas_protocolos` | Portas, TCP e UDP |
| `09_comandos_windows` | ipconfig, ping, tracert... |
| `10_passo_a_passo_calculo` | Calculo no papel + explicador |
| `calculadora_web` | Calculadora de redes |
| `exercicios_sub_redes` | 10 exercicios com respostas |

**Programas em C** (usam o mesmo `executar.ps1`; digite o IP quando o programa pedir, ex.: `192.168.10.77/26`):

```powershell
powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c rede_08_passo_a_passo
```

| Nome | O que faz |
|---|---|
| `rede_01_ip_binario` | IP em binario |
| `rede_02_mascara_cidr` | Mascara, wildcard e hosts de um CIDR |
| `rede_03_rede_broadcast` | Rede e broadcast com AND/OR binario |
| `rede_04_faixa_hosts` | Faixa de hosts e quantidade |
| `rede_05_mesma_rede` | Duas maquinas na mesma rede? |
| `rede_06_dividir_sub_redes` | Divide em sub-redes |
| `rede_07_classe_tipo_ip` | Classe e tipo (privado/publico) |
| `rede_08_passo_a_passo` | Calculo narrado passo a passo |

## 7. Instalacao rapida (Professor e Aluno)

Pagina com os dois botoes: **https://cordeirotelecom.github.io/aula_programacao/**

**Professor** (baixa tudo e instala GCC, Node.js e bibliotecas):

```powershell
irm https://raw.githubusercontent.com/cordeirotelecom/aula_programacao/main/instalar_professor.ps1 | iex
```

**Aluno** (instala ferramentas e cria pastas/arquivos em branco em `Documentos\programacao\aluno`, sem baixar o conteudo pronto):

```powershell
irm https://raw.githubusercontent.com/cordeirotelecom/aula_programacao/main/preparar_aluno.ps1 | iex
```

## 8. Outras pastas do curso

Todas tem um `abrir.ps1` (aulas HTML) e cada aula traz no final o comando para abri-la. Comece pelas paginas indicadas:

| Pasta | O que ensina | Comece por |
|---|---|---|
| `ux_design` | Conceitos e boas praticas de UX/design | `01_conceitos` |
| `mobile_iot` | Apps PWA para IoT, servidor local, firmware ESP32 | `01_conceitos` |
| `esp32` | ESP32 e ESP32-S3: diferencas, 13 exemplos, 4 projetos | `01_conceitos\06_escolhedor.html` |
| `sistemas_embarcados` | Simulacoes em C, VHDL (simulado com GHDL), conceitos | `03_conceitos` |
| `integracao` | ESP32 + MQTT + Node-RED + SQLite + app, tudo copiar e colar | `03_passo_a_passo\01_passo_a_passo_completo.html` |

Abrir o passo a passo da integracao:

```powershell
powershell -ExecutionPolicy Bypass -File ".\integracao\abrir.ps1" 01_passo_a_passo_completo
```

Simular uma aula de VHDL:

```powershell
powershell -ExecutionPolicy Bypass -File ".\sistemas_embarcados\01_vhdl\simular.ps1" 01_porta_and
```

Observacao: `c\04_sistemas_embarcados` e `cpp\04_sistemas_embarcados` ensinam a *linguagem* C/C++ aplicada a hardware; a pasta `sistemas_embarcados` na raiz ensina os *conceitos*, a simulacao e o VHDL.

## Se algo der errado

- **`gcc` nao e reconhecido:** feche o PowerShell, abra uma janela nova e repita o passo 3. O passo 1 adiciona o GCC ao PATH da sua conta.
- **Nao encontrei o arquivo:** confira o nome da aula e se a pasta esta em `Documentos\programacao\curso_programacao`.
- **O download falhou:** confira a conexao com a internet e repita o passo 1.

O GCC fica em `tools` dentro da sua pasta de usuario. A configuracao nao altera o PATH do sistema nem precisa de permissao de administrador. Como o PATH e individual, cada conta Windows deve executar o passo 1 na propria conta.
