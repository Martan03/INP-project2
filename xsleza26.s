; Autor reseni: Martin Slezák xsleza26
; Pocet cyklu k serazeni puvodniho retezce: 965
; Pocet cyklu razeni sestupne serazeneho retezce: 1295
; Pocet cyklu razeni vzestupne serazeneho retezce: 254
; Pocet cyklu razeni retezce s vasim loginem: 251
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
        ; Inits variables and handles first two characters
        daddi $t0, $zero, 1
        lb $s1, login($zero)
        daddi $t3, $zero, -1
        lb $s0, login($t0)
        ; Checks if char is zero character
        beqz $s1, insert_end
        daddi $v0, $zero, 2
        sltu $a0, $s0, $s1
        ; Checks if char is zero character
        beqz $s0, insert_end
        daddi $a2, $t0, 1
        ; Skips swapping if latter char is not less
        beqz $a0, init
        ; Swaps first two characters
        sb $s1, login($t0)
        sb $s0, login($zero)

; Inits for main loop
init:
        lb $s0, login($v0)
        lb $s1, login($t0)
        daddi $t1, $zero, 0
        beqz $s0, insert_end

; Main loop loads two chars at the time
; It uses insertion sort
; When char is smaller or equal to char on $v0, jumps to insert_inner_end
; This cycle is repeated until there are at least two chars to swap
; When not enough chars, continues to code which swaps last two
insert:
        sltu $a0, $s0, $s1
        lb $s2, login($t1)
        daddi $t1, $t1, -1
        beqz $a0, insert_inner_end
        sltu $a1, $s0, $s2

        sb $s1, login($a2)
        daddi $a2, $a2, -1
        beqz $a1, insert_inner_end

        nop
        sb $s2, login($a2)
        daddi $a2, $a2, -1
        beq $t1, $t3, insert_inner_end
        lb $s1, login($t1)
        daddi $t1, $t1, -1
        bne $a2, $t0, insert

        ; Swaps first character with character $a0 from loop
        ; Inits variables for next loop
        sltu $a0, $s0, $s1
        daddi $a2, $v0, 1
        sb $s0, login($t0)
        ; If it's not supposed to swap, jump to insert_inner_end1
        beqz $a0, insert_inner_end1
        sb $s1, login($t0)
        sb $s0, login($zero)

; Inits variables for next loop
; Jumps to insert loop if next loaded char is not zero char
insert_inner_end1:
        lb $s1, login($v0)
        lb $s0, login($a2)
        daddi $v0, $v0, 1
        daddi $t1, $a2, -2
        bnez $s0, insert
        j insert_end

; Saves char in $s0 to $a2
; Inits variables for next loop
; Jumps to insert loop if next loaded char is not zero char
insert_inner_end:
        daddi $t1, $v0, 0
        daddi $v0, $v0, 1
        sb $s0, login($a2)
        daddi $a2, $t1, 1
        lb $s0, login($v0)
        lb $s1, login($t1)
        daddi $t1, $t1, -1
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
