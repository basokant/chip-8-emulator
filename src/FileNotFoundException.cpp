#include <stdexcept>
#include <string>

#include "FileNotFoundException.h"

FileNotFoundException::FileNotFoundException():runtime_error("File not found") {}
FileNotFoundException::FileNotFoundException(std::string msg):runtime_error(msg.c_str()) {}