#include "operations.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <thread>
#include <mutex>

namespace fs = std::filesystem;
std::mutex print_lock;

void list_directory(const std::string& dir_path) {
    for (const auto& entry : fs::directory_iterator(dir_path)) {
        std::cout << entry.path().filename() << std::endl;
    }
}

void create_file(const std::string& file_name) {
    try {
        std::ofstream new_file(file_name);
        if (new_file) {
            std::cout << "File created successfully: " << file_name << std::endl;
        } else {
            std::cerr << "Failed to create file: " << file_name << std::endl;
        }
        new_file.close();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void create_directory(const std::string& dir_name) {
    if (!fs::create_directory(dir_name)) {
        std::cout << "Failed to create directory: " << dir_name << std::endl;
    } else {
        std::cout << "Directory created: " << dir_name << std::endl;
    }
}

void move_item(const std::string& src_path, const std::string& dest_path) {
    if (!fs::exists(src_path)) {
        std::cout << "Source path does not exist: " << src_path << std::endl;
        return;
    }

    try {
        if (fs::exists(dest_path) && fs::is_directory(dest_path)) {
            fs::path new_dest_path = fs::path(dest_path) / fs::path(src_path).filename();
            fs::rename(src_path, new_dest_path);
            std::cout << "Moved " << src_path << " to " << new_dest_path.string() << std::endl;
        } else {
            fs::rename(src_path, dest_path);
            std::cout << "Renamed " << src_path << " to " << dest_path << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error moving file/directory: " << e.what() << std::endl;
    }
}

void change_directory(const std::string& dir_path) {
    fs::current_path(dir_path);
    std::cout << "Switched to Directory: " << fs::current_path().string() << std::endl;
}

void delete_item(const std::string& path) {
    if (fs::exists(path)) {
        try {
            if (fs::is_directory(path)) {
                fs::remove_all(path);
                std::cout << "Directory deleted: " << path << std::endl;
            } else {
                fs::remove(path);
                std::cout << "File deleted: " << path << std::endl;
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error deleting file/directory: " << e.what() << std::endl;
        }
    } else {
        std::cout << "Path does not exist: " << path << std::endl;
    }
}

void rename_item(const std::string& old_name, const std::string& new_name) {
    if (!fs::exists(old_name)) {
        std::cout << "Source file/directory does not exist: " << old_name << std::endl;
        return;
    }

    try {
        fs::rename(old_name, new_name);
        std::cout << "Renamed " << old_name << " to " << new_name << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error renaming file/directory: " << e.what() << std::endl;
    }
}

void process_worker(int process_id) {
    {
        std::lock_guard<std::mutex> lock(print_lock);
        std::cout << "Process " << process_id << " started." << std::endl;
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate process running
    
    {
        std::lock_guard<std::mutex> lock(print_lock);
        std::cout << "Process " << process_id << " completed." << std::endl;
    }
}

