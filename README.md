![pipexm](https://github.com/mc-putchar/pipex/assets/126549052/4fc8793c-db77-4995-be15-29c48fd3c9c0)

# Pipex

## Description
<p>
Pipex is a C project that simulates the functionality of the shell command `< file1 cmd1 | cmd2 > file2`.<br>
It takes minimum of four arguments: `file1`, `cmd1`, `cmd2`, and `file2`.<br>
The program reads the contents of `file1`, applies `cmd1` to the input, then applies `cmd2` to the output, and finally writes the result to `file2`.<br>
It can also handle multiple pipes chained into a pipeline, as well as rudimentary here_doc support to read from standard input
  </p>

## Usage

```bash
$> ./pipex file1 cmd1 cmd2 ... cmdn file2
```
Behaves like bash command:
```bash
$> < file1 cmd1 | cmd2 ... | cmdn > file2
```
  
### Heredoc
For reading from standard input, provide keyword **here_doc** or **<<** or **"-"**<br>
As per requirements of the project, final output is **appended** to file, instead of overwriting it. 
It also handles multiple pipes.
```bash
$> ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file
```
Behaves like: 
```bash
cmd1 << LIMITER | cmd2 ... | cmdn >> file
```

## Dependecies
+ <unistd.h>
+ <stdlib.h>
+ <fcntl.h>
+ <sys/types.h>
+ <sys/wait.h>
+ <errno.h>
+ <string.h>
