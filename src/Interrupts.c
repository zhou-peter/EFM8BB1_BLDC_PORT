//=========================================================
// src/Interrupts.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include <SI_EFM8BB1_Register_Enums.h>
#include "bldcdk.h"

//-----------------------------------------------------------------------------
// ADC0EOC_ISR
//-----------------------------------------------------------------------------
//
// ADC0EOC ISR Content goes here. Remember to clear flag bits:
// ADC0CN0::ADINT (Conversion Complete Interrupt Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (ADC0EOC_ISR, ADC0EOC_IRQn)
{
//	static uint32_t accumulator = 0;     // Accumulator for averaging
//	static uint16_t measurements = 2048;// Measurement counter
//	uint32_t result = 0;
//	uint32_t mV;// Measured voltage in mV
//
//	ADC0CN0_ADINT = 0;// Clear ADC0 conv. complete flag
//
//	accumulator += ADC0;
//	measurements--;
//
//	if(measurements == 0)
//	{
//		measurements = 2048;
//		result = accumulator / 2048;
//		accumulator = 0;
//
//		// The 10-bit ADC value is averaged across 2048 measurements.
//		// The measured voltage applied to P1.7 is then:
//		//
//		//                           Vref (mV)
//		//   measurement (mV) =   --------------- * result (bits)
//		//                       (2^10)-1 (bits)
//
//		mV = (result * 3300) / 1023;
//
//		RETARGET_PRINTF ("\nP0.7 voltage: %ld mV\n", mV);
//	}
}

//-----------------------------------------------------------------------------
// PCA0_ISR
//-----------------------------------------------------------------------------
//
// PCA0 ISR Content goes here. Remember to clear flag bits:
// PCA0CN0::PCA0CN0_CCF0 (PCA Module 0 Capture/Compare Flag)
// PCA0CN0::CCF1 (PCA Module 1 Capture/Compare Flag)
// PCA0CN0::CCF2 (PCA Module 2 Capture/Compare Flag)
// PCA0CN0::CF (PCA Counter/Timer Overflow Flag)
// PCA0PWM::COVF (Cycle Overflow Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (PCA0_ISR, PCA0_IRQn)
{
	static UU16 xpca_count;
	U16 user_timer;
	static UU16 new_duty;
	static UU16 new_cpblank_duty;
	static U8 new_polarity;

	if ( (PCA0PWM & 0x60) == 0x60 )
	{
		// PCA Cycle counter overflow interrupt - this is enabled because
		// user needs to update duty cycle of both the motor PWM and
		// the blanking PWM signal

		PCA0PWM = (PWM_RESOLUTION - 8) | 0x80;
		// protect from high priority interrupt service
		IE_EA = 0;
		PCA0POL = new_polarity;
		PCA0CN0_CCF0 = 0;
		MOTPWM_CCF = 0;
		// This clIE_EArs the ECOM bit-causing PWM output to go to inactive state
		PCA0CPL0 = new_cpblank_duty.U8[LSB];
		// This sets the ECOM bit
		PCA0CPH0 = new_cpblank_duty.U8[MSB];
		// This clIE_EArs the ECOM bit-causing PWM output to go to inactive state
		MOTPWM_PCA0CPL = new_duty.U8[LSB];
		MOTPWM_PCA0CPH = new_duty.U8[MSB];
		PCA0PWM = (PWM_RESOLUTION - 8);
		// CEX1, match flag is set
		if (MOTPWM_CCF)
		{
			xpca_count.U8[LSB] = PCA0L;
			xpca_count.U8[MSB] = PCA0H;
			// Additional hIE_EAdroom due to delays in execution
			// in case we miss the match event (toggling CEXn), we ensure that
			// postponed(+32) event occur. Otherwise, it could make 1(one) 100%
			// or 0% pwm cycle once in a while. This is happening at very low
			// or very high duty cycle when the period between pca cycle overflow
			// and match event is very short.
			xpca_count.U16 += 32;
			MOTPWM_PCA0CPL = xpca_count.U8[LSB];
			MOTPWM_PCA0CPH = xpca_count.U8[MSB];
		}
		// CEX0, match flag is set
		if (PCA0CN0_CCF0)
		{
			xpca_count.U8[LSB] = PCA0L;
			xpca_count.U8[MSB] = PCA0H;
			// Additional hIE_EAdroom due to delays in execution
			// in case we miss the match event (toggling CEXn), we ensure that
			// postponed(+32) event occur. Otherwise, it could make 1(one) 100%
			// or 0% pwm cycle once in a while. This is happening at very low
			// or very high duty cycle when the period between pca cycle overflow
			// and match event is very short.
			xpca_count.U16 += 32;
			PCA0CPL0 = xpca_count.U8[LSB];
			PCA0CPH0 = xpca_count.U8[MSB];
		}
		IE_EA = 1;
		// for application level information.
		SLW_pwm_updated = 1;
	}

	if (PCA0CN0_CF)
	{
		// Disable global interrupts to ensure coherence
		// in upper 16-bits of timer by higher priority interrupt.
		IE_EA = 0;
		PCA0CN0_CF = 0;
		user_timer++;
		IE_EA = 1;

		if( 0 == ((U8)user_timer & pid_calc_interval) )
		{
			pid_flag = 1;
		}
	}
}

//-----------------------------------------------------------------------------
// CMP1_ISR
//-----------------------------------------------------------------------------
//
// CMP1 ISR Content goes here. Remember to clear flag bits:
// CMP1CN0::CPFIF (Comparator Falling-Edge Flag)
// CMP1CN0::CPRIF (Comparator Rising-Edge Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (CMP1_ISR, CMP1_IRQn)
{

}

//-----------------------------------------------------------------------------
// TIMER3_ISR
//-----------------------------------------------------------------------------
//
// TIMER3 ISR Content goes here. Remember to clear flag bits:
// TMR3CN0::TF3H (Timer # High Byte Overflow Flag)
// TMR3CN0::TF3L (Timer # Low Byte Overflow Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (TIMER3_ISR, TIMER3_IRQn)
{

}

//-----------------------------------------------------------------------------
// TIMER1_ISR
//-----------------------------------------------------------------------------
//
// TIMER1 ISR Content goes here. Remember to clear flag bits:
// TCON::TF1 (Timer 1 Overflow Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (TIMER1_ISR, TIMER1_IRQn)
{
//-----------------------------------------------------------------------------
// Timer1_ISR - Not invoked
//-----------------------------------------------------------------------------
}


