# README #

### What is intpart for? ###

* Silly but unfortunately necessary code for creating an integer partition given certain constraints.

### Can you give an example? ###

* Say you have 32 discrete resources, and you want to partition them up among 4 users at arbitrary ratios respecting fractions ( 1/6, 1/4, 1/3, 1/4 ). `intpart`  can help you to create an *integer* partitioning of 16 which best respects this goal: (5, 8, 11, 8).
* What if you wanted to restrict the resources to being allocated in groups of 3? Intpart will suggest (6, 9, 9, 6), which only sums to 30 but is the best we can do since 32 % 3 is 2.

### Who do I talk to? ###

* tcreech@umd.edu
