# Programming cpp assignments 
Computer Programming I — Homework Assignment #9

1. Let str be a string. Write a program that finds every word w in a dictionary file which satisfies one of the following three pairs of conditions:
a. the length of w is equal to the length of str, and
b. w is different from str by exactly one character.
c. the length of w is one greater than the length of str, and
d. str is equal to a substring obtained by deleting a character from w.
e. the length of w is one less than the length of str, and
f. w is equal to a substring obtained by deleting a character from str.
For example, if str is the string tabe, then the word table satisfies conditions c and d, the word tab satisfies conditions e and f, and the following words satisfy conditions a and b:
babe
tabs
take
tale
tame
tape
tube

If str is the string tabe, the contents in the output file should appear as follows:
babe
tabs
take
tale
tame
tape
tube
table
tab

2. Write a program that has the same function as the program in problem 1. All strings in this program are represented as STL strings.

3. Write a program that has the same function as the program in problem 1. All arrays of STL strings in program 2 are changed to vectors of STL strings.
