#include "NegrobovHack.h"


std::vector<int> get_frequency(std::vector<unsigned char>& text) {
	std::vector<int> frequency(256, 0);

	for (unsigned char symbol : text)
		frequency[(int)symbol]++;
	return frequency;
}


double compliance_index(std::vector<unsigned char>& text) {
	std::vector<int> frequency = get_frequency(text);
	int numerator = 0;

	for (int fi : frequency)
		numerator += fi * (fi - 1);
	return double(numerator) / (text.size() * (text.size() - 1));
}


int find_key_len(int least, int great, std::vector<unsigned char>& text, bool show, int n) {

	std::vector<unsigned char> temporary_text;
	std::vector<std::pair<int, double>> compliance_indices;

	for (int length = least; length <= great; ++length) {

		temporary_text.clear();
		for (int i = length; i <= text.size() - 1; i += length)
			temporary_text.push_back(text[i]);

		compliance_indices.push_back(std::make_pair(length, compliance_index(temporary_text)));
	}

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < compliance_indices.size(); ++j) {
			if (compliance_indices[i].second < compliance_indices[j].second)
				std::swap(compliance_indices[i], compliance_indices[j]);
		}
	}

	if (show) {
		for (int i = 0; i < n; ++i) {
			std::cout << "ƒлина ключа: " << compliance_indices[i].first
				<< "; »ндекс соответсви€: " << compliance_indices[i].second << std::endl;
		}
    }

	return compliance_indices.begin()->first;
}


std::vector<int> get_popular_chars(std::vector<unsigned char> &text, int n) {

	std::vector<int> frequency = get_frequency(text);
	std::vector<int> char_numbers;

	for (int i = 0; i < 256; ++i)
		char_numbers.push_back(i);


	for (int i = 0; i < n; ++i) {
		for (int j = i; j < frequency.size(); ++j) {
			if (frequency[i] < frequency[j]) {
				std::swap(frequency[i], frequency[j]);
				std::swap(char_numbers[i], char_numbers[j]);
			}
		}
	}

	std::vector<int> popular_char_numbers;

	for (int i = 0; i < n; ++i) {
		popular_char_numbers.push_back(char_numbers[i]);
	}

	return popular_char_numbers;
}


std::string get_key(int length, std::vector<unsigned char>& text, std::vector<int> popular_chars) {

	std::string key;
	std::vector<unsigned char> temporary_text;
	std::vector<int> temporary_frequency;
	unsigned char temporary_popular_char;
	int temporary_max_frequency;

	for (int i = 0; i < length; ++i) {

		temporary_text.clear();

		for (int j = i; j < text.size(); j += length)
			temporary_text.push_back(text[j]);

		temporary_frequency = get_frequency(temporary_text);

		temporary_max_frequency = 0;
		temporary_popular_char = (unsigned char)temporary_max_frequency;

		for (int numb = 0; numb < 256; ++numb) {
			if (temporary_frequency[numb] > temporary_max_frequency) {
				temporary_max_frequency = temporary_frequency[numb];
				temporary_popular_char = (unsigned char)numb;
			}
		}

		key += (unsigned char)(temporary_popular_char - popular_chars[0]);
	}

	return key;
}


bool hack_key() {

	std::string input_file, sample_file, output_file;

	std::cout << "¬ведите \"название зашифрованного файла\"" << std::endl
		<< "-> ";

	std::cin.ignore();
	std::getline(std::cin, input_file);
	std::ifstream fin1(input_file, std::ios::binary);
	if (!fin1.is_open())
		return false;

	std::vector<char> t((std::istreambuf_iterator<char>(fin1)), std::istreambuf_iterator<char>());
	std::vector<unsigned char> text;
	for (char symbol : t) {
		text.push_back((unsigned char)symbol);
	}

	std::cout << "¬ведите \"название эталонного файла\"" << std::endl
		<< "-> ";

	std::getline(std::cin, sample_file);
	std::ifstream fin2(sample_file, std::ios::binary);
	if (!fin2.is_open())
		return false;

	std::vector<char> sample_t((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
	std::vector<unsigned char> sample_text;
	for (char symbol : sample_t) {
		sample_text.push_back((unsigned char)symbol);
	}



	std::cout << "¬ведите минимальную длину ключа (1, 100)" << std::endl
		<< "-> ";
	int least = get_num_value(1, 100);
	std::cout << "¬ведите максимальную длину ключа (" << least << ", 100)" << std::endl
		<< "-> ";
	int great = get_num_value(least, 100);
	int key_len = find_key_len(least, great, text, true, 5);
	std::string key = get_key(key_len, text, get_popular_chars(sample_text, 5));
	std::cout << " люч дл€ дешифрации: " << key << std::endl;

	std::ifstream fin(input_file, std::ios::binary);
	if (!fin.is_open())
		return false;

	std::cin.ignore();
	std::cout << "¬ведите \"название файла дл€ расшифровки\"" << std::endl
		<< "-> ";
	std::getline(std::cin, output_file);
	std::ofstream fout(output_file, std::ios::binary);
	if (!fout.is_open())
		return false;

	cripting(fin, fout, key, false);

	return true;
}