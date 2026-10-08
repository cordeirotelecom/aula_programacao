-- Elaborado pelo Prof. Vagner Cordeiro
-- AULA 07 - Registrador de deslocamento (shift register) de 8 bits
--
-- A cada pulso de clock com en='1', todos os bits andam uma casa:
--   dir='0' : desloca para a ESQUERDA, o bit "din" entra pela direita (carga serial)
--   dir='1' : desloca para a DIREITA,  o bit "din" entra pela esquerda
-- Carga serial = colocar um valor no registrador enviando 1 bit por clock.
--
-- Depois usamos o registrador para o efeito "carro fantastico":
-- um LED aceso que vai e volta pela fileira de 8 LEDs.

library ieee;
use ieee.std_logic_1164.all;

entity shreg is
    port (
        clk, reset, en, dir, din : in  std_logic;
        q : out std_logic_vector(7 downto 0)
    );
end entity;

architecture rtl of shreg is
    signal r : std_logic_vector(7 downto 0) := (others => '0');
begin
    process (clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                r <= (others => '0');
            elsif en = '1' then
                if dir = '0' then
                    r <= r(6 downto 0) & din;
                else
                    r <= din & r(7 downto 1);
                end if;
            end if;
        end if;
    end process;
    q <= r;
end architecture;

library ieee;
use ieee.std_logic_1164.all;

-- Carro fantastico: usa o shreg e inverte a direcao nas pontas
entity carro is
    port (
        clk, reset, go : in  std_logic;
        leds : out std_logic_vector(7 downto 0)
    );
end entity;

architecture rtl of carro is
    signal q   : std_logic_vector(7 downto 0);
    signal dir : std_logic := '0';
    signal din : std_logic := '0';
    signal en  : std_logic := '0';
    signal carregado : std_logic := '0';
    signal n : integer range 0 to 8 := 0;
begin
    -- carga serial inicial: entra um '1' e depois zeros; o '1' fica no LED 0
    process (clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                carregado <= '0';
                n <= 0;
                dir <= '0';
            elsif go = '1' and carregado = '0' then
                n <= n + 1;
                if n = 0 then
                    -- primeiro clock: o bit '1' entra
                    null;
                elsif n = 1 then
                    carregado <= '1';
                end if;
            elsif carregado = '1' then
                if q(6) = '1' and dir = '0' then
                    dir <= '1';
                elsif q(1) = '1' and dir = '1' then
                    dir <= '0';
                end if;
            end if;
        end if;
    end process;

    en  <= '1' when (go = '1' and carregado = '0' and n <= 1) or carregado = '1' else '0';
    din <= '1' when carregado = '0' and n = 0 else '0';

    u : entity work.shreg port map (clk, reset, en, dir, din, q);
    leds <= q;
end architecture;

library ieee;
use ieee.std_logic_1164.all;

entity tb is end entity;

architecture teste of tb is
    signal clk : std_logic := '0';
    signal reset : std_logic := '1';
    signal go : std_logic := '0';
    signal fim : boolean := false;
    signal leds : std_logic_vector(7 downto 0);
begin
    clk <= not clk after 5 ns when not fim else '0';
    dut : entity work.carro port map (clk, reset, go, leds);

    process
    begin
        wait for 12 ns;
        reset <= '0';
        go <= '1';
        wait until rising_edge(clk);
        for i in 1 to 24 loop
            wait until rising_edge(clk);
            wait for 1 ns;
            report "ciclo " & integer'image(i) & ":  LEDs = " & to_string(leds);
        end loop;
        report "Teste concluido.";
        fim <= true;
        wait;
    end process;
end architecture;

-- EXERCICIOS:
-- 1) Faca o efeito andar so para um lado (anel: o bit que sai volta pelo outro lado).
-- 2) Acenda 2 LEDs vizinhos em vez de 1.
-- 3) Use a entrada "en" para deixar o efeito mais lento (en a cada 4 clocks).
-- Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\sistemas_embarcados\01_vhdl\simular.ps1" 07_registrador_deslocamento
