; Autor reseni: Martin Slezák xsleza26
; Pocet cyklu k serazeni puvodniho retezce:
; Pocet cyklu razeni sestupne serazeneho retezce:
; Pocet cyklu razeni vzestupne serazeneho retezce:
; Pocet cyklu razeni retezce s vasim loginem:
; Implementovany radici algoritmus:
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

        ; SEM DOPLNTE VASE RESENI
        daddi $t0, $zero, 1
        daddi $v1, $zero, 0
        daddi $t3, $zero, -1
        lb $s0, login($t0)
        lb $s1, login($v1)
        daddi $v0, $zero, 1
        beqz $s0, insert_end
        daddi $a2, $v1, 1

        j insert_inner_last
insert:
        lb $s2, login($t1)
        sltu $a0, $s0, $s1
        daddi $v1, $v1, -2
        sltu $a1, $s0, $s2
        beqz $a0, insert_inner_end

        sb $s1, login($a2)
        daddi $a2, $v1, 2
        beqz $a1, insert_inner_end

        sltu $a3, $v1, $t0
        sb $s2, login($a2)
        daddi $a2, $a2, -1
        beq $v1, $t3, insert_inner_end
        lb $s1, login($v1)
        daddi $t1, $v1, -1
        bne $a3, $t0, insert

insert_inner_last:
        sb $s1, login($a2)
        daddi $a2, $a2, -1

insert_inner_end:
        daddi $v1, $v0, 0
        daddi $v0, $v0, 1
        sb $s0, login($a2)
        lb $s1, login($v1)
        lb $s0, login($v0)
        daddi $t1, $v1, -1
        daddi $a2, $v1, 1
        bnez $s0, insert

insert_end:

        daddi   r4, r0, login   ; vozrovy vypis: adresa login: do r4
        jal     print_string    ; vypis pomoci print_string - viz nize

        syscall 0   ; halt

print_string:   ; adresa retezce se ocekava v r4
                sw      r4, params_sys5(r0)
                daddi   r14, r0, params_sys5    ; adr pro syscall 5 musi do r14
                syscall 5   ; systemova procedura - vypis retezce na terminal
                jr      r31 ; return - r31 je urcen na return address
