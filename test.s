; Autor reseni: Martin Slezák xsleza26
; Pocet cyklu k serazeni puvodniho retezce: 872
; Pocet cyklu razeni sestupne serazeneho retezce: 1169
; Pocet cyklu razeni vzestupne serazeneho retezce: 300
; Pocet cyklu razeni retezce s vasim loginem: 252
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
        daddi $a3, $zero, 1
        daddi $v0, $zero, 2
        lb $s1, login($zero)
        lb $s2, login($a3)
        daddi $t2, $zero, -1
        beqz $s1, insert_end
        lb $s0, login($v0)
        sltu $a1, $s2, $s1
        daddi $t1, $zero, 0
        beqz $s2, insert_end
        beqz $a1, loop
        sb $s1, login($a3)
        sb $s2, login($zero)

        j loop_first

insert_inner_end1:
        daddi $a3, $v0, 0
        daddi $v0, $v0, 1
        sb $s0, login($t5)
        ; nop
        lb $s0, login($v0)
        daddi $t1, $a3, -1
        ; nop
        bnez $s0, loop
        j insert_end

insert_inner_end2:
        daddi $v0, $v0, 1
        sb $s0, login($a3)
        ; nop
        lb $s0, login($v0)
        daddi $t1, $v0, -2
        daddi $a3, $v0, -1
        beqz $s0, insert_end

loop:
        lb $s1, login($a3)
        lb $s2, login($t1)
loop_first:
        daddi $t5, $a3, 1
        sltu $a1, $s0, $s1
        sltu $a2, $s0, $s2
        daddi $t1, $t1, -2
        beqz $a1, insert_inner_end1
        sb $s1, login($t5)
        beqz $a2, insert_inner_end2
        sb $s2, login($a3)
        daddi $a3, $a3, -2
        bgez $t1, loop

insert_inner_last:
        daddi $t5, $t1, 2
        beq $a3, $t2, insert_inner_end
        lb $s1, login($a3)
        sltu $a1, $s0, $s1
        ; nop
        ; nop
        beqz $a1, insert_inner_end
        sb $s1, login($t5)
        daddi $t5, $t5, -1

insert_inner_end:
        daddi $a3, $v0, 0
        daddi $v0, $v0, 1
        sb $s0, login($t5)
        daddi $t1, $a3, -1
        lb $s0, login($v0)
        ; nop
        ; nop
        bnez $s0, loop

insert_end:

        daddi   r4, r0, login   ; vozrovy vypis: adresa login: do r4
        jal     print_string    ; vypis pomoci print_string - viz nize

        syscall 0   ; halt

print_string:   ; adresa retezce se ocekava v r4
                sw      r4, params_sys5(r0)
                daddi   r14, r0, params_sys5    ; adr pro syscall 5 musi do r14
                syscall 5   ; systemova procedura - vypis retezce na terminal
                jr      r31 ; return - r31 je urcen na return address
