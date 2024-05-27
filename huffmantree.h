
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

};

//_____________________Funções padrões__________________________
void mostrarArvore(NoArvore *raiz){
    if (raiz == nullptr) return;
    mostrarArvore(raiz->esquerdo);
    std::cout<<raiz->caracter<<" : "<<raiz->frequencia<<std::endl;
    mostrarArvore(raiz->direito);
}


void mostrarLista (lista text){ //mostra a lista
    No *aux = text.inicio;
    while (aux != nullptr) {
        std::cout << aux->letter<< " : "<< aux->frequencia<< "\n";
        aux = aux->direito;
    }
}

bool inserirlista(lista &lista,char caracter,int freq){ // iserir de forma ordenada
    auto *novo = new No;
    novo->letter = caracter;
    novo->frequencia = freq;
    if (novo->frequencia <= lista.inicio->frequencia) {      //caso for igual ou menor que a primeira
        novo->direito = lista.inicio;
        lista.inicio = novo;
        return true;
    } else if (novo->frequencia > lista.fim->frequencia) {
        lista.fim->direito = novo;
        lista.fim = novo;
        return true;
    }                                    //caso for a maior
    else {
        No *aux = lista.inicio;
        while (aux != nullptr) {  //caso 1: aux <= x <= next
            if (aux->frequencia <= novo->frequencia && novo->frequencia <= aux->direito->frequencia) {
                novo->direito = aux->direito;
                aux->direito = novo;
                return true;
            }
            aux = aux->direito;
        }
        return false;
    }
}

bool inserirnacopia(lista &lista,No ){

}

bool retirarLista(lista &lista, char valor ){ // Função feita para retirar da lista
    if( lista.inicio == nullptr ) return false;

    No *aux = lista.inicio;
    No *ant = nullptr;
    while( aux != nullptr && valor != aux->letter ){ // loop para procurar o no da lista
        ant = aux;
        aux = aux->direito;
    }
    if( aux == nullptr ) return false; // caso não esteja na lista

    if( aux == lista.inicio && aux == lista.fim ){ // Se for o único da lista
        lista.inicio = nullptr;
        lista.fim = nullptr;
        delete aux;
        return true;
    }
    if( aux == lista.inicio ){ // Se for o primeiro da Lista
        lista.inicio = aux->direito;
        delete aux;
        return true;
    }
    if( aux == lista.fim ){ // Se for ultimo da lista
        ant->direito = nullptr;
        lista.fim = ant;
        delete aux;
        return true;
    }
    // se estiver no meio da lista
    ant->direito = aux->direito;
    delete aux;
    return true;
}
//_____________________Fim Funções Padrões__________________________________

//______________________Funções gerais______________________________________
bool inserirlistadefrequencia(lista &x,char caracter ){
    if (x.inicio == nullptr && x.fim == nullptr){  // Caso que acontece quando não tem nada na lista
        No* novoNo = new No;
        novoNo->letter = caracter;
        novoNo->frequencia = 1;
        x.inicio= novoNo;
        x.fim= novoNo;
        return  true;
    }

    No *current = x.inicio;
    while (current) { // loop que percorre a lista...
        if (current->letter == caracter) {   // caso já tenha na lista,
            int freq = current->frequencia +1;  // ele aumenta +1 de frequência e realoca dentro da lista
            retirarLista(x,current->letter);
            inserirlista(x,caracter,freq);
            return true;
        }
        if (!current->direito){ // se chegou até o ultimo da lista e não o achou, inseri ele no começo dela
            inserirlista(x,caracter,1);
            return true;
        }
        current = current->direito;
    }

    return true;
}

bool listadefrequencia(const char text,No*  &x){ // Função que gera a lista de frequência
    No* atual = x;
    while (atual != nullptr && atual->letter != text) {
        atual = atual->direito;
    }
    if (atual != nullptr) {
        atual->frequencia++;
    } else {
        No* novafrequencia = new No();
        novafrequencia->letter = text;
        novafrequencia->frequencia = 1;
        novafrequencia->direito = x;
        x = novafrequencia;
    }
}
//_____________________Fim Funções Gerais_____________________________________


//_________________________Árvore_____________________________________________

int somaFrequencia (int x,int y){
    return x+y;
}

void copieNos(No *x, No *&y){
    y->frequencia = x->frequencia;
    y->letter = x->letter;
}
/*
bool brotoDaLista(lista x,Arvore &z)  // Função que cria um árvore dos primeiros nós da lista
{
    No *aux = x.inicio;
    auto *raiz = new NoArvore('c',3);
    auto *esq = new No;
    auto *dir = new No;
    int soma = somaFrequencia(aux->frequencia,aux->direito->frequencia);
    raiz->frequencia= soma;
    copieNos(aux,dir);
    copieNos(aux->direito,esq);
    raiz->direito = dir;
    raiz->esquerdo = esq;
    z.raiz = raiz;
    return true;
}
*/
bool criarArvore(lista l_ordenada, Arvore ArvoreMae){
    if(l_ordenada.inicio == nullptr){return false;}
    No *aux = l_ordenada.inicio;
    lista copia = l_ordenada;
    /*
    while (aux){
        if(aux->direito->frequencia == ArvoreMae.raiz->frequencia)
        {
            if (aux->direito->direito->frequencia >= ArvoreMae.raiz->frequencia){
                brotoDaLista(copia,ArvoreMae);
            }
            if (aux->direito->direito->frequencia == ArvoreMae.raiz->frequencia){

            }
        }
        aux = aux->direito;
    }*/
/*
    while(aux){


        brotoDaLista(copia,ArvoreMae);
        retirarLista(copia,aux->letter);

        aux = aux->direito;
    }


    mostrarArvore(ArvoreMae.raiz);*/
}
//_______________________Fim Árvore___________________________________________
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


void codigo_de_huffman(std::string text){
    No * lista_defrequencia = nullptr;
    for (char i : text) {
        listadefrequencia(text[i],lista_defrequencia);
    }
    Lista* listaNo = nullptr;
    No* atual = lista_defrequencia;
    while (atual != nullptr) {
        inserirNoLista(listaNo, new No(atual->letter, atual->frequencia));
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
    printHuffmanCodes(listaNo->nodaArvore, "", bitMap);

    // Imprimir tabela de bits
    std::cout << "Tabela de Bits:\n";
    while (bitMap != nullptr) {
        std::cout << bitMap->character << " : " << bitMap->bits << "\n";
        bitMap = bitMap->next;
    }
}