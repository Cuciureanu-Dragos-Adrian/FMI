.data
	g:       .space 1600									# matricea de adiacenta facuta nula
	roles:   .space 80									# vectorul cu roluri
	vis:     .space 80									# vectorul vizitat
	queue:   .space 80									# vectorul queue
	s1:      .asciiz "switch malitios index "
	s2:	 .asciiz "controller index "
	s3:	 .asciiz "host index "
	s4:	 .asciiz "switch index "
	s5:  	 .asciiz "Yes"
	s6:	 .asciiz "No"
	dp:	 .asciiz ": "
	sp:      .asciiz " "
	pv: 	 .asciiz "; "
	endl:	 .asciiz "\n"
	str:	 .space 100

.text

main:
	li $v0, 5
	syscall
	move $t0, $v0					# nr de linii si coloane

	li $v0, 5
	syscall
	move $t1, $v0					#nr de muchii

	li $t9, 1
	li $t5,0

introducere_muchii_in_matrice:				# realizarea matricii de adiacenta
	bge $t5, $t1, cont_1
	li $v0, 5
	syscall
	move $t2, $v0

	li $v0, 5
	syscall
	move $t3, $v0

	mul $t4, $t2, $t0
	add $t4, $t4, $t3
	mul $t4, $t4, 4

	sw $t9, g($t4)

	mul $t4, $t3, $t0
	add $t4, $t4, $t2
	mul $t4, $t4, 4

	sw $t9, g($t4)

	addi $t5, 1

	j introducere_muchii_in_matrice

cont_1:	
	li $t5,0

introducere_roles:					# realizarea vectorului de roluri
	bge $t5, $t0, det_cer	
	li $v0, 5
	syscall
	move $t2, $v0
	
	mul $t3, $t5, 4
	sw $t2, roles($t3)

	addi $t5, 1

	j introducere_roles


det_cer:

	li $v0, 5
	syscall
	move $t1, $v0

	beq $t1, 1, cer_1
	beq $t1, 2, cer_2
	beq $t1, 3, cer_3


cer_1:

	cont_2_cer_1:				
		li $t1, 0

	for_roles_cer_1:
		bge $t1, $t0, et_exit

		mul $t2, $t1, 4					# indexul elementului $t1
		lw $t3, roles($t2)				# nr de pe roles($t2)
	
		beq $t3, 1, cont_for_roles_cer_1		# daca nu este malitios sarim peste element
		beq $t3, 2, cont_for_roles_cer_1		# daca nu este malitios sarim peste element
		beq $t3, 4, cont_for_roles_cer_1		# daca nu este malitios sarim peste element
		la $a0, s1
		li $v0, 4
		syscall
	
		move $a0, $t1
		li $v0, 1
		syscall

		la $a0, dp
		li $v0, 4
		syscall

		li $t4, 0

		for_g_cer_1:
			bge $t4, $t0, cont_for_g_cer_1		# cautam in matrice ce elemente au muchie cu $t1
			mul $t5, $t1, $t0
			add $t5, $t5, $t4
			mul $t5, $t5, 4

			lw $t6, g($t5)				# punem in $t6 elem de pe poz $t5

			beq $t6, 0, fara_muchie_cer_1		# verificam daca exista muchie

			mul $t7, $t4, 4
			lw $t8, roles($t7)

			beq $t8, 1, hi_cer_1
			beq $t8, 2, si_cer_1
			beq $t8, 3, smi_cer_1
			beq $t8, 4, ci_cer_1


	fara_muchie_cer_1:
			addi $t4, 1
			j for_g_cer_1

	cont_for_g_cer_1:
		la $a0, endl
		li $v0, 4
		syscall

	cont_for_roles_cer_1:
		addi $t1, 1
		j for_roles_cer_1
	

	smi_cer_1:
		la $a0, s1
		li $v0, 4
		syscall
		move $a0, $t4
		li $v0, 1
		syscall
		la $a0, pv
		li $v0, 4
		syscall
		j fara_muchie_cer_1

	ci_cer_1:
		la $a0, s2
		li $v0, 4
		syscall
		move $a0, $t4
		li $v0, 1
		syscall
		la $a0, pv
		li $v0, 4
		syscall
		j fara_muchie_cer_1

	hi_cer_1:
		la $a0, s3
		li $v0, 4
		syscall
		move $a0, $t4
		li $v0, 1
		syscall
		la $a0, pv
		li $v0, 4
		syscall
		j fara_muchie_cer_1

	si_cer_1:
		la $a0, s4
		li $v0, 4
		syscall
		move $a0, $t4
		li $v0, 1
		syscall
		la $a0, pv
		li $v0, 4
		syscall
		j fara_muchie_cer_1


cer_2:

	cont_2_cer_2:				
		li $t1, 0					# queueIdx
		li $t2, 1					# queueLen
		sw $t1, queue($t1)				# punem in queue(0) pe 0
		sw $t9, vis($t1)				# il facem pe vis(0) 1


	bfs_cer_2:
		bge $t1, $t2, conex_cer_2
		mul $t3, $t1, 4					# queueLen efectiv
		lw $t4, queue($t3)				# currentNode
		addu $t1, $t1, 1

		mul $t7, $t4, 4
		lw $t3, roles($t7)				# rolul lui t4

		beq $t3, 2, nebun_cer_2				# if roles[currentNode] == 1
		beq $t3, 3, nebun_cer_2
		beq $t3, 4, nebun_cer_2

		la $a0, s3
		li $v0, 4
		syscall
	
		move $a0, $t4					# print currentNode
		li $v0, 1
		syscall	

		la $a0, pv
		li $v0, 4
		syscall

	nebun_cer_2:
		li $t5, 0

		pwhile_cer_2:
			beq $t5, $t0, bfs_cer_2			# while columnIndex < N
	
			mul $t6, $t4, $t0
			add $t6, $t6, $t5
			mul $t6, $t6, 4

			lw $t3, g($t6)				# g[currentNode][columnIndex]

			beq $t3, 0, cont_pwhile_cer_2		# if graph[currentNode][columnIndex] == 1

			mul $t6, $t5, 4				# columnIndex efectiv
			lw $t3, vis($t6)			# vis(columnIndex)

			beq $t3, 1, cont_pwhile_cer_2		# if visited[columnIndex] != 1
	
			mul $t3, $t2, 4				# queueLen efectiv
			sw $t5, queue($t3)			# queue[queueLen] := columnIndex
		
			addi $t2, 1				# queueLen := queueLen + 1

			sw $t9, vis($t6)			# visited[columnIndex] := 1


	cont_pwhile_cer_2:
			addi $t5, 1
			j pwhile_cer_2

	conex_yeees_cer_2:
		la $a0, endl
		li $v0, 4
		syscall	

		la $a0, s5
		li $v0, 4
		syscall

		j et_exit
	
	conex_nooo_cer_2:
		la $a0, endl
		li $v0, 4
		syscall	

		la $a0, s6
		li $v0, 4
		syscall

		j et_exit

	conex_cer_2:
		beq $t2, $t0, conex_yeees_cer_2
		j conex_nooo_cer_2


cer_3:

	cont_2_cer_3:	
		li $v0, 5
		syscall
		move $t7, $v0					# elem de unde se porneste bfs

		li $t1, 0					# queueIdx
		li $t2, 1					# queueLen
		sw $t7, queue($t1)				# punem in queue(0) pe $t7, de unde o sa pornim bfs

		mul $t3, $t7, 4
		sw $t9, vis($t3)				# il facem pe vis(0) 1

		li $v0, 5
		syscall
		move $t8, $v0					# elem unde tr sa ajungem

	bfs_cer_3:
		bge $t1, $t2, apartenenta_cer_3
		mul $t3, $t1, 4					# queueLen efectiv
		lw $t4, queue($t3)				# currentNode
		addu $t1, $t1, 1

		mul $t3, $t4, 4
		lw $t3, roles($t3)				# rolul lui t4

		beq $t3, 2, nebun_cer_3				# if roles[currentNode] == 1
		beq $t3, 3, nebun_cer_3
		beq $t3, 4, nebun_cer_3

	nebun_cer_3:
		li $t5, 0

		pwhile_cer_3:
			bge $t5, $t0, bfs_cer_3			# while columnIndex < N
	
			mul $t6, $t4, $t0
			add $t6, $t6, $t5
			mul $t6, $t6, 4

			lw $t3, g($t6)				# g[currentNode][columnIndex]

			beq $t3, 0, cont_pwhile_cer_3		# if graph[currentNode][columnIndex] == 1

			mul $t6, $t5, 4				# columnIndex efectiv
			lw $t3, vis($t6)			# vis(columnIndex)

			beq $t3, 1, cont_pwhile_cer_3		# if visited[columnIndex] != 1

			lw $t3, roles($t6)			# rolul lui $t5

			beq $t3, 3, cont_pwhile_cer_3		# daca rolul sau este de swicth malitios sarim peste el
	
			mul $t3, $t2, 4				# queueLen efectiv
			sw $t5, queue($t3)			# queue[queueLen] := columnIndex
		
			addi $t2, 1				# queueLen := queueLen + 1

			sw $t9, vis($t6)			# visited[columnIndex] := 1


	cont_pwhile_cer_3:
			addi $t5, 1
			j pwhile_cer_3

	drum_sigur_cer_3:
		la $a0, str
		li $v0, 4
		syscall

		j et_exit
	
	drum_nesigur_cer_3:
		li $t0, 0
		lb $t1, str($t0)

	criptare_cer_3:
		beq $t1, 0, afisare_cer_3

		subu $t1, $t1, 10
		bge $t1, 97, inlocuire_cer_3
		addu $t1, $t1, 26

	inlocuire_cer_3:
		sb $t1, str($t0)

		addu $t0, 1
		lb $t1, str($t0)
	
		j criptare_cer_3

	afisare_cer_3:
		la $a0, str
		li $v0, 4
		syscall

		j et_exit

	apartenenta_cer_3:
		li $t1, 0
		move $t3, $t7					# elem de unde se pleaca
		move $t4, $t8					# elem unde tr sa ajungem

		li $v0, 8
		li $a1, 100
		la $a0, str
		syscall

		for_queue_cer_3:
			bge $t1, $t2, drum_nesigur_cer_3
		
			mul $t5, $t1, 4
			lw $t6, queue($t5)

			beq $t6, $t4, drum_sigur_cer_3

			addi $t1, 1

			j for_queue_cer_3

et_exit:
	li $v0, 10
	syscall