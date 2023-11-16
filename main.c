#include <stdio.h>

int main(void) {
    char login[] = "vitejte-v-inp-2023";
    int v0, v1, a0, a1, t0, a2, a3, t1, t2, t3, t4, t5;
    char s0, s1, s2, s3, s4, s5;
    int zero = 0;

        s2 = login[zero]; // lb $s2, login($zero)
        v1 = zero + 1; // daddi $v1, $zero, 1
        t0 = zero + 2; // daddi $t0, $zero, 2
        if (s2 == 0) goto insert_end; // beqz $s2, insert_end

        s0 = login[v1]; // lb $s0, login($v1)
        t1 = zero + 3; // daddi $t1, $zero, 3
        t2 = zero + 1; // daddi $t2, $zero, 1
        if (s0 == 0) goto insert_end; // beqz $s0, insert_end

        a0 = s0 < s2; // sltu $a0, $s0, $s2
        t3 = zero + 0; // daddi $t3, $zero, 0
        // ; nop
        if (a0 == 0) goto prep; // beqz $a0, prep
        login[v1] = s2; // sb $s2, login($v1)
        login[zero] = s0; // sb $s0, login($zero)

prep:
        s0 = login[t0]; // lb $s0, login($t0)
        // ; nop
        // ; nop
        if (s0 == 0) goto insert_end; // beqz $s0, insert_end

        s1 = login[t1]; // lb $s1, login($t1)
        // ; nop
        // ; nop
        if (s1 == 0) goto insert_end_swap; // beqz $s1, insert_end_swap

insert_cmp:
        a0 = s0 < s1; // sltu $a0, $s0, $s1
        // ; nop
        // ; nop
        if (a0 != 0) goto insert; // bnez $a0, insert
        s0 = login[t1]; // lb $s0, login($t1)
        s1 = login[t0]; // lb $s1, login($t0)

insert:
        s2 = login[t2]; // lb $s2, login($t2)
        s3 = login[t3]; // lb $s3, login($t3)
        t2 = t2 + -2; // daddi $t2, $t2, -2
        a0 = s1 < s2; // sltu $a0, $s1, $s2
        t3 = t3 + -2; // daddi $t3, $t3, -2
        a1 = s1 < s3; // sltu $a1, $s1, $s3
        if (a0 == 0) goto insert_inner_end; // beqz $a0, insert_inner_end
        login[t1] = s2; // sb $s2, login($t1)
        t1 = t1 + -1; // daddi $t1, $t1, -1
        if (a1 == 0) goto insert_inner_end1; // beqz $a1, insert_inner_end1
        // ; nop
        login[t1] = s3; // sb $s2, login($t1)
        t1 = t1 + -1; // daddi $t1, $t1, -1

        if (t3 >= 0) goto insert; // bgez $t3, insert

        t1 = t0 + 3; // daddi $t1, $t0, 3
        t2 = t0 + 1; // daddi $t2, $t0, 1
        t3 = t0 + 0; // daddi $t3, $t0, 0
        t0 = t0 + 2; // daddi $t0, $t0, 2
        login[zero] = s0; // sb $s0, login($zero)
        login[v1] = s1; // sb $s1, login($v1)
        s0 = login[t0]; // lb $s0, login($t0)
        // ; nop
        // ; nop
        if (s0 == 0) goto insert_end; // beqz $s0, insert_end
        s1 = login[t1]; // lb $s1, login($t1)
        // ; nop
        // ; nop
        if (s1 != 0) goto insert_cmp; // bnez $s1, insert_cmp
        goto insert_single_prep; // j insert_single_prep

insert_inner_end:
        t2 = t2 + 1;
        a0 = t3 & v1; // and $a0, $t3, $v1
        login[t1] = s1; // sb $s1, login($t1)
        t1 = t1 + -1; // daddi $t1, $t1, -1
        if (a0 != 0) goto insert_single_last; // bnez $a0, insert_single_last
        goto insert_single; // j insert_single

insert_inner_end1:

        a0 = t2 & v1; // and $a0, $t2, $v1
        login[t1] = s1; // sb $s1, login($t1)
        t1 = t1 + -1; // daddi $t1, $t1, -1
        s2 = s3 + 0; // daddi $s2, $s3, 0
        if (a0 != 0) goto insert_single_last; // bnez $a0, insert_single_last

insert_single_prep:
        s2 = login[t2]; // lb $s2, login($t2)
        t2 = t2 + -1; // daddi $t2, $t2, -1

insert_single:
        a0 = s0 < s2; // sltu $a0, $s0, $s2
        // ; nop
        // ; nop
        if (a0 == 0) goto insert_single_end; // beqz $a0, insert_single_end
        login[t1] = s2; // sb $s2, login($t1)
        t1 = t1 + -1; // daddi $t1, $t1, -1

        s2 = login[t2]; // lb $s2, login($t2)
        t2 = t2 + -1; // daddi $t2, $t2, -1
        // ; nop
        a0 = s0 < s2; // sltu $a0, $s0, $s2
        // ; nop
        // ; nop
        if (a0 == 0) goto insert_single_end; // beqz $a0, insert_single_end
        login[t1] = s2; // sb $s2, login($t1)
        t1 = t1 + -1; // daddi $t1, $t1, -1
        if (t2 >= 0) goto insert_single_prep; // bgez $t2, insert_single_prep

insert_single_end:
        login[t1] = s0; // sb $s0, login($t1)

        t1 = t0 + 3; // daddi $t1, $t0, 3
        t2 = t0 + 1; // daddi $t2, $t0, 1
        t3 = t0 + 0; // daddi $t3, $t0, 0
        t0 = t0 + 2; // daddi $t0, $t0, 2
        // ; nop
        // ; nop
        s0 = login[t0]; // lb $s0, login($t0)
        // ; nop
        // ; nop
        if (s0 == 0) goto insert_end; // beqz $s0, insert_end
        s1 = login[t1]; // lb $s1, login($t1)
        // ; nop
        // ; nop
        if (s1 != 0) goto insert_cmp; // bnez $s1, insert_cmp
        goto insert_single_prep; // j insert_single_prep

insert_single_last:
        a0 = s0 < s2; // sltu $a0, $s0, $s2
        // ; nop
        // ; nop
        if (a0 == 0) goto insert_single_last_end; // beqz $a0, insert_single_last_end
        login[t1] = s2; // sb $s2, login($t1)
        t1 = t1 + -1; // daddi $t1, $t1, -1

        if (t1 != 0) goto insert_single_prep; // bnez $t1, insert_single_prep

insert_single_last_end:
        login[t1] = s0; // sb $s0, login($t1)
        t1 = t0 + 3; // daddi $t1, $t0, 3
        t2 = t0 + 1; // daddi $t2, $t0, 1
        t3 = t0 + 0; // daddi $t3, $t0, 0
        t0 = t0 + 2; // daddi $t0, $t0, 2
        // ; nop
        // ; nop
        s0 = login[t0]; // lb $s0, login($t0)
        // ; nop
        // ; nop
        if (s0 == 0) goto insert_end; // beqz $s0, insert_end
        s1 = login[t1]; // lb $s1, login($t1)
        // ; nop
        // ; nop
        if (s1 != 0) goto insert_cmp; // bnez $s1, insert_cmp
        goto insert_single_prep; // j insert_single_prep

insert_end_swap:
        a0 = s0 < s2; // sltu $a0, $s0, $s2
        // ; nop
        // ; nop
        if (a0 == 0) goto insert_end; // beqz $a0, insert_end
        login[t0] = s2; // sb $s2, login($t0)

        s2 = login[v1]; // lb $s2, login($v1)
        // ; nop
        // ; nop
        a0 = s0 < s2; // sltu $a0, $s0, $s2
        // ; nop
        // ; nop
        if (a0 == 0) goto insert_end_swap_end; // beqz $a0, insert_end_swap_end
        login[zero] = s0; // sb $s0, login($zero)
        login[v1] = s2; // sb $s2, login($v1)
        goto insert_end; // j insert_end

insert_end_swap_end:
        login[v1] = s0; // sb $s0, login($v1)
        login[zero] = s2; // sb $s2, login($zero)

insert_end:

    printf("---0223eeiijnpttvv\n");
    printf("%s\n", login);

    return 0;
}
