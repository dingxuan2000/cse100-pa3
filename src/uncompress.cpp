/**
 * TODO: file header
 *
 * Author:
 */

#include <fstream>
#include <iostream>

#include <cxxopts.hpp>
#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

/* TODO: Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(string inFileName, string outFileName) {
    // 1. 首先read the input file, 将1-256行的每一行的数字存进frequency vectors,
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
    // fin.close();

    //接下来call build() to construct HCTree
    tree->build(frequency);
    //接下来从257行到end of file去不断地call decode()
    // stringstream input;  // create an istream object
    string content;
    // fin.open(inFileName, ios_base::app | ios::in);
    fout.open(outFileName, ios::out);

    // content.assign(istreambuf_iterator<char>(fin),
    // istreambuf_iterator<char>());

    // while (!fin.eof() && fin.peek() != EOF) {
    //     getline(fin, content, '\n');
    //     content += content;
    // }
    // fin >> content;
    // check content string
    // cout << input << endl;
    byte symbol;
    while (!fin.eof() && fin.peek() != EOF) {
        symbol = tree->decode(fin);
        cout << symbol << endl;
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
        exit(0);
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
