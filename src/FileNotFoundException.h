/**
 * @file FileNotFoundException.h
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief Interface for a custom exception for missing files
 * @version 0.1
 * @date 2022-11-08
 *
 * @copyright Copyright (c) 2022
 *
 */

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
        /**
         * @brief Construct a new File Not Found Exception object
         * 
         */
        FileNotFoundException();

        /**
         * @brief Construct a new File Not Found Exception object
         * 
         * @param msg Exception error message
         */
        FileNotFoundException(std::string msg);
};

#endif