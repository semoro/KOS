.global floor
.type floor, @function

floor:
    fldt	8(%rsp)

    fstcw	-4(%rsp)		/* store fpu control word */

    /* We use here %edx although only the low 1 bits are defined.
        But none of the operations should care and they are faster
        than the 16 bit operations.  */
    movl	$0x400,%edx		/* round towards -oo */
    orl	-4(%rsp),%edx
    andl	$0xf7ff,%edx
    movl	%edx,-8(%rsp)
    fldcw	-8(%rsp)		/* load modified control word */

    frndint				/* round */

    fldcw	-4(%rsp)		/* restore original control word */

    ret 
