# Zishan Kazi (2019111031)

## Instructions 
1. type `make`
2. `./shell` to run

## Description

1. header.h - consists of all headers.
2. shell.c - the main/master file.
    - semicolon_tokenize - divides input with `;` as delimiter
    - actual_path - returns actual path from root 
    - relative_paths - returns relative paths 
    - prompt - prints prompt
3. cd.c 
    - CD
4. echo.c 
    - ECHO
5. exit_stat - Used for printing status of background process when finished
    - EXIT_STAT

6. input.c - execution file 
    - filter_token - Every command tokenized with `" \n\t\r"` delimiters
    - execute - it sends commands to the specific `x.c` file to execute
7. ls.c 
    - LS
    - print_permissions
    - ls_l_a
    - ls_l
    - ls_a
8. pinfo.c - prints process information of process
    - PINFO
9. pwd.c - prints current working directory from the root
    - PWD
10. rest.c - Background & Other Foreground processes are implemented
    - REST
    - foreground - executes other commands
    - background - executes commands with & at the end in background

### BONUS
1. history.c 
    - load_hist: loads at start of int main 
    - history_add: Adds input to the hist[] char array
    - HISTORY
    - hist_exit: writes hist[] char array into history.txt file
    - Similar to history in terminal
    - Can store upto 20 commands. E.g: `history 20`
    - `history` prints previous 10 commands (if available) or less commands
2. nightswatch.c 
    - `interrupt` argument prints the number of times CPU has been interrupted by keyboard
    - Executes every `n` seconds specified by user

## Assumptions

1. nightswatch
    - Only `interrupt` has been implemented
    - Pressing `q` doesn't directly exit the program, we need to press `q+enter`. 
2. Many char arrays store 1024 or 2048 characters in it. Its assumed that it will not overflow.
3. No. of background processes should be less than 1000.
4. Running background processes and then exiting thorough `Ctrl+C` will give error (Ctrl+C handling is not implemented).
5. Process exit status (E.g: process exited normally) is printed after next prompt.