; Simple register movement
main:
	;move.b #0x01,d0
	;move.w #0xfafa,d1
	;move.l #0xfafbfcfd, d2
	;move.l d2, d3
	;move.w d1, d4
	;move.b d0, d5
	;move.l (a0),d0
	;move.l (a1)+,d0
	;move.l -(a0),d0
	;move.l (0x0000).w, d0
	;move.w (0x0000).w, d0
	;move.l (0x00000000).l,d0
	;move.w (0x00000000).l,d0
	move.b #0x1, d1
	move.w (0x0000,a0), d0
	move.b #0x2, d2
	move.l (0x00,a0,d1),d0
	move.b #0x3, d3
	move.l (0x0000,pc), d0
	move.b #0x4, d4
	move.w (0x00,pc,d1), d0
	move.b #0x5, d5

	
