Proof of concept program for xor linked lists demonstrating effortless list reversal

An exclusive-or linked list is a doubly linked list that uses an integer large enough to hold any pointer to consolidate the next and previous pointers into one value that is the exlusive or of the pointers to the previous and to the next nodes.

It does, however, beg the question as to whether or not this behavior is strictly defined under the C-standard.

In C there exists a standard datatype called intptr_t, which is an integer type such that any void pointer that is cast to it and cast back is guaranteed to compare equal to the original pointer. Any pointer when cast to void pointer and back is guaranteed, as well, to compare equal to the original.

The exclusive or bitwise operator is defined for only integer types, thus performing the exclusive or operation on a pointer uncast to an integer type is at best undefined in a conforming C environment.

Consider the following truth table of two bits a and b to se how a^b^b is strictly equal to a, and a^b^a is strictly equal to b.

a  b  a^b a^b^b  a^b^a
0  0   0    0      0
0  1   1    0      1
1  0   1    1      0
1  1   0    1      1

This logic can be extended to any two integer types of the same width, which is the mathematical logic of the list
