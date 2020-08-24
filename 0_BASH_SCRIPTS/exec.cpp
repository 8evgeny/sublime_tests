
#include <fstream>
// Получить результат работы скрипта
 std::string exec(const char* cmd) {
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}

// Альтернатива
std::string ComplexExecutor::GetCommandResult(const std::string& command) {
  std::this_thread::sleep_for(1s);
  FILE* popen_result;
  std::string result;
  std::cout << "executing command: " << command << std::endl;
  char buff[512];
  popen_result = popen(command.c_str(), "r");
  if (!popen_result) {
    printf("Can't execute command\n");
    return 0;
  }
  while (fgets(buff, sizeof(buff), popen_result) != NULL) {
    result += buff;
  }
  pclose(popen_result);
  return result;
}

