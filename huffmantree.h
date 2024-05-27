struct NoArvore {
    char caracter;
    unsigned frequencia;
    NoArvore *esquerdo, *direito;

    NoArvore(char caracter, unsigned freq) {
        this->caracter = caracter;
        this->frequencia = freq;
        esquerdo = direito = nullptr;
    }
};

struct Lista {
    NoArvore *nodoArvore;
    Lista *proximo;
};

struct MapaDeBits {
    char caracter;
    std::string bits;
    MapaDeBits *proximo;
};

void atualizarListaDeFrequencia(char text, NoArvore* &lista) {
    NoArvore *atual = lista;
    while (atual != nullptr && atual->caracter != text) {
        atual = atual->direito;
    }
    if (atual != nullptr) {
        atual->frequencia++;
    } else {
        NoArvore *novaFrequencia = new NoArvore(text, 1);
        novaFrequencia->direito = lista;
        lista = novaFrequencia;
    }
}

void inserirNoLista(Lista* &topo, NoArvore* no) {
    Lista* novoNodo = new Lista();
    novoNodo->nodoArvore = no;
    novoNodo->proximo = nullptr;

    if (topo == nullptr || topo->nodoArvore->frequencia >= no->frequencia) {
        novoNodo->proximo = topo;
        topo = novoNodo;
    } else {
        Lista* atual = topo;
        while (atual->proximo != nullptr && atual->proximo->nodoArvore->frequencia < no->frequencia) {
            atual = atual->proximo;
        }
        novoNodo->proximo = atual->proximo;
        atual->proximo = novoNodo;
    }
}

void atualizarMapaDeBits(MapaDeBits* &topo, char caracter, std::string bits) {
    MapaDeBits* novoBit = new MapaDeBits();
    novoBit->caracter = caracter;
    novoBit->bits = bits;
    novoBit->proximo = topo;
    topo = novoBit;
}

void mostrarHuffman(NoArvore* raiz, std::string str, MapaDeBits* &mapaDeBits) {
    if (!raiz) return;

    if (raiz->caracter != '$')
        atualizarMapaDeBits(mapaDeBits, raiz->caracter, str);

    mostrarHuffman(raiz->esquerdo, str + "0", mapaDeBits);
    mostrarHuffman(raiz->direito, str + "1", mapaDeBits);
}

void codigoDeHuffman(std::string text) {
    NoArvore *listaDeFrequencia = nullptr;
    for (char i : text) {
        atualizarListaDeFrequencia(i, listaDeFrequencia);
    }

    Lista* listaNo = nullptr;
    NoArvore* atual = listaDeFrequencia;
    while (atual != nullptr) {
        inserirNoLista(listaNo, new NoArvore(atual->caracter, atual->frequencia));
        atual = atual->direito;
    }

    while (listaNo != nullptr && listaNo->proximo != nullptr) {
        NoArvore *esquerdo = listaNo->nodoArvore;
        listaNo = listaNo->proximo;
        NoArvore *direito = listaNo->nodoArvore;
        listaNo = listaNo->proximo;

        NoArvore *topo = new NoArvore('$', esquerdo->frequencia + direito->frequencia);
        topo->esquerdo = esquerdo;
        topo->direito = direito;
        inserirNoLista(listaNo, topo);
    }

    MapaDeBits* bitMap = nullptr;
    mostrarHuffman(listaNo->nodoArvore, "", bitMap);

    std::cout << "Tabela de Bits:\n";
    while (bitMap != nullptr) {
        std::cout << bitMap->caracter << " : " << bitMap->bits << "\n";
        bitMap = bitMap->proximo;
    }
}