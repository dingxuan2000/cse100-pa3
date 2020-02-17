/**
 * TODO: file header
 *
 * Author:
 */
#include "BitInputStream.hpp"

/* TODO */
void BitInputStream::fill() {
    in.read(buf, bufSize);  // read from ifstream and overwrite the buffer.

    numBytesRead = in.gcount();  // stores number of bytes successfully read.

    nbits = 0;
}

/* TODO */
bool BitInputStream::atEndOfFile() {
    return (nbits == numBytesRead * 8 - 1) && (in.peek() == EOF);
}

/* Returns true when trying to read past the end of the file, false otherwise */
bool BitInputStream::eof() { return eofBit; }

/* TODO */
unsigned int BitInputStream::readBit() {
    if (atEndOfFile()) eofBit = true;
    // fills the buffer from input stream if all the bits have already been read
    if (nbits == numBytesRead * 8 - 1) this->fill();
    unsigned int byte_size = 8;
    unsigned int index = nbits / 8;
    unsigned int left_dight = nbits % byte_size + 1;
    byte bit = bitVal((byte)buf[index], left_dight);
    nbits++;
    return (unsigned int)bit;
}
byte BitInputStream::bitVal(byte b, unsigned int n) {
    return (b >> (8 - n)) & 1;
}