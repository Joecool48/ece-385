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
			sdram_wire_addr                : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_wire_ba                  : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n               : out   std_logic;                                        -- cas_n
			sdram_wire_cke                 : out   std_logic;                                        -- cke
			sdram_wire_cs_n                : out   std_logic;                                        -- cs_n
			sdram_wire_dq                  : inout std_logic_vector(31 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm                 : out   std_logic_vector(3 downto 0);                     -- dqm
			sdram_wire_ras_n               : out   std_logic;                                        -- ras_n
			sdram_wire_we_n                : out   std_logic;                                        -- we_n
			sprite_address_pio_export      : out   std_logic_vector(31 downto 0);                    -- export
			sprite_height_pio_export       : out   std_logic_vector(15 downto 0);                    -- export
			sprite_id_pio_export           : out   std_logic_vector(15 downto 0);                    -- export
			sprite_rotate_pio_export       : out   std_logic_vector(7 downto 0);                     -- export
			sprite_width_pio_export        : out   std_logic_vector(15 downto 0);                    -- export
			sprite_x_pio_export            : out   std_logic_vector(15 downto 0);                    -- export
			sprite_y_pio_export            : out   std_logic_vector(15 downto 0);                    -- export
			sys_clk_clk                    : out   std_logic;                                        -- clk
			keycode_pio_export_export      : in    std_logic_vector(15 downto 0) := (others => 'X'); -- export
			otg_data_pio_export_in_port    : in    std_logic_vector(15 downto 0) := (others => 'X'); -- in_port
			otg_data_pio_export_out_port   : out   std_logic_vector(15 downto 0);                    -- out_port
			otg_cs_pio_export_export       : out   std_logic_vector(7 downto 0);                     -- export
			otg_read_pio_export_export     : out   std_logic_vector(7 downto 0);                     -- export
			otg_write_pio_export_export    : out   std_logic_vector(7 downto 0);                     -- export
			otg_address_pio_export_export  : out   std_logic_vector(7 downto 0)                      -- export
		);
	end component final_project;

	u0 : component final_project
		port map (
			avalon_control_fixed_location  => CONNECTED_TO_avalon_control_fixed_location,  --         avalon_control.fixed_location
			avalon_control_read_base       => CONNECTED_TO_avalon_control_read_base,       --                       .read_base
			avalon_control_read_length     => CONNECTED_TO_avalon_control_read_length,     --                       .read_length
			avalon_control_go              => CONNECTED_TO_avalon_control_go,              --                       .go
			avalon_control_done            => CONNECTED_TO_avalon_control_done,            --                       .done
			avalon_control_early_done      => CONNECTED_TO_avalon_control_early_done,      --                       .early_done
			avalon_user_read_buffer        => CONNECTED_TO_avalon_user_read_buffer,        --            avalon_user.read_buffer
			avalon_user_buffer_output_data => CONNECTED_TO_avalon_user_buffer_output_data, --                       .buffer_output_data
			avalon_user_data_available     => CONNECTED_TO_avalon_user_data_available,     --                       .data_available
			clk_clk                        => CONNECTED_TO_clk_clk,                        --                    clk.clk
			reset_reset_n                  => CONNECTED_TO_reset_reset_n,                  --                  reset.reset_n
			sdram_clk_clk                  => CONNECTED_TO_sdram_clk_clk,                  --              sdram_clk.clk
			sdram_wire_addr                => CONNECTED_TO_sdram_wire_addr,                --             sdram_wire.addr
			sdram_wire_ba                  => CONNECTED_TO_sdram_wire_ba,                  --                       .ba
			sdram_wire_cas_n               => CONNECTED_TO_sdram_wire_cas_n,               --                       .cas_n
			sdram_wire_cke                 => CONNECTED_TO_sdram_wire_cke,                 --                       .cke
			sdram_wire_cs_n                => CONNECTED_TO_sdram_wire_cs_n,                --                       .cs_n
			sdram_wire_dq                  => CONNECTED_TO_sdram_wire_dq,                  --                       .dq
			sdram_wire_dqm                 => CONNECTED_TO_sdram_wire_dqm,                 --                       .dqm
			sdram_wire_ras_n               => CONNECTED_TO_sdram_wire_ras_n,               --                       .ras_n
			sdram_wire_we_n                => CONNECTED_TO_sdram_wire_we_n,                --                       .we_n
			sprite_address_pio_export      => CONNECTED_TO_sprite_address_pio_export,      --     sprite_address_pio.export
			sprite_height_pio_export       => CONNECTED_TO_sprite_height_pio_export,       --      sprite_height_pio.export
			sprite_id_pio_export           => CONNECTED_TO_sprite_id_pio_export,           --          sprite_id_pio.export
			sprite_rotate_pio_export       => CONNECTED_TO_sprite_rotate_pio_export,       --      sprite_rotate_pio.export
			sprite_width_pio_export        => CONNECTED_TO_sprite_width_pio_export,        --       sprite_width_pio.export
			sprite_x_pio_export            => CONNECTED_TO_sprite_x_pio_export,            --           sprite_x_pio.export
			sprite_y_pio_export            => CONNECTED_TO_sprite_y_pio_export,            --           sprite_y_pio.export
			sys_clk_clk                    => CONNECTED_TO_sys_clk_clk,                    --                sys_clk.clk
			keycode_pio_export_export      => CONNECTED_TO_keycode_pio_export_export,      --     keycode_pio_export.export
			otg_data_pio_export_in_port    => CONNECTED_TO_otg_data_pio_export_in_port,    --    otg_data_pio_export.in_port
			otg_data_pio_export_out_port   => CONNECTED_TO_otg_data_pio_export_out_port,   --                       .out_port
			otg_cs_pio_export_export       => CONNECTED_TO_otg_cs_pio_export_export,       --      otg_cs_pio_export.export
			otg_read_pio_export_export     => CONNECTED_TO_otg_read_pio_export_export,     --    otg_read_pio_export.export
			otg_write_pio_export_export    => CONNECTED_TO_otg_write_pio_export_export,    --   otg_write_pio_export.export
			otg_address_pio_export_export  => CONNECTED_TO_otg_address_pio_export_export   -- otg_address_pio_export.export
		);

