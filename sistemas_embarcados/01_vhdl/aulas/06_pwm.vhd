-- Elaborado pelo Prof. Vagner Cordeiro
-- AULA 06 - PWM (controle de brilho de LED / velocidade de motor)
--
-- PWM = liga e desliga muito rapido. Quanto mais tempo ligado ("duty cycle"),
-- mais brilho. O contador vai de 0 a 9; a saida fica '1' enquanto contador < duty.
--   duty=0 -> sempre apagado | duty=5 -> 50% | duty=10 -> sempre aceso
-- Mesma ideia do analogWrite() do Arduino, mas feita em hardware.

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity pwm is
    port (
        clk  : in  std_logic;
        duty : in  unsigned(3 downto 0);   -- 0 a 10
        saida : out std_logic
    );
end entity;

architecture simples of pwm is
    signal cont : unsigned(3 downto 0) := (others => '0');
begin
    process (clk)
    begin
        if rising_edge(clk) then
            if cont = 9 then cont <= (others => '0');
            else cont <= cont + 1;
            end if;
        end if;
    end process;

    saida <= '1' when cont < duty else '0';
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb is end entity;

architecture teste of tb is
    signal clk : std_logic := '0';
    signal duty : unsigned(3 downto 0) := to_unsigned(0, 4);
    signal saida : std_logic;
begin
    dut : entity work.pwm port map (clk, duty, saida);
    clk <= not clk after 5 ns;

    process
        variable ligados : integer;
        variable linha : string(1 to 10);
    begin
        for d in 0 to 10 loop
            duty <= to_unsigned(d, 4);
            wait until rising_edge(clk);       -- deixa o novo duty valer
            ligados := 0;
            for i in 1 to 10 loop              -- observa um periodo completo (10 ciclos)
                wait until rising_edge(clk);
                wait for 1 ns;
                if saida = '1' then
                    ligados := ligados + 1;
                    linha(i) := '#';           -- # = LED ligado
                else
                    linha(i) := '.';           -- . = LED desligado
                end if;
            end loop;
            report "duty=" & integer'image(d) & "  " & linha & "  ligado " & integer'image(ligados * 10) & "%";
            assert ligados = d report "ERRO: percentual incorreto" severity error;
        end loop;
        report "Teste concluido.";
        wait;
    end process;
end architecture;

-- EXERCICIOS:
-- 1) Faca o duty subir e descer sozinho (efeito "respirando").
-- 2) Aumente a resolucao para 0..99 (contador maior).
-- Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\sistemas_embarcados\01_vhdl\simular.ps1" 06_pwm
