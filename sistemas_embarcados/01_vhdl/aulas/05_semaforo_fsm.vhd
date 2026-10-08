-- Elaborado pelo Prof. Vagner Cordeiro
-- AULA 05 - Maquina de estados (FSM): semaforo
--
-- FSM = Finite State Machine. O circuito esta sempre em UM estado
-- e muda de estado quando uma condicao acontece (aqui: o tempo acabou).
--
--   VERDE --(3 ciclos)--> AMARELO --(1 ciclo)--> VERMELHO --(3 ciclos)--> VERDE ...
--
-- E o mesmo conceito da maquina de estados que voce ja viu em C.

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity semaforo is
    port (
        clk, reset : in  std_logic;
        verde, amarelo, vermelho : out std_logic
    );
end entity;

architecture fsm of semaforo is
    type estado_t is (S_VERDE, S_AMARELO, S_VERMELHO);   -- nossos estados, com nomes
    signal estado : estado_t := S_VERMELHO;
    signal tempo  : unsigned(2 downto 0) := (others => '0');
begin
    -- Parte 1: SEQUENCIAL - guarda o estado e conta o tempo
    process (clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                estado <= S_VERMELHO;
                tempo  <= (others => '0');
            else
                tempo <= tempo + 1;
                case estado is
                    when S_VERDE =>
                        if tempo = 2 then estado <= S_AMARELO; tempo <= (others => '0'); end if;
                    when S_AMARELO =>
                        if tempo = 0 then estado <= S_VERMELHO; tempo <= (others => '0'); end if;
                    when S_VERMELHO =>
                        if tempo = 2 then estado <= S_VERDE; tempo <= (others => '0'); end if;
                end case;
            end if;
        end if;
    end process;

    -- Parte 2: COMBINACIONAL - as saidas dependem so do estado
    verde    <= '1' when estado = S_VERDE    else '0';
    amarelo  <= '1' when estado = S_AMARELO  else '0';
    vermelho <= '1' when estado = S_VERMELHO else '0';
end architecture;

library ieee;
use ieee.std_logic_1164.all;

entity tb is end entity;

architecture teste of tb is
    signal clk : std_logic := '0';
    signal reset : std_logic := '1';
    signal verde, amarelo, vermelho : std_logic;
begin
    dut : entity work.semaforo port map (clk, reset, verde, amarelo, vermelho);
    clk <= not clk after 5 ns;

    process
    begin
        wait for 12 ns;
        reset <= '0';
        for i in 1 to 14 loop
            wait until rising_edge(clk);
            wait for 1 ns;
            report "ciclo " & integer'image(i) & ":  V=" & to_string(verde)
                   & "  A=" & to_string(amarelo) & "  R=" & to_string(vermelho);
        end loop;
        report "Teste concluido.";
        wait;
    end process;
end architecture;

-- EXERCICIOS:
-- 1) Aumente o tempo do amarelo para 2 ciclos.
-- 2) Acrescente a entrada "pedestre" que forca o estado VERMELHO.
-- 3) Desenhe o diagrama de estados no papel antes de alterar o codigo.
-- Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\sistemas_embarcados\01_vhdl\simular.ps1" 05_semaforo_fsm
