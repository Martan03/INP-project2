#include <stdio.h>

int main(void) {
    char login[] = "vvttpnjiiee3220---";
    int v0, v1, a0, a1, t0, a2, a3, t1, t2, t3;
    char s0, s1, s2;
    int zero = 0;

        t3 = zero + -1; // daddi $t3, $zero, -1
        t0 = zero + 1; // daddi $t0, $zero, 1
        v1 = zero + 0; // daddi $v1, $zero, 0
        t2 = zero + 3; // daddi $t2, $zero, 3
        s0 = login[t0]; // lb $s0, login($t0)
        s1 = login[v1]; // lb $s1, login($v1)
        v0 = zero + 1; // daddi $v0, $zero, 1
        if (s0 == 0) goto insert_end; // beqz $s0, insert_end

insert_inner_last:
        a0 = s0 < s1; // sltu $a0, $s0, $s1
        a2 = v1 + 1; // daddi $a2, $v1, 1
        v1 = v1 + -1; // daddi $v1, $v1, -1
        if (a0 == 0) goto insert_inner_end; // beqz $a0, insert_inner_end
        login[a2] = s1; // sb $s1, login($a2)
        a2 = v1 + 1; // daddi $a2, $v1, 1

insert_inner_end:
        v1 = v0 + 0; // daddi $v1, $v0, 0
        v0 = v0 + 1; // daddi $v0, $v0, 1
        login[a2] = s0; // sb $s0, login($a2)
        s1 = login[v1]; // lb $s1, login($v1)
        s0 = login[v0]; // lb $s0, login($v0)
        t1 = v1 + -1; // daddi $t1, $v1, -1
        if (s0 == 0) goto insert_end; // beqz $s0, insert_end

insert:
        // ; nop
        s2 = login[t1]; // lb $s2, login($t1)
        a0 = s0 < s1; // sltu $a0, $s0, $s1
        a2 = v1 + 1; // daddi $a2, $v1, 1
        a1 = s0 < s2; // sltu $a1, $s0, $s2
        if (a0 == 0) goto insert_inner_end; // beqz $a0, insert_inner_end

        login[a2] = s1; // sb $s1, login($a2)
        a2 = v1 + 0; // daddi $a2, $v1, 0
        if (a1 == 0) goto insert_inner_end; // beqz $a1, insert_inner_end

        v1 = v1 + -2; // daddi $v1, $v1, -2
        a3 = a2 < t2; // sltu $a3, $a2, $t2
        login[a2] = s2; // sb $s2, login($a2)
        a2 = a2 - 1;
        if (v1 == t3) goto insert_inner_end; // beq $v1, $t3, insert_inner_end
        s1 = login[v1]; // lb $s1, login($v1)
        if (a3 == t0) goto insert_inner_last; // beq $a3, $t0, insert_inner_last
        t1 = v1 + -1; // daddi $t1, $v1, -1
        goto insert; // j insert

insert_end:

    printf("---0223eeiijnpttvv\n");
    printf("%s\n", login);

    return 0;
}
