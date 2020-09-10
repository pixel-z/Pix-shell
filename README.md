# Zishan Kazi (2019111031)

## Instructions 
1. type `make`
2. `./shell` to run

## Description

1. header.h - consists of all headers.
2. shell.c - the main/master file.
3. prompt.c - consists prompt display 
4. rest.c 
    - Background & Other Foreground processes are implemented

4. history.c 
    - Similar to history in terminal
    - Can store upto 20 commands. E.g: `history 20`
    - `history` prints previous 10 commands (if available) or less commands
5. nightswatch.c 
    - Only `interrupt` has been implemented
    - `interrupt` argument prints the number of times CPU has been interrupted by keyboard
    - Executes every `n` seconds specified by user
    - Pressing `q` doesn't directly exit the program, we need to press `q` and then `enter`