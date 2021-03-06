/*  ------------------------------------------------------------
    Copyright(C) 2015 MindTribe Product Engineering, Inc.
    All Rights Reserved.

    Author:     Sander Vocke, MindTribe Product Engineering
                <sander@mindtribe.com>

    Target(s):  ISO/IEC 9899:1999 (TI CC3200 - Launchpad XL)
    --------------------------------------------------------- */

/*
 * Functions to interact with the Cortex M4's JTAG-DP debug port, as found in the CC3200 SoC
 * (and as should be found in any other Cortex M4 core with debug functionality).
 */

#ifndef CC3200_JTAGDP_H_
#define CC3200_JTAGDP_H_

#include "jtag_scan.h"

//initialize the jtagdp state.
//this represents the "JTAGDP" as specified in the ARM debug interface architecture (one layer deeper than TI's ICEPICK router).
//Therefore it is not the first thing in the scan chain - the ICEPICK is always in front on the CC3200.
//This module does assume it is the LAST thing in the scan chain.
//Arguments to this function allow to configure how many preceding IR and DR bits there are in the scan chain, and what their
//values should be set to when trying to access the JTAGDP (normally, 6 bits IR set to 1 for BYPASSing the ICEPICK, and
//1 bit with dont-care value for going through the 1-bit BYPASS DR of the ICEPICK).
int cc3200_jtagdp_init(int num_precede_ir_bits, uint64_t precede_ir_bits, int num_precede_dr_bits, uint64_t precede_dr_bits);

//de-initialize, after which this module may be re-initialized again.
int cc3200_jtagdp_deinit(void);

//attempt to detect the JTAGDP of the ARM core. Note that all ICEPICK configuration must have been done beforehand.
int cc3200_jtagdp_detect(void);

//wrapper for shiftIR to access JTAG-DP port only
int cc3200_jtagdp_shiftIR(uint8_t data, enum jtag_state_scan toState);

//wrapper for shiftDR to access JTAG-DP port only
int cc3200_jtagdp_shiftDR(uint64_t data, int DR_len, enum jtag_state_scan toState);

//get the response of the last transaction.
int cc3200_jtagdp_accResponse(uint8_t* response, enum jtag_state_scan toState);

//perform a DPACC write on the JTAG-DP
int cc3200_jtagdp_DPACC_write(uint8_t addr, uint32_t value, uint8_t check_response);

//perform a DPACC read on the JTAG-DP
int cc3200_jtagdp_DPACC_read(uint8_t addr, uint32_t* result, uint8_t check_response);

//perform an APACC write on the JTAG-DP
int cc3200_jtagdp_APACC_write(uint8_t addr, uint32_t value, uint8_t check_response);

//perform an APACC read on the JTAG-DP
int cc3200_jtagdp_APACC_read(uint8_t addr, uint32_t* result, uint8_t check_response);

//clear the control/status register.
int cc3200_jtagdp_clearCSR(void);

//read the control/status register.
int cc3200_jtagdp_checkCSR(uint32_t* csr);

//Power up the debug/SoC power domains.
int cc3200_jtagdp_powerUpDebug(void);

//Select a certain AP and register bank.
int cc3200_jtagdp_selectAPBank(uint8_t AP, uint8_t bank);

//Read the IDCODEs of all APs.
int cc3200_jtagdp_readAPs(void);

//send system powerup request and wait for ACK.
int cc3200_jtagdp_powerUpSystem(void);

//pipelined APACC accesses.
int cc3200_jtagdp_APACC_pipeline_write(uint8_t addr, uint32_t len, uint32_t* values, uint8_t check_response);

//pipelined APACC accesses.
int cc3200_jtagdp_APACC_pipeline_read(uint8_t addr, uint32_t len, uint32_t* dst);

#endif
