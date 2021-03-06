#include <filesystem>
#include <fstream>
#include <iostream>

/**
	Note: 
	use next compile option to compile:
	-lstdc++fs
**/

int main() {

	const std::filesystem::path currentDir = std::filesystem::current_path();
	std::cout << currentDir << std::endl;

	const std::filesystem::path someFile = currentDir / "subfolder" / "readme.txt";
	std::cout << someFile << std::endl;

	const std::filesystem::path otherFile = currentDir / "otherFolder/otherFile.txt";
	std::cout << otherFile << std::endl;

	// parent folder
	std::cout << otherFile.parent_path() << std::endl;
	// filename with extenstion
	std::cout << otherFile.filename() << std::endl;
	// filename only
	std::cout << otherFile.stem() << std::endl;
	// extension
	std::cout << otherFile.extension() << std::endl;

	const std::filesystem::path cyrillic = currentDir / L"директория/файл.txt";
	std::cout << cyrillic << std::endl;
	std::cout << cyrillic.u8string() << std::endl;


	const std::filesystem::path folder = currentDir / "folder";
	std::cout << "First exists: " << std::filesystem::exists(folder) << std::endl;
	try {
		std::filesystem::create_directories(folder);
	}
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cout << "Exception! " << e.what() << '\n';
	}
	std::cout << "Second exists: " << std::filesystem::exists(folder) << std::endl;

	const std::filesystem::path wrongFolder = "/not_permitted";

	std::error_code errCode;
	std::filesystem::create_directories(wrongFolder, errCode);
	if (errCode) {
		std::cout << "Creation failed! " << errCode.message() << std::endl;
	}

	const std::filesystem::path file = folder / "file.txt";
	{
		std::ofstream stream(file.native());
		if (!stream.is_open()) {
			std::cout << "Failed to create file: " << file << std::endl;
		}
		else {
			stream << "Hello, World!" << std::endl;
		}
	}
	std::cout << "File exists: " << std::filesystem::exists(file) << std::endl;
	std::cout << "IsRegular: " << std::filesystem::is_regular_file(file) << std::endl;
	std::cout << "FileSize = " << std::filesystem::file_size(file) << std::endl;

	std::filesystem::remove(file);

	std::cout << "File exists after remove: " << std::filesystem::exists(file) << std::endl;

	return 0;
}