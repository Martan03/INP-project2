#include <stdio.h>

int main(void) {
    char login[] = "vitejte-v-inp-2023";
    int v0, v1, a0, a1, t0;
    char s0, s1;
    int zero = 0;

        t0 = zero + 1; // t0 = zero + 1; // daddi $t0, $zero, 1

        // // ; SEM DOPLNTE VASE RESENI
        // // ; i = 1
        v0 = zero + 1; // v0 = zero + 1; // daddi $v0, $zero, 1
        // // ; s0 = login[i]
        s0 = login[v0]; // s0 = login[v0]; // lb $s0, login($v0)

insert:
        v1 = v0 + -1; // v1 = v0 + -1; // daddi $v1, $v0, -1
        if (s0 == 0) goto insert_end; // if (s0 == 0) goto insert_end; // beqz $s0, insert_end

insert_inner:
        s1 = login[v1]; // s1 = login[v1]; // lb $s1, login($v1)
        // // ; nop
        // // ; nop
        a0 = s0 < s1; // a0 = s0 < s1; // sltu $a0, $s0, $s1
        // // ; nop
        // // ; nop
        if (a0 == 0) goto insert_inner_end; // if (a0 == 0) goto insert_inner_end; // beqz $a0, insert_inner_end
        a1 = v1 + 1; // a1 = v1 + 1; // daddi $a1, $v1, 1
        v1 = v1 + -1; // v1 = v1 + -1; // daddi $v1, $v1, -1
        // // ; nop
        login[a1] = s1; // login[a1] = s1; // sb $s1, login($a1)
        if (a1 != t0) goto insert_inner; // if (a1 != t0) goto insert_inner; // bne $a1, $t0, insert_inner

insert_inner_end:
        // // ; login[j] = s0
        a0 = v1 + 1; // a0 = v1 + 1; // daddi $a0, $v1, 1
        login[a0] = s0; // login[a0] = s0; // sb $s0, login($a0)
        v0 = v0 + 1; // v0 = v0 + 1; // daddi $v0, $v0, 1
        s0 = login[v0]; // s0 = login[v0]; // lb $s0, login($v0)
        if (s0 != 0) goto insert; // if (s0 != 0) goto insert; // bnez $s0, insert

insert_end:


    printf("---0223eeiijnpttvv\n");
    printf("%s\n", login);

    return 0;
}
