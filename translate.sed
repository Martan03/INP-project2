s/; [^\/].*/\/\/ \0/
s/lb \$([^,]*), ([^\(]*)\(\$([^\)]*)\)/\1 = \2[\3]\; \/\/ \0/g;
s/lbu \$([^,]*), ([^\(]*)\(\$([^\)]*)\)/\1 = (unsigned char)\2[\3]\; \/\/ \0/g;
s/sb \$([^,]*), ([^\(]*)\(\$([^\)]*)\)/\2[\3] = \1\; \/\/ \0/g;
s/sw \$([^,]*), ([^\(]*)\(\$([^\)]*)\)/*(int *)(\2 + \3) = \1\; \/\/ \0/g;
s/lw \$([^,]*), ([^\(]*)\(\$([^\)]*)\)/\1 = *(int *)(\2 + \3)\; \/\/ \0/g;
s/daddi \$([^,]*), \$([^,]*), (.*)/\1 = \2 + \3\; \/\/ \0/g;
s/dsub \$([^,]*), \$([^,]*), \$(.*)/\1 = \2 - \3\; \/\/ \0/g;
s/sltu \$([^,]*), \$([^,]*), \$(.*)/\1 = \2 < \3\; \/\/ \0/g;
s/dsrl \$([^,]*), \$([^,]*), (.*)/\1 = \2 >> \3\; \/\/ \0/g;
s/dsll \$([^,]*), \$([^,]*), (.*)/\1 = \2 << \3\; \/\/ \0/g;
s/andi \$([^,]*), \$([^,]*), (.*)/\1 = \2 \& \3\; \/\/ \0/g;
s/beq \$([^,]*), \$([^,]*), (.*)/if (\1 == \2) goto \3\; \/\/ \0/g;
s/bne \$([^,]*), \$([^,]*), (.*)/if (\1 != \2) goto \3\; \/\/ \0/g;
s/bgez \$([^,]*), (.*)/if (\1 >= 0) goto \2\; \/\/ \0/g;
s/beqz \$([^,]*), (.*)/if (\1 == 0) goto \2\; \/\/ \0/g;
s/bnez \$([^,]*), (.*)/if (\1 != 0) goto \2\; \/\/ \0/g;
s/j (.*)/goto \1\; \/\/ \0/g;