#include <iostream>
#include "huffmantree.h"

int main() {
    lista listadefrequenci;
    Arvore huffman;
    std::string text;
    text = "My name is Jonatas"; // a=3 s=2 n=2 m=2
    listadefrequencia(text,listadefrequenci);
    mostrarLista(listadefrequenci);
    std::cout<<"\n";
    criarArvore(listadefrequenci,huffman);
    return 0;
}
