library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity my_circuit is
    port (
        A, B, C : in  std_logic;
        Y       : out std_logic
    );
end my_circuit;

architecture Structural of my_circuit is
    signal N1 : std_logic;

    -- declare components
    component AND2
        port (
            A, B : in  std_logic;
            O    : out std_logic
        );
    end component;

    component OR2
        port (
            A, B : in  std_logic;
            O    : out std_logic
        );
    end component;

begin
    -- instantiate AND2 gate
    U1: AND2 PORT MAP (A => A, B => B, O => N1);

    -- instantiate OR2 gate
    U2: OR2 PORT MAP (A => N1, B => C, O => Y);

end Structural;
