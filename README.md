# Open MP - Concurrent Programming

## Introduction
Matrix multiplication is a basic computational methodology that is used in engineering application
such as pixel value computation in image processing, digital signal processing and general graph
solving problems. Generally, large matrix multiplication requires higher computational time and its
complexity is also O (𝑛􀬷). Due to the fact that many computational throughputs require minimum time thus
many sequential and parallel algorithms are developed. In this report, I have presented, implemented and
analysed matrix multiplication using block method algorithm. Evidence of performance analysis is evaluated
and a comparison study is detailed out on block method algorithm with their computational speedup/time
values.

## Objective
The design principle and method that I have analysed and implemented is a block matrix
multiplication algorithm. In this method, the matrix is assumed to be broken into to sections called
blocks or submatrices. It can also be viewed as a computing collection of smaller matrices. The
main objective of this algorithm is to reduce the communication between two processors that are
parallelly performing matrix multiplication.

## Tools Used
Intel® i5 processor with 1.6Ghz and with 8 GB memory is used to implement block matrix
multiplication. Visual Studio 2019 with OpenMP library is used as an environment for building,
executing and testing matrix multiplication code. Distributed processing of matrices is carried out
by launching different threads from 1 to 4 in steps of 2.

