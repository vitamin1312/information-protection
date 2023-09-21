#include "NegrobovCrypto.h"


bool cript_file(bool encripting) {
	
	std::string input_file, output_file, key;

	std::cin.ignore();
	std::cout << "¬ведите \"название входного файла\"" << std::endl
		      << "-> ";
	std::getline(std::cin, input_file);
	std::ifstream fin(input_file, std::ios::binary);
	if (!fin.is_open())
		return false;

	std::cout << "¬ведите \"название выходного файла\"" << std::endl
		      << "-> ";
	std::getline(std::cin, output_file);
	std::ofstream fout(output_file, std::ios::binary);
	if (!fout.is_open())
		return false;

	std::cout << "¬ведите ключ" << std::endl
		      << "-> ";
	std::getline(std::cin, key);

	cripting(fin, fout, key, encripting);
	fin.close();
	fout.close();
	return true;
}


void cripting(std::ifstream& fin, std::ofstream& fout, const std::string& key, bool encripting) {

	unsigned char text_symbol;
	unsigned int key_len = key.size();
	unsigned int i = 0;
	int sign = encripting ? 1:-1;

	text_symbol = fin.get();

	while (!fin.eof()) {
		fout << (unsigned char)(text_symbol + sign * key[i % key_len]);
		text_symbol = fin.get();
		i++;
	}
}
