#include "ClientApp.h"

#ifdef _WIN32
#include "Windows.h"
#endif // _WIN32

int main() {
	std::filesystem::path executablePath;
#ifdef _WIN32
	char exePath[1000];
	GetModuleFileName(NULL, exePath, sizeof(exePath));
	executablePath = std::filesystem::path(exePath);
#else
	executablePath = std::filesystem::canonical("/proc/self/exe"); // LINUX
#endif // _WIN32
	std::string exeFolderPath = executablePath.parent_path().string();
	TheTraitor::ClientApp clientApp(exeFolderPath);
	clientApp.run();
}