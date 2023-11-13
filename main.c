#include <stdio.h>

int main(void) {
    char login[] = "vitejte-v-inp-2023";
    int v0, v1, a0, a1, t0, a2, a3, t1, t2, t3, t4, t5;
    char s0, s1, s2, s3, s4, s5;
    int zero = 0;

        a3 = zero + 1; // daddi $a3, $zero, 1
        v0 = zero + 2; // daddi $v0, $zero, 2
        s1 = login[zero]; // lb $s1, login($zero)
        s2 = login[a3]; // lb $s2, login($a3)
        t2 = zero + -1; // daddi $t2, $zero, -1
        if (s1 == 0) goto insert_end; // beqz $s1, insert_end
        s0 = login[v0]; // lb $s0, login($v0)
        a1 = s2 < s1; // sltu $a1, $s2, $s1
        t1 = zero + 0; // daddi $t1, $zero, 0
        if (s2 == 0) goto insert_end; // beqz $s2, insert_end
        if (a1 == 0) goto loop; // beqz $a1, loop
        login[a3] = s1; // sb $s1, login($a3)
        login[zero] = s2; // sb $s2, login($zero)

        goto loop_first; // j loop_first

insert_inner_end1:
        // ; t5 == v0 no need to swap
        a3 = v0 + 0; // daddi $a3, $v0, 0
        v1 = v0 + 1; // daddi $v1, $v0, 1
        login[t5] = s0; // sb $s0, login($t5)
        t1 = a3 + -1; // daddi $t1, $a3, -1
        s3 = login[v1]; // lb $s3, login($v1)
        s1 = login[a3]; // lb $s1, login($a3)
        s2 = login[t1]; // lb $s2, login($t1)
        if (s3 != 0) goto loop1_first; // bnez $s3, loop1_first
        goto insert_end; // j insert_end

insert_inner_end2:
        v1 = v0 + 1; // daddi $v1, $v0, 1
        login[a3] = s0; // sb $s0, login($a3)
        // nop
        s3 = login[v1]; // lb $s3, login($v1)
        a3 = v1 + -1; // daddi $a3, $v1, -1
        t1 = v1 + -2; // daddi $t1, $v1, -2
        if (s3 != 0) goto loop1; // bnez $s3, loop1
        goto insert_end; // j insert_end

loop:
        s1 = login[a3]; // lb $s1, login($a3)
        s2 = login[t1]; // lb $s2, login($t1)
loop_first:
        t5 = a3 + 1; // daddi $t5, $a3, 1
        a1 = s0 < s1; // sltu $a1, $s0, $s1
        a2 = s0 < s2; // sltu $a2, $s0, $s2
        t1 = t1 + -2; // daddi $t1, $t1, -2
        if (a1 == 0) goto insert_inner_end1; // beqz $a1, insert_inner_end1
        login[t5] = s1; // sb $s1, login($t5)
        if (a2 == 0) goto insert_inner_end2; // beqz $a2, insert_inner_end2
        login[a3] = s2; // sb $s2, login($a3)
        a3 = a3 + -2; // daddi $a3, $a3, -2
        if (t1 >= 0) goto loop; // bgez $t1, loop

        v1 = v0 + 1; // daddi $v1, $v0, 1
        t5 = t1 + 2; // daddi $t5, $t1, 2
        a3 = v0 + 0; // daddi $a3, $v0, 0
        s3 = login[v0]; // lb $s3, login($v0)
        login[t5] = s0; // sb $s0, login($t5)
        t1 = v0 + -1; // daddi $t1, $v0, -1
        if (s3 != 0) goto loop1; // bnez $s3, loop1
        goto insert_end; // j insert_end

loop1_inner_end1:
        // ; t5 == v0 no need to swap
        a3 = v1 + 0; // daddi $a3, $v1, 0
        v0 = v1 + 1; // daddi $v0, $v1, 1
        login[t5] = s3; // sb $s3, login($t5)
        t1 = a3 + -1; // daddi $t1, $a3, -1
        s0 = login[v0]; // lb $s0, login($v0)
        s1 = login[a3]; // lb $s1, login($a3)
        s2 = login[t1]; // lb $s2, login($t1)
        if (s0 != 0) goto loop_first; // bnez $s0, loop_first
        goto insert_end; // j insert_end

loop1_inner_end2:
        v0 = v1 + 1; // daddi $v0, $v1, 1
        login[a3] = s3; // sb $s3, login($a3)
        // nop
        s0 = login[v0]; // lb $s0, login($v0)
        a3 = v0 + -1; // daddi $a3, $v0, -1
        t1 = v0 + -2; // daddi $t1, $v0, -2
        if (s0 != 0) goto loop; // bnez $s0, loop
        goto insert_end; // j insert_end

loop1:
        s1 = login[a3]; // lb $s1, login($a3)
        s2 = login[t1]; // lb $s2, login($t1)
loop1_first:
        t5 = a3 + 1; // daddi $t5, $a3, 1
        a1 = s3 < s1; // sltu $a1, $s3, $s1
        a2 = s3 < s2; // sltu $a2, $s3, $s2
        t1 = t1 + -2; // daddi $t1, $t1, -2
        if (a1 == 0) goto loop1_inner_end1; // beqz $a1, loop1_inner_end1
        login[t5] = s1; // sb $s1, login($t5)
        if (a2 == 0) goto loop1_inner_end2; // beqz $a2, loop1_inner_end2
        login[a3] = s2; // sb $s2, login($a3)
        a3 = a3 + -2; // daddi $a3, $a3, -2
        if (t1 >= 0) goto loop1; // bgez $t1, loop1

insert_inner_last:
        t5 = t1 + 2; // daddi $t5, $t1, 2
        s1 = login[a3]; // lb $s1, login($a3)
        a3 = v1 + 0; // daddi $a3, $v1, 0
        v0 = v1 + 1; // daddi $v0, $v1, 1
        a1 = s0 < s1; // sltu $a1, $s0, $s1
        t4 = t5 + -1; // daddi $t4, $t5, -1
        t1 = v0 + -2; // daddi $t1, $v0, -2
        if (a1 == 0) goto insert_inner_last_end; // beqz $a1, insert_inner_last_end
        login[t5] = s1; // sb $s1, login($t5)
        login[t4] = s3; // sb $s3, login($t4)
        s0 = login[v0]; // lb $s0, login($v0)
        s1 = login[a3]; // lb $s1, login($a3)
        s2 = login[t1]; // lb $s2, login($t1)
        if (s0 != 0) goto loop_first; // bnez $s0, loop_first
        goto insert_end; // j insert_end

insert_inner_last_end:
        login[t5] = s3; // sb $s3, login($t5)
        s0 = login[v0]; // lb $s0, login($v0)
        s1 = login[a3]; // lb $s1, login($a3)
        s2 = login[t1]; // lb $s2, login($t1)
        if (s0 != 0) goto loop_first; // bnez $s0, loop_first

insert_end:

    printf("---0223eeiijnpttvv\n");
    printf("%s\n", login);

    return 0;
}
