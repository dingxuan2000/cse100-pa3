/**
 * TODO: file header
 *
 * Author:
 */
#include "BitOutputStream.hpp"

/* TODO
 * When the buffer
 */
void BitOutputStream::flush() {
    if (nbits == 0) return;
    //应该改成unsigned int byte_written = nbits/8+1;
    unsigned int byte_written =
        nbits / 8 + 1;  // determine how many bytes are in the buffer

    out.write(buf, byte_written);  // write byte written into outstream.

    for (int i = 0; i < byte_written; i++) {  // fill the buffer with zeros.
        buf[i] = 0;
    }

    nbits = 0;
}

/* TODO */
void BitOutputStream::writeBit(unsigned int i) {
    if (nbits == bufSize * 8 - 1) {  // flush the buffer is it is full
        this->flush();
    }
    unsigned int byte_size = 8;  // size of byte
    unsigned int index = nbits / 8;
    // current index
    unsigned int left_digit = nbits % byte_size + 1;

    if (i == 1) {
        buf[index] =
            buf[index] |
            (1 << (byte_size - left_digit));  // adding 1 to that digit of that
                                              // byte in the buff at [index].

        nbits++;  // increment bit count
    } else {
        nbits++;  // increment bit count , zero stays in place
    }
}
