#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <string>
#include "function.h"

//����У������
bool validate_arguments(int argc, char* argv[]);

//�ļ���������
std::string read_file(const std::string& filename);
void write_result(const std::string& filename, double similarity);

#endif 