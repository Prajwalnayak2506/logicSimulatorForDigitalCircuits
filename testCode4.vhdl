library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity my_circuit is
    port (
        A, B, C : in  std_logic;
        Y       : out std_logic
    );
end my_circuit;

architecture Structural of my_circuit is
    signal N1, N2 : std_logic;

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

    component NOT1
        port (
            A : in  std_logic;
            O : out std_logic
        );
    end component;

begin
    -- instantiate AND2 gate
    U1: AND2 PORT MAP (A => A, B => B, O => N1);

    -- instantiate NOT gate
    U2: NOT1 PORT MAP (A => C, O => N2);

    -- instantiate OR2 gate
    U3: OR2 PORT MAP (A => N1, B => N2, O => Y);

end Structural;
