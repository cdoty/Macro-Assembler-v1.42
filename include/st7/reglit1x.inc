		ifndef	__reglit1xinc	; avoid multiple inclusion
__reglit1xinc	equ	1

		save
		listing	off		; no listing over this file

;****************************************************************************
;*                                                                          *
;*   AS 1.42 - File REGLIT1X.INC                                            *
;*                                                                          *
;*   contains SFR and Bit Definitions for ST7LITE1x                         *
;*                                                                          *
;*   Source: ST7LITE1 Data Sheet, Rev. 2.0, December 2004                   *
;*                                                                          *
;****************************************************************************

;----------------------------------------------------------------------------
; Memory Addresses

RAMSTART	label	$0080		; Start Address Internal RAM
					; ($100...$17f not occupied)
RAMEND		label	$01ff		; End     "        "      "

                switch  SUBSTR(MOMCPUNAME,STRLEN(MOMCPUNAME)-3,1)
                case	"0","5"
		case	"9"
EESTART		label  $1000		; Start Address Internal EEPROM
EEEND		label  $107f		; End     "        "      "
		endcase

RCCR0		label	$1000		; RC Oscillator Calibration Values
RCCR1		label	$1001

;----------------------------------------------------------------------------
; Interrupt Vectors

SPI_vect	label	$ffe2		; SPI Interrupt
LT_RTC1_vect	label	$ffe4		; Lite Timer RTC1 Interrupt
LT_IC_vect	label	$ffe6		; Lite Timer Input Capture Interrupt
AT_OF1_vect	label	$ffe8		; AT Timer Overflow 1 Interrupt
AT_OC_vect	label	$ffea		; AT Timer Output Compare Interrupt, shared with...
AT_IC_vect	label	$ffea		; AT Timer Input Capture Interrupt
SI_vect		label	$ffec		; AVD Interrupt
LT_RTC2_vect	label	$fff0		; LITE TIMER RTC2 interrupt
EI3_vect	label	$fff2		; External Interrupt Vector EI3
EI2_vect	label	$fff4		; External Interrupt Vector EI2
EI1_vect	label	$fff6		; External Interrupt Vector EI1
EI0_vect	label	$fff8		; External Interrupt Vector EI0
AWU_vect	label	$fffa		; Auto Wakeup Interrupt Vector
TRAP_vect	label	$fffc		; TRAP (software) Interrupt Vector
RESET_vect	label	$fffe		; RESET Vector

;----------------------------------------------------------------------------
; GPIO

		include	"gpio.inc"
		__defgpio "PA",$0000
		__defgpio "PB",$0003

;----------------------------------------------------------------------------
; Lite Timer

LTCSR2		label	$0008		; Lite Timer Control/Status Register 2
TB2IE		bit	LTCSR2,1	;  Timebase 2 Interrupt Enable Bit
TB2F		bit	LTCSR2,0	;  Timebase 2 Interrupt Flag
LTARR		label	$0009		; Lite Timer Auto-reload Register
LTCNTR		label	$000a		; Lite Timer Counter Register
LTCSR1		label	$000b		; Lite Timer Control/Status Register 1
TBICIE		bit	LTCSR1,7	;  Interrupt Enable Bit
TBICF		bit	LTCSR1,6	;  Input Capture Flag
TB		bit	LTCSR1,5	;  Timebase Period Selection Bit
TB1IE		bit	LTCSR1,4	;  Timebase Interrupt Enable Bit
TB1F		bit	LTCSR1,3	;  Timebase Interrupt Flag
LTICR		label	$000c		; Lite Timer Input Capture Register

;----------------------------------------------------------------------------
; Auto-Reload Timer

ATCSR		label	$000d		; Timer Control/Status Register
ICF		bit	ATCSR,6		;  Input Capture flag
ICIE		bit	ATCSR,5		;  IC Interrupt Enable bit
CK		bfield	ATCSR,3,2	;  Counter Clock Selection
OVF1		bit	ATCSR,2		;  Overflow flag
OVFIE1		bit	ATCSR,1		;  Overflow Interrupt Enable bit
ATCMPIE		bit	ATCSR,0		;  Compare Interrupt Enable bit
CNTRH		label	$000e		; Counter Register High
CNTRL		label	$000f		; Counter Register Low
ATRH		label	$0010		; Auto-Reload Register 1 High
ATRL		label	$0011		; Auto-Reload Register 1 Low
PWMCR		label	$0012		; PWM Output Control Register
OE3		bit	PWMCR,6		;  PWM3 Output Enable
OE2		bit	PWMCR,4		;  PWM2 Output Enable
OE1		bit	PWMCR,2		;  PWM1 Output Enable
OE0		bit	PWMCR,0		;  PWM0 Output Enable
PWM0CSR		label	$0013		; PWM 0 Control/Status Register
OP0		bit	PWM0CSR,1	;  PWM0 Output Polarity Bit
CMPF0		bit	PWM0CSR,0	;  PWM0 Compare Flag
PWM1CSR		label	$0014		; PWM 1 Control/Status Register
OP1		bit	PWM1CSR,1	;  PWM1 Output Polarity Bit
CMPF1		bit	PWM1CSR,0	;  PWM1 Compare Flag
PWM2CSR		label	$0015		; PWM 2 Control/Status Register
OP2		bit	PWM2CSR,1	;  PWM2 Output Polarity Bit
CMPF2		bit	PWM2CSR,0	;  PWM2 Compare Flag
PWM3CSR		label	$0016		; PWM 3 Control/Status Register
OP_EN		bit	PWM3CSR,3	;  One Pulse Mode Enable Bit
OPEDGE		bit	PWM3CSR,2	;  One Pulse Edge Selection Bit
OP3		bit	PWM3CSR,1	;  PWM3 Output Polarity Bit
CMPF3		bit	PWM3CSR,0	;  PWM3 Compare Flag
DCR0H		label	$0017		; PWM 0 Duty Cycle Register High
DCR0L		label	$0018		; PWM 0 Duty Cycle Register Low
DCR1H		label	$0019		; PWM 1 Duty Cycle Register High
DCR1L		label	$001a		; PWM 1 Duty Cycle Register Low
DCR2H		label	$001b		; PWM 2 Duty Cycle Register High
DCR2L		label	$001c		; PWM 2 Duty Cycle Register Low
DCR3H		label	$001d		; PWM 3 Duty Cycle Register High
DCR3L		label	$001e		; PWM 3 Duty Cycle Register Low
ATICRH		label	$001f		; Input Capture Register High
ATICRL		label	$0020		; Input Capture Register Low
TRANCR		label	$0021		; Transfer Control Register
TRAN		bit	TRANCR,0	;  Transfer enable
BREAKCR		label	$0022		; Break Control Register
PWM		bfield	BREAKCR,0,4	;  Break Pattern bits
BA		bit	BREAKCR,5	;  Break Active
BPEN		bit	BREAKCR,4	;  Break Pin Enable

;----------------------------------------------------------------------------
; Watchdog

WDGCR		label	$002e		; Watchdog Control Register
WDGA		bit	WDGCR,7		; Activation bit

;----------------------------------------------------------------------------
; Flash

FCSR		label	$002f		; Flash Control/Status Register

;----------------------------------------------------------------------------
; EEPROM

		ifdef EESTART
EECSR		label	$0030		; Data EEPROM Control/Status Register
E2LAT		bit	EECSR,1		;  Latch Access Transfer
E2PGM		bit	EECSR,0		;  Programming control and status
		endif

;----------------------------------------------------------------------------
; SPI

		include	"spi2.inc"
		__defspi $0031

;----------------------------------------------------------------------------
; Analog/Digital Converter

		include	"adc10.inc"
		__defadc10 $0034

;----------------------------------------------------------------------------
; ITC

EICR		label	$0037		; External Interrupt Control Register
IS3		bfield	EICR,6,2	;  ei3 Sensitivity
IS2		bfield	EICR,4,2	;  ei2 Sensitivity
IS1		bfield	EICR,2,2	;  ei1 Sensitivity
IS0		bfield	EICR,0,2	;  ei0 Sensitivity
EISR		label	$003c		; External Interrupt Selection Register
EI3		bfield	EISR,6,2	;  ei3 Pin Selection
EI2		bfield	EISR,4,2	;  ei2 Pin Selection
EI1		bfield	EISR,2,2	;  ei1 Pin Selection
EI0		bfield	EISR,0,2	;  ei0 Pin Selection

;----------------------------------------------------------------------------
; MCC

MCCSR		label	$0038		; Main Clock Control / Status Register
MCO		bit	MCCSR,1		;  Main Clock Out Enable Bit
SMS		bit	MCCSR,0		;  Slow Mode Selection Bit

;----------------------------------------------------------------------------
; RC Calibration

RCCR		label	$0039		; RC Calibration Control/Status Register
SICSR		label	$003a		; System Integrity Control/Status Register
LOCK32		bit	SICSR,7		;  PLL 32Mhz Locked Flag
WDGRF		bit	SICSR,4		;  Watchdog Reset Flag
LOCKED		bit	SICSR,3		;  PLL Locked Flag
LVDRF		bit	SICSR,2		;  LVD Reset Flag
AVDF		bit	SICSR,1		;  Voltage Detector Flag
AVDIE		bit	SICSR,0		;  Voltage Detector Interrupt Enable

;----------------------------------------------------------------------------
; Auto Wakeup Unit

AWUPR		label	$0049		; AWU Preload Register
AWUCSR		label	$004a		; AWU Control/Status Register
AWUF		bit	AWUCSR,2	;  Auto Wakeup Flag
AWUM		bit	AWUCSR,1	;  Auto Wakeup Measurement Bit
AWUEN		bit	AWUCSR,0	;  Auto Wakeup From Halt Enabled Bit

;----------------------------------------------------------------------------
; Debug Module

		include	"dm.inc"
		__defdm	$004b

		restore
		endif			; __reglit1xinc
