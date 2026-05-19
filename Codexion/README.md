*This project has been created as part of the 42 curriculum by dijonker*  

---
# Description
## Goal
To solve a modified dining philosophers problem with the application of multithreading.  

## Overview  
### Scheduling
#### EDF
When two coders request a dongle the coder with the earlies time to burnout must own the dongle  
  
EDF scehduling has two queues. The first bieng the request queue. A dongle's owner can not be set when there is not two request waiting on it. After the queue is filled the loop_start_time is compared and the owner and next is assigned. When released the owner becomes the id stored in next and next is set to 0.

#### FIFO
When two coders request a dongle, the one which requested it the earliest recieve the dongle 

When requesting a dongle, the owner is set when either the owner or next field is set to 0 eg. ownerless. This cretes the equivalent of a queue as it dongles can only be aquired by the coder with the highest priority. When releasing the next becomes the owner and the next is reset to 0, meaning ownership can be assigned to that field.

#### Optimisation
When a coder aquires, it must ideally aquire two dongles. The reason for this is if they aquire one it is highly probable that it will form a queue where a series all wait for the left. This does not create a race condition, but it does make the code inefficient.  
To prevent this in FIFO, the coder aquires two dongles at a time, other as the owner or the next_owner.
To prevent it in EDF, when the loop_start_time (equivalent to time_to_burnout) is equal, the even coder id is prioritised. This is done so that there is a higher chance that coders aquire two dongles.

### Monotoring
Monotoring is a thread that runs each 900 microseconds. This will compare the time loop start of a coder to their time to burnout.  
If it has passed the threshold it will burnout, otherwise it is left along. To make the end of program efficient one simple variable is checked by the function has_stopped to see if a thread should continue with its execution.
To further optimise burnout, when a coder enters a sleep cycles. it calculates if it will pass the time to burnout and change the time to fit.

## Structure
#### ./coders
Directory with all the header files
#### ./src
Drectory with all the extra source files other than main

---
# Instructions
## Paramaters
> ./codexion number_of_coders time_to_burnout time_to_compile time_to_refactor time_to_debug compilations_per_coder dongle_cooldown_time scheduler  

| ___Variable___ | ___Description___ |
| :--- | :---: |
| **number_of_coders** | How many coders are present |
| **number_of_coders** | how many coders are present |
| **compilations_per_coder** | how many compilations is required from each coder |  
| **time_to_burnout** | time since start of program or last compilation a coders must compile in   |
| **time_to_compile** | time taken to compile   |
| **time_to_refactor** | time it takes to refactor   |
| **time_to_debug** | time taken to debug   |
| **dongle_cooldown** | time after a dongle is set back on table it may not be used  | 
| **scheduler** | the priority system a coder aquires dongles   |

## Makefile
> **make all**  

Creates an archive and a binary from the source files  

---
  
> **make run**  

Runs the program with pre-set paramaters  

---

> **make clean**  

Removes the objects directory  

---

> **make fclean**  

Removes the object and bin directory and codexion binary  

---

> **make re**  

Removes the object and bin directory and codexion binary, then creates an archive and a binary from the source files  

---

> ** make memory **  

Validates the memory usage of the codexion binary using Valgrind  

---

> **make helgrind**  

Validates threads using the Helgrind flag of Valgrind  

---
# Resources

## General
- [ANSI - fnky](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797)  
- [Multi Threading - CodeVault](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)  
- [Philosophers Problem - GeeksForGeeks](https://www.geeksforgeeks.org/operating-systems/dining-philosophers-problem/)  
- [Helgrind Manual](https://valgrind.org/docs/manual/hg-manual.html)

## AI
None  
( ͡° ͜ʖ ͡°)

---
