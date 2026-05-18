*This project has been created as part of the 42 curriculum by dijonker*  

---
# Description
## Goal
To solve a modified dining philosophers problem with the application of multithreading.  

## Overview  
### Scheduling
#### EDF
When two coders request a dongle the coder with the earlies time to burnout must own the dongle  
  
The dongles request the dongle and fills a queue. When the queue has recieved two request the two coders,  
time since loop start are compared and dongle ownership is assigned to coder with a earlier time. The coder with  
a later time is assigned as the next owner of the dongle.  
To optimise efficiency when two coders have equal time, the coder that has an even id is prioritised. This is done so that  
a coder has a larger chance of recieving two dongles, reducin the amount of coders hoarding one dongle.  

#### FIFO
When two coders request a dongle, the one which requested it the earliest recieve the dongle 

The dongles ownership is set to the first coder who takes it. The next coder waits until the dongle is let go.  
When a dongle is taken by a coder it takes two at a time to optimise efficiency, otherwise it takes none and waits  
until it can take two.

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
./codexion number_of_coders time_to_burnout time_to_compile time_to_refactor time_to_debug compilations_per_coder dongle_cooldown_time scheduler

**number_of_coders** - how many coders are present  
**compilations_per_coder** - how many compilations is required from each coder  
**time_to_burnout** - time since start of program or last compilation a coders must compile in  
**time_to_compile** - time taken to compile  
**time_to_refactor** - time it takes to refactor  
**time_to_debug** - time taken to debug  
**dongle_cooldown** - time after a dongle is set back on table it may not be used  
**scheduler** - the priority system a coder aquires dongles  

## Makefile
#### Make all
Creates an archive and a binary from the source files
  
#### Make run
Runs the program with pre-set paramaters

#### Make clean
Removes the objects directory

#### Make fclean
Removes the object and bin directory and codexion binary

#### Make re
Removes the object and bin directory and codexion binary, then creates an archive and a binary from the source files  

#### Make memory
Validates the memory usage of the codexion binary using Valgrind

#### Make helgrind
Validates threads using the Helgrind flag of Valgrind

---
# Resources

## General
- [ANSI - fnky](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797)  
- [Multi Threading - CodeVault](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)  
- [Philosophers Problem - GeeksForGeeks](https://www.geeksforgeeks.org/operating-systems/dining-philosophers-problem/)  
- [Helgrind Manual](https://valgrind.org/docs/manual/hg-manual.html)

## AI
None ( ͡° ͜ʖ ͡°)

---

The README.md must include at least:
• A “Description” section that clearly presents the project, including its goal and a
brief overview.
• An “Instructions” section containing any relevant information about compilation,
installation, and/or execution.
• A “Resources” section listing classic references related to the topic (documentation, articles, tutorials, etc.), as well as a description of how AI was used —
specifying for which tasks and which parts of the project.
➠ Additional sections may be required depending on the project (e.g., usage
examples, feature list, technical choices, etc.).
Any required additions will be explicitly listed below.
For this project, the README.md must also include:
• A “Blocking cases handled” section describing all the concurrency issues addressed in your solution (e.g., deadlock prevention and Coffman’s conditions, starvation prevention, cooldown handling, precise burnout detection, and log serialization).
• A “Thread synchronization mechanisms” section explaining the specific threading primitives used in your implementation (pthread_mutex_t, pthread_cond_t,
custom event implementation) and how they coordinate access to shared resources
(dongles, logging, monitor state). Include examples of how race conditions are
prevented