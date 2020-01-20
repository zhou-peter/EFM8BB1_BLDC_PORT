//-----------------------------------------------------------------------------
// comp.c
//-----------------------------------------------------------------------------
// Copyright 2013, Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Created on: Mat 20, 2013
//     Author: sgghang
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "bldcdk.h"

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// COMP_initialize_comp
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Description  :
//-----------------------------------------------------------------------------
#if (BLDC_RD_PWM_METHOD == H_BRIDGE_HIGH_SIDE_PWM) || \
    (BLDC_RD_PWM_METHOD == H_BRIDGE_LOW_SIDE_PWM) || \
    (BLDC_RD_PWM_METHOD == H_BRIDGE_MIXED_MODE_PWM)
void COMP_initialize_comp(void)
{
	CMP1MX = compMux[0];

    // enable comparator 0
    // Hysteresis 0mV
}
#endif
