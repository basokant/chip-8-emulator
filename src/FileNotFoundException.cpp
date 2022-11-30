/**
 * @file FileNotFoundException.cpp
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief Implementation for the FileNotFoundException
 * @version 0.1
 * @date 2022-11-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdexcept>
#include <string>

#include "FileNotFoundException.h"

FileNotFoundException::FileNotFoundException()
    : runtime_error("File not found")
{}

FileNotFoundException::FileNotFoundException(std::string msg)
    : runtime_error(msg.c_str())
{}