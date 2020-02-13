/**
 * TODO: file header
 *
 * Author:Xuan Ding, xding@ucsd.edu
 *        Qilong Li, qil009@ucsd.edu
 * this file decodes an encoded file as input and outputs original content into
 * an output file.this file includes function
 * psudouncompress which takes parameter of two file names inputfile and
 * outputfile. inputs encoded file and outputs original file.
 */

#include <fstream>
#include <iostream>

#include <cxxopts.hpp>
#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

/* TODO: Pseudo decompression with ascii encoding and naive header (checkpoint)
 * psudouncompress which takes parameter of two file names inputfile and
 * outputfile. inputs encoded file and outputs original file.
 */
void pseudoDecompression(string inFileName, string outFileName) {
    // 1. Read the input file, put 1-125 line's numbers into frequency vector
    // then, build the Huffman coding tree
    HCTree* tree = new HCTree();
    ifstream fin;
    ofstream fout;
    string c;
    unsigned int freq;
    vector<unsigned int> frequency(256);
    fin.open(inFileName, ios::in);
    int num_row = 1;
    while (num_row <= 256) {
        getline(fin, c, '\n');
        // convert string into int
        stringstream geek(c);
        geek >> freq;
        // cout << freq << endl;
        frequency.at(num_row - 1) = freq;
        num_row++;
    }

    // then, call build() to construct HCTree
    tree->build(frequency);
    // then, call decode() from 257 line until hit the end of file
    string content;
    fout.open(outFileName, ios::out);

    byte symbol;
    while (!fin.eof() && fin.peek() != EOF) {
        symbol = tree->decode(fin);
        // cout << symbol << endl;
        fout << symbol;
    }
    fin.close();
    fout.close();
    delete tree;
}

/* TODO: True decompression with bitwise i/o and small header (final) */
void trueDecompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the uncompress */
int main(int argc, char* argv[]) {
    cxxopts::Options options("./compress",
                             "Compress files using Huffman Encoding");
    options.positional_help("./path_to_input_file ./path_to_output_file");

    bool isAsciiOutput = false;
    string inFileName, outFileName;
    options.allow_unrecognised_options().add_options()(
        "ascii", "Write output in ascii mode instead of bit stream",
        cxxopts::value<bool>(isAsciiOutput))(
        "input", "", cxxopts::value<string>(inFileName))(
        "output", "", cxxopts::value<string>(outFileName))(
        "h,help", "Print help and exit");

    options.parse_positional({"input", "output"});
    auto userOptions = options.parse(argc, argv);
    // when the inputfile is not valid, print help(does it include empty file
    // case)
    if (userOptions.count("help") || !FileUtils::isValidFile(inFileName) ||
        outFileName.empty()) {
        cout << options.help({""}) << std::endl;
        return 0;
    }
    // check if the file is empty, if it's empty, do
    // we need to return an empty output file, or exit(0)?
    if (FileUtils::isEmptyFile(inFileName)) {
        ofstream fout;
        fout.open(outFileName, ios::out);
        fout << "";
        fout.close();
        return 0;
    }

    // call pseudoCompression() to implement encoding part
    pseudoDecompression(inFileName, outFileName);

    return 0;
}
