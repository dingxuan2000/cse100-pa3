/**
 * TODO: file header
 *
 * Author:
 */
#include "BitInputStream.hpp"

/* TODO */
void BitInputStream::fill() {
    in.read(buf, bufSize);  // read from ifstream and overwrite the buffer.
    // test the character in buffer
    // for (int i = 0; i < bufSize; i++) {
    //     cout << buf[i] << endl;
    // }
    numBytesRead = in.gcount();  // stores number of bytes successfully read.

    nbits = 0;
}

/* TODO */
bool BitInputStream::atEndOfFile() {
    return (nbits == numBytesRead * 8) && (in.peek() == EOF);
}

/* Returns true when trying to read past the end of the file, false otherwise */
bool BitInputStream::eof() { return eofBit; }

/* TODO */
unsigned int BitInputStream::readBit() {
    if (atEndOfFile()) eofBit = true;
    // fills the buffer from input stream if all the bits have already been read
    if (nbits == numBytesRead * 8) this->fill();  //去掉减1
    unsigned int byte_size = 8;

    unsigned int index = nbits / 8;
    // cout << index << endl;
    unsigned int left_dight = nbits % byte_size + 1;
    byte bit = bitVal((byte)buf[index], left_dight);
    nbits++;
    return (unsigned int)bit;
}
byte BitInputStream::bitVal(byte b, unsigned int n) {
    //威为什么是8-n
    return (b >> (8 - n)) & 1;
}