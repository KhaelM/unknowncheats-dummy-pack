#include <iostream>
#include <Windows.h>

int main() {
	const int ARR_CHAR_SIZE = 128;
	int varInt = 123456;
	std::string varString = "DefaultString";
	char arrChar[ARR_CHAR_SIZE] = "Long char array right there ->";
	int* ptr2varInt = &varInt;
	int** ptr2ptr = &ptr2varInt;
	int*** ptr2ptr2ptr = &ptr2ptr;
	float varFloat = 125.52f;
	double varDouble = 987654321.89;
	short varShort = 100;
	long long varLongLong = 999999999;
	int incInt = 888;
	double incDouble = 100.55;

	DWORD pid = GetCurrentProcessId();

	do {
		std::cout << "Process ID: " << pid << "\n\n";

		std::cout << "varShort\t(" << std::hex << &varShort << ") = " << std::dec << varShort << " (" << sizeof(short) << " bytes)" << std::endl;
		std::cout << "varLongLong\t(" << std::hex << &varLongLong << ") = " << std::dec << varLongLong << " (" << sizeof(long long) << " bytes)" << std::endl;
		std::cout << "varInt\t\t(" << std::hex << &varInt << ") = " << std::dec << varInt << " (" << sizeof(int) << " bytes)" << std::endl;
		std::cout << "varFloat\t(" << std::hex << &varFloat << ") = " << std::dec << varFloat << " (" << sizeof(float) << " bytes)" << std::endl;
		std::cout << "varDouble\t(" << std::hex << &varDouble << ") = " << std::dec << varDouble << " (" << sizeof(double) << " bytes)" << std::endl;
		std::cout << "varString\t(" << std::hex << &varString << ") = " << varString << std::endl;
		std::cout << "arrChar[" << std::dec << ARR_CHAR_SIZE << "]\t(" << &arrChar << ") = " << arrChar << std::endl << std::hex; // No need to specify hex cause it keeps last config
		std::cout << "ptr2varInt\t(" << &ptr2varInt << ") = " << ptr2varInt << std::endl;
		std::cout << "ptr2ptr\t\t(" << &ptr2ptr << ") = " << ptr2ptr << std::endl;
		std::cout << "ptr2ptr2ptr\t(" << &ptr2ptr2ptr << ") = " << ptr2ptr2ptr << std::endl; // std::dec again to prevent pid to be displayed as hexadecimal
		std::cout << "incDouble\t(" << &incDouble << ") = " << std::dec << incDouble << std::endl;
		std::cout << "incInt\t(" << &incInt << ") = " << std::dec << incInt << std::endl << std::endl;

		std::cout << "Press ENTER to print again.";
		std::cin.get();
		++incInt;
		++incDouble;
		std::cout << "---------------------------------------------" << std::endl;

	} while (true);


	return 0;
}