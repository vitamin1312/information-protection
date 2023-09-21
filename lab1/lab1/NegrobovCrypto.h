#pragma once

#include <iostream>
#include <fstream>
#include <string>
 
bool cript_file(bool encripting);

void cripting(std::ifstream &fin, std::ofstream &fout, const std::string &key, bool encript);
