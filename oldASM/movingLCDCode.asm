#define LCD_LIBONLY
.include "lcd.asm"


.cseg

	
ldi r22, 0
ldi r23, 0
ldi r24, 0
ldi r25, 0
call lcd_init
call lcd_clr
call init_strings

thrice:
	call SetZero
	;;;;;;;run twice?
	twice:
		call lcd_clr
		call display_strings
		call delay
		call display_strings2
		call delay
		inc r24
		cpi r24, 3
	//	call display_stringsA
		brne twice
	inc r22
	inc r23
	inc r25
	cpi r25, 4
	brne thrice

call lcd_clr
call display_stringsA
call done

done:
	rjmp done
;copy the strings from program to data memory


SetZero:
	;rowcounter
	ldi r25, 0
	ldi r26, 0
	ret

init_strings:
	push r16
	; copy strings from program memory to data memory
	ldi r16, high(msg1)		; this the destination
	push r16
	ldi r16, low(msg1)
	push r16
	ldi r16, high(msg1_p << 1) ; this is the source
	push r16
	ldi r16, low(msg1_p << 1)
	push r16
	call str_init			; copy from program to data
	pop r16					; remove the parameters from the stack
	pop r16
	pop r16
	pop r16

	ldi r16, high(msg2)
	push r16
	ldi r16, low(msg2)
	push r16
	ldi r16, high(msg2_p << 1)
	push r16
	ldi r16, low(msg2_p << 1)
	push r16
	call str_init
	pop r16
	pop r16
	pop r16
	pop r16

	pop r16
	ret




delay:
;.equ PORTB = 0x25
;.equ DDRB = 0x24
;.equ PORTL = 0x10B
;.equ DDRL = 0x10A

;	ldi r17, 0xFF		; set data direction 
;	sts DDRB, r17
;	sts DDRL, r17

;	lp:
;			ldi r19, 0b00001010
;			sts PORTB, r19
;			ldi r19, 0b10101010
;			sts PORTL, r19
;			ldi r20, 0x40
	del1:	nop
			ldi r21,0xFF
	del2:	nop
			ldi r22, 0xFF
	del3:	nop
			dec r22
			brne del3
			dec r21
			brne del2
			dec r20
			brne del1	

			ldi r19, 0x00
			sts PORTB, r19
			sts PORTL, r19

			ldi r20, 0x40
;	del1_2:	nop
;			ldi r21,0xFF
;	del2_2:	nop
;			ldi r22, 0xFF
;	del3_2:	nop
;			dec r22
	;		brne del3_2
	;		dec r21
	;		brne del2_2
	;		dec r20
	;		brne del1_2
			
;			rjmp lp
			ret

display_strings:
	//push r16
	;call lcd_clr

	ldi r16, 0x00
	push r16
	ldi r16, 0x00
	push r16
	call lcd_gotoxy
	pop r16
	pop r16

	; Now display msg1 on the first line
	ldi r16, high(msg1)
	push r16
	ldi r16, low(msg1)
	push r16
	call lcd_puts
	pop r16
	pop r16

	; Now move the cursor to the second line (ie. 0,1)
;ldi r16, 0x01
;push r16
;ldi r16, 0x00
;push r16
;call lcd_gotoxy
;pop r16
;pop r16
	call delay
	call lcd_clr
	 ;Now display msg1 on the second line
	ldi r16, high(msg2)
	push r16
	ldi r16, low(msg2)
	push r16
	call lcd_puts
	pop r16	
	pop r16
;pop r16
	ret

;display_strings2:
;push r16
;all lcd_clr

;ldi r16, 0x00
;push r16
;ldi r16, 0x00
;push r16
;call lcd_gotoxy
;pop r16
;pop r16

display_strings2:
	call lcd_clr
	; Now move the cursor to the second line (ie. 0,1)
;	ldi r16, 0x00
;	push r16
;	ldi r16, 0x00
;	push r16
;	call lcd_gotoxy
;	pop r16
;	pop r16

	ldi r16, 0x01
	push r16
	ldi r16, 0x00
	push r16
	call lcd_gotoxy
	pop r16
	pop r16

	; Now display msg1 on the first line
;	ldi r16, high(msg1)
;	push r16
;	ldi r16, low(msg1)
;	push r16
;	call lcd_puts
;	pop r16
;	pop r16
;	call lcd_clr
;	call delay

	; Now display msg1 on the second line
	ldi r16, high(msg1)
	push r16
	ldi r16, low(msg1)
	push r16
	call lcd_puts
	pop r16
	pop r16

	call delay
	call lcd_clr

	ldi r16, 0x01
	push r16
	ldi r16, 0x00
	push r16
	call lcd_gotoxy
	pop r16
	pop r16

	ldi r16, high(msg2)
	push r16
	ldi r16, low(msg2)
	push r16
	call lcd_puts
	pop r16
	pop r16
;	pop r16

;	ldi r16, high(msg1)
;	push r16
;	ldi r16, low(msg1)
;	push r16
;	call lcd_puts
;	pop r16
;	pop r16
;	call lcd_clr
;	call delay
	ret

display_stringsA:
	push r16

	call lcd_clr

	ldi r16, 0x00
	push r16
	ldi r16, 0x00
	push r16
	call lcd_gotoxy
	pop r16
	pop r16

	; Now display msg1 on the first line
	ldi r16, high(msg3)
	push r16
	ldi r16, low(msg3)
	push r16
	call lcd_puts
	pop r16
	pop r16

	call delay

	; Now move the cursor to the second line (ie. 0,1)
;	ldi r16, 0x01
;	push r16
;	ldi r16, 0x00
;	push r16
;	call lcd_gotoxy
;	pop r16
;	pop r16

	; Now display msg1 on the second line
;	ldi r16, high(msg2)
;	push r16
;	ldi r16, low(msg2)
;	push r16
;	call lcd_puts
;	pop r16
;	pop r16

;	pop r16
	ret

; sample strings
; These are in program memory
msg1_p: .db "AAAAAAA", 0
msg2_p: .db "BBBBBBB", 0
msg3_p: .db "CCCCCCC", 0
msg4_p: .db "DDDDDDD", 0

.dseg

msg1: .byte 200
msg2: .byte 200
msg3: .byte 200
msg4: .byte 200
; These strings contain the 16 characters to be displayed on the LCD
; Each time through, the 16 characters are copied into these memory locations
line1: .byte 17
line2: .byte 17
line3: .byte 17
line4: .byte 17

;
; The program copies the strings from program memory
; into data memory.
;
