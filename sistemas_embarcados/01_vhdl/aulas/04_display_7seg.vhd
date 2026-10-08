-- Elaborado pelo Prof. Vagner Cordeiro
-- AULA 04 - Decodificador de display de 7 segmentos
--
-- Display de 7 segmentos: 7 LEDs (a,b,c,d,e,f,g) formam os numeros.
--      aaa
--     f   b
--      ggg
--     e   c
--      ddd
-- Esta tabela converte um numero de 4 bits (0-9) nos 7 segmentos acesos ('1' = aceso).

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity decod7 is
    port (
        num : in  unsigned(3 downto 0);
        seg : out std_logic_vector(6 downto 0)   -- ordem: a b c d e f g
    );
end entity;

architecture tabela of decod7 is
begin
    -- "with ... select" = tabela verdade
    with to_integer(num) select
        seg <= "1111110" when 0,
               "0110000" when 1,
               "1101101" when 2,
               "1111001" when 3,
               "0110011" when 4,
               "1011011" when 5,
               "1011111" when 6,
               "1110000" when 7,
               "1111111" when 8,
               "1111011" when 9,
               "0000001" when others;   -- tracinho '-' para valores invalidos
end architecture;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb is end entity;

architecture teste of tb is
    signal num : unsigned(3 downto 0) := (others => '0');
    signal seg : std_logic_vector(6 downto 0);
begin
    dut : entity work.decod7 port map (num => num, seg => seg);

    process
    begin
        report "num | a b c d e f g";
        for i in 0 to 10 loop
            num <= to_unsigned(i, 4);
            wait for 10 ns;
            report integer'image(i) & "   | " & to_string(seg);
        end loop;
        assert seg = "0000001" report "ERRO: 10 deve mostrar tracinho" severity error;
        num <= to_unsigned(8, 4); wait for 10 ns;
        assert seg = "1111111" report "ERRO: 8 acende tudo" severity error;
        report "Teste concluido.";
        wait;
    end process;
end architecture;

-- EXERCICIOS:
-- 1) Acrescente as letras A-F (hexadecimal) para os valores 10 a 15.
-- 2) Para display de anodo comum, inverta os bits (not seg).
-- Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\sistemas_embarcados\01_vhdl\simular.ps1" 04_display_7seg
