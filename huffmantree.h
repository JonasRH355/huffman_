struct No{
    char letter = '\0';
    int frequencia = 0;
    No * direito = nullptr;
};

struct NoArvore{
    char letter = '\0';
    int frequencia = 0;
    NoArvore * direito = nullptr;
    NoArvore * esquerdo = nullptr;
};

struct lista{
    No* inicio = nullptr;
    No* fim = nullptr;
};

struct Arvore{
    NoArvore *raiz = nullptr;
};

//_____________________Funções padrões__________________________
void mostrarArvore(NoArvore *raiz){
    if (raiz == nullptr) return;
    mostrarArvore(raiz->esquerdo);
    std::cout<<raiz->letter<<" : "<<raiz->frequencia<<std::endl;
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
    No *novo = new No;
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

bool retirarLista( lista &lista, char valor ){ // Função feita para retirar da lista
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

bool listadefrequencia(const std::string& text,lista  &x){ // Função que gera a lista de frequência
    for (char i : text) {
        inserirlistadefrequencia(x,i);
    }
    return true;
}
//_____________________Fim Funções Gerais_____________________________________


//_________________________Árvore_____________________________________________

int somaFrequencia (int x,int y){
    return x+y;
}

void copieNos(No *x, NoArvore *&y){
    y->frequencia = x->frequencia;
    y->letter = x->letter;
}

bool brotoDaLista(lista x,Arvore &z)  // Função que cria um árvore dos primeiros nós da lista
{
    No *aux = x.inicio;
    auto *raiz = new NoArvore;
    auto *esq = new NoArvore;
    auto *dir = new NoArvore;
    int soma = somaFrequencia(aux->frequencia,aux->direito->frequencia);
    raiz->frequencia= soma;
    copieNos(aux,dir);
    copieNos(aux->direito,esq);
    raiz->direito = dir;
    raiz->esquerdo = esq;
    z.raiz = raiz;
    return true;
}

bool criarArvore(){

}
//_______________________Fim Árvore___________________________________________