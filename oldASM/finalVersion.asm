;;Soroush Hajizadeh
;; CSC 230 Assignment 3 programming



#define LCD_LIBONLY
.include "lcd.asm"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		; initialize the Analog to Digital conversion



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.cseg


init:
	ldi r17, 0x87
	sts 0x7A, r17
	ldi r17, 0x40
	sts 0x7C, r17


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ldi r24, 0
ldi r25, 0
call lcd_init
call lcd_clr
call init_strings

thrice: 
	inc r25
	call SetZero
	twice:
		inc r24
		call lcd_clr
		call display_strings
		call delay
		call display_strings2
		call delay
		cpi r24, 3
		brne twice
	cpi r25, 4
	breq end

end:
	call lcd_clr
	call LastString
	call lcd_clr
	call done

done:
	jmp done



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

	ldi r16, high(msg3)
	push r16
	ldi r16, low(msg3)
	push r16
	ldi r16, high(msg3_p << 1)
	push r16
	ldi r16, low(msg3_p << 1)
	push r16
	call str_init
	pop r16
	pop r16
	pop r16
	pop r16

	pop r16
	ret

check_button:
		; start a2d
		lds	r17, 0x7A
		ori r17, 0x40
		sts	0x7A, r17

wait:	lds r17, 0x7A
		andi r17, 0x40
		brne wait

		; read the value
		lds r17, 0x78
		lds r18, 0x79

		clr r27

		cpi r18, 0
		brne skip
		
		call delay2
		ldi r27,1
skip:	ret

delay:
	ldi r20, 0x20
	call check_button
	cpi r27, 1
	breq delay2

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
			ret



delay2:
;	cpi r17,1
;	breq returner
	cpi r18,0

;	call check_button
	
	
	ret
	
;	ldi r20, 0x50
;
;	del12:	nop
;			ldi r21,0xFF
;	del22:	nop
;			ldi r22, 0xFF
;	del32:	nop
;			dec r22
;			brne del3
;			dec r21
;			brne del2
;			dec r20
;			brne del1	
;			ret
;
;	call check_button
;	cpi r17,0
;	breq delay2




display_strings:

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
	ldi r16, 0x01
	push r16
	call lcd_gotoxy
	pop r16
	pop r16

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
	ldi r16, 0x01
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

	ret

LastString:
	push r16

	call lcd_clr

	ldi r16, 0x08
	push r16
	ldi r16, 0x08
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
	call lcd_clr
	call delay

	ldi r16, 0x08
	push r16
	ldi r16, 0x08
	push r16
	call lcd_gotoxy
	pop r16
	pop r16

	ldi r16, high(msg3)
	push r16
	ldi r16, low(msg3)
	push r16
	call lcd_puts
	pop r16
	pop r16

	call delay
	call lcd_clr
	call delay

	ldi r16, 0x08
	push r16
	ldi r16, 0x08
	push r16
	call lcd_gotoxy
	pop r16
	pop r16

	ldi r16, high(msg3)
	push r16
	ldi r16, low(msg3)
	push r16
	call lcd_puts
	pop r16
	pop r16
	
	call delay
	call lcd_clr

	call lcd_clr
	ret




; sample strings
; These are in program memory
msg1_p: .db "Fiona H. Albioni", 0
msg2_p: .db "CSC 230 Student!", 0
msg3_p: .db "A", 0


.dseg

msg1: .byte 200
msg2: .byte 200
msg3: .byte 200

; These strings contain the 16 characters to be displayed on the LCD
; Each time through, the 16 characters are copied into these memory locations
line1: .byte 17
line2: .byte 17
line3: .byte 17


