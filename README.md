# Classical DFA on AES
1. AES design from scratch based on https://github.com/boppreh/aes/blob/master/aes.py and the book The Rjindael Design.
2. Differential Fault attack on round 9 in Python and C.
3. Differential Fault attack on round 8 in C.

For the program written in C.<br>
For the simple DFA on Encryption on 8th Round, it ran 11 hrs on my computer,<br>
while the DFA on Encryption on 8th Round with 2 phases takes 3.5hrs on my computer. <br>
For the 9th round Encryption it took roughly 2-5 mins. <br>

For program written in Python,<br>
It took 3.5hrs to run the 9th round Encryption. <br>

The structure of the data for AES is as follows: <br>

The matrix[i][j] means i is the column and j is the row.<br>
We converting from b0,b1,b2,....,b15 as<br>
b0 b4 b8 b12 <br>
b1 b5 b9 b13<br>
b2 b6 b10 b14<br>
b3 b7 b11 b15<br>
