library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--
-- Simple preset data generator
-- Ports:
--  - DIN_RDY : in  STD_LOGIC       -- rising edge triggers output of next preset
--  - DIN_VLD : out STD_LOGIC       -- '1' while data is being presented, '0' otherwise
--  - data    : out STD_LOGIC_VECTOR(7 downto 0) -- 8-bit output value
--
entity preset_data_gen is
  port (
    DIN_RDY : in  std_logic;
    DIN_VLD : out std_logic;
    data    : out std_logic_vector(7 downto 0)
  );
end entity preset_data_gen;

architecture rtl of preset_data_gen is
  -- change this count and the PRESETS constant to modify the sequence
  constant PRESET_COUNT : integer := 5;
  type preset_array_t is array (0 to PRESET_COUNT-1) of std_logic_vector(7 downto 0);
  constant PRESETS : preset_array_t := (
    0 => x"AA",
    1 => x"55",
    2 => x"FF",
    3 => x"00",
    4 => x"0F"
  );

  signal idx      : integer range 0 to PRESET_COUNT-1 := 0;
  signal data_reg : std_logic_vector(7 downto 0) := (others => '0');
  signal vld_reg  : std_logic := '0';
begin
  data    <= data_reg;
  DIN_VLD <= vld_reg;

  --
  -- On a rising edge of DIN_RDY present the next preset on `data` and assert DIN_VLD.
  -- On the falling edge of DIN_RDY, deassert DIN_VLD.
  -- This treats DIN_RDY as a handshake/strobe line (use a short pulse).
  --
  process(DIN_RDY)
  begin
    if (DIN_RDY'event and DIN_RDY = '1') then
      -- output current preset, then advance index
      data_reg <= PRESETS(idx);
      vld_reg  <= '1';
      if idx = PRESET_COUNT-1 then
        idx <= 0;
      else
        idx <= idx + 1;
      end if;
    elsif (DIN_RDY'event and DIN_RDY = '0') then
      -- lower valid when the ready/strobe goes low
      vld_reg <= '0';
    end if;
  end process;
end architecture rtl;
