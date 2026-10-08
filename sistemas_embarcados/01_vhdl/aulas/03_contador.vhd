-- Elaborado pelo Prof. Vagner Cordeiro
-- AULA 03 - Flip-flop D e contador (circuito com MEMORIA e CLOCK)
--
-- Ate agora o circuito era "combinacional": a saida depende so da entrada agora.
-- Circuito "sequencial" tem memoria: usa um CLOCK (relogio) para decidir QUANDO atualizar.
--
-- Flip-flop D: na subida do clock, guarda o valor de D.
-- Contador: soma 1 a cada subida do clock. reset zera.

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;   -- tipo "unsigned": numeros sem sinal

entity contador is
    port (
        clk   : in  std_logic;
        reset : in  std_logic;                       -- '1' zera
        q     : out unsigned(3 downto 0)             -- 4 bits: conta de 0 a 15
    );
end entity;

architecture simples of contador is
    signal valor : unsigned(3 downto 0) := (others => '0');
begin
    -- process com lista de sensibilidade (clk): roda quando clk muda
    process (clk)
    begin
        if rising_edge(clk) then            -- so na SUBIDA do clock
            if reset = '1' then
                valor <= (others => '0');
            else
                valor <= valor + 1;         -- 15 + 1 volta a 0 (estouro natural)
            end if;
        end if;
    end process;

    q <= valor;
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb is end entity;

architecture teste of tb is
    signal clk   : std_logic := '0';
    signal reset : std_logic := '1';
    signal q     : unsigned(3 downto 0);
begin
    dut : entity work.contador port map (clk => clk, reset => reset, q => q);

    -- Gerador de clock: periodo de 10 ns (inverte a cada 5 ns)
    clk <= not clk after 5 ns;

    process
    begin
        wait for 12 ns;
        reset <= '0';                       -- solta o reset
        for i in 1 to 18 loop
            wait until rising_edge(clk);
            wait for 1 ns;                  -- pequena folga para ler o novo valor
            report "clock " & integer'image(i) & " -> q = " & to_string(q)
                   & " (decimal " & integer'image(to_integer(q)) & ")";
        end loop;
        reset <= '1';
        wait until rising_edge(clk); wait for 1 ns;
        assert q = 0 report "ERRO: reset deveria zerar" severity error;
        report "Reset zerou o contador. Teste concluido.";
        wait;
    end process;
end architecture;

-- EXERCICIOS:
-- 1) Observe: depois de 15 vem 0. Por que? (4 bits so vao ate 15)
-- 2) Mude para 8 bits (unsigned(7 downto 0)) e conte ate 20.
-- 3) Faca o contador regressivo (valor - 1).
-- Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\sistemas_embarcados\01_vhdl\simular.ps1" 03_contador
