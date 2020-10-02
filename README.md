# Pix-shell made by pixel-z

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
    
4. echo.c 
    
5. exit_stat - Used for printing status of background process when finished
    - EXIT_STAT

6. input.c - execution file 
    - filter_token - Every command tokenized with `" \n\t\r"` delimiters
    - execute - it sends commands to the specific `x.c` file to execute

7. ls.c - `ls [flags]`
    - lists contents in the current directory.
    - `-l`,`-a`,`-la` and `-al` flags are supported.

8. pinfo.c - `pinfo <pid>`
    - prints process information of process
    - If `<pid>` is empty, it returns info on current process.

9. pwd.c - `pwd`
    - prints current working directory from the root

10. rest.c - Background & Other Foreground processes are implemented
    - foreground - executes other commands
    - background - executes commands with & at the end in background

11. history.c - `history <num>`
    - `history` prints previous 10 commands (if available) or less commands
    - Can store upto 20 commands. E.g: `history 20`
    - load_hist: loads at start of int main 
    - history_add: Adds input to the hist[] char array
    - hist_exit: writes hist[] char array into history.txt file

12. nightswatch.c - `nightswatch -n <seconds> interrupt`
    - `interrupt` argument prints the number of times CPU has been interrupted by keyboard
    - Executes every `<seconds>` seconds specified by user
    - Press `q+enter` to end command.

13. jobs.c
    - prints all the background jobs with their status and pid.

14. kjob
    - `kjob <job number> <signal number>`
    -  background job with given job number

15. environment.c 
    - setenv() & unsetenv() are implemented

16. overkill.c - `overkill`
    - kills all the background processes

- `quit` - Exits the shell.

## Assumptions

1. Many char arrays store 1024 or 2048 characters in it. Its assumed that it will not overflow.
2. No. of background processes should be less than 1000.
3. Running background processes and then exiting thorough `Ctrl+C` will give error (Ctrl+C handling is not implemented).
4. Process exit status (E.g: process exited normally) is printed after next prompt.

## NOTE
- All functions returns:
    - `=0` value if successful
    - `>0` value if error occurs

## Features
- `CtrlD` exits the shell.