#include <iostream>
#include "huffmantree.h"
#include <string>


int main() {
    lista listadefrequenci;
    std::string text;

    //Primeira parte: pegar um text e criar uma lista
    // em ordem crescente com caracteres e sua frequência
    text = "My name is Jonatas"; // a=3 s=2 n=2 m=2

    // Segunda parte: Codigo de Huffman
    codigo_de_huffman(text);

    return 0;
}
