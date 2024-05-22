## 42 Better Stuff
this is a collection of some projects in the 42 core that for some reason i decided to place in one repository. I don't know why i thought this is a good idea, and will forever mourn the loss of the individual project's commit history. oh well.

## FT PRINTF	
A project to recode the default printf function. Uses variable arguments. Was a big headache because of all the special cases that form with combination of the formatting options. the functions have a lot of unexplained if statements for ft_printf to have the same output as the default printf.

## GET_NEXT_LINE
A function to get a complete line, terminated with a '\n' char, from a file descriptor using any buffer size (that is bigger than 0, of course).
Uses a static array of strings to hold parts of the lines that weren't returned yet, and to be able to read from multiple FDs without mixing or losing lines.

## PHILOSOPHERS
A simulation of the philosophers problem, in which the different philosophers around the table need t share forks in order to eat their spaghetti. 
**./philo** - solution using threads and s mutexes
**./philo_bonus** - using child processes and semaphores

## PUSH_SWAP
sorting an array of integers using two stacks and a set of actions.
algorithm from here:
		[Medium - Jamie Robert Dawson](https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a)

## Exams
my practice files for exams 3, 4, and 6.

**Exam 3 - gnl**:  in this exam you can get either get_next_line or printf. Printf is pretty simple, but gnl is more complex. this is the simplest solution i found for gnl.

**Exam 4 - microshell**: a small shell, uses only full path commands, and needs to implement pipes. isn't too bad but i had some problems understanding what pipes i needed to close and when.

**note: exam 05 is the cpp exam. its not too bad and there are lots of references online.**

**Exam 06 - miniserver**: allow a couple clients to chat. this uses 'select',  the older version of 'poll', which we used in ft_irc.
