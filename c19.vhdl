library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity my_circuit is
    port (
        A : in std_logic_vector(0 to 3);  
        B : in std_logic_vector(3 downto 0);  -- 4-bit input
        Y : out std_logic_vector(3 downto 0)  -- 4-bit output
    );
end my_circuit;

architecture Structural of my_circuit is
begin
    -- Y(0) = A(0) AND B(0)
    Y(0) <= A(0) and B(0);

    -- Y(1) = A(1) OR B(1)
    Y(1) <= A(1) or B(1);

    -- Y(2) = A(2) XOR B(2)
    Y(2) <= A(2) xor B(2);

    Y(3) <= A(3) and B(3);
end Structural;
