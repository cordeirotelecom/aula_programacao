-- Elaborado pelo Prof. Vagner Cordeiro
-- AULA 01 - Primeiro circuito: portas logicas
--
-- VHDL NAO e um programa que executa linha por linha.
-- Ele DESCREVE um circuito (hardware). Todas as partes funcionam ao mesmo tempo.
--
-- Todo projeto VHDL tem 2 partes:
--   ENTITY       = a "caixa preta": quais sao as entradas e saidas (os pinos)
--   ARCHITECTURE = o que tem DENTRO da caixa
--
-- Depois escrevemos um TESTBENCH (entidade "tb"): um circuito falso que
-- aplica valores nas entradas e confere as saidas. Assim simulamos sem placa.

library ieee;
use ieee.std_logic_1164.all;   -- tipo std_logic: '0', '1', 'Z', 'U'...

-- ---------- 1) A CAIXA PRETA ----------
entity portas is
    port (
        a, b   : in  std_logic;   -- duas entradas
        e_and  : out std_logic;   -- saida: a AND b
        e_or   : out std_logic;   -- saida: a OR b
        e_xor  : out std_logic;   -- saida: a XOR b
        nao_a  : out std_logic    -- saida: NOT a
    );
end entity;

-- ---------- 2) O QUE TEM DENTRO ----------
architecture simples of portas is
begin
    -- "<=" liga um fio a uma expressao. Nao e atribuicao de variavel:
    -- e uma conexao permanente (como soldar fios).
    e_and <= a and b;
    e_or  <= a or  b;
    e_xor <= a xor b;
    nao_a <= not a;
end architecture;

-- ---------- 3) TESTBENCH ----------
library ieee;
use ieee.std_logic_1164.all;

entity tb is end entity;   -- sem pinos: e so um laboratorio virtual

architecture teste of tb is
    signal a, b : std_logic := '0';
    signal e_and, e_or, e_xor, nao_a : std_logic;
begin
    -- Liga o circuito ao laboratorio
    dut : entity work.portas
        port map (a => a, b => b, e_and => e_and, e_or => e_or, e_xor => e_xor, nao_a => nao_a);

    -- Processo: roteiro de teste (aqui sim, linha por linha)
    estimulo : process
    begin
        report "  a b | AND OR XOR | NOT a";
        for i in 0 to 3 loop
            a <= '1' when (i / 2) = 1 else '0';   -- i=0..3 gera 00,01,10,11
            b <= '1' when (i mod 2) = 1 else '0';
            wait for 10 ns;                       -- espera o circuito reagir
            report "  " & to_string(a) & " " & to_string(b) & " |  " & to_string(e_and)
                   & "   " & to_string(e_or) & "   " & to_string(e_xor) & "  |   " & to_string(nao_a);
        end loop;

        -- assert: se a condicao for falsa, mostra erro (teste automatico)
        a <= '1'; b <= '1'; wait for 10 ns;
        assert e_and = '1' report "ERRO: 1 AND 1 deveria ser 1" severity error;
        report "Teste concluido.";
        wait;   -- para a simulacao
    end process;
end architecture;

-- EXERCICIOS:
-- 1) Acrescente uma saida e_nand (a nand b) e confira a tabela.
-- 2) Acrescente e_nor. O que acontece com a e 'a' = '1'?
-- 3) Troque o assert para 0 AND 1 e veja como o erro aparece (mude o esperado).
-- Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\sistemas_embarcados\01_vhdl\simular.ps1" 01_porta_and
