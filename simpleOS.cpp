#include <iostream>
#include <fstream>
#include <filesystem>
#include "operations.h"
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;


/**
 * This function to display all the available commands.
 */
void display_help() {
    std::cout << "Available commands:\n"
              << "  help              - Show this help message\n"
              << "  ls                - List files and directories in the current directory\n"
              << "  create <dir>      - Create a new directory\n"
              << "  create_file <file> - Create a new file\n"
              << "  cd <path>         - Change current directory to <path>\n"
              << "  delete <path>     - Delete a file or directory\n"
              << "  move <src> <dest> - Move a file or directory from <src> to <dest>\n"
              << "  rename <old> <new> - Rename a file or directory from <old> to <new>\n"
              << "  exit              - Exit the shell\n"
              << "\nExamples:\n"
              << "  create test_dir            - Creates a directory named 'test_dir'\n"
              << "  create_file example.txt    - Creates a file named 'example.txt'\n"
              << "  cd test_dir                - Changes current directory to 'test_dir'\n"
              << "  ls                         - Lists the contents of the current directory\n"
              << "  delete test_dir            - Deletes the directory 'test_dir' and its contents\n"
              << "  move example.txt test_dir/ - Moves 'example.txt' into 'test_dir/'\n"
              << "  rename old_name.txt new_name.txt - Renames 'old_name.txt' to 'new_name.txt'\n"
              << "  exit                       - Exit the shell\n";
}


/**
 * This function to display a start menu for new user.
 */
void start_menu() {
    std::string choice;

    while (true) {
        std::cout << "\n============== Welcome ==============\n";
        std::cout << "1. Start Shell\n";
        std::cout << "2. Help\n";
        std::cout << "3. Exit\n";
        std::cout << "=====================================\n";
        std::cout << "Enter your choice: ";
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::cout << "Starting Shell...\n";
            return; 
        } else if (choice == "2") {
            display_help();
        } else if (choice == "3") {
            std::cout << "Exiting program. Goodbye!\n";
            exit(0); 
        } else {
            std::cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }
}

int main() {
    // Display the start menu and ask for initial user input
    start_menu(); 
    std::string current_dir = fs::current_path().string();
    std::string user_input;
    std::string command;
    std::string arguments;

    std::cout << "\n========== Simple OS Project==========\n";
    std::cout << "Type 'help' to view the list of available commands." << std::endl;
    // Start shell operations only after user selects "1" to start
    while (true) {
        std::cout << "[" << current_dir << "] MyShell> ";
        std::getline(std::cin, user_input);

        if (user_input.empty()) {
            continue;
        }

        std::istringstream input_stream(user_input);
        command.clear();
        arguments.clear();
        input_stream >> command;
        std::getline(input_stream, arguments);
        size_t first_non_space = arguments.find_first_not_of(' ');
        if (first_non_space != std::string::npos) {
            arguments = arguments.substr(first_non_space);
        } else {
            arguments.clear(); 
        }

        if (command == "exit") {
            break;
        } else if (command == "help") {
            display_help();
        } else if (command == "ls") {
            list_directory(current_dir);
        } else if (command == "create" && !arguments.empty()) {
            create_directory(arguments);
        } else if (command == "create_file" && !arguments.empty()) {
            create_file(arguments);
        } else if (command == "cd" && !arguments.empty()) {
            change_directory(arguments);
            current_dir = fs::current_path().string();
        } else if (command == "delete" && !arguments.empty()) {
            delete_item(arguments);
        } else if (command == "move") {
            std::string src, dest;
            std::istringstream args_stream(arguments);
            args_stream >> src >> dest;
            if (!src.empty() && !dest.empty()) {
                move_item(src, dest);
            } else {
                std::cout << "Invalid arguments for 'move'. Usage: move <src> <dest>" << std::endl;
            }
        } else if (command == "rename") {
            std::string old_name, new_name;
            std::istringstream args_stream(arguments);
            args_stream >> old_name >> new_name;
            if (!old_name.empty() && !new_name.empty()) {
                rename_item(old_name, new_name);
            } else {
                std::cout << "Invalid arguments for 'rename'. Usage: rename <old> <new>" << std::endl;
            }
        }else {
            std::cout << "Unknown command or missing argument." << std::endl;
        }
    }

    return 0;
}
