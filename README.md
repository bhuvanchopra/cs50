# cs50
It is a repository of all my programs written for solving problem sets in the CS50 course of Harvard University.

It is a C program that recovers JPEGs from a forensic image.

The program runs on the fact that every JPEG file's first three bytes are 0xff, 0xd8, and 0xff.
The fourth byte, meanwhile, is either 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 
0xea, 0xeb, 0xec, 0xed, 0xee, of 0xef.

Based on this information, every JPEG image is identified and written in a separate file.
