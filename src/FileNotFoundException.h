#ifndef FILE_NOT_FOUND_EXCEPTION_H_INCLUDED
#define FILE_NOT_FOUND_EXCEPTION_H_INCLUDED

#include <stdexcept>
#include <string>

/**
 * @brief A custom exception class for errors thrown by memory when the rom file does not exist.
 * 
 */
class FileNotFoundException : public std::runtime_error {
    public:
        FileNotFoundException();
        FileNotFoundException(std::string msg);
};

#endif