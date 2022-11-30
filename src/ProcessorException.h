/**
 * @file ProcessorException.h
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief IA custom exception class derived from std::runtime_error
 * @version 0.1
 * @date 2022-11-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef PROCESSOR_EXCEPTION_H_INCLUDED
#define PROCESSOR_EXCEPTION_H_INCLUDED

#include <stdexcept>

/**
 * @brief A custom exception class for errors thrown by the Processor.
 * 
 */
struct ProcessorException : std::runtime_error {
    // Use std::runtime_error constructor for this class
    using std::runtime_error::runtime_error;
};

#endif