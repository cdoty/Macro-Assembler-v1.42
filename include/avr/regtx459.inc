		ifndef	__regt459inc
__regtx459inc	equ	1
                save
                listing off   ; kein Listing ueber diesen File

;****************************************************************************
;*                                                                          *
;*   AS 1.42 - File REGTX459.INC                                            *
;*                                                                          *
;*   Contains Bit & Register Definitions for ATtiny4/5/9/10                 *
;*                                                                          *
;****************************************************************************

;----------------------------------------------------------------------------
; Chip Configuration

VLMCSR		port	0x34		; VCC Level Monitoring Control and Status Register
VLM0		avrbit	VLMCSR,0	; Trigger Level of Voltage Level Monitor
VLM1		avrbit	VLMCSR,1
VLM2		avrbit	VLMCSR,2
VLMIE		avrbit	VLMCSR,6	; VLM Interrupt Enable
VLMF		avrbit	VLMCSR,7	; VLM Flag

RSTFLR		port	0x3b		; Reset Flag Register
WDRF		avrbit	RSTFLR,3	; Watchdog Reset Flag
EXTRF		avrbit	RSTFLR,1	; External Reset Flag
PORF		avrbit	RSTFLR,0	; Power-on Reset Flag

OSCCAL		port	0x39		; Oscillator Calibration

CLKPSR		port	0x36		; Clock Prescaler Register
CLKPS0		avrbit	CLKPSR,0	; Clock Prescaler Select
CLKPS1		avrbit	CLKPSR,1
CLKPS2		avrbit	CLKPSR,2

CLKMSR		port	0x37		; Clock Main Settings Register
CLKMS0		avrbit	CLKMSR,0	; Clock Main Select Bits
CLKMS1		avrbit	CLKMSR,1

SMCR		port	0x3a		; Sleep Mode Control Register
SE		avrbit	SMCR,0		; Sleep Mode Enable
SM0		avrbit	SMCR,1		; Sleep Mode Select
SM1		avrbit	SMCR,2
SM2		avrbit	SMCR,3

PRR		port	0x35		; Power Reduction Register
PRTIM0		avrbit	PRR,0		; Power Reduction Timer/Counter 0
		if	__HAS_ADC__
PRADC		 avrbit	PRR,1		; Power Reduction A/D Converter
		endif

CCP		port	0x3c		; Configuration Change Protection Register

;----------------------------------------------------------------------------
; EEPROM/Flash Access

NVMCSR		port	0x32		; Non-Volatile Memory Control and Status Register
NVMBSY		avrbit	NVMCSR,7	; Non-Volatile Memory Busy

NVMCMD		port	0x33		; Non-Volatile Memory Command Register
NVMCMD0		avrbit	NVMCMD,0	; Non-Volatile Memory Command
NVMCMD1		avrbit	NVMCMD,1
NVMCMD2		avrbit	NVMCMD,2
NVMCMD3		avrbit	NVMCMD,3
NVMCMD4		avrbit	NVMCMD,4
NVMCMD5		avrbit	NVMCMD,5

;----------------------------------------------------------------------------
; GPIO

PINB		port	0x00		; Port B @ 0x00 (IO) ff.
__PORTB_BITS	equ	0x0f		; (bits 0..3)
PUEB		port	0x03		; Pull-Up Enable Port B
PUEB0		avrbit	PUEB,0
PUEB1		avrbit	PUEB,1
PUEB2		avrbit	PUEB,2
PUEB3		avrbit	PUEB,3

PCMSK		port	0x10		; Pin-Change Mask Register
PCINT0		avrbit	PCMSK,0		; Enable Pin-Change Interrupt 0
PCINT1		avrbit	PCMSK,1		; Enable Pin-Change Interrupt 1
PCINT2		avrbit	PCMSK,2		; Enable Pin-Change Interrupt 2
PCINT3		avrbit	PCMSK,3		; Enable Pin-Change Interrupt 3

PORTCR		port	0x0c		; Port Control Register
BBMB		avrbit	PORTCR,1	; Break-Before-Make Mode Enable

PCICR		port	0x12		; Pin-Change Interrupt Control Register
PCIE0		avrbit	PCICR,0		; Enable Pin-Change Interrupt 0

PCIFR		port	0x11		; Pin-Change Interrupt Flag Register
PCIF0		avrbit	PCIFR,0		; Pin-Change Interrupt 0 Occured

;----------------------------------------------------------------------------
; Interrupt Vectors

		enumconf 1,code
		enum	 INT0_vect=1		; External Interrupt Request 0
		nextenum PCINT0_vect		; Pin Change Interrupt 0
		nextenum TIM0_CAPT_vect		; Timer/Counter 0 Capture
		nextenum TIM0_OVF_vect		; Timer/Counter 0 Overflow
		nextenum TIM0_COMPA_vect	; Timer/Counter 0 Compare Match 1A
		nextenum TIM0_COMPB_vect	; Timer/Counter 0 Compare Match 1B
		nextenum ANA_COMP_vect		; Analog Comparator
		nextenum WDT_vect		; Watchdog Time-out Interrupt
		nextenum VLM_vect		; VCC Voltage Level Monitor
                if      __HAS_ADC__
		 nextenum ADC_vect		; ADC Conversion Complete
		endif

;----------------------------------------------------------------------------
; External Interrupts

EICRA		port	0x15		; External Interrupt Control Register A
ISC00		avrbit	EICRA,0		; Interrupt Sense Control 0
ISC01		avrbit	EICRA,1

EIMSK		port	0x13		; External Interrupt Mask Register
INT0		avrbit	EIMSK,6		; Enable External Interrupt 0

EIFR		port	0x14		; External Interrupt Flag Register
INTF0		avrbit	EIFR,6		; External Interrupt 0 Occured

;----------------------------------------------------------------------------
; Timers

TCCR0A		port	0x2e		; Timer/Counter 0 Control Register A
WGM00		avrbit	TCCR0A,0	; Timer/Tounter 0 Waveform Generation Mode
WGM01		avrbit	TCCR0A,1
COM0B0		avrbit	TCCR0A,4	; Timer/Counter 0 Output Compare Mode B
COM0B1		avrbit	TCCR0A,5
COM0A0		avrbit	TCCR0A,6	; Timer/Counter 0 Output Compare Mode A
COM0A1		avrbit	TCCR0A,7
TCCR0B		port	0x2d		; Timer/Counter 0 Control Register B
CS00            avrbit	TCCR0B,0	; Timer/Counter 0 Clock Select
CS01            avrbit	TCCR0B,1
CS02            avrbit	TCCR0B,2
WGM02		avrbit	TCCR0B,3
WGM03		avrbit	TCCR0B,4
ICES0		avrbit	TCCR0B,6	; Timer/Counter 0 Input Capture Edge Select
CTC0		avrbit	TCCR0B,7	; Timer/Counter 0 Clean on Match
TCCR0C		port	0x2c		; Timer/Counter 0 Control Register C
FOC0B		avrbit	TCCR0C,6	; Timer/Counter 0 Force Output Compare Match B
FOC0A		avrbit	TCCR0C,7	; Timer/Counter 0 Force Output Compare Match A
TCNT0L		port	0x28		; Timer/Counter 0 Value LSB
TCNT0H		port	0x29		; Timer/Counter 0 Value MSB
OCR0AL		port	0x26		; Timer/Counter 0 Output Compare Value A LSB
OCR0AH		port	0x27		; Timer/Counter 0 Output Compare Value A MSB
OCR0BL		port	0x24		; Timer/Counter 0 Output Compare Value B LSB
OCR0BH		port	0x25		; Timer/Counter 0 Output Compare Value B MSB
ICR0L		port	0x22		; Timer/Counter 0 Input Capture Register LSB
ICR0H		port	0x23		; Timer/Counter 0 Input Capture Register MSB

TIMSK0		port	0x2b		; Timer/Counter 0 Interrupt Mask Register
TOIE0		avrbit	TIMSK0,0	; Timer/Counter 0 Overflow Interrupt Enable
OCIE0A		avrbit	TIMSK0,1	; Timer/Counter 0 Output Compare Interrupt Enable A
OCIE0B		avrbit	TIMSK0,2	; Timer/Counter 0 Output Compare Interrupt Enable B
ICIE0		avrbit	TIMSK0,5	; Timer/Counter 0 Input Capture Interrupt Enable

TIFR0		port	0x2a		; Timer/Counter 0 Interrupt Status Register

GTCCR		port	0x2f		; General Timer/Counter Control Register
PSR		avrbit	GTCCR,0		; Prescaler 0 Reset Timer/Counter 0
TSM		avrbit	GTCCR,7		; Timer/Counter Synchronization Mode

;----------------------------------------------------------------------------
; Watchdog Timer

WDTCSR		port	0x31		; Watchdog Control/Status Register
WDP0		avrbit	WDTCSR,0	; Prescaler
WDP1		avrbit	WDTCSR,1
WDP2		avrbit	WDTCSR,2
WDE		avrbit	WDTCSR,3	; Enable watchdog
WDP3		avrbit	WDTCSR,5
WDIE		avrbit	WDTCSR,6	; Watchdog Interrupt Enable
WDIF		avrbit	WDTCSR,7	; Watchdog Interrupt Flag

;----------------------------------------------------------------------------
; Analog Comparator

ACSR		port    0x1f		; Analog Comparator Control and Status Register
ACIS0		avrbit	ACSR,0		; Interrupt-Mode
ACIS1		avrbit	ACSR,1
ACIC		avrbit	ACSR,2		; Use Comparator As Capture Signal For Timer 0?
ACIE		avrbit	ACSR,3		; Interrupt Enable
ACI		avrbit	ACSR,4		; Interrupt Flag
ACO		avrbit	ACSR,5		; Analog Comparator Output
ACD		avrbit	ACSR,7		; Disable

;----------------------------------------------------------------------------
; A/D Converter

		if	__HAS_ADC__

ADMUX		port	0x1b		; ADC Multiplexer Selection Register
MUX1		avrbit	ADMUX,1		; Analog Channel Selection
MUX0		avrbit	ADMUX,0

ADCSRA		port	0x1d		; ADC Control/Status Register A
ADEN		avrbit	ADCSRA,7	; Enable ADC
ADSC		avrbit	ADCSRA,6	; Start Conversion
ADATE		avrbit	ADCSRA,5	; ADC Auto Trigger Enable
ADIF		avrbit	ADCSRA,4	; Interrupt Flag
ADIE		avrbit	ADCSRA,3	; Interrupt Enable
ADPS2		avrbit	ADCSRA,2	; Prescaler Select
ADPS1		avrbit	ADCSRA,1
ADPS0		avrbit	ADCSRA,0

ADCSRB		port	0x1c		; ADC Control/Status Register A
ADTS0		avrbit	ADCSRB,0	; ADC Auto Trigger Source
ADTS1		avrbit	ADCSRB,1
ADTS2		avrbit	ADCSRB,2

ADCL		port	0x19		; ADC Conversion Result Low Byte

DIDR0		port	0x17		; Digital Input Disable Register 0
ADC0D		avrbit	DIDR0,0		; ADC0 Digital Input Disable
ADC1D		avrbit	DIDR0,1		; ADC1 Digital Input Disable
ADC2D		avrbit	DIDR0,2		; ADC2 Digital Input Disable
ADC3D		avrbit	DIDR0,3		; ADC3 Digital Input Disable

		endif

		restore

		endif			; __regtx459inc
