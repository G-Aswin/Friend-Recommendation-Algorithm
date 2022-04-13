# Friend-Recommendation-Algorithm
A menu driven C Program written to simulate the workings of a friendship graph.

## Motivation behind Friend-Recommendation-Algorithm
- During my second semester, we were given the task of writing a program with a fair amount of complexity only using C language. At that time, I was unaware of the powers of C in the world of unix programming, but still I wanted to make something interesting.
- I was always fascinated to know how the big social media apps manage the connection data, and after some research it was evident that they use graph theory extensively.
- Once a friendship graph is established, numerous advanced graph algorithms can be used to manage and analyse the friendship graph to suggest more connections.
- Hence I decided to make something similar, albeit a bit simpler, but I wanted to mimic the process of storing and recommending connections.

## Directory Structure
- `prototypes.h` : a file which contains the structure definition of a user and also all the functions that have been used in main.c
- `functionDefinitions.c` : contains all the implementation details of each function mentioned in `prototypes.h`.
- `main.c` : the driver code. Contains the menu driven execution details as well as any data validation and conversion before calling functions from `functionDefinitions.c`.

## Sample Graph

![Sample Graph](/sample.jpg)

## Some functions written in the program

<pre><code>1. Add and display a user
2. Add and remove friends
3. Display friends of a user
4. Recommend friends based on mutuals
5. Recommend friends based on hobbies</code></pre>
