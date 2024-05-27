
struct No{
    char letter = '\0';
    int frequencia = 0;
    No * direito = nullptr;
};

struct NoArvore{
    char caracter;
    unsigned frequencia = 0;
    NoArvore * direito = nullptr;
    NoArvore * esquerdo = nullptr;
    NoArvore(char caracter, unsigned freq){
        this->caracter = caracter;
        this->frequencia = freq;
    }
};

struct lista{
    No* inicio = nullptr;
    No* fim = nullptr;
};

struct Lista{
    NoArvore * nodaArvore = nullptr;
    Lista * proximo = nullptr;
};

struct Arvore{
    NoArvore *raiz = nullptr;
};

struct MapadeBits{
    char caracter;
    std::string bits;
    MapadeBits *next;
};

bool listadefrequencia(const char text,No*  &x) { // Função que gera a lista de frequência
    No *atual = x;
    while (atual != nullptr && atual->letter != text) {
        atual = atual->direito;
    }
    if (atual != nullptr) {
        atual->frequencia++;
    } else {
        No *novafrequencia = new No();
        novafrequencia->letter = text;
        novafrequencia->frequencia = 1;
        novafrequencia->direito = x;
        x = novafrequencia;
    }
}

bool inserir(NoArvore * &raiz, char caracter, unsigned freq){
    if(raiz == nullptr){
        raiz = new NoArvore(caracter,freq);
        return true;
    }
    if(freq < raiz->frequencia){
        return inserir(raiz->esquerdo,caracter,freq);
    }else {
        return inserir(raiz->direito,caracter,freq);
    }
}

void inserirNoLista(Lista* &topo, NoArvore* no){
    Lista* newNode = new Lista();
    newNode->nodaArvore = no;
    newNode->proximo = nullptr;

    if (topo == nullptr || topo->nodaArvore->frequencia >= no->frequencia) {
        newNode->proximo = topo;
        topo = newNode;
    } else {
        Lista* Atual = topo;
        while (Atual->proximo != nullptr && Atual->proximo->nodaArvore->frequencia < no->frequencia) {
            Atual = Atual->proximo;
        }
        newNode->proximo = Atual->proximo;
        Atual->proximo = newNode;
    }
}

void atualizarbitmapa(MapadeBits* &topo, char caracter,std::string bits){
    MapadeBits* novobit = new MapadeBits();
    novobit->caracter = caracter;
    novobit->bits = bits;
    novobit->next = topo;
    topo = novobit;
}

void mostrarHuffman(NoArvore* rota,std::string str,MapadeBits* &bitmap){
    if (!rota)
        return;

    if (rota->caracter != '$')
        atualizarbitmapa(bitmap, rota->caracter, str);

    mostrarHuffman(rota->esquerdo, str + "0", bitmap);
    mostrarHuffman(rota->direito, str + "1", bitmap);
}


void codigo_de_huffman(std::string text){
    No * lista_defrequencia = nullptr;
    for (char i : text) {
        listadefrequencia(i,lista_defrequencia);
    }
    Lista* listaNo = nullptr;
    No* atual = lista_defrequencia;
    while (atual != nullptr) {
        inserirNoLista(listaNo, reinterpret_cast<NoArvore *>(new No(atual->letter, atual->frequencia)));
        atual = atual->direito;
    }

        while (listaNo != nullptr && listaNo->proximo != nullptr) {
        NoArvore * esquerdo= listaNo->nodaArvore;
        listaNo = listaNo->proximo;
        NoArvore *right = listaNo->nodaArvore;
        listaNo = listaNo->proximo;

        NoArvore *topo = new NoArvore('$', esquerdo->frequencia + right->frequencia);
        topo->esquerdo = esquerdo;
        topo->direito = right;
        inserirNoLista(listaNo, topo);
    }

    MapadeBits* bitMap = nullptr;
    mostrarHuffman(listaNo->nodaArvore, "", bitMap);

    // Imprimir tabela de bits
    std::cout << "Tabela de Bits:\n";
    while (bitMap != nullptr) {
        std::cout << bitMap->caracter << " : " << bitMap->bits << "\n";
        bitMap = bitMap->next;
    }
}