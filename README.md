## Homework T1:

Find the minimum for the following functions: [De Jong
1](http://www.geatbx.com/docu/fcnindex-01.html#P89_3085), [Schwefel's](http://www.geatbx.com/docu/fcnindex-01.html#P150_6749), [Rastrigin's](http://www.geatbx.com/docu/fcnindex-01.html#P140_6155), [Michalewicz's](http://www.geatbx.com/docu/fcnindex-01.html#P204_10395)
using the Hill Climbing (both the first improvement and best improvement variants) and Simulated Annealing algorithms

### Homework T1':

For the function $f=x^3-60x^2+900x+100$, with x in [0, 31], find the maximum.
On [0, 31], the function is uni-modal, having a single maximum point, for which the value is 10.
Study the maximisation of the function using a Hill Climbing algorithm where a candidate solution is represented on 5 bits (32 possible values, so all the integers from 0 to 31). A candidate's neighbourhood is all the bitstrings at a Hamming distance of 1. Study and explain the function landscape in the context of the first improvement and best improvement variants of the Hill Climbing algorithm. Specify the attraction basing of all local maximum points (attraction basin: the set of points for which the gradient search leads to the same optimum).

## Homework T2:

Solve Homework T1 using a Genetic Algorithm.
