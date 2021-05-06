## App launch program

Goal

```
latinlaunch -n/--numvoc numvoc -f/--vocfile filename.csv command
```
1. Use csv voc file to ask `numvoc` words from it (separate program for asking a certain amount of words given a csv file as an input)
	1. exec this word asking program after forking
	1. redirect output of program to stdout
	1. redirect stdin to input of program (at least one correct meaning needs to be typed in)
	1. wait for the child process to finish
1. exec `command`

## Voc learning program

```
latinlearn
```

Make a **python** script with a queue data type from `deque` asking a certain number of random words from the given tab separated file (every word will be put back onto the queue until it was answered with at least one correct meaning)


(((
1. Detect whether Overwatch.exe is running (use `kill(pid, 0)`)
2. Print informative message
3. try to SIGTSTP Overwatch.exe
4. then continue with SIGCONT
5. find way to effectively train a specified number of latin voc
6. fork latin training process
7. wait for it to finish
8. SIGCONT Overwatch.exe
)))
