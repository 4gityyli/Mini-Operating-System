#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <string>
#include <mutex>
extern std::mutex print_lock;

void list_directory(const std::string& dir_path);
void create_file(const std::string& file_name);
void create_directory(const std::string& dir_name);
void move_item(const std::string& src_path, const std::string& dest_path);
void change_directory(const std::string& dir_path);
void delete_item(const std::string& path);
void rename_item(const std::string& old_name, const std::string& new_name);


#endif // OPERATIONS_H
