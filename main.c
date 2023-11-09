#include <stdio.h>

int main(void) {
    char login[] = "edcba";
    int v0, v1, a0, a1, t0, a2, a3, t1, t2, t3, t5;
    char s0, s1, s2;
    int zero = 0;

        t2 = zero + -1;
        v0 = zero + 2;
        t1 = zero + 0; // daddi $t1, $zero, 0
        a3 = zero + 1; // daddi $a2, $zero, 1

        s0 = login[v0]; // lb $s0, login($a2)

loop:
        s1 = login[a3]; // lb $s1, login($a2)
        s2 = login[t1]; // lb $s2, login($t1)
        t5 = a3 + 1; // daddi $t5, $a2, 1
        a1 = s0 < s1; // sltu $a1, $s0, $s1
        a2 = s0 < s2; // sltu $a2, $s0, $s2
        t1 = t1 + -2; // daddi $t1, $t1, -1
        if (a1 == 0) goto insert_end; // beqz $a1, insert_inner_end
        if (a2 == 0) goto insert_end; // beqz $a2, insert_inner_end
        login[t5] = s1; // sb $s1, login($t5)
        login[a3] = s2; // sb $s2, login($a2)
        a3 = a3 + -2; // daddi $a2, $a2, -1
        if (t1 >= 0) goto loop; // bgez $t1, loop

insert_inner_last:
        t5 = a3 + 1;
        if (a3 == t2) goto insert_inner_end;
        s1 = login[a3];
        a1 = s0 < s1;
        if (a1 == 0) goto insert_inner_end;
        login[t5] = s1;
        t5 = t5 + -1;

insert_inner_end:
        s1 = login[v0]; // lb $s1, login($v0)
        a3 = v0 + 0; // daddi $a2, $a2, 1
        v0 = v0 + 1; // daddi $v0, $v0, 1
        login[t5] = s0; // sb $s0, login($a2)
        t1 = a3 + -1;
        s0 = login[v0]; // lb $s0, login($v0)

        if (s0 != 0) goto loop;

insert_end:

    printf("---0223eeiijnpttvv\n");
    printf("%s\n", login);

    return 0;
}
