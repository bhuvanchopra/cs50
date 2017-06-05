# cs50
It is a repository of all my programs written for solving problem sets in the CS50 course of Harvard University.

It is a C program that determines whether a provided credit card number is valid according to Luhn’s algorithm.

In addition to that, the program is written in such a manner that it can also print the credit card's company name
(either AMEX or VISA or MASTERCARD). So the output set of the program is { AMEX, VISA, MASTERCARD, INVALID }.

Most cards use this algorithm invented by Hans Peter Luhn, a fellow from IBM. According to Luhn’s algorithm, 
we can determine if a credit card number is (syntactically) valid as follows:

1. Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products' digits together.
2. Add the sum to the sum of the digits that weren’t multiplied by 2.
3. If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
