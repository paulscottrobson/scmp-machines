// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		rendering.h
//		Purpose:	CPU debug rendering includes [WILLIAMSON]
//		Date:		1st October 2017
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

for (int i = 0;i < 8;i++) {
	DBGXDigit(GRID(19+i*2,11),GRIDSIZE*6*2,GRIDSIZE*8*2,HWIGetDisplayDigit(7-i));
}
