; Autor reseni: Martin Slezák xsleza26
; Pocet cyklu k serazeni puvodniho retezce: 625
; Pocet cyklu razeni sestupne serazeneho retezce: 668
; Pocet cyklu razeni vzestupne serazeneho retezce: 298
; Pocet cyklu razeni retezce s vasim loginem: 169
; Implementovany radici algoritmus: Insertion sort
; ------------------------------------------------

; DATA SEGMENT
                .data
; login:          .asciiz "vitejte-v-inp-2023"    ; puvodni uvitaci retezec
; login:          .asciiz "vvttpnjiiee3220---"  ; sestupne serazeny retezec
; login:          .asciiz "---0223eeiijnpttvv"  ; vzestupne serazeny retezec
login:          .asciiz "xsleza26"            ; SEM DOPLNTE VLASTNI LOGIN
                                                ; A POUZE S TIMTO ODEVZDEJTE

params_sys5:    .space  8   ; misto pro ulozeni adresy pocatku
                            ; retezce pro vypis pomoci syscall 5
                            ; (viz nize - "funkce" print_string)

; CODE SEGMENT
                .text
main:
        ; I used insertion sort with optimization inspired by merge sort.
        ; I sort two elements at the time to the sorted part in order to reduce
        ; iterations. The two elements are sorted before sorting them to the
        ; sorted part.

        ; Initializes variable
        lb $s2, login($zero)
        daddi $v1, $zero, 1
        daddi $t0, $zero, 2
        beqz $s2, insert_end

        lb $s0, login($v1)
        daddi $t1, $zero, 3
        daddi $t2, $zero, 1
        beqz $s0, insert_end

        sltu $a0, $s0, $s2
        daddi $t3, $zero, 0
        daddi $v0, $zero, 4
        beqz $a0, prep
        sb $s2, login($v1)
        sb $s0, login($zero)

prep:
        lb $s0, login($t0)
        ; nop
        ; nop
        beqz $s0, insert_end

        lb $s1, login($t1)
        ; nop
        ; nop
        beqz $s1, insert_end_swap

insert_cmp:
        sltu $a0, $s0, $s1
        lb $s2, login($t2)
        lb $s3, login($t3)
        bnez $a0, insert_skip
        lb $s0, login($t1)
        lb $s1, login($t0)
        j insert_skip

; Checks if larger value from the two chars I sort is smaller then current char
; If so, moves current char two places to the right, else inserts larger char
; to the string and continues to sort remaining char to the string
; I needed to use 4 indexes so in order to reduce instructions count I have
; two loops next to each other with index reusing
; (1. loop $t3, $t2, $t0, $t1, 2. loop $t0, $t1, $t3, $t2)
insert:
        lb $s2, login($t2)
        lb $s3, login($t3)
insert_skip:
        ; nop
        sltu $a0, $s1, $s2
        sltu $a1, $s1, $s3
        sb $s2, login($t1)
        beqz $a0, insert_inner_end
        daddi $t1, $t1, -4
        beqz $a1, insert_inner_end1
        sb $s3, login($t0)
        daddi $t0, $t0, -4

        bgez $t1, insert1
        j insert_outer_end

insert1:
        lb $s2, login($t1)
        lb $s3, login($t0)
        ; nop
        sltu $a0, $s1, $s2
        sltu $a1, $s1, $s3
        sb $s2, login($t2)
        beqz $a0, insert_inner_end2
        daddi $t2, $t2, -4
        beqz $a1, insert_inner_end3
        sb $s3, login($t3)
        daddi $t3, $t3, -4

        bgez $t2, insert

insert_outer_end:
        sb $s1, login($v1)
        sb $s0, login($zero)
        lb $s0, login($v0)
        daddi $t1, $v0, 1
        daddi $t0, $v0, 0
        beqz $s0, insert_end
        lb $s1, login($t1)
        daddi $t2, $v0, -1
        daddi $t3, $v0, -2
        daddi $v0, $v0, 2
        bnez $s1, insert_cmp
        j insert_single_prep

insert_inner_end:
        sb $s1, login($t1)
        daddi $t1, $t1, -1
        j insert_single

insert_inner_end1:
        sb $s1, login($t0)
        daddi $t1, $t1, 2
        j insert_single_last

insert_inner_end2:
        sb $s1, login($t2)
        daddi $t1, $t3, 0
        daddi $t3, $t3, -2
        daddi $t2, $t2, -2
        j insert_single

insert_inner_end3:
        sb $s1, login($t3)
        daddi $t1, $t3, -1
        daddi $t2, $t2, -2
        daddi $t3, $t3, -2
        j insert_single_last

; Checks if remaining char is smaller then current char. If so it moves it to
; the right one place, else it writes remaining char to the string and starts
; new iteration of inserting two chars at the time
insert_single_prep:
        lb $s2, login($t2)
        lb $s3, login($t3)

insert_single:
        daddi $t5, $t2, 1
        sltu $a0, $s0, $s2
        sltu $a1, $s0, $s3
        daddi $t3, $t3, -2
        beqz $a0, insert_single_end1
        sb $s2, login($t5)
        beqz $a1, insert_single_end2
        sb $s3, login($t2)
        daddi $t2, $t2, -2

        bgez $t3, insert_single_prep

        daddi $t2, $v0, -1
        daddi $t0, $v0, 0
        sb $s0, login($zero)
        lb $s2, login($t2)
        lb $s0, login($t0)
        daddi $t1, $t0, 1
        daddi $t3, $t0, -2
        beqz $s0, insert_end
        lb $s1, login($t1)
        lb $s3, login($t3)
        daddi $v0, $v0, 2
        beqz $s1, insert_single

        sltu $a1, $s0, $s1
        ; nop
        ; nop
        bnez $a1, insert_skip
        lb $s0, login($t1)
        lb $s1, login($t0)
        j insert_skip

insert_single_end1:
        daddi $t2, $v0, -1
        daddi $t0, $v0, 0
        sb $s0, login($t5)
        lb $s2, login($t2)
        lb $s0, login($t0)
        daddi $t1, $t0, 1
        daddi $t3, $t0, -2
        beqz $s0, insert_end
        lb $s1, login($t1)
        lb $s3, login($t3)
        daddi $v0, $v0, 2
        beqz $s1, insert_single

        sltu $a1, $s0, $s1
        ; nop
        ; nop
        bnez $a1, insert_skip
        lb $s0, login($t1)
        lb $s1, login($t0)
        j insert_skip

insert_single_end2:
        daddi $t3, $v0, -2
        daddi $t0, $v0, 0
        sb $s0, login($t2)
        lb $s3, login($t3)
        lb $s0, login($t0)
        daddi $t1, $t0, 1
        daddi $t2, $t0, -1
        beqz $s0, insert_end
        lb $s1, login($t1)
        lb $s2, login($t2)
        daddi $v0, $v0, 2
        beqz $s1, insert_single

        sltu $a1, $s0, $s1
        ; nop
        ; nop
        bnez $a1, insert_skip
        lb $s0, login($t1)
        lb $s1, login($t0)
        j insert_skip

insert_single_last:
        sltu $a0, $s0, $s3
        daddi $t2, $t2, -2
        daddi $t3, $t3, -2
        beqz $a0, insert_single_last_end
        sb $s3, login($t1)
        daddi $t1, $t1, -1

        bnez $t1, insert_single_prep

insert_single_last_end:
        daddi $t2, $v0, -1
        daddi $t0, $v0, 0
        sb $s0, login($t1)
        lb $s2, login($t2)
        lb $s0, login($t0)
        daddi $t1, $t0, 1
        daddi $t3, $t0, -2
        beqz $s0, insert_end
        lb $s1, login($t1)
        lb $s3, login($t3)
        daddi $v0, $v0, 2
        beqz $s1, insert_single

        sltu $a1, $s0, $s1
        ; nop
        ; nop
        bnez $a1, insert_skip
        lb $s0, login($t1)
        lb $s1, login($t0)
        j insert_skip

insert_end_swap:
        sltu $a0, $s0, $s2
        ; nop
        ; nop
        beqz $a0, insert_end
        sb $s2, login($t0)

        lb $s2, login($v1)
        ; nop
        ; nop
        sltu $a0, $s0, $s2
        ; nop
        ; nop
        beqz $a0, insert_end_swap_end
        sb $s0, login($zero)
        sb $s2, login($v1)
        j insert_end

insert_end_swap_end:
        sb $s0, login($v1)
        sb $s2, login($zero)

insert_end:

        daddi   r4, r0, login   ; vozrovy vypis: adresa login: do r4
        jal     print_string    ; vypis pomoci print_string - viz nize

        syscall 0   ; halt

print_string:   ; adresa retezce se ocekava v r4
                sw      r4, params_sys5(r0)
                daddi   r14, r0, params_sys5    ; adr pro syscall 5 musi do r14
                syscall 5   ; systemova procedura - vypis retezce na terminal
                jr      r31 ; return - r31 je urcen na return address