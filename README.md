# 👚 Microshell

---

A minimal shell built in C as part of the ALX Software Engineering curriculum.

---

## 📚 Project Description

---

This project is a simplified version of a Unix shell. It supports executing basic commands, chaining commands with `;`, and connecting commands using pipes `|`.

The goal is to gain a deep understanding of process creation, execution, file descriptors, and inter-process communication using system calls like `fork`, `execve`, `pipe`, and `wait`.

---

## 🚀 Features

---

* Execute simple shell commands (e.g., `ls`, `echo`, `pwd`)
* Support for command separators `;`
* Support for pipelines using `|`
* Built-in support for `cd`
* Proper error handling and exit codes
* Manual path resolution using `/bin/` prefix

---

## ⚙️ Usage

---

```bash
./microshell ls -l \| grep .c \; echo done
```

This command will:

1. List all files using `ls -l`
2. Filter output through `grep .c` using a pipe
3. After the pipe finishes, `echo done` is executed

---

## 🔧 How it works

---

1. **Parsing**
   The program iterates over arguments and identifies separators `|` and `;`

2. **Built-in Handling**
   If the command is `cd`, it is handled internally using `chdir()`

3. **Execution**

   * A child process is created with `fork()`
   * The command is run with `execve()` (after prepending `/bin/` manually)
   * If piped, the input/output is redirected using `pipe()` and `dup2()`

4. **Error Handling**
   Custom error messages are printed to `stderr` if something fails

5. **Synchronization**
   The parent waits for child processes with `waitpid()`

---

## 📁 File Structure

---

```bash
microshell/
│
├── microshell.c       # All logic: parsing, execution, piping, etc.
├── Makefile
└── README.md
```

---

## 📌 System Calls Used

---

* `fork()`
* `execve()`
* `pipe()`
* `dup2()`
* `waitpid()`
* `chdir()`
* `write()`
* `malloc()`

---

## 🧐 What I Learned

---

* Deep understanding of how Unix shells work internally
* Handling built-in commands manually
* Working with file descriptors and pipes
* Error handling and memory allocation in C

---

## 👨‍💻 Author

---

Made with ❤️ by [Samir — @Samir-Ouaammou](https://github.com/Samir-Ouaammou)
Project part of [ALX SE Program](https://www.alxafrica.com/)

---

## 📝 License

---

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
