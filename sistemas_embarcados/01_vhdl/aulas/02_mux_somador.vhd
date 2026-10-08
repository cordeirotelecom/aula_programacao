-- Elaborado pelo Prof. Vagner Cordeiro
-- AULA 02 - Multiplexador (MUX) 2 para 1 e somador
--
-- MUX = chave seletora: uma entrada "sel" escolhe qual dado passa.
-- Somador completo = soma 3 bits (a, b e o "vai um" que veio de antes).

library ieee;
use ieee.std_logic_1164.all;

entity mux_somador is
    port (
        a, b, sel : in  std_logic;
        saida_mux : out std_logic;   -- sel='0' -> a ; sel='1' -> b
        cin       : in  std_logic;   -- "vem um"
        soma      : out std_logic;
        cout      : out std_logic    -- "vai um"
    );
end entity;

architecture simples of mux_somador is
begin
    -- "when ... else" cria um seletor (um mux) no hardware
    saida_mux <= b when sel = '1' else a;

    -- Soma binaria: 1+1 = 10 (soma 0, vai um 1)
    soma <= a xor b xor cin;
    cout <= (a and b) or (cin and (a xor b));
end architecture;

library ieee;
use ieee.std_logic_1164.all;

entity tb is end entity;

architecture teste of tb is
    signal a, b, sel, cin : std_logic := '0';
    signal saida_mux, soma, cout : std_logic;
begin
    dut : entity work.mux_somador
        port map (a => a, b => b, sel => sel, saida_mux => saida_mux,
                  cin => cin, soma => soma, cout => cout);

    process
        variable v : std_logic_vector(2 downto 0);
    begin
        report "--- MUX: a='1', b='0' ---";
        a <= '1'; b <= '0';
        sel <= '0'; wait for 10 ns;
        report "sel=0 -> saida=" & to_string(saida_mux) & "  (esperado 1, vem de a)";
        sel <= '1'; wait for 10 ns;
        report "sel=1 -> saida=" & to_string(saida_mux) & "  (esperado 0, vem de b)";

        report "--- SOMADOR COMPLETO: a + b + cin ---";
        for i in 0 to 7 loop
            -- converte i em 3 bits para testar todas as combinacoes
            a   <= '1' when (i / 4) mod 2 = 1 else '0';
            b   <= '1' when (i / 2) mod 2 = 1 else '0';
            cin <= '1' when i mod 2 = 1 else '0';
            wait for 10 ns;
            report to_string(a) & " + " & to_string(b) & " + " & to_string(cin)
                   & " = vai " & to_string(cout) & " soma " & to_string(soma);
        end loop;

        a <= '1'; b <= '1'; cin <= '1'; wait for 10 ns;
        assert soma = '1' and cout = '1' report "ERRO: 1+1+1 deveria dar 11" severity error;
        report "Teste concluido.";
        wait;
    end process;
end architecture;

-- EXERCICIOS:
-- 1) Faca um MUX 4 para 1 (sel com 2 bits, tipo std_logic_vector(1 downto 0)).
-- 2) Ligue dois somadores completos para somar numeros de 2 bits.
-- Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\sistemas_embarcados\01_vhdl\simular.ps1" 02_mux_somador
