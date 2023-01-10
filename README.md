# Hanoi Sort 

|  |  |
| :-: | - |
| Topic | Complexity, Sorting Algorithms |
| Related | Data Structures, Algorithms & Analysis |
| Stack | C |
| Slides | [hanoi_sort_slides](https://docs.google.com/presentation/d/e/2PACX-1vTEFvmQacI0a-NeA9DnU58SuYOy3MqDvup1_kxTQklIl93tVBSGWQalBJoeJAv8oACY-o2M35ARGiqq/pub?start=false&loop=false&delayms=3000) |

# Description

The first program hanoi_sort that sorts numbers in ascending order. Hanoi Sort is a variation on the Tower of Hanoi puzzle. <br>
It has only 2 rods and a different goal: sort numbers on stack_a in the least amount of instructions possible. <br>
The allowed instructions differ from the original.<br>
The second program checker checks if any given solution is valid. <br><br>
To learn more check out the explanatory [hanoi_sort_slides](https://docs.google.com/presentation/d/e/2PACX-1vTEFvmQacI0a-NeA9DnU58SuYOy3MqDvup1_kxTQklIl93tVBSGWQalBJoeJAv8oACY-o2M35ARGiqq/pub?start=false&loop=false&delayms=3000) 

# Key features
- Use hanoi_sort to sort any number sequence in ascending order in the least amount of operations possible.
- Use checker to check if any given solution is valid: you can input solution manually or redirect hanoi_sort ouput to it.

# Getting Started

First, compile both hanoi_sort and checker programs:<br>

```bash
make
make checker
```

Then run the compiled executable with any sequence of numbers without duplicates:

```bash
./hanoi_sort 3 2 1 100

#or

ARG="3 2 1 100"; ./hanoi_sort $ARG
```

You can run the checker as follows to input sort commands manually: <br>
 
```bash
./checker 3 67 23 -90 0

#or

ARG="3 67 23 -90 0"; ./checker $ARG
```
Checker will wait for an input from your keyboard until it receives an end-of-file ( EOF ) signal produced by CTRL+D key combination.<br><br>
Input the desired sequence of commands. Follow each entered command with Enter. <br>
After you inputted all the sorting commands press CTRL+D to recieve the checker output - either OK or KO.<br>
OK means the sorting sequence is correct. KO stands for incorrect sorting sequence.

Alternatively, instead of inputting sorting sequence manually, you can use pipes to redirect hanoi_sort output to checker:
```bash
ARG="3 67 23 -90 0"; ./hanoi_sort $ARG | ./checker $ARG 
```
<br><br>
![hanoi_sort](https://i.ibb.co/68K8LDK/Screenshot-from-2023-01-10-13-04-32.png)
