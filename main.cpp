#include <iostream>
#include <string>
#include "huffmantree.h"


int main() {

    std::string text;
    std::cout << "Digite o texto a ser comprimido: ";
    std::getline(std::cin, text);

    codigoDeHuffman(text);

    return 0;
}