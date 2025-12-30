#include "ClientApp.h"
#include <filesystem>
#include <string>

#ifdef _WIN32
#include "Windows.h"
#endif // _WIN32

int main(int argc, char* argv[]) {
	std::filesystem::path executablePath;
#ifdef _WIN32
	char exePath[1000];
	GetModuleFileName(NULL, exePath, sizeof(exePath));
	executablePath = std::filesystem::path(exePath);
#else
	executablePath = std::filesystem::canonical("/proc/self/exe"); // LINUX
#endif // _WIN32
	std::string exeFolderPath = executablePath.parent_path().string();

	bool testResolution = false;
	for (int i = 1; i < argc; ++i) {
		if (std::string(argv[i]) == "--test-resolution") {
			testResolution = true;
		}
	}

	TheTraitor::ClientApp clientApp(exeFolderPath, testResolution);
	clientApp.run();
}