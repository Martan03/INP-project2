#include <stdio.h>

int main(void) {
    char login[] = "acb";
    int v0, v1, a0, a1, t0, a2, a3, t1, t2, t3, t4, t5;
    char s0, s1, s2, s3, s4, s5;
    int zero = 0;

        s3 = login[zero]; // lb $s3, login($zero)
        v1 = zero + 1; // daddi $v1, $zero, 1
        t0 = zero + 2; // daddi $t0, $zero, 2
        if (s3 == 0) goto insert_end; // beqz $s3, insert_end

        s2 = login[v1]; // lb $s2, login($v1)
        t3 = zero + 3; // daddi $t3, $zero, 3
        t2 = zero + 1; // daddi $t2, $zero, 1
        if (s2 == 0) goto insert_end; // beqz $s2, insert_end

        s0 = login[t0]; // lb $s0, login($t0)
        t1 = zero + 3; // daddi $t1, $zero, 3
        a0 = s2 < s3; // sltu $a0, $s2, $s3
        if (s0 == 0) goto insert_end2; // beqz $s0, insert_end2

        s1 = login[t1]; // lb $s1, login($t1)
        if (a0 == 0) goto prep; // beqz $a0, prep

        login[zero] = s2; // sb $s2, login($zero)
        login[v1] = s3; // sb $s3, login($v1)
        s2 = login[v1]; // lb $s2, login($v1)
        s3 = login[zero]; // lb $s3, login($zero)
prep:
        if (s1 == 0) goto insert_end_swap; // beqz $s1, insert_end_swap

        a1 = s0 < s1; // sltu $a1, $s0, $s1
        t3 = zero + 0; // daddi $t3, $zero, 0
        v0 = zero + 4; // daddi $v0, $zero, 4
        if (a1 != 0) goto insert_skip; // bnez $a1, insert_skip
        s0 = login[t1]; // lb $s0, login($t1)
        s1 = login[t0]; // lb $s1, login($t0)
        goto insert_skip; // j insert_skip

insert_cmp:
        a0 = s0 < s1; // sltu $a0, $s0, $s1
        s2 = login[t2]; // lb $s2, login($t2)
        s3 = login[t3]; // lb $s3, login($t3)
        if (a0 != 0) goto insert_skip; // bnez $a0, insert_skip
        s0 = login[t1]; // lb $s0, login($t1)
        s1 = login[t0]; // lb $s1, login($t0)
        goto insert_skip; // j insert_skip

// ; Checks if larger value from the two chars I sort is smaller then current char
// ; If so, moves current char two places to the right, else inserts larger char
// ; to the string and continues to sort remaining char to the string
// ; I needed to use 4 indexes so in order to reduce instructions count I have
// ; two loops next to each other with index reusing
// ; (1. loop $t3, $t2, $t0, $t1, 2. loop $t0, $t1, $t3, $t2)
insert:
        s2 = login[t2]; // lb $s2, login($t2)
        s3 = login[t3]; // lb $s3, login($t3)
insert_skip:
        // ; nop
        a0 = s1 < s2; // sltu $a0, $s1, $s2
        a1 = s1 < s3; // sltu $a1, $s1, $s3
        login[t1] = s2; // sb $s2, login($t1)
        if (a0 == 0) goto insert_inner_end; // beqz $a0, insert_inner_end
        t1 = t1 + -4; // daddi $t1, $t1, -4
        if (a1 == 0) goto insert_inner_end1; // beqz $a1, insert_inner_end1
        login[t0] = s3; // sb $s3, login($t0)
        t0 = t0 + -4; // daddi $t0, $t0, -4

        if (t1 >= 0) goto insert1; // bgez $t1, insert1
        goto insert_outer_end; // j insert_outer_end

insert1:
        s2 = login[t1]; // lb $s2, login($t1)
        s3 = login[t0]; // lb $s3, login($t0)
        // ; nop
        a0 = s1 < s2; // sltu $a0, $s1, $s2
        a1 = s1 < s3; // sltu $a1, $s1, $s3
        login[t2] = s2; // sb $s2, login($t2)
        if (a0 == 0) goto insert_inner_end2; // beqz $a0, insert_inner_end2
        t2 = t2 + -4; // daddi $t2, $t2, -4
        if (a1 == 0) goto insert_inner_end3; // beqz $a1, insert_inner_end3
        login[t3] = s3; // sb $s3, login($t3)
        t3 = t3 + -4; // daddi $t3, $t3, -4

        if (t2 >= 0) goto insert; // bgez $t2, insert

insert_outer_end:
        login[v1] = s1; // sb $s1, login($v1)
        login[zero] = s0; // sb $s0, login($zero)
        s0 = login[v0]; // lb $s0, login($v0)
        t1 = v0 + 1; // daddi $t1, $v0, 1
        t0 = v0 + 0; // daddi $t0, $v0, 0
        if (s0 == 0) goto insert_end; // beqz $s0, insert_end
        s1 = login[t1]; // lb $s1, login($t1)
        t2 = v0 + -1; // daddi $t2, $v0, -1
        t3 = v0 + -2; // daddi $t3, $v0, -2
        v0 = v0 + 2; // daddi $v0, $v0, 2
        if (s1 != 0) goto insert_cmp; // bnez $s1, insert_cmp
        goto insert_single_prep; // j insert_single_prep

insert_inner_end:
        login[t1] = s1; // sb $s1, login($t1)
        t1 = t1 + -1; // daddi $t1, $t1, -1
        goto insert_single; // j insert_single

insert_inner_end1:
        login[t0] = s1; // sb $s1, login($t0)
        t1 = t1 + 2; // daddi $t1, $t1, 2
        goto insert_single_last; // j insert_single_last

insert_inner_end2:
        login[t2] = s1; // sb $s1, login($t2)
        t1 = t3 + 0; // daddi $t1, $t3, 0
        t3 = t3 + -2; // daddi $t3, $t3, -2
        t2 = t2 + -2; // daddi $t2, $t2, -2
        goto insert_single; // j insert_single

insert_inner_end3:
        login[t3] = s1; // sb $s1, login($t3)
        t1 = t3 + -1; // daddi $t1, $t3, -1
        t2 = t2 + 2; // daddi $t2, $t2, 2
        t3 = t3 + -2; // daddi $t3, $t3, -2
        goto insert_single_last; // j insert_single_last

// ; Checks if remaining char is smaller then current char. If so it moves it to
// ; the right one place, else it writes remaining char to the string and starts
// ; new iteration of inserting two chars at the time
insert_single_prep:
        s2 = login[t2]; // lb $s2, login($t2)
        s3 = login[t3]; // lb $s3, login($t3)

insert_single:
        t5 = t2 + 1; // daddi $t5, $t2, 1
        a0 = s0 < s2; // sltu $a0, $s0, $s2
        a1 = s0 < s3; // sltu $a1, $s0, $s3
        t3 = t3 + -2; // daddi $t3, $t3, -2
        if (a0 == 0) goto insert_single_end1; // beqz $a0, insert_single_end1
        login[t5] = s2; // sb $s2, login($t5)
        if (a1 == 0) goto insert_single_end2; // beqz $a1, insert_single_end2
        login[t2] = s3; // sb $s3, login($t2)
        t2 = t2 + -2; // daddi $t2, $t2, -2

        if (t3 >= 0) goto insert_single_prep; // bgez $t3, insert_single_prep

        login[zero] = s0; // sb $s0, login($zero)
        s0 = login[v0]; // lb $s0, login($v0)
        t1 = v0 + 1; // daddi $t1, $v0, 1
        t0 = v0 + 0; // daddi $t0, $v0, 0
        if (s0 == 0) goto insert_end; // beqz $s0, insert_end
        s1 = login[t1]; // lb $s1, login($t1)
        t2 = v0 + -1; // daddi $t2, $v0, -1
        t3 = v0 + -2; // daddi $t3, $v0, -2
        v0 = v0 + 2; // daddi $v0, $v0, 2
        if (s1 != 0) goto insert_cmp; // bnez $s1, insert_cmp
        v0 = v0 + -1;
        goto insert_single_prep; // j insert_single

insert_single_end1:
        login[t5] = s0; // sb $s0, login($t5)
        s0 = login[v0]; // lb $s0, login($v0)
        t1 = v0 + 1; // daddi $t1, $v0, 1
        t0 = v0 + 0; // daddi $t0, $v0, 0
        if (s0 == 0) goto insert_end; // beqz $s0, insert_end
        s1 = login[t1]; // lb $s1, login($t1)
        t2 = v0 + -1; // daddi $t2, $v0, -1
        t3 = v0 + -2; // daddi $t3, $v0, -2
        v0 = v0 + 2; // daddi $v0, $v0, 2
        if (s1 != 0) goto insert_cmp; // bnez $s1, insert_cmp
        v0 = v0 + -1;
        goto insert_single_prep; // j insert_single

insert_single_end2:
        login[t2] = s0; // sb $s0, login($t2)
        s0 = login[v0]; // lb $s0, login($v0)
        t1 = v0 + 1; // daddi $t1, $v0, 1
        t0 = v0 + 0; // daddi $t0, $v0, 0
        if (s0 == 0) goto insert_end; // beqz $s0, insert_end
        s1 = login[t1]; // lb $s1, login($t1)
        t2 = v0 + -1; // daddi $t2, $v0, -1
        t3 = v0 + -2; // daddi $t3, $v0, -2
        v0 = v0 + 2; // daddi $v0, $v0, 2
        if (s1 != 0) goto insert_cmp; // bnez $s1, insert_cmp
        v0 = v0 + -1;
        goto insert_single_prep; // j insert_single

insert_single_last:
        a0 = s0 < s3; // sltu $a0, $s0, $s3
        t2 = t2 + -2; // daddi $t2, $t2, -2
        t3 = t3 + -2; // daddi $t3, $t3, -2
        if (a0 == 0) goto insert_single_last_end; // beqz $a0, insert_single_last_end
        login[t1] = s3; // sb $s3, login($t1)
        t1 = t1 + -1; // daddi $t1, $t1, -1

        if (t3 >= 0) goto insert_single_prep; // bgez $t3, insert_single_prep

insert_single_last_end:
        t2 = v0 + -1; // daddi $t2, $v0, -1
        login[t1] = s0; // sb $s0, login($t1)
        s0 = login[v0]; // lb $s0, login($v0)
        t1 = v0 + 1; // daddi $t1, $v0, 1
        t0 = v0 + 0; // daddi $t0, $v0, 0
        if (s0 == 0) goto insert_end; // beqz $s0, insert_end
        s1 = login[t1]; // lb $s1, login($t1)
        t3 = v0 + -2; // daddi $t3, $v0, -2
        v0 = v0 + 2; // daddi $v0, $v0, 2
        if (s1 != 0) goto insert_cmp; // bnez $s1, insert_cmp
        v0 = v0 + -1; // daddi $v0, $v0, -1
        goto insert_single_prep; // j insert_single_prep

insert_end_swap:
        a0 = s0 < s2; // sltu $a0, $s0, $s2
        // ; nop
        // ; nop
        if (a0 == 0) goto insert_end; // beqz $a0, insert_end
        login[t0] = s2; // sb $s2, login($t0)

        a0 = s0 < s3; // sltu $a0, $s0, $s2
        login[v1] = s0;
        // ; nop
        if (a0 == 0) goto insert_end; // beqz $a0, insert_end_swap_end
        login[zero] = s0; // sb $s0, login($zero)
        login[v1] = s3; // sb $s2, login($v1)
        goto insert_end; // j insert_end

insert_end2:
        if (a0 == 0) goto insert_end; // beqz $a0, insert_end
        login[zero] = s2; // sb $s2, login($zero)
        login[v1] = s3; // sb $s3, login($v1)
        goto insert_end; // j insert_end

insert_end:

    printf("      !,03?AJMPaaaaeeeeehhiijjjmmnnooprrsstuz\n");
    printf("%s\n", login);

    return 0;
}
