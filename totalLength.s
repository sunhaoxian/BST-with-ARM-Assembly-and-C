@ Put your implementation of totalLength here
.text
.global totalLength

totalLength:
		mov r1, r0	@store the node into r1

		mov r0, #0	@clear the return value
		
		
@A case to get the key and count the number of characters in it
countString:				
		push {r4, r5, lr}	@at the beginning of recursion, push
					@registers to store address
	
		ldr r3, [r1, #0]	@get the key

		mov r4, #0	@set zero variable


@loop to count the number of characters in key
loop:		
		ldrb r5, [r3, r4]	@load each character everytime

		cmp r5, #0	@end condition for r5

		beq recursion		@leave the loop

		add r0, #1	@count the total number of characters

		add r4, #1
		b loop		


@recursive calling where checking leftward firstly, and then checking
@rightward
recursion:	
		ldr r2, [r1, #4]	@get the left pointer of current node

		cmp r2, #0	@if it is null

		beq right	@jump to right checking

		push {r1}	@if not null, store the current node into 
				@stack

		mov r1, r2	@n = n -> left

		bl countString		@recursive call

		pop {r1}	@when ending, pop the old node back


@right to 
right:		
	ldr r2, [r1, #8]	@get the right pointer of current node

	cmp r2, #0	@see if it is null

	beq end		

	push {r1}	@store the original node

	mov r1, r2	@n = n -> right

	bl countString	@recursive calling back

	pop {r1}	@pop the old node back


end:	
	pop {r4, r5, pc}	@go to specific address

