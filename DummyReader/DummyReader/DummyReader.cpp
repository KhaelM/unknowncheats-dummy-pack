#include <iostream>
#include <Windows.h>
#include <vector>

#if _WIN64
#define POINTER_SIZE 8
#else
#define POINTER_SIZE 4
#endif

uintptr_t getDynamicAdressFromBaseAddress(HANDLE procHandle, uintptr_t baseAddress, std::vector<unsigned int> offsets);

uintptr_t getDynamicAdressFromBaseAddress(HANDLE procHandle, uintptr_t baseAddress, std::vector<unsigned int> offsets) {
	uintptr_t curAddress = baseAddress;
	uintptr_t curAddressValue = 0x0;


	for (unsigned int &offset : offsets) {
		if (!ReadProcessMemory(procHandle, (LPCVOID)curAddress, &curAddressValue, sizeof(POINTER_SIZE), NULL)) {
			std::cout << "ReadProcessMemory Failed at adress " << curAddress  << ". GetLastError = " << GetLastError() << std::endl;
			std::cin.get();
			CloseHandle(procHandle);
			return EXIT_FAILURE;
		}
		curAddress = curAddressValue + offset;
	}

	return curAddress;
}


int main() {
	DWORD pid = 0;
	std::cout << "Enter the pid: ";
	std::cin >> std::dec >> pid;
	std::cin.clear(); // clears error flag, indeed if user types string other than number it will fail and the future INPUT/OUTPUT operations will fail as well
	std::cin.ignore(1000, '\n'); // Will loop through user input and if it meets a \n then it will stop or if it loops thro

	HANDLE procHandle = OpenProcess(PROCESS_VM_READ, false, pid);

	if (procHandle == NULL) {
		std::cout << "OpenProcess Failed. GetLastError = " << GetLastError() << std::endl;
		std::cin.get();
		return EXIT_FAILURE;
	}

	uintptr_t varIntMemoryAddress = 0x0;
	std::cout << "varInt Adress: ";
	std::cin >> std::hex >> varIntMemoryAddress;
	std::cin.clear();
	std::cin.ignore();

	int varInt = 0;
	if (!ReadProcessMemory(procHandle, (LPCVOID)varIntMemoryAddress, &varInt, sizeof(varInt), NULL)) {
		std::cout << "varInt ReadProcessMemory Failed. GetLastError = " << GetLastError() << std::endl;
		std::cin.get();
		CloseHandle(procHandle);
		return EXIT_FAILURE;
	}


	uintptr_t varStringMemoryAddress = 0x0;
	std::cout << "varString Adress: ";
	std::cin >> std::hex >> varStringMemoryAddress;
	std::cin.clear();
	std::cin.ignore();

	std::string varString(13, ' ');// even if it works, it is better to use char* or char[] to read data because string is an object and not pure data
	// no need take in consideration the '\0' cause it's a string object
	if (!ReadProcessMemory(procHandle, (LPCVOID)varStringMemoryAddress, &varString, 13 * sizeof(char), NULL)) {
		std::cout << "varString ReadProcessMemory Failed. GetLastError = " << GetLastError() << std::endl;
		std::cin.get();
		CloseHandle(procHandle);
		return EXIT_FAILURE;
	}


	uintptr_t arrCharMemoryAddress = 0x0;
	std::cout << "arrChar Adress: ";
	std::cin >> std::hex >> arrCharMemoryAddress;
	std::cin.clear();
	std::cin.ignore();

	char arrChar[30];
	if (!ReadProcessMemory(procHandle, (LPCVOID)arrCharMemoryAddress, arrChar, 30 * sizeof(arrChar[0]), NULL)) { // arrChar or &arrChar as argument is correct because arrChar value is its own address which is the address of the first element
		// don't forget the '\0' which is included in the size of the char[]
		std::cout << "arrChar ReadProcessMemory Failed. GetLastError = " << GetLastError() << std::endl;
		std::cin.get();
		CloseHandle(procHandle);
		return EXIT_FAILURE;
	}

	uintptr_t ptr2varIntMemoryAddress = 0x0;
	std::cout << "ptr2varInt Adress: ";
	std::cin >> std::hex >> ptr2varIntMemoryAddress;
	std::cin.clear();
	std::cin.ignore();

	uintptr_t ptr2varIntValue = 0x0;

	if (!ReadProcessMemory(procHandle, (LPCVOID)ptr2varIntMemoryAddress, &ptr2varIntValue, POINTER_SIZE, NULL)) { // arrChar or &arrChar as argument is correct because arrChar value is its own address which is the address of the first element
		// don't forget the '\0' which is included in the size of the char[]
		std::cout << "arrChar ReadProcessMemory Failed. GetLastError = " << GetLastError() << std::endl;
		std::cin.get();
		CloseHandle(procHandle);
		return EXIT_FAILURE;
	}


	std::cout << "intRead = " << varInt << std::endl;
	std::cout << "varString = " << varString << std::endl;
	std::cout << "arrChar = " << arrChar << std::endl;
	std::cout << "ptr2IntValue = " << std::hex << ptr2varIntValue << std::endl;
	std::cout << "varInt Addr = " << std::hex << getDynamicAdressFromBaseAddress(procHandle, 0x8FFB3C, std::vector<unsigned int>{0,0,0}) << std::endl;
	std::cout << "Press ENTER to quit.";
	std::cin.get();
	CloseHandle(procHandle);

	return EXIT_SUCCESS;
}