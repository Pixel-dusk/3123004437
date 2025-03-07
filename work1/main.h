#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <string>
#include "function.h"

//参数校验声明
bool validate_arguments(int argc, char* argv[]);

//文件操作声明
std::string read_file(const std::string& filename);
void write_result(const std::string& filename, double similarity);

#endif 