-- This VHDL code describes the c17 benchmark circuit, which is a common
-- example used in digital logic testing and synthesis.

-- Library declarations
library ieee;
use ieee.std_logic_1164.all;

-- The ENTITY block defines the primary inputs and outputs of the circuit.
-- The signal names (N1, N2, etc.) correspond to the numbers in the .bench file.
entity c17 is
  port (
    N1  : in  std_logic_vector(3 downto 0);
    N2  : in  std_logic;
    N3  : in  std_logic;
    N6  : in  std_logic;
    N7  : in  std_logic;
    N22 : out std_logic;
    N23 : out std_logic
  );
end entity c17;

-- The ARCHITECTURE block describes the internal structure and logic.
-- This is a structural model using dataflow-style assignments.
architecture structural of c17 is

  -- Internal wires (signals) are declared here. These connect the gates.
  signal N10 : std_logic;
  signal N11 : std_logic;
  signal N16 : std_logic;
  signal N19 : std_logic;

begin

  -- Gate instantiations using concurrent signal assignments.
  -- Each line corresponds to a gate in the .bench file.
  N10 <= N1(0) nand N3;  -- 10 = NAND(1, 3)
  N11 <= N3 nand N6;  -- 11 = NAND(3, 6)
  N16 <= N2 nand N11; -- 16 = NAND(2, 11)
  N19 <= N11 nand N7; -- 19 = NAND(11, 7)
  N22 <= N10 nand N16; -- 22 = NAND(10, 16)
  N23 <= N16 nand N19; -- 23 = NAND(16, 19)

end architecture structural;