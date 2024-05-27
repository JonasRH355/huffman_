#include <iostream>
#include "huffmantree.h"

int main() {
    lista listadefrequenci;
    Arvore huffman;
    std::string text;

    //Primeira parte: pegar um text e criar uma lista
    // em ordem crescente com caracteres e sua frequência
    text = "My name is Jonatas"; // a=3 s=2 n=2 m=2
    listadefrequencia(text,listadefrequenci);
    mostrarLista(listadefrequenci);

    // Segunda parte: Codigo de Huffman
    codigo_de_huffman(listadefrequenci);

    return 0;
}
