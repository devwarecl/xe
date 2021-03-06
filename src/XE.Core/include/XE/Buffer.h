
#ifndef __XE_BUFFER_HPP__
#define __XE_BUFFER_HPP__

#include <XE/Predef.h>
#include <cstddef>

namespace XE {
    /**
     * @brief Memory area abstraction
     */
    class Buffer {
    public:
        virtual ~Buffer();

        /**
         * @brief Get the size of the buffer, in bytes.
         */
        virtual int getSize() const = 0;

        /**
         * @brief Read the buffer data into a user-defined memory region.
         */
        virtual void read(std::byte* destination, const int size = 0, const int offset = 0, const int destinationOffset = 0) const = 0;

        /**
         * @brief Write a user-defined memory region to the buffer
         */
        virtual void write(const std::byte *source, const int size = 0, const int offset = 0, const int sourceOffset = 0) = 0;
    };
}

#endif
