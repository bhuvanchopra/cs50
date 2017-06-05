# cs50
It is a repository of all my programs written for solving problem sets in the CS50 course of Harvard University.

It is a C program that encrypts messages using Vigenère’s cipher, as shown below:

$ ./vigenere ABC
plaintext:  HELLO
ciphertext: HFNLP

In this program, the key entered is in a series of alphabets rather than in number. These alphabets have a particular
value when encrypting.

In other words, if Vigenère himself wanted to say HELLO to someone confidentially, using a keyword of ABC,
he would encrypt the H with a key of 0 (i.e., A), the E with a key of 1 (i.e., B), and the first L with a key of 
2 (i.e., C), at which point he’d be out of letters in the keyword, and so he’d reuse (part of) it to encrypt the 
second L with a key of 0 (i.e., A) again, and the O with a key of 1 (i.e., B) again. And so he’d write HELLO as HFNLP.
