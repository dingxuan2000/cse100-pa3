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
        (nbits - 1) / 8 + 1;  // determine how many bytes are in the buffer

    out.write(buf, byte_written);  // write byte written into outstream.

    for (int i = 0; i < byte_written; i++) {  // fill the buffer with zeros.
        buf[i] = 0;
    }

    nbits = 0;
}

/* TODO */
void BitOutputStream::writeBit(unsigned int i) {
    if (nbits == bufSize * 8) {  // flush the buffer is it is full
        this->flush();
    }
    unsigned int byte_size = 8;  // size of byte
    unsigned int index = nbits / 8;
    // cout<<index<<endl;
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

byte BitOutputStream::bitVal(byte b, unsigned int n) {
    //为什么是7-n
    return (b >> (7 - n)) & 1;
}
void BitOutputStream::writeByte(byte b) {
    for (int i = 0; i < 8; i++) {
        unsigned int bit = (int)bitVal(b, i);
        writeBit(bit);
    }
}

byte BitOutputStream::IntbitVal(unsigned int b, unsigned int n) {
    return (b >> (31 - n)) & 1;
}
void BitOutputStream::WriteInt(unsigned int b) {
    for (int i = 0; i < 32; i++) {
        unsigned int bit = (int)IntbitVal(b, i);
        writeBit(bit);
    }
}
void BitOutputStream::deleteBuffer() { delete[] buf; }
