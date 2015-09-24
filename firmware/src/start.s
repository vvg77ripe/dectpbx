
.global asm_set_ipl
.global asm_wr_flashbar
.global asm_cache_enable

.extern __SP_INIT
.extern main
.extern irq_handler


.text

VECTOR_TABLE:
INITSP:		.long	__SP_INIT
INITPC:		.long	start
vector02:	.long	asm_exception_handler	/* Access Error			*/
vector03:	.long	asm_exception_handler	/* Address Error		*/
vector04:	.long	asm_exception_handler	/* Illegal Instruction	*/
vector05:	.long	asm_exception_handler	/* Reserved				*/
vector06:	.long	asm_exception_handler	/* Reserved				*/
vector07:	.long	asm_exception_handler	/* Reserved				*/
vector08:	.long	asm_exception_handler	/* Privilege Violation	*/
vector09:	.long	asm_exception_handler	/* Trace				*/
vector0A:	.long	asm_exception_handler	/* Unimplemented A-Line	*/
vector0B:	.long	asm_exception_handler	/* Unimplemented F-Line	*/
vector0C:	.long	asm_exception_handler	/* Debug Interrupt		*/
vector0D:	.long	asm_exception_handler	/* Reserved				*/
vector0E:	.long	asm_exception_handler	/* Format Error			*/
vector0F:	.long	asm_exception_handler	/* Unitialized Int.		*/
vector10:	.long	asm_exception_handler	/* Reserved				*/
vector11:	.long	asm_exception_handler	/* Reserved				*/
vector12:	.long	asm_exception_handler	/* Reserved				*/
vector13:	.long	asm_exception_handler	/* Reserved				*/
vector14:	.long	asm_exception_handler	/* Reserved				*/
vector15:	.long	asm_exception_handler	/* Reserved				*/
vector16:	.long	asm_exception_handler	/* Reserved				*/
vector17:	.long	asm_exception_handler	/* Reserved				*/
vector18:	.long	asm_exception_handler	/* Spurious Interrupt	*/
vector19:	.long	irq_handler		/* Autovector Level 1	*/
vector1A:	.long	irq_handler		/* Autovector Level 2	*/
vector1B:	.long	irq_handler		/* Autovector Level 3	*/
vector1C:	.long	irq_handler		/* Autovector Level 4	*/
vector1D:	.long	irq_handler		/* Autovector Level 5	*/
vector1E:	.long	irq_handler		/* Autovector Level 6	*/
vector1F:	.long	irq_handler		/* Autovector Level 7	*/
vector20:	.long	asm_exception_handler	/* TRAP #0				*/
vector21:	.long	asm_exception_handler	/* TRAP #1				*/
vector22:	.long	asm_exception_handler	/* TRAP #2				*/
vector23:	.long	asm_exception_handler	/* TRAP #3				*/
vector24:	.long	asm_exception_handler	/* TRAP #4				*/
vector25:	.long	asm_exception_handler	/* TRAP #5				*/
vector26:	.long	asm_exception_handler	/* TRAP #6				*/
vector27:	.long	asm_exception_handler	/* TRAP #7				*/
vector28:	.long	asm_exception_handler	/* TRAP #8				*/
vector29:	.long	asm_exception_handler	/* TRAP #9				*/
vector2A:	.long	asm_exception_handler	/* TRAP #10				*/
vector2B:	.long	asm_exception_handler	/* TRAP #11				*/
vector2C:	.long	asm_exception_handler	/* TRAP #12				*/
vector2D:	.long	asm_exception_handler	/* TRAP #13				*/
vector2E:	.long	asm_exception_handler	/* TRAP #14				*/
vector2F:	.long	asm_exception_handler	/* TRAP #15				*/
vector30:	.long	asm_exception_handler	/* Reserved				*/
vector31:	.long	asm_exception_handler	/* Reserved				*/
vector32:	.long	asm_exception_handler	/* Reserved				*/
vector33:	.long	asm_exception_handler	/* Reserved				*/
vector34:	.long	asm_exception_handler	/* Reserved				*/
vector35:	.long	asm_exception_handler	/* Reserved				*/
vector36:	.long	asm_exception_handler	/* Reserved				*/
vector37:	.long	asm_exception_handler	/* Reserved				*/
vector38:	.long	asm_exception_handler	/* Reserved				*/
vector39:	.long	asm_exception_handler	/* Reserved				*/
vector3A:	.long	asm_exception_handler	/* Reserved				*/
vector3B:	.long	asm_exception_handler	/* Reserved				*/
vector3C:	.long	asm_exception_handler	/* Reserved				*/
vector3D:	.long	asm_exception_handler	/* Reserved				*/
vector3E:	.long	asm_exception_handler	/* Reserved				*/
vector3F:	.long	asm_exception_handler	/* Reserved				*/
vector40:	.long	irq_handler
vector41:	.long	irq_handler
vector42:	.long	irq_handler
vector43:	.long	irq_handler
vector44:	.long	irq_handler
vector45:	.long	irq_handler
vector46:	.long	irq_handler
vector47:	.long	irq_handler
vector48:	.long	irq_handler
vector49:	.long	irq_handler
vector4A:	.long	irq_handler
vector4B:	.long	irq_handler
vector4C:	.long	irq_handler
vector4D:	.long	irq_handler
vector4E:	.long	irq_handler
vector4F:	.long	irq_handler
vector50:	.long	irq_handler
vector51:	.long	irq_handler
vector52:	.long	irq_handler
vector53:	.long	irq_handler
vector54:	.long	irq_handler
vector55:	.long	irq_handler
vector56:	.long	irq_handler
vector57:	.long	irq_handler
vector58:	.long	irq_handler
vector59:	.long	irq_handler
vector5A:	.long	irq_handler
vector5B:	.long	irq_handler
vector5C:	.long	irq_handler
vector5D:	.long	irq_handler
vector5E:	.long	irq_handler
vector5F:	.long	irq_handler
vector60:	.long	irq_handler
vector61:	.long	irq_handler
vector62:	.long	irq_handler
vector63:	.long	irq_handler
vector64:	.long	irq_handler
vector65:	.long	irq_handler
vector66:	.long	irq_handler
vector67:	.long	irq_handler
vector68:	.long	irq_handler
vector69:	.long	irq_handler
vector6A:	.long	irq_handler
vector6B:	.long	irq_handler
vector6C:	.long	irq_handler
vector6D:	.long	irq_handler
vector6E:	.long	irq_handler
vector6F:	.long	irq_handler
vector70:	.long	irq_handler
vector71:	.long	irq_handler
vector72:	.long	irq_handler
vector73:	.long	irq_handler
vector74:	.long	irq_handler
vector75:	.long	irq_handler
vector76:	.long	irq_handler
vector77:	.long	irq_handler
vector78:	.long	irq_handler
vector79:	.long	irq_handler
vector7A:	.long	irq_handler
vector7B:	.long	irq_handler
vector7C:	.long	irq_handler
vector7D:	.long	irq_handler
vector7E:	.long	irq_handler
vector7F:	.long	irq_handler
vector80:	.long	irq_handler
vector81:	.long	irq_handler
vector82:	.long	irq_handler
vector83:	.long	irq_handler
vector84:	.long	irq_handler
vector85:	.long	irq_handler
vector86:	.long	irq_handler
vector87:	.long	irq_handler
vector88:	.long	irq_handler
vector89:	.long	irq_handler
vector8A:	.long	irq_handler
vector8B:	.long	irq_handler
vector8C:	.long	irq_handler
vector8D:	.long	irq_handler
vector8E:	.long	irq_handler
vector8F:	.long	irq_handler
vector90:	.long	irq_handler
vector91:	.long	irq_handler
vector92:	.long	irq_handler
vector93:	.long	irq_handler
vector94:	.long	irq_handler
vector95:	.long	irq_handler
vector96:	.long	irq_handler
vector97:	.long	irq_handler
vector98:	.long	irq_handler
vector99:	.long	irq_handler
vector9A:	.long	irq_handler
vector9B:	.long	irq_handler
vector9C:	.long	irq_handler
vector9D:	.long	irq_handler
vector9E:	.long	irq_handler
vector9F:	.long	irq_handler
vectorA0:	.long	irq_handler
vectorA1:	.long	irq_handler
vectorA2:	.long	irq_handler
vectorA3:	.long	irq_handler
vectorA4:	.long	irq_handler
vectorA5:	.long	irq_handler
vectorA6:	.long	irq_handler
vectorA7:	.long	irq_handler
vectorA8:	.long	irq_handler
vectorA9:	.long	irq_handler
vectorAA:	.long	irq_handler
vectorAB:	.long	irq_handler
vectorAC:	.long	irq_handler
vectorAD:	.long	irq_handler
vectorAE:	.long	irq_handler
vectorAF:	.long	irq_handler
vectorB0:	.long	irq_handler
vectorB1:	.long	irq_handler
vectorB2:	.long	irq_handler
vectorB3:	.long	irq_handler
vectorB4:	.long	irq_handler
vectorB5:	.long	irq_handler
vectorB6:	.long	irq_handler
vectorB7:	.long	irq_handler
vectorB8:	.long	irq_handler
vectorB9:	.long	irq_handler
vectorBA:	.long	irq_handler
vectorBB:	.long	irq_handler
vectorBC:	.long	irq_handler
vectorBD:	.long	irq_handler
vectorBE:	.long	irq_handler
vectorBF:	.long	irq_handler
vectorC0:	.long	irq_handler
vectorC1:	.long	irq_handler
vectorC2:	.long	irq_handler
vectorC3:	.long	irq_handler
vectorC4:	.long	irq_handler
vectorC5:	.long	irq_handler
vectorC6:	.long	irq_handler
vectorC7:	.long	irq_handler
vectorC8:	.long	irq_handler
vectorC9:	.long	irq_handler
vectorCA:	.long	irq_handler
vectorCB:	.long	irq_handler
vectorCC:	.long	irq_handler
vectorCD:	.long	irq_handler
vectorCE:	.long	irq_handler
vectorCF:	.long	irq_handler
vectorD0:	.long	irq_handler
vectorD1:	.long	irq_handler
vectorD2:	.long	irq_handler
vectorD3:	.long	irq_handler
vectorD4:	.long	irq_handler
vectorD5:	.long	irq_handler
vectorD6:	.long	irq_handler
vectorD7:	.long	irq_handler
vectorD8:	.long	irq_handler
vectorD9:	.long	irq_handler
vectorDA:	.long	irq_handler
vectorDB:	.long	irq_handler
vectorDC:	.long	irq_handler
vectorDD:	.long	irq_handler
vectorDE:	.long	irq_handler
vectorDF:	.long	irq_handler
vectorE0:	.long	irq_handler
vectorE1:	.long	irq_handler
vectorE2:	.long	irq_handler
vectorE3:	.long	irq_handler
vectorE4:	.long	irq_handler
vectorE5:	.long	irq_handler
vectorE6:	.long	irq_handler
vectorE7:	.long	irq_handler
vectorE8:	.long	irq_handler
vectorE9:	.long	irq_handler
vectorEA:	.long	irq_handler
vectorEB:	.long	irq_handler
vectorEC:	.long	irq_handler
vectorED:	.long	irq_handler
vectorEE:	.long	irq_handler
vectorEF:	.long	irq_handler
vectorF0:	.long	irq_handler
vectorF1:	.long	irq_handler
vectorF2:	.long	irq_handler
vectorF3:	.long	irq_handler
vectorF4:	.long	irq_handler
vectorF5:	.long	irq_handler
vectorF6:	.long	irq_handler
vectorF7:	.long	irq_handler
vectorF8:	.long	irq_handler
vectorF9:	.long	irq_handler
vectorFA:	.long	irq_handler
vectorFB:	.long	irq_handler
vectorFC:	.long	irq_handler
vectorFD:	.long	irq_handler
vectorFE:	.long	irq_handler
vectorFF:	.long	irq_handler

cfm_backdoor:	.long 0
				.long 0
cfm_cfmprot:	.long 0
cfm_cfmsacc:	.long 0
cfm_cfmdacc:	.long 0
cfm_cfmsec:		.long 0


start:
	/* Initialize stack */
	move.w #0x2700, %sr
	move.l #__SP_INIT, %sp
	
	/* Initialize RAM */
	move.l #0x10000201, %d0
	.long   0x4e7b0C05      /* movec d0, RAMBAR	*/

	/* Start main program */
	jmp main


asm_exception_handler:
	rte

asm_set_ipl:
	link	%a6,#-8
	movem.l	%d6-%d7,(%sp)

	move.w	%sr,%d7		/* current sr	 */

	move.l	%d7, %d0	/* prepare return value	 */
	andi.l	#0x0700, %d0	/* mask out IPL	 */
	lsr.l	#8, %d0		/* IPL	 */

	move.l	8(%a6), %d6	/* get argument	 */
	andi.l	#0x07, %d6	/* least significant three bits	 */
	lsl.l	#8, %d6		/* move over to make mask	 */

	andi.l	#0x0000F8FF,%d7	/* zero out current IPL	 */
	or.l	%d6, %d7	/* place new IPL in sr	 */
	move.w	%d7, %sr

	movem.l	(%sp), %d6-%d7
	lea	8(%sp), %sp
	unlk	%a6
	rts


asm_wr_flashbar:
	move.l  4(%sp), %d0
	.long   0x4e7b0C04			/* movec d0, FLASHBAR	*/
	nop
	rts

asm_cache_enable:
	move.l	#0x01400000, %d0	/* Invalidate cache */
	movec	%d0, %CACR
	nop
	
	move.l	#0x80400000, %d0	/* CENB | DISD */
	movec	%d0, %CACR
	nop
	rts

.end
