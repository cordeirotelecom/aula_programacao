-- Elaborado pelo Prof. Vagner Cordeiro
-- AULA 08 - Transmissor UART 8N1 simplificado (FSM)
--
-- 8N1 = 8 bits de dados, sem paridade (None), 1 stop bit.
-- A linha fica em '1' (ociosa). Quadro enviado:
--   START ('0') | D0 D1 D2 D3 D4 D5 D6 D7 (LSB primeiro) | STOP ('1')
-- Cada bit dura BIT_CLKS ciclos de clock (aqui 4, para a simulacao ser curta).
--
-- Estados: IDLE -> START -> DADOS -> STOP -> IDLE

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity uart_tx is
    generic (BIT_CLKS : positive := 4);
    port (
        clk, reset, start : in  std_logic;
        dado : in  std_logic_vector(7 downto 0);
        tx   : out std_logic;
        busy : out std_logic
    );
end entity;

architecture fsm of uart_tx is
    type estado_t is (S_IDLE, S_START, S_DADOS, S_STOP);
    signal estado : estado_t := S_IDLE;
    signal cont   : integer range 0 to BIT_CLKS - 1 := 0;
    signal idx    : integer range 0 to 7 := 0;
    signal reg    : std_logic_vector(7 downto 0) := (others => '0');
begin
    process (clk)
    begin
        if rising_edge(clk) then
            if reset = '1' then
                estado <= S_IDLE;
                cont <= 0;
                idx <= 0;
            else
                case estado is
                    when S_IDLE =>
                        if start = '1' then
                            reg <= dado;
                            cont <= 0;
                            estado <= S_START;
                        end if;
                    when S_START =>
                        if cont = BIT_CLKS - 1 then
                            cont <= 0; idx <= 0; estado <= S_DADOS;
                        else
                            cont <= cont + 1;
                        end if;
                    when S_DADOS =>
                        if cont = BIT_CLKS - 1 then
                            cont <= 0;
                            if idx = 7 then
                                estado <= S_STOP;
                            else
                                idx <= idx + 1;
                            end if;
                        else
                            cont <= cont + 1;
                        end if;
                    when S_STOP =>
                        if cont = BIT_CLKS - 1 then
                            cont <= 0; estado <= S_IDLE;
                        else
                            cont <= cont + 1;
                        end if;
                end case;
            end if;
        end if;
    end process;

    tx <= '0'         when estado = S_START else
          reg(idx)    when estado = S_DADOS else
          '1';
    busy <= '0' when estado = S_IDLE else '1';
end architecture;

library ieee;
use ieee.std_logic_1164.all;

entity tb is end entity;

architecture teste of tb is
    signal clk : std_logic := '0';
    signal reset : std_logic := '1';
    signal start : std_logic := '0';
    signal dado : std_logic_vector(7 downto 0) := x"41";   -- 'A'
    signal tx, busy : std_logic;
    signal fim : boolean := false;
begin
    clk <= not clk after 5 ns when not fim else '0';
    dut : entity work.uart_tx generic map (4) port map (clk, reset, start, dado, tx, busy);

    process
    begin
        wait for 12 ns;
        reset <= '0';
        wait until rising_edge(clk);
        start <= '1';
        wait until rising_edge(clk);
        start <= '0';
        report "Enviando 'A' = 0x41 = 01000001. Bits na ordem da linha:";
        -- amostra no meio de cada bit: 10 bits (start + 8 dados + stop)
        wait for 1 ns;
        wait for 20 ns;   -- vai para o meio do bit de start (2 clocks)
        for i in 0 to 9 loop
            if i = 0 then
                report "start : " & to_string(tx);
            elsif i = 9 then
                report "stop  : " & to_string(tx);
            else
                report "D" & integer'image(i - 1) & "    : " & to_string(tx);
            end if;
            wait for 40 ns;   -- 4 clocks = 1 bit
        end loop;
        wait for 20 ns;
        assert busy = '0' report "UART deveria estar livre" severity error;
        report "Teste concluido.";
        fim <= true;
        wait;
    end process;
end architecture;

-- EXERCICIOS:
-- 1) Mude o dado para x"4F" ('O') e confira os bits.
-- 2) Acrescente um bit de paridade par antes do stop (8E1).
-- 3) Troque BIT_CLKS por um valor calculado: clock 50 MHz e 115200 baud (~434).
-- Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\sistemas_embarcados\01_vhdl\simular.ps1" 08_uart_tx
