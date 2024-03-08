# Minishell

## Git

    --To see branch list--

    git branch

    --To create new branch--

    git branch "branch name"

    --To switch to a branch--

    git checkout "branch name"

    --To merge with master--

    git merge "branch name"

## Branch
    cassie branch = parsing
    rjacq branch = ...

## Autorized function
    
### Readline

    readline : char *readline(const char *prompt);
        get a line from a user with editing
        return the malloc line from prompt

#### History

    add_history : void add_history (const char *string)
        add string to the end of history list

    rl_clear_history : void rl_clear_history(void)
        clear history list

#### Redisplay

    rl_redisplay : void rl_redisplay (void)
        Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.

    rl_on_newline : int rl_on_new_line (void)
        Tell the update functions that we have moved onto a new (empty) line, usually after outputting a ne        wline.

#### Utils

    rl_replace_line : void rl_replace_line (const char *text, int clear_undo)
        Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If        clear_undo is non-zero, the undo list associated with the current line is cleared. 

### Signals

    signal  : dont use, use sigaction

    sigaction : int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
        change the action of process on receopt of specific signal

#### Signal handling

    sigemptyset : int sigemptyset(sigset_t *set);
        init signal given by set to empty

    sigaddset : int sigaddset(sigset_t *set, int signum);
        add signal signum from set

    kill : int kill(pid_t pid, int sig);
        send any signal to any process group or process

### Directory handling

    getcwd : char *getcwd(char *buf, size_t size);
        copy absolute pathname of cwd to array buf of lenght size

    chdir : int chdir(const char *path);
        changes current cwd of calling process to the directory of path

    opendir : DIR *opendir(const char *name);
        open dir stream of name and return a pointer to the stream 

    readdir : struct dirent *readdir(DIR *dirp);
        return pointer to a dirent struct of the next directory entry in the stream dirp
    
    closedir : int closedir(DIR *dirp);
        close the directory stream dirp (close all fd associated with dirp)

### File handling

    stat : int stat(const char *pathname, struct stat *statbuf);
        return information about file in the struc statbuf

    ltsat : int fstat(int fd, struct stat *statbuf);
        identical to stat excepte that if pathname is symbolic path return info of the symbolic path

    fstat : int lstat(const char *pathname, struct stat *statbuf);
        identical stat, but file is a fd
    
    unlink : int unlink(const char *pathname);
        deletes a name from the filesystem

### tty

    isatty : int isatty(int fd);
        test if fd is an open fd referring to a terminal (return 1 on sucess else 0)

    ttyname : char *ttyname(int fd);
        return pointer of pathname of the terminal open in fd (if fd is a terminal)

    ttyslot : int ttyslot(void);
        return index of the current user's entry in some file

    getenv : char *getenv(const char *name);
        search env name and return a string of the name env
    
    tcsetattr : int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
    tcgetattr : int tcgetattr(int fd, struct termios *termios_p);
        see man
    
    tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
        see man

### Known functions

    printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, 
    exit, execve, dup, dup2, pipe, strerror, perror, 

### lo pas compris

    ioctl


## Minishell todo
 
### Romain

ajouter la gestions des builts in
<< stop > test

### Camille

cat sans rien prompt * 2
pwd max size 4096 path byte
signal dans boucle infini

#### builtin


### FAIT

check erreur pre parsing et parsing ( tripe chevron , pipe vide)
unclosed quote 
cd a faire + oldpwd null at begin
export +x declare voir comment savoir si on est dans sous bash
OK reste $?(dollars dans dquote (on remplace si besoin pendant le parsing) + $?)
exit gerer argument avec atoi et la valeur retourner par lexec;
export faire le tri 
echo a finir + -n
mettre a jour la liste chainee
segfault avec commande '<'in
pwd fini
env
unset finir delete chainnons list
pipe dans quote semble ok

a gerer cat'<'infile ok
## Command to keep for final test

 ...
