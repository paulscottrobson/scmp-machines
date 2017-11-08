// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		hardware.cpp
//		Purpose:	Hardware Interface
//		Date:		1st October 2017
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include "sys_processor.h"
#include "hardware.h"
#include "gfx.h"																

#define KEY_DP 		(100)
#define KEY_EQUALS 	(101) 
#define KEY_MINUS 	(102)
#define KEY_PLUS 	(103)
#define KEY_TIMES 	(104)
#define KEY_DIVIDE 	(105)
#define KEY_C 		(106)
#define KEY_NC 		(107)
#define KEY_K 		(108)
#define KSQ_END 	(0xFF)

// *******************************************************************************************************************************
//	
//	Hardware:
//
//	Not scanning:
//		SA is zero except if keySequencePosition is not $FF, and a random 1 in 8 chance. This allows us to simulate
//		'waiting' for the start of the sequence. Once that is done we do not use SA again.
//
//	Scanning:
//		Assuming that the key is triggered by being logic '1' at some point after the start of selection - 
//		to allow for debounce to settle ?
//
//		[CSA;ANI $20;JZ <back>] SA has returned a '1'. Now in phase 1, position 0
//
//		In phase 1: 
//
//		the programmer:
//			F0 is set according to whether you want the current key pressed or not (by the user)
//
//	ON->[DLY 01] 	Simulates allowing the line to settle, switches to Phase 2.
//					Emulator: Reads F0 to see if we are faking pressing a key.
//
//		In phase 2: 
//
//			the programmer:
//				SB is now set to logic '1' if the physical key is pressed. All characters can be checked on each scan.
//				The value in F0 is 'accepted' by the calculator and the current key is pressed now and the display is updated.
//
//	ON->[DLY 02]	Simulates the delay to the next scan position.
//					Emulator: If reached the end of the table, reset keySequencePosition to $FF
//							  Else increase keySequencePosition and go to phase 1.
//
//		Go back to set F0 again. If the sequence is completed in the program clear F0.
//
//		Only one character should be entered per scantime.
//
// *******************************************************************************************************************************


static BYTE8 keySequencePosition;								// Current position in scanning sequence
static BYTE8 keyPhase;											// Phase in individual scan

																// Order in which key lines are scanned.
static char keySequence[] = {									// This is the GI CZL-550
		// These are the keys to pins 3-12, left to right.
		7,6,4,8,9,5,1,2,3,0,								
		// These are the keys to pins 14-22, top to bottom.
		KEY_DP,KEY_EQUALS,KEY_MINUS,KEY_PLUS,KEY_TIMES,KEY_DIVIDE,KEY_C,KEY_NC,KEY_K

};

// *******************************************************************************************************************************
//											Hardware Reset
// *******************************************************************************************************************************

void HWIReset(void) {
	keySequencePosition = 0xFF;
}

// *******************************************************************************************************************************
//											End of frame code.
// *******************************************************************************************************************************

void HWIEndFrame() {
}

// *******************************************************************************************************************************
//						 Read current digit for a given digit (0 = right most)
// *******************************************************************************************************************************

BYTE8 HWIGetDisplayDigit(BYTE8 digit) {
	return (digit & 1) ? digit : digit+16;
}
