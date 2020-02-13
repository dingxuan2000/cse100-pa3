/**
 * TODO: file header
 *
 * Author:Xuan Ding, xding@ucsd.edu
 *        Qilong Li, qil009@ucsd.edu
 * this file encodes an input file and outputs to a encoded file. this file
 *includes function psudocompress which takes parameter of two file names
 *inputfile and outputfile. inputs orginal file and outputs encoded file.
 */
#include <fstream>
#include <iostream>

#include <cxxopts.hpp>
#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"
/* TODO: add pseudo compression with ascii encoding and naive header
 * (checkpoint)
 * psudocompress takes parameter of two file names inputfile and outputfile.
 * inputs orginal file and outputs encoded file.
 */
void pseudoCompression(string inFileName, string outFileName) {
    // 1. scan the input file, to compute each ascii value's count into freqency
    // vector
    HCTree* tree = new HCTree();
    ifstream fin;
    ofstream fout;
    byte c1;
    // int num_row = 0;
    vector<unsigned int> frequency(256);
    fin.open(inFileName, ios::in);
    while (!fin.eof() && fin.peek() != EOF) {
        // c = fin.peek();
        c1 = (byte)fin.get();
        // cout << c << endl;
        if (c1 == '\n') {
            frequency[c1]++;
            // continue;
        } else {
            // cout << c1 << endl;
            frequency[c1]++;
        }
    }
    fin.close();
    //接下来把frequency的每个index的值写进output file的1-256行
    fout.open(outFileName, ios::out);
    for (int i = 0; i < frequency.size(); i++) {
        // cout << frequency.at(i) << endl; //here,it's correct
        fout << frequency.at(i) << endl;
    }
    fout.close();

    // 2.当读取完第一遍file,将frequency vector存好后，call build()
    tree->build(frequency);
    // 3.当build好tree之后，再次scan一遍file, 然后每读到一个char, call encode()
    // to encode each char into encoding bits.
    fin.open(inFileName, ios_base::app);

    fout.open(outFileName, ios_base::app);
    while (!fin.eof() && fin.peek() != EOF) {
        // c = fin.peek();
        c1 = (byte)fin.get();
        tree->encode(c1, fout);
    }
    fin.close();
    fout.close();
    delete tree;
}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the compress */
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
    pseudoCompression(inFileName, outFileName);
    return 0;
}