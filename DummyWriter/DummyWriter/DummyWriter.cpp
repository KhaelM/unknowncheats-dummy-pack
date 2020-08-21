#include <iostream>
#include <Windows.h>
#include <vector>

#if _WIN64
#define POINTER_SIZE 8
#else
#define POINTER_SIZE 4
#endif

int main() {
	DWORD pid = 0;
	std::cout << "Enter the pid: ";
	std::cin >> std::dec >> pid;
	std::cin.clear(); // clears error flag, indeed if user types string other than number it will fail and the future INPUT/OUTPUT operations will fail as well
	std::cin.ignore(1000, '\n'); // Will loop through user input and if it meets a \n then it will stop or if it loops thro

	HANDLE procHandle = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, pid);

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

	int varInt = 9999;
	if (!WriteProcessMemory(procHandle, (LPVOID)varIntMemoryAddress, &varInt, sizeof(varInt), NULL)) {
		std::cout << "varInt WriteProcessMemory Failed. GetLastError = " << GetLastError() << std::endl;
		std::cin.get();
		CloseHandle(procHandle);
		return EXIT_FAILURE;
	}


	uintptr_t varStringMemoryAddress = 0x0;
	std::cout << "varString Adress: ";
	std::cin >> std::hex >> varStringMemoryAddress;
	std::cin.clear();
	std::cin.ignore();

	char varString[] = "azertyuiopqs"; // It's really hard to write a string object because of its unknown structure so prefer char[]
	if (!WriteProcessMemory(procHandle, (LPVOID)(varStringMemoryAddress), &varString, strlen(varString)+1, NULL)) { // strlen +1 for '\0'
		std::cout << "varString WriteProcessMemory Failed. GetLastError = " << GetLastError() << std::endl;
		std::cin.get();
		CloseHandle(procHandle);
		return EXIT_FAILURE;
	}


	uintptr_t arrCharMemoryAddress = 0x0;
	std::cout << "arrChar Adress: ";
	std::cin >> std::hex >> arrCharMemoryAddress;
	std::cin.clear();
	std::cin.ignore();

	char arrChar[] = "All by me"; // dont forget last char is '\0'
	if (!WriteProcessMemory(procHandle, (LPVOID)arrCharMemoryAddress, arrChar, strlen(arrChar)+1, NULL)) { // arrChar or &arrChar as argument is correct because arrChar value is its own address which is the address of the first element
		std::cout << "arrChar WriteProcessMemory Failed. GetLastError = " << GetLastError() << std::endl;
		std::cin.get();
		CloseHandle(procHandle);
		return EXIT_FAILURE;
	}


	std::cout << "Press ENTER to quit.";
	std::cin.get();
	CloseHandle(procHandle);

	return EXIT_SUCCESS;
}