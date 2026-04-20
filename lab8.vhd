library ieee ;

use ieee.std_logic_1164.all;

use ieee.std_logic_unsigned.all;

 

entity lab8 is

port( writedata: in std_logic_vector(31 downto 0);

      clk_clk, reset_reset_n:   in std_logic;

      wr, cs : in std_logic;

      pwm_out: out std_logic;
		
		h_out1 : out STD_LOGIC_VECTOR(6 downto 0);
		
		h_out2 : out STD_LOGIC_VECTOR(6 downto 0));
		

end lab8;

 

architecture rtl of lab8 is

signal reg: std_logic_vector(1 downto 0);

signal licznik: std_logic_vector(25 downto 0);   

signal h_in1: std_logic_vector (1 downto 0 );    

begin

process(clk_clk)

begin

   if (clk_clk'event and clk_clk='1') then

      if(wr='1' and cs='1') then

        reg <=writedata(1 downto 0);
		  h_in1 <= writedata (3 downto 2);
        end if;

    end if;

end process;


process(h_in1)
begin
    case h_in1 is
        when "00" =>
            h_out1 <= "1111111"; 
				h_out2 <= "1111111"; 				

        when "01" =>
            h_out1 <= "0000010";
				h_out2 <= "0011001";  			

        when "10" =>
            h_out1 <= "0000010"; --6
				h_out2 <= "0010010"; --5

        when others =>
            h_out1 <= "0000110";
			   h_out2 <= "1111111";	
    end case;
end process;


process(clk_clk)

begin

   if (clk_clk'event and clk_clk='1') then

      licznik <= licznik +1;

    -- 1 okres=1.34s
	 

      if h_in1 = "11" then pwm_out <= licznik(25); 

      elsif (reg="00") then pwm_out <= '0';

      elsif (reg="11") then pwm_out <= '1';

      elsif (licznik(25 downto 22) = "00") then pwm_out <= '1';

      elsif (licznik(25 downto 22) = reg) then  pwm_out <= '0';

      end if;

    end if;

end process;

end rtl;