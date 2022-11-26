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