library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

--
-- SPI sample data provider compatible with SPI_client_dummy user interface.
-- The module asserts DIN_VLD for one clock cycle when DIN_RDY is high,
-- supplies the next sample on DIN, and then advances to the next batch element.
--
entity spi_sample_data_provider is
    generic (
        WORD_SIZE : natural := 8  -- size of transfer word in bits
    );
    port (
        CLK      : in  std_logic;  -- system clock
        RST      : in  std_logic;  -- synchronous active-high reset
        DIN_RDY  : in  std_logic;  -- input ready handshake from SPI client
        DIN_VLD  : out std_logic;  -- data valid to SPI client
        DIN      : out std_logic_vector(WORD_SIZE-1 downto 0)  -- data word to transmit
    );
end entity spi_sample_data_provider;

architecture RTL of spi_sample_data_provider is
    type sample_array_t is array (natural range <>) of std_logic_vector(WORD_SIZE-1 downto 0);
    constant SAMPLES : sample_array_t := (
        0 => x"01",
        1 => x"23",
        2 => x"45",
        3 => x"67",
        4 => x"89",
        5 => x"AB",
        6 => x"CD",
        7 => x"EF"
    );
    constant SAMPLE_COUNT : natural := SAMPLES'length;

    signal sample_index : natural range 0 to SAMPLE_COUNT := 0;
    signal vld_reg      : std_logic := '0';
    signal next_sample  : std_logic_vector(WORD_SIZE-1 downto 0) := (others => '0');

begin
    DIN <= next_sample;
    DIN_VLD <= vld_reg;

    process(CLK)
    begin
        if rising_edge(CLK) then
            if RST = '1' then
                sample_index <= 0;
                next_sample  <= SAMPLES(0);
                vld_reg      <= '0';
            else
                if vld_reg = '0' then
                    if sample_index < SAMPLE_COUNT and DIN_RDY = '1' then
                        -- present the current sample for one cycle
                        vld_reg <= '1';
                    end if;
                else
                    -- one-cycle valid pulse has been presented; advance sample
                    vld_reg <= '0';
                    if sample_index < SAMPLE_COUNT-1 then
                        sample_index <= sample_index + 1;
                        next_sample <= SAMPLES(sample_index + 1);
                    else
                        sample_index <= SAMPLE_COUNT;
                    end if;
                end if;
            end if;
        end if;
    end process;
end architecture RTL;
