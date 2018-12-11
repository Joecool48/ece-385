/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_gen2_0' in SOPC Builder design 'final_project'
 * SOPC Builder design path: ../../final_project.sopcinfo
 *
 * Generated: Tue Dec 11 01:52:18 CST 2018
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x08000020
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 100000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1c
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00000020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 100000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x1c
#define ALT_CPU_NAME "nios2_gen2_0"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x08000020
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 100000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x1c
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00000020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x1c
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00000000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_NIOS2_GEN2
#define __ALTPLL


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_game_nios"
#define ALT_STDERR_BASE 0x80011d8
#define ALT_STDERR_DEV jtag_game_nios
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_game_nios"
#define ALT_STDIN_BASE 0x80011d8
#define ALT_STDIN_DEV jtag_game_nios
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_game_nios"
#define ALT_STDOUT_BASE 0x80011d8
#define ALT_STDOUT_DEV jtag_game_nios
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "final_project"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_game_nios configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_game_nios altera_avalon_jtag_uart
#define JTAG_GAME_NIOS_BASE 0x80011d8
#define JTAG_GAME_NIOS_IRQ 0
#define JTAG_GAME_NIOS_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_GAME_NIOS_NAME "/dev/jtag_game_nios"
#define JTAG_GAME_NIOS_READ_DEPTH 64
#define JTAG_GAME_NIOS_READ_THRESHOLD 8
#define JTAG_GAME_NIOS_SPAN 8
#define JTAG_GAME_NIOS_TYPE "altera_avalon_jtag_uart"
#define JTAG_GAME_NIOS_WRITE_DEPTH 64
#define JTAG_GAME_NIOS_WRITE_THRESHOLD 8


/*
 * keycode_pio configuration
 *
 */

#define ALT_MODULE_CLASS_keycode_pio altera_avalon_pio
#define KEYCODE_PIO_BASE 0x80010e0
#define KEYCODE_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define KEYCODE_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define KEYCODE_PIO_CAPTURE 0
#define KEYCODE_PIO_DATA_WIDTH 16
#define KEYCODE_PIO_DO_TEST_BENCH_WIRING 0
#define KEYCODE_PIO_DRIVEN_SIM_VALUE 0
#define KEYCODE_PIO_EDGE_TYPE "NONE"
#define KEYCODE_PIO_FREQ 100000000
#define KEYCODE_PIO_HAS_IN 1
#define KEYCODE_PIO_HAS_OUT 0
#define KEYCODE_PIO_HAS_TRI 0
#define KEYCODE_PIO_IRQ -1
#define KEYCODE_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define KEYCODE_PIO_IRQ_TYPE "NONE"
#define KEYCODE_PIO_NAME "/dev/keycode_pio"
#define KEYCODE_PIO_RESET_VALUE 0
#define KEYCODE_PIO_SPAN 16
#define KEYCODE_PIO_TYPE "altera_avalon_pio"


/*
 * otg_address_pio configuration
 *
 */

#define ALT_MODULE_CLASS_otg_address_pio altera_avalon_pio
#define OTG_ADDRESS_PIO_BASE 0x8001130
#define OTG_ADDRESS_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_ADDRESS_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_ADDRESS_PIO_CAPTURE 0
#define OTG_ADDRESS_PIO_DATA_WIDTH 8
#define OTG_ADDRESS_PIO_DO_TEST_BENCH_WIRING 0
#define OTG_ADDRESS_PIO_DRIVEN_SIM_VALUE 0
#define OTG_ADDRESS_PIO_EDGE_TYPE "NONE"
#define OTG_ADDRESS_PIO_FREQ 100000000
#define OTG_ADDRESS_PIO_HAS_IN 0
#define OTG_ADDRESS_PIO_HAS_OUT 1
#define OTG_ADDRESS_PIO_HAS_TRI 0
#define OTG_ADDRESS_PIO_IRQ -1
#define OTG_ADDRESS_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_ADDRESS_PIO_IRQ_TYPE "NONE"
#define OTG_ADDRESS_PIO_NAME "/dev/otg_address_pio"
#define OTG_ADDRESS_PIO_RESET_VALUE 0
#define OTG_ADDRESS_PIO_SPAN 16
#define OTG_ADDRESS_PIO_TYPE "altera_avalon_pio"


/*
 * otg_cs_pio configuration
 *
 */

#define ALT_MODULE_CLASS_otg_cs_pio altera_avalon_pio
#define OTG_CS_PIO_BASE 0x8001100
#define OTG_CS_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_CS_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_CS_PIO_CAPTURE 0
#define OTG_CS_PIO_DATA_WIDTH 8
#define OTG_CS_PIO_DO_TEST_BENCH_WIRING 0
#define OTG_CS_PIO_DRIVEN_SIM_VALUE 0
#define OTG_CS_PIO_EDGE_TYPE "NONE"
#define OTG_CS_PIO_FREQ 100000000
#define OTG_CS_PIO_HAS_IN 0
#define OTG_CS_PIO_HAS_OUT 1
#define OTG_CS_PIO_HAS_TRI 0
#define OTG_CS_PIO_IRQ -1
#define OTG_CS_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_CS_PIO_IRQ_TYPE "NONE"
#define OTG_CS_PIO_NAME "/dev/otg_cs_pio"
#define OTG_CS_PIO_RESET_VALUE 0
#define OTG_CS_PIO_SPAN 16
#define OTG_CS_PIO_TYPE "altera_avalon_pio"


/*
 * otg_data_pio configuration
 *
 */

#define ALT_MODULE_CLASS_otg_data_pio altera_avalon_pio
#define OTG_DATA_PIO_BASE 0x80010f0
#define OTG_DATA_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_DATA_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_DATA_PIO_CAPTURE 0
#define OTG_DATA_PIO_DATA_WIDTH 16
#define OTG_DATA_PIO_DO_TEST_BENCH_WIRING 0
#define OTG_DATA_PIO_DRIVEN_SIM_VALUE 0
#define OTG_DATA_PIO_EDGE_TYPE "NONE"
#define OTG_DATA_PIO_FREQ 100000000
#define OTG_DATA_PIO_HAS_IN 1
#define OTG_DATA_PIO_HAS_OUT 1
#define OTG_DATA_PIO_HAS_TRI 0
#define OTG_DATA_PIO_IRQ -1
#define OTG_DATA_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_DATA_PIO_IRQ_TYPE "NONE"
#define OTG_DATA_PIO_NAME "/dev/otg_data_pio"
#define OTG_DATA_PIO_RESET_VALUE 0
#define OTG_DATA_PIO_SPAN 16
#define OTG_DATA_PIO_TYPE "altera_avalon_pio"


/*
 * otg_read_pio configuration
 *
 */

#define ALT_MODULE_CLASS_otg_read_pio altera_avalon_pio
#define OTG_READ_PIO_BASE 0x8001110
#define OTG_READ_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_READ_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_READ_PIO_CAPTURE 0
#define OTG_READ_PIO_DATA_WIDTH 8
#define OTG_READ_PIO_DO_TEST_BENCH_WIRING 0
#define OTG_READ_PIO_DRIVEN_SIM_VALUE 0
#define OTG_READ_PIO_EDGE_TYPE "NONE"
#define OTG_READ_PIO_FREQ 100000000
#define OTG_READ_PIO_HAS_IN 0
#define OTG_READ_PIO_HAS_OUT 1
#define OTG_READ_PIO_HAS_TRI 0
#define OTG_READ_PIO_IRQ -1
#define OTG_READ_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_READ_PIO_IRQ_TYPE "NONE"
#define OTG_READ_PIO_NAME "/dev/otg_read_pio"
#define OTG_READ_PIO_RESET_VALUE 0
#define OTG_READ_PIO_SPAN 16
#define OTG_READ_PIO_TYPE "altera_avalon_pio"


/*
 * otg_write_pio configuration
 *
 */

#define ALT_MODULE_CLASS_otg_write_pio altera_avalon_pio
#define OTG_WRITE_PIO_BASE 0x8001120
#define OTG_WRITE_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_WRITE_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_WRITE_PIO_CAPTURE 0
#define OTG_WRITE_PIO_DATA_WIDTH 8
#define OTG_WRITE_PIO_DO_TEST_BENCH_WIRING 0
#define OTG_WRITE_PIO_DRIVEN_SIM_VALUE 0
#define OTG_WRITE_PIO_EDGE_TYPE "NONE"
#define OTG_WRITE_PIO_FREQ 100000000
#define OTG_WRITE_PIO_HAS_IN 0
#define OTG_WRITE_PIO_HAS_OUT 1
#define OTG_WRITE_PIO_HAS_TRI 0
#define OTG_WRITE_PIO_IRQ -1
#define OTG_WRITE_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_WRITE_PIO_IRQ_TYPE "NONE"
#define OTG_WRITE_PIO_NAME "/dev/otg_write_pio"
#define OTG_WRITE_PIO_RESET_VALUE 0
#define OTG_WRITE_PIO_SPAN 16
#define OTG_WRITE_PIO_TYPE "altera_avalon_pio"


/*
 * pll configuration
 *
 */

#define ALT_MODULE_CLASS_pll altpll
#define PLL_BASE 0x80011b0
#define PLL_IRQ -1
#define PLL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PLL_NAME "/dev/pll"
#define PLL_SPAN 16
#define PLL_TYPE "altpll"


/*
 * sdram configuration
 *
 */

#define ALT_MODULE_CLASS_sdram altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x0
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/sdram"
#define SDRAM_POWERUP_DELAY 200.0
#define SDRAM_REFRESH_PERIOD 7.8125
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x19
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 10
#define SDRAM_SDRAM_DATA_WIDTH 32
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 0
#define SDRAM_SPAN 134217728
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.5
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 20.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 20.0
#define SDRAM_T_WR 14.0


/*
 * sprite_address_pio configuration
 *
 */

#define ALT_MODULE_CLASS_sprite_address_pio altera_avalon_pio
#define SPRITE_ADDRESS_PIO_BASE 0x8001190
#define SPRITE_ADDRESS_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define SPRITE_ADDRESS_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SPRITE_ADDRESS_PIO_CAPTURE 0
#define SPRITE_ADDRESS_PIO_DATA_WIDTH 32
#define SPRITE_ADDRESS_PIO_DO_TEST_BENCH_WIRING 0
#define SPRITE_ADDRESS_PIO_DRIVEN_SIM_VALUE 0
#define SPRITE_ADDRESS_PIO_EDGE_TYPE "NONE"
#define SPRITE_ADDRESS_PIO_FREQ 100000000
#define SPRITE_ADDRESS_PIO_HAS_IN 0
#define SPRITE_ADDRESS_PIO_HAS_OUT 1
#define SPRITE_ADDRESS_PIO_HAS_TRI 0
#define SPRITE_ADDRESS_PIO_IRQ -1
#define SPRITE_ADDRESS_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SPRITE_ADDRESS_PIO_IRQ_TYPE "NONE"
#define SPRITE_ADDRESS_PIO_NAME "/dev/sprite_address_pio"
#define SPRITE_ADDRESS_PIO_RESET_VALUE 0
#define SPRITE_ADDRESS_PIO_SPAN 16
#define SPRITE_ADDRESS_PIO_TYPE "altera_avalon_pio"


/*
 * sprite_height_pio configuration
 *
 */

#define ALT_MODULE_CLASS_sprite_height_pio altera_avalon_pio
#define SPRITE_HEIGHT_PIO_BASE 0x8001170
#define SPRITE_HEIGHT_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define SPRITE_HEIGHT_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SPRITE_HEIGHT_PIO_CAPTURE 0
#define SPRITE_HEIGHT_PIO_DATA_WIDTH 16
#define SPRITE_HEIGHT_PIO_DO_TEST_BENCH_WIRING 0
#define SPRITE_HEIGHT_PIO_DRIVEN_SIM_VALUE 0
#define SPRITE_HEIGHT_PIO_EDGE_TYPE "NONE"
#define SPRITE_HEIGHT_PIO_FREQ 100000000
#define SPRITE_HEIGHT_PIO_HAS_IN 0
#define SPRITE_HEIGHT_PIO_HAS_OUT 1
#define SPRITE_HEIGHT_PIO_HAS_TRI 0
#define SPRITE_HEIGHT_PIO_IRQ -1
#define SPRITE_HEIGHT_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SPRITE_HEIGHT_PIO_IRQ_TYPE "NONE"
#define SPRITE_HEIGHT_PIO_NAME "/dev/sprite_height_pio"
#define SPRITE_HEIGHT_PIO_RESET_VALUE 0
#define SPRITE_HEIGHT_PIO_SPAN 16
#define SPRITE_HEIGHT_PIO_TYPE "altera_avalon_pio"


/*
 * sprite_id_pio configuration
 *
 */

#define ALT_MODULE_CLASS_sprite_id_pio altera_avalon_pio
#define SPRITE_ID_PIO_BASE 0x80011a0
#define SPRITE_ID_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define SPRITE_ID_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SPRITE_ID_PIO_CAPTURE 0
#define SPRITE_ID_PIO_DATA_WIDTH 16
#define SPRITE_ID_PIO_DO_TEST_BENCH_WIRING 0
#define SPRITE_ID_PIO_DRIVEN_SIM_VALUE 0
#define SPRITE_ID_PIO_EDGE_TYPE "NONE"
#define SPRITE_ID_PIO_FREQ 100000000
#define SPRITE_ID_PIO_HAS_IN 0
#define SPRITE_ID_PIO_HAS_OUT 1
#define SPRITE_ID_PIO_HAS_TRI 0
#define SPRITE_ID_PIO_IRQ -1
#define SPRITE_ID_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SPRITE_ID_PIO_IRQ_TYPE "NONE"
#define SPRITE_ID_PIO_NAME "/dev/sprite_id_pio"
#define SPRITE_ID_PIO_RESET_VALUE 0
#define SPRITE_ID_PIO_SPAN 16
#define SPRITE_ID_PIO_TYPE "altera_avalon_pio"


/*
 * sprite_rotate_pio configuration
 *
 */

#define ALT_MODULE_CLASS_sprite_rotate_pio altera_avalon_pio
#define SPRITE_ROTATE_PIO_BASE 0x8001140
#define SPRITE_ROTATE_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define SPRITE_ROTATE_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SPRITE_ROTATE_PIO_CAPTURE 0
#define SPRITE_ROTATE_PIO_DATA_WIDTH 8
#define SPRITE_ROTATE_PIO_DO_TEST_BENCH_WIRING 0
#define SPRITE_ROTATE_PIO_DRIVEN_SIM_VALUE 0
#define SPRITE_ROTATE_PIO_EDGE_TYPE "NONE"
#define SPRITE_ROTATE_PIO_FREQ 100000000
#define SPRITE_ROTATE_PIO_HAS_IN 0
#define SPRITE_ROTATE_PIO_HAS_OUT 1
#define SPRITE_ROTATE_PIO_HAS_TRI 0
#define SPRITE_ROTATE_PIO_IRQ -1
#define SPRITE_ROTATE_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SPRITE_ROTATE_PIO_IRQ_TYPE "NONE"
#define SPRITE_ROTATE_PIO_NAME "/dev/sprite_rotate_pio"
#define SPRITE_ROTATE_PIO_RESET_VALUE 0
#define SPRITE_ROTATE_PIO_SPAN 16
#define SPRITE_ROTATE_PIO_TYPE "altera_avalon_pio"


/*
 * sprite_width_pio configuration
 *
 */

#define ALT_MODULE_CLASS_sprite_width_pio altera_avalon_pio
#define SPRITE_WIDTH_PIO_BASE 0x8001180
#define SPRITE_WIDTH_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define SPRITE_WIDTH_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SPRITE_WIDTH_PIO_CAPTURE 0
#define SPRITE_WIDTH_PIO_DATA_WIDTH 16
#define SPRITE_WIDTH_PIO_DO_TEST_BENCH_WIRING 0
#define SPRITE_WIDTH_PIO_DRIVEN_SIM_VALUE 0
#define SPRITE_WIDTH_PIO_EDGE_TYPE "NONE"
#define SPRITE_WIDTH_PIO_FREQ 100000000
#define SPRITE_WIDTH_PIO_HAS_IN 0
#define SPRITE_WIDTH_PIO_HAS_OUT 1
#define SPRITE_WIDTH_PIO_HAS_TRI 0
#define SPRITE_WIDTH_PIO_IRQ -1
#define SPRITE_WIDTH_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SPRITE_WIDTH_PIO_IRQ_TYPE "NONE"
#define SPRITE_WIDTH_PIO_NAME "/dev/sprite_width_pio"
#define SPRITE_WIDTH_PIO_RESET_VALUE 0
#define SPRITE_WIDTH_PIO_SPAN 16
#define SPRITE_WIDTH_PIO_TYPE "altera_avalon_pio"


/*
 * sprite_x_pio configuration
 *
 */

#define ALT_MODULE_CLASS_sprite_x_pio altera_avalon_pio
#define SPRITE_X_PIO_BASE 0x8001160
#define SPRITE_X_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define SPRITE_X_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SPRITE_X_PIO_CAPTURE 0
#define SPRITE_X_PIO_DATA_WIDTH 16
#define SPRITE_X_PIO_DO_TEST_BENCH_WIRING 0
#define SPRITE_X_PIO_DRIVEN_SIM_VALUE 0
#define SPRITE_X_PIO_EDGE_TYPE "NONE"
#define SPRITE_X_PIO_FREQ 100000000
#define SPRITE_X_PIO_HAS_IN 0
#define SPRITE_X_PIO_HAS_OUT 1
#define SPRITE_X_PIO_HAS_TRI 0
#define SPRITE_X_PIO_IRQ -1
#define SPRITE_X_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SPRITE_X_PIO_IRQ_TYPE "NONE"
#define SPRITE_X_PIO_NAME "/dev/sprite_x_pio"
#define SPRITE_X_PIO_RESET_VALUE 0
#define SPRITE_X_PIO_SPAN 16
#define SPRITE_X_PIO_TYPE "altera_avalon_pio"


/*
 * sprite_y_pio configuration
 *
 */

#define ALT_MODULE_CLASS_sprite_y_pio altera_avalon_pio
#define SPRITE_Y_PIO_BASE 0x8001150
#define SPRITE_Y_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define SPRITE_Y_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SPRITE_Y_PIO_CAPTURE 0
#define SPRITE_Y_PIO_DATA_WIDTH 16
#define SPRITE_Y_PIO_DO_TEST_BENCH_WIRING 0
#define SPRITE_Y_PIO_DRIVEN_SIM_VALUE 0
#define SPRITE_Y_PIO_EDGE_TYPE "NONE"
#define SPRITE_Y_PIO_FREQ 100000000
#define SPRITE_Y_PIO_HAS_IN 0
#define SPRITE_Y_PIO_HAS_OUT 1
#define SPRITE_Y_PIO_HAS_TRI 0
#define SPRITE_Y_PIO_IRQ -1
#define SPRITE_Y_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SPRITE_Y_PIO_IRQ_TYPE "NONE"
#define SPRITE_Y_PIO_NAME "/dev/sprite_y_pio"
#define SPRITE_Y_PIO_RESET_VALUE 0
#define SPRITE_Y_PIO_SPAN 16
#define SPRITE_Y_PIO_TYPE "altera_avalon_pio"


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid_qsys
#define SYSID_BASE 0x80011d0
#define SYSID_ID 0
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1544514522
#define SYSID_TYPE "altera_avalon_sysid_qsys"

#endif /* __SYSTEM_H_ */
