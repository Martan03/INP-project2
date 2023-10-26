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
; login:          .asciiz "xlogin00"            ; SEM DOPLNTE VLASTNI LOGIN
                                                ; A POUZE S TIMTO ODEVZDEJTE

params_sys5:    .space  8   ; misto pro ulozeni adresy pocatku
                            ; retezce pro vypis pomoci syscall 5
                            ; (viz nize - "funkce" print_string)

; CODE SEGMENT
                .text
main:

        ; SEM DOPLNTE VASE RESENI
        daddi $t0, $zero, 1
        daddi $v0, $zero, 1
        ; nop

insert:
        lb $s0, login($v0)
        ; nop
        daddi $v1, $v0, -1
        beqz $s0, insert_end
        ; nop

insert_inner:
        lb $s1, login($v1)
        ; nop
        ; nop
        sltu $a0, $s0, $s1
        daddi $a1, $v1, 1
        ; nop
        beqz $a0, insert_inner_end
        daddi $v1, $v1, -1
        sb $s1, login($a1)
        bne $a1, $t0, insert_inner

insert_inner_end:
        daddi $a0, $v1, 1
        daddi $v0, $v0, 1
        ; nop
        sb $s0, login($a0)
        j insert

insert_end:

        daddi   r4, r0, login   ; vozrovy vypis: adresa login: do r4
        jal     print_string    ; vypis pomoci print_string - viz nize

        syscall 0   ; halt

print_string:   ; adresa retezce se ocekava v r4
                sw      r4, params_sys5(r0)
                daddi   r14, r0, params_sys5    ; adr pro syscall 5 musi do r14
                syscall 5   ; systemova procedura - vypis retezce na terminal
                jr      r31 ; return - r31 je urcen na return address
