 Adebunmi

Boss-Worker(sorting out prime numbers)

 Description:
This project demonstrates a boss-worker model where the boss creates worker processes to calculate prime numbers in a given range. 
The boss forks worker processes, which then execute a separate program to find and print prime numbers in assigned ranges.
It creates a text file for the prime number and displays the value.

 Files contain:
boss.cpp: The boss process that forks worker processes.
worker.cpp: The worker program that calculates prime numbers within a given range.
README.md: This file explaining the project and how to run it.

## How to Compile and Run:

Compiling the programs:
  g++ -o boss boss.cpp
  g++ -o worker worker.cpp
Attached are some process run .

