/**
 * TODO: file header
 *
 * Author:
 */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** TODO: class header */
class BitOutputStream {
  private:
    ostream& out;          // reference to the output stream to use
    char* buf;             // buffer of an char array
    unsigned int bufSize;  // size of buffer in byte
    unsigned int nbits;    // number of bits have been writen to buf

    byte bitVal(byte b, unsigned int n);
    byte IntbitVal(byte b, unsigned int n);

  public:
    void writeByte(byte b);
    void WriteInt(unsigned int b);
    /* TODO: add function header and implement */
    explicit BitOutputStream(ostream& os, unsigned int bufSize)
        : out(os), bufSize(bufSize), nbits(0) {
        // initialize buffer with zero-filled.
        buf = new char[bufSize - 1];
        for (int i = 0; i < bufSize; i++) {
            buf[i] = 0;
        }
    };

    /* TODO: add function header
     * Write the part of buffer that was written by the user to the output
     * stream and then clear the buffer to allow further use.
     */
    void flush();

    /* TODO: add function header */
    void writeBit(unsigned int i);
};

#endif
