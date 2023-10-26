#include <stdio.h>

int main(void) {
    char login[] = "vitejte-v-inp-2023";
    int v0, v1, a0, a1, t0, a2, a3;
    char s0, s1, s2;
    int zero = 0;

// // ; SEM DOPLNTE VASE RESENI
        t0 = zero + 1; // daddi $t0, $zero, 1
        v1 = zero + 0; // daddi $v1, $zero, 0
        s0 = login[t0]; // lb $s0, login($t0)
        v0 = zero + 1; // daddi $v0, $zero, 1
        // ; nop
        if (s0 == 0) goto insert_end; // beqz $s0, insert_end

insert:
        a3 = v1 < t0; // sltu $a3, $v1, $t0
        a2 = v1 + -1; // daddi $a2, $v1, -1
        s1 = login[v1]; // lb $s1, login($v1)
        if (a3 == t0) goto insert_inner_last; // beq $a3, $t0, insert_inner_last

        s2 = login[a2]; // lb $s2, login($a2)
        a0 = s0 < s1; // sltu $a0, $s0, $s1
        a2 = v1 + 1; // daddi $a2, $v1, 1
        a1 = s0 < s2; // sltu $a1, $s0, $s2
        if (a0 == 0) goto insert_inner_end; // beqz $a0, insert_inner_end

        v1 = v1 + -1; // daddi $v1, $v1, -1
        login[a2] = s1; // sb $s1, login($a2)
        a0 = a1 + 0; // daddi $a0, $a1, 0
        a2 = v1 + 1; // daddi $a2, $v1, 1
        if (a1 == 0) goto insert_inner_end; // beqz $a1, insert_inner_end

        v1 = v1 + -1; // daddi $v1, $v1, -1
        login[a2] = s2; // sb $s2, login($a2)
        if (a2 != t0) goto insert; // bne $a2, $t0, insert

        a0 = v1 + 1; // daddi $a0, $v1, 1
        v0 = v0 + 1; // daddi $v0, $v0, 1
        // ; nop
        login[a0] = s0; // sb $s0, login($a0)
        s0 = login[v0]; // lb $s0, login($v0)
        v1 = v0 + -1; // daddi $v1, $v0, -1
        // ; nop
        if (s0 != 0) goto insert; // bnez $s0, insert

insert_inner_last:
        a0 = s0 < s1; // sltu $a0, $s0, $s1
        a2 = v1 + 1; // daddi $a2, $v1, 1
        // ; nop
        if (a0 == 0) goto insert_inner_end; // beqz $a0, insert_inner_end
        v1 = v1 + -1; // daddi $v1, $v1, -1
        login[a2] = s1; // sb $s1, login($a2)
        if (a2 != t0) goto insert; // bne $a2, $t0, insert

insert_inner_end:
        v0 = v0 + 1; // daddi $v0, $v0, 1
        // ; nop
        login[a2] = s0; // sb $s0, login($a2)
        s0 = login[v0]; // lb $s0, login($v0)
        v1 = v0 + -1; // daddi $v1, $v0, -1
        // ; nop
        if (s0 != 0) goto insert; // bnez $s0, insert

insert_end:


    printf("---0223eeiijnpttvv\n");
    printf("%s\n", login);

    return 0;
}
