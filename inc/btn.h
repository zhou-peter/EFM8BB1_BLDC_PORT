//-----------------------------------------------------------------------------
// btn.h
//-----------------------------------------------------------------------------
// Copyright 2013, Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Created on: Jun 19, 2013
//     Author: khsoh
//-----------------------------------------------------------------------------

#ifndef _BTN_H
#define _BTN_H

#include "bldcdk.h"

//-----------------------------------------------------------------------------
// is_btn1_pressed
//-----------------------------------------------------------------------------
// Return Value:
//     0: btn1 is not pressed
//     1: btn1 is pressed.
//
// Parameters:
//     None
//
// Description:
//
//-----------------------------------------------------------------------------
U8 is_btn1_pressed(void);


//-----------------------------------------------------------------------------
// btn_process
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Function to be called regularly to detect button state and
// ensure button release is debounced
//-----------------------------------------------------------------------------
void btn_process(void);

#endif