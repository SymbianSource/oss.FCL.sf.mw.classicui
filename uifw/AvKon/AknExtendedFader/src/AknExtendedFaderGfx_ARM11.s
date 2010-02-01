;
; Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
; All rights reserved.
; This component and the accompanying materials are made available
; under the terms of "Eclipse Public License v1.0"
; which accompanies this distribution, and is available
; at the URL "http://www.eclipse.org/legal/epl-v10.html".
;
; Initial Contributors:
; Nokia Corporation - initial contribution.
;
; Contributors:
;
; Description:
;

; A macro for transparently defining ARM functions with THUMB calling conventions.
		MACRO
$func	Entry
		AREA Entry_$func, CODE
		GLOBAL $func
		ALIGN 2
		CODE16
$func
		bx		pc		; go to ARM mode
		nop
		CODE32
		MEND


		; Trashes $temp, result is in $pixel
		MACRO 
$label	Pixel_GrayColorize_16MX $pixel, $rbCoef, $gCoef, $fadeMapFactor, $fadeMapOffset, $rbOverlay, $gOverlay, $temp
$label		
		; Separate RB (temp = pixel & 0x00FF00FF)
		bic $temp, $pixel, #0xFF000000      ; temp = pixel & 0x00FFFFFF
		bic $temp, $temp, #0x0000FF00       ; temp = pixel & 0x00FF00FF
		
		; Separate G
		uxtb $pixel, $pixel, ror #8         ; pixel = (pixel & 0x0000FF00) >> 8);
		
		; Calculate unadjusted grayscale intensity
		smuad $temp, $temp, $rbCoef             ; temp = r*rCoef + b*bCoef;
		smlabb $pixel, $pixel, $gCoef, $temp    ; pixel = g*gCoef + temp
		
		; Do fading and adjustment (aFadeMapOffset is already shifted left 18 bits so we can do single accumulating mul)
		mla $pixel, $pixel, $fadeMapFactor, $fadeMapOffset   ; pixel = pixel * fadeMapFactor + fadeMapOffset
		mov $pixel, $pixel, lsr #18                          ; pixel = pixel >> 18
		and $pixel, $pixel, #0x000000ff                      ; pixel &= 0x000000ff
		
		; Calculate final AXGX
		mul $temp, $pixel, $gOverlay       ; g = pixel * gOverlay
		and $temp, $temp, #0x0000FF00        ; g &= 0x0000FF00
		orr $temp, $temp, #0xFF000000        ; g |= 0xFF000000
		
		; Calculate final RXBX
		mul $pixel, $rbOverlay, $pixel        ; pixel = r*rOverlay | b*bOverlay
		bic $pixel, $pixel, #0x00FF0000       ; pixel &= 0xFF00FF00
		bic $pixel, $pixel, #0x000000FF
	
		; Combine A,G with R,B
		orr $pixel, $temp, $pixel, LSR #8  ; pixel = ag | (rb>>8);

		MEND
	
;----------------------
; FadeAlignedRect_GrayColorize_16MX
;
; Param: address        Scanline start address              (r0)
; Param: height         Number of scanlines                 (r1)
; Param: rbCoef         R&B coefficients as a 16x16         (r2)
; Param: gCoef          G coefficient                       (r3)
; Param: fadeMapFactor  Fade map factor                     (s0 -> r4)
; Param: fadeMapOffset  Fade map offset                     (s1 -> r5)
; Param: rbOverlay      R&B overlay as 0x00RR00BB           (s2 -> r6)
; Param: gOverlay       G overlay as 0x000000GG             (s3 -> r7)
; Param: leftwidth      Number of unaligned pixels on left  (s4)
; Param: middlewidth    Number of aligned sections          (s5)
; Param: rightwidth     Number of unaligned pixels on right (s6)
; Param: padding        Extra pixels on scanline			(s7)
;----------------------

FadeAlignedRect_GrayColorize_16MX Entry
	ARM	
		; Push registers to stack
		PUSH { r4-r12, r14 }
		
		; Read the commonly needed values from stack
		add		r8, sp, #10 * 4
		ldmia	r8, {r4-r7}
		
		mov r14, r1
		
yloop_start
		;while(--height>=0)
		subs r14, r14, #1
		bmi yloop_end
			
		; x = leftwidth	
		add r1, sp, #14 * 4
		ldr r1, [r1]
		
		; Left unaligned section processing
xloop_left_start
		subs r1, r1, #1
		bmi xloop_left_end
		
		; Load pixel
		ldr r8, [r0]
		
		; Process pixel
		Pixel_GrayColorize_16MX r8, r2, r3, r4, r5, r6, r7, r12
		
		; Write pixel
		str r8, [r0], #4
		
		; Loop
		b xloop_left_start
xloop_left_end


		; x = middlewidth	
		add r1, sp, #15 * 4
		ldr r1, [r1]
		
		; Aligned section processing		
xloop_middle_start
		subs r1, r1, #1
		bmi xloop_middle_end
		
		; Load 4 pixels straight-away
		ldmia r0, {r8-r11}
		
		; Hint cache about preloading next 8 pixels
		pld [r0, #32]
		
		; Process the first four pixels
		Pixel_GrayColorize_16MX r8, r2, r3, r4, r5, r6, r7, r12
		Pixel_GrayColorize_16MX r9, r2, r3, r4, r5, r6, r7, r12
		Pixel_GrayColorize_16MX r10, r2, r3, r4, r5, r6, r7, r12
		Pixel_GrayColorize_16MX r11, r2, r3, r4, r5, r6, r7, r12
		
		; Store four pixels
		stmia r0!, {r8-r11}
		
		; Load next four
		ldmia r0, {r8-r11}
		
		; Process the next four pixels
		Pixel_GrayColorize_16MX r8, r2, r3, r4, r5, r6, r7, r12
		Pixel_GrayColorize_16MX r9, r2, r3, r4, r5, r6, r7, r12
		Pixel_GrayColorize_16MX r10, r2, r3, r4, r5, r6, r7, r12
		Pixel_GrayColorize_16MX r11, r2, r3, r4, r5, r6, r7, r12
		
		; Store four pixels
		stmia r0!, {r8-r11}
	
		; Loop
		b xloop_middle_start
xloop_middle_end

		; x = rightwidth	
		add r1, sp, #16 * 4
		ldr r1, [r1]

xloop_right_start
		subs r1, r1, #1
		bmi xloop_right_end
		
		; Load pixel
		ldr r8, [r0]
		
		; Process pixel
		Pixel_GrayColorize_16MX r8, r2, r3, r4, r5, r6, r7, r12
		
		; Write pixel
		str r8, [r0], #4
		
		b xloop_right_start
xloop_right_end
		
		; data += padding
		add r1, sp, #17 * 4
		ldr r1, [r1]
		add r0, r0, r1
		
		b yloop_start
yloop_end

		POP { r4-r12, r14 }
		
		bx lr
	END

