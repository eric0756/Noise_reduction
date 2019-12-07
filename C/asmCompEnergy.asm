					.global _asmCompEnergy
																; A4 stores sig
																; A0 stores sig[i]
																; B4 stores n

_asmCompEnergy:				ldw		.D1		*A4++, A0			; A0 = A4[i]
				|| 			mv		.S2		B4, B1				; B1 = B4 (moved for the b condition)
				||			zero	.L1		A2					; A2 = 0

							ldw		.D1		*A4++, A0			; A0 = A4[i]

							ldw		.D1		*A4++, A0			; A0 = A4[i]

							ldw		.D1		*A4++, A0			; A0 = A4[i]
				||	[B1]	sub		.L2		B1, 1, B1			; B1 = B1 - 1

							ldw		.D1		*A4++, A0			; A0 = A4[i]
				||	[B1]	sub		.L2		B1, 1, B1			; B1 = B1 - 1
				||	[B1]	b		.S2		loop				; Go to loop label if B1 != 0

							ldw		.D1		*A4++, A0			; A0 = A4[i]
				||	[B1]	sub		.L2		B1, 1, B1			; B1 = B1 - 1
				||	[B1]	b		.S2		loop				; Go to loop label if B1 != 0
				||			mpysp	.M1		A0, A0, A1			; A1 = A0 * A0

							ldw		.D1		*A4++, A0			; A0 = A4[i]
				||	[B1]	sub		.L2		B1, 1, B1			; B1 = B1 - 1
				||	[B1]	b		.S2		loop				; Go to loop label if B1 != 0
				||			mpysp	.M1		A0, A0, A1			; A1 = A0 * A0

							ldw		.D1		*A4++, A0			; A0 = A4[i]
				||	[B1]	sub		.L2		B1, 1, B1			; B1 = B1 - 1
				||	[B1]	b		.S2		loop				; Go to loop label if B1 != 0
				||			mpysp	.M1		A0, A0, A1			; A1 = A0 * A0

							ldw		.D1		*A4++, A0			; A0 = A4[i]
				||	[B1]	sub		.L2		B1, 1, B1			; B1 = B1 - 1
				||	[B1]	b		.S2		loop				; Go to loop label if B1 != 0
				||			mpysp	.M1		A0, A0, A1			; A1 = A0 * A0

loop:						ldw		.D1		*A4++, A0			; A0 = A4[i]  B1 = B1 - 1
				||	[B1]	sub		.L2		B1, 1, B1			; B1 = B1 - 1
				||	[B1]	b		.S2		loop				; Go to loop label if B1 != 0
				||			mpysp	.M1		A0, A0, A1			; A1 = A0 * A0
				||			addsp	.L1		A1, A2, A2			; A2 = A1 + A2


							mpysp	.M1		A0, A0, A1			; A1 = A0 * A0
				||			addsp	.L1		A1, A2, A2			; A2 = A1 + A2

							mpysp	.M1		A0, A0, A1			; A1 = A0 * A0
				||			addsp	.L1		A1, A2, A2			; A2 = A1 + A2

							mpysp	.M1		A0, A0, A1			; A1 = A0 * A0
				||			addsp	.L1		A1, A2, A2			; A2 = A1 + A2

							mpysp	.M1		A0, A0, A1			; A1 = A0 * A0
				||			addsp	.L1		A1, A2, A2			; A2 = A1 + A2

							mpysp	.M1		A0, A0, A1			; A1 = A0 * A0
				||			addsp	.L1		A1, A2, A2			; A2 = A1 + A2

							addsp	.L1		A1, A2, A2			; A2 = A1 + A2

							addsp	.L1		A1, A2, A2			; A2 = A1 + A2

							addsp	.L1		A1, A2, A2			; A2 = A1 + A2

							addsp	.L1		A1, A2, A2			; A2 = A1 + A2
							nop				3					; Delay for addsp

							mv		.S1		A2, A4				; A4 = A2
				||			b		.S2		B3					; Return to calling function
							nop				5					; Delay for b

