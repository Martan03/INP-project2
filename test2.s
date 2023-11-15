; Autor reseni: Martin Slezák xsleza26
; Pocet cyklu k serazeni puvodniho retezce: 838
; Pocet cyklu razeni sestupne serazeneho retezce: 1121
; Pocet cyklu razeni vzestupne serazeneho retezce: 270
; Pocet cyklu razeni retezce s vasim loginem: 235
; Implementovany radici algoritmus: Insertion sort
; ------------------------------------------------

; DATA SEGMENT
                .data
login:          .asciiz "vitejte-v-inp-2023"    ; puvodni uvitaci retezec
; login:          .asciiz "vvttpnjiiee3220---"  ; sestupne serazeny retezec
; login:          .asciiz "---0223eeiijnpttvv"  ; vzestupne serazeny retezec
; login:          .asciiz "xsleza26"            ; SEM DOPLNTE VLASTNI LOGIN
                                                ; A POUZE S TIMTO ODEVZDEJTE

params_sys5:    .space  8   ; misto pro ulozeni adresy pocatku
                            ; retezce pro vypis pomoci syscall 5
                            ; (viz nize - "funkce" print_string)

; CODE SEGMENT
                .text
main:
        ; No swap: s2 s1 s0 -> can reuse s1 and s0
        ; One swap: s2 s0 s1 -> can reuse s0 and s1
        ; Multiple swaps: _ s2 s1 -> can reuse s2 and s1
        ; Problem is with using s0 as key char for comparison

        ; s1 s0 s5
        ; s0 s1 s5

        ; No swap: s1 s0 s5, s0 s1 s5
        ; One swap: s5 s0, s5 s1

        ; Solution: two loops with one s0 as key and second with different
        ; Might be too complicated, would need to have 2 different beginnings
        ; for two different loops

        daddi $a3, $zero, 1
        daddi $v0, $zero, 2
        lb $s1, login($zero)
        lb $s2, login($a3)
        daddi $t2, $zero, -1
        beqz $s1, insert_end
        lb $s0, login($v0)
        sltu $a1, $s2, $s1
        daddi $t1, $zero, -2
        beqz $s2, insert_end
        beqz $a1, loop
        sb $s1, login($a3)
        sb $s2, login($zero)

        j loop_pre

insert_inner_end1:
        ; t5 == v0 no need to swap
        daddi $a3, $v0, 0
        daddi $v0, $v0, 1
        sb $s0, login($t5)
        daddi $t1, $a3, -1
        lb $s0, login($v0)
        lb $s1, login($a3)
        lb $s2, login($t1)
        bnez $s0, loop_pre_prep_skip
        j insert_end

insert_inner_end2:
        daddi $v0, $v0, 1
        sb $s0, login($a3)
        ; nop
        lb $s0, login($v0)
        daddi $a3, $v0, -1
        daddi $t1, $v0, -2
        beqz $s0, insert_end

loop_pre_prep:
        lb $s1, login($a3)
        lb $s2, login($t1)
loop_pre_prep_skip:
        daddi $t1, $t1, -2

loop_pre:
        sltu $a1, $s0, $s1
        daddi $t5, $a3, 1
looop_pre_skip:
        sltu $a2, $s0, $s2
        beqz $a1, insert_inner_end1
        sb $s1, login($t5)
        beqz $a2, insert_inner_end2
        sb $s2, login($a3)
        daddi $a3, $a3, -2
        bgez $t1, loop
        j insert_inner_last

loop:
        lb $s3, login($a3)
        lb $s4, login($t1)
loop_first:
        daddi $t5, $a3, 1
        sltu $a1, $s0, $s3
        sltu $a2, $s0, $s4
        daddi $t1, $t1, -2
        beqz $a1, loop_inner_end1
        sb $s3, login($t5)
        beqz $a2, loop_inner_end2
        sb $s4, login($a3)
        daddi $a3, $a3, -2
        bgez $t1, loop

insert_inner_last:
        daddi $t5, $t1, 2
        beq $a3, $t2, insert_inner_end
        lb $s3, login($a3)
        daddi $a3, $v0, 0
        daddi $v0, $v0, 1
        sltu $a1, $s0, $s3
        daddi $t4, $t5, -1
        daddi $t1, $v0, -4
        beqz $a1, insert_inner_last_end
        sb $s0, login($t4)
        lb $s0, login($v0)
        sb $s3, login($t5)
        ; nop
        bnez $s0, loop_pre
        j insert_end

insert_inner_last_end:
        sb $s0, login($t5)
        lb $s0, login($v0)
        ; nop
        ; nop
        bnez $s0, loop_pre
        j insert_end

insert_inner_end:
        daddi $v0, $v0, 1
        ; nop
        sb $s0, login($t5)
        lb $s0, login($v0)
        daddi $a3, $v0, -1
        daddi $t1, $v0, -4
        bnez $s0, loop_pre
        j insert_end

loop_inner_end1:
        ; t5 == v0 no need to swap
        daddi $v0, $v0, 1
        sb $s0, login($t5)
        ; nop
        lb $s0, login($v0)
        daddi $a3, $v0, -1
        daddi $t1, $v0, -4
        bnez $s0, loop_pre
        j insert_end

loop_inner_end2:
        daddi $t5, $v0, 1
        sb $s0, login($a3)
        daddi $v0, $v0, 1
        lb $s0, login($t5)
        daddi $a3, $t5, -1
        daddi $t1, $t5, -4
        sltu $a1, $s0, $s1
        bnez $s0, loop_pre

insert_end:

        daddi   r4, r0, login   ; vozrovy vypis: adresa login: do r4
        jal     print_string    ; vypis pomoci print_string - viz nize

        syscall 0   ; halt

print_string:   ; adresa retezce se ocekava v r4
                sw      r4, params_sys5(r0)
                daddi   r14, r0, params_sys5    ; adr pro syscall 5 musi do r14
                syscall 5   ; systemova procedura - vypis retezce na terminal
                jr      r31 ; return - r31 je urcen na return address