# Simple OS Project

This project is a simple command-line-based simulation of an operating system shell. It allows users to perform basic file operations, such as listing directories, creating and deleting files, moving and renaming files, and navigating through directories. It also includes a basic menu system to guide the user through the available features.

## Features

- **Help Command**: Displays a list of all available commands and examples.
- **File System Commands**:
  - `ls`: Lists files and directories in the current directory.
  - `create <dir>`: Creates a new directory.
  - `create_file <file>`: Creates a new file.
  - `cd <path>`: Changes the current directory to `<path>`.
  - `delete <path>`: Deletes a file or directory.
  - `move <src> <dest>`: Moves a file or directory from `<src>` to `<dest>`.
  - `rename <old> <new>`: Renames a file or directory from `<old>` to `<new>`.
- **Shell Interface**: A simple text-based interface where users can input commands.
- **Start Menu**: The program presents a welcome screen with options to start the shell, view the help, or exit the program.

## Requirements

- C++17 or later.
- A C++ compiler (e.g., GCC, Clang) that supports C++17 standard.
- The `<filesystem>` library (available in C++17 and above).

## Compilation and Running

1. use ` make ` to complile the file
2. Run the shell: ` make run`
