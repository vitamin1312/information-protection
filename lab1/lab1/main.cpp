#include "Windows.h"
#include "NegrobovCrypto.h"
#include "utils.h"

const bool encripting = true;
const bool decripting = false;


void do_command(unsigned int choice);


int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int choice;
	while (true) {
		std::cout << "1: �������� �����" << std::endl
			<< "2: ���������� �����" << std::endl
			<< "0: ����� �� ���������" << std::endl
			<< "-> ";

		choice = get_num_value(0, 2);
		do_command(choice);
		if (choice == 0) break;
	}

	return 0;
}

void do_command(unsigned int choice) {

	if (choice == 1) {
		if (cript_file(encripting))
			std::cout << "���� ��� ������ ����������" << std::endl;
		else
			std::cout << "�� ������� ����������� ����" << std::endl;
	}

	else if (choice == 2) {
		if (cript_file(decripting))
			std::cout << "���� ��� ������ �����������" << std::endl;
		else
			std::cout << "�� ������� ������������ ����" << std::endl;
	}

	else if (choice == 0)
		std::cout << "�� ��������!!!";
}
