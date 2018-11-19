	component final_project is
		port (
			avalon_control_fixed_location  : in    std_logic                     := 'X';             -- fixed_location
			avalon_control_read_base       : in    std_logic_vector(31 downto 0) := (others => 'X'); -- read_base
			avalon_control_read_length     : in    std_logic_vector(31 downto 0) := (others => 'X'); -- read_length
			avalon_control_go              : in    std_logic                     := 'X';             -- go
			avalon_control_done            : out   std_logic;                                        -- done
			avalon_control_early_done      : out   std_logic;                                        -- early_done
			avalon_user_read_buffer        : in    std_logic                     := 'X';             -- read_buffer
			avalon_user_buffer_output_data : out   std_logic_vector(7 downto 0);                     -- buffer_output_data
			avalon_user_data_available     : out   std_logic;                                        -- data_available
			clk_clk                        : in    std_logic                     := 'X';             -- clk
			reset_reset_n                  : in    std_logic                     := 'X';             -- reset_n
			sdram_clk_clk                  : out   std_logic;                                        -- clk
			sdram_wire_addr                : out   std_logic_vector(11 downto 0);                    -- addr
			sdram_wire_ba                  : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n               : out   std_logic;                                        -- cas_n
			sdram_wire_cke                 : out   std_logic;                                        -- cke
			sdram_wire_cs_n                : out   std_logic;                                        -- cs_n
			sdram_wire_dq                  : inout std_logic_vector(31 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm                 : out   std_logic_vector(3 downto 0);                     -- dqm
			sdram_wire_ras_n               : out   std_logic;                                        -- ras_n
			sdram_wire_we_n                : out   std_logic;                                        -- we_n
			sys_clk_clk                    : out   std_logic                                         -- clk
		);
	end component final_project;

	u0 : component final_project
		port map (
			avalon_control_fixed_location  => CONNECTED_TO_avalon_control_fixed_location,  -- avalon_control.fixed_location
			avalon_control_read_base       => CONNECTED_TO_avalon_control_read_base,       --               .read_base
			avalon_control_read_length     => CONNECTED_TO_avalon_control_read_length,     --               .read_length
			avalon_control_go              => CONNECTED_TO_avalon_control_go,              --               .go
			avalon_control_done            => CONNECTED_TO_avalon_control_done,            --               .done
			avalon_control_early_done      => CONNECTED_TO_avalon_control_early_done,      --               .early_done
			avalon_user_read_buffer        => CONNECTED_TO_avalon_user_read_buffer,        --    avalon_user.read_buffer
			avalon_user_buffer_output_data => CONNECTED_TO_avalon_user_buffer_output_data, --               .buffer_output_data
			avalon_user_data_available     => CONNECTED_TO_avalon_user_data_available,     --               .data_available
			clk_clk                        => CONNECTED_TO_clk_clk,                        --            clk.clk
			reset_reset_n                  => CONNECTED_TO_reset_reset_n,                  --          reset.reset_n
			sdram_clk_clk                  => CONNECTED_TO_sdram_clk_clk,                  --      sdram_clk.clk
			sdram_wire_addr                => CONNECTED_TO_sdram_wire_addr,                --     sdram_wire.addr
			sdram_wire_ba                  => CONNECTED_TO_sdram_wire_ba,                  --               .ba
			sdram_wire_cas_n               => CONNECTED_TO_sdram_wire_cas_n,               --               .cas_n
			sdram_wire_cke                 => CONNECTED_TO_sdram_wire_cke,                 --               .cke
			sdram_wire_cs_n                => CONNECTED_TO_sdram_wire_cs_n,                --               .cs_n
			sdram_wire_dq                  => CONNECTED_TO_sdram_wire_dq,                  --               .dq
			sdram_wire_dqm                 => CONNECTED_TO_sdram_wire_dqm,                 --               .dqm
			sdram_wire_ras_n               => CONNECTED_TO_sdram_wire_ras_n,               --               .ras_n
			sdram_wire_we_n                => CONNECTED_TO_sdram_wire_we_n,                --               .we_n
			sys_clk_clk                    => CONNECTED_TO_sys_clk_clk                     --        sys_clk.clk
		);

