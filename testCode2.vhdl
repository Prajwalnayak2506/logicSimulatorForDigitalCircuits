library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity my_circuit is
    port (
        A : in  std_logic_vector(3 downto 0); -- Corrected range for consistency
        B : in  std_logic_vector(3 downto 0);
        Y : out std_logic_vector(3 downto 0)
    );
end my_circuit;

architecture Structural of my_circuit is
    -- Signal 'C' must be declared before it can be used
    signal C, D : std_logic_vector(3 downto 0);
begin
    -- Y(0) = A(0) AND B(0)
    Y(0) <= A(0) and B(0);

    -- Y(1) = A(1) OR B(1)
    Y(1) <= A(1) or B(1);

    -- Y(2) = A(2) XOR B(2)
    Y(2) <= A(2) xor B(2);

    -- Intermediate signal for the NAND operation
    C(1) <= A(3) and B(3);
    Y(3) <= not C(1); -- Added missing semicolon
    
end Structural;