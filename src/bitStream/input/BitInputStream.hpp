/**
 * TODO: file header
 *
 * Author:
 */
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** TODO: class header */
class BitInputStream {
  private:
    istream& in;           // reference to the input stream to use
    char* buf;             // buffer of an char array
    unsigned int bufSize;  // size of buffer in byte
    unsigned int nbits;    // number of bits that have been read from buf
    bool eofBit;           // true when trying to read past the end of the file
    unsigned int numBytesRead;  // to keep track the number of bytes that we
                                // read

    /* TODO: add function header */
    bool atEndOfFile();
    byte bitVal(byte b, unsigned int n);
    void setbit(byte& b, int n, int i);

  public:
    unsigned int numBits;
    unsigned int readInt();
    byte readByte();
    void deleteBuffer();
    /* TODO: add function header and implement */
    explicit BitInputStream(istream& is, unsigned int bufSize)
        : in(is), bufSize(bufSize), nbits(0), eofBit(false), numBytesRead(1) {
        buf = new char[bufSize - 1];
        this->fill();
    };

    /* TODO: add function header
     * To zero-fill the buffer(char array)
     */
    void fill();

    /* TODO: add function header */
    bool eof();

    /* TODO: add function header */
    unsigned int readBit();
};

#endif