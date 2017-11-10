@ Put your implementation of count here
.text
.global count


count: 	
	mov r1, r0  @ node
	mov r0, #1  @ count


@recursive calling: left side to right side
recursion:	
		push {lr}	@ before running recursion, push lr

		ldr r2, [r1, #4]	@load the left pointer

		cmp r2, #0	@check if it is null
	
		beq right	@if it is null, 

		push {r1}	@store the original node into 

		mov r1, r2	@promote the checking to its right node

		add r0, #1	@since there is one more node, plus the 
				@result by 1

		bl recursion	@recursive calling

		pop {r1}	@when it finishes, pop the r1 back


@in order to arrive the rightmost node from the current node
right:	
	ldr r2, [r1, #8]	@load the right node

	cmp r2, #0	@see if that node is null

	beq end		@if so, leave the case

	push {r1}	@store the original node

	mov r1, r2	@n = n -> right

	add r0, #1	@increment the return value

	bl recursion	@call recursion

	pop {r1}	@pop the node in the last step back


end:	
	pop {pc}	@return to specific address

