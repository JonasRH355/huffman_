struct Folha{
    char caracter;
};

struct Arvore{
    Folha* raiz = nullptr;
    Arvore * Tl = nullptr;
    Arvore * TR = nullptr;
};

struct No{
    char letter = '\0';
    int frequencia = 0;
    No * direito = nullptr;
};

struct lista{
    No* inicio = nullptr;
    No* fim = nullptr;
};

bool inserirlista(lista &lista,char caracter,int freq){
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
        while (aux != nullptr) {
            if (aux->frequencia <= novo->frequencia && novo->frequencia <= aux->direito->frequencia) {//caso 1: aux <= x <= next
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

    while (current) { //
        if (current->letter == caracter) {
            int freq = current->frequencia +1;
            retirarLista(x,current->letter);
            inserirlista(x,caracter,freq);
            return true;
        }
        if (!current->direito){
            inserirlista(x,caracter,1);
            return true;
        }
        current = current->direito;
    }

    return true;
}

bool listadefrequencia(const std::string& text,lista  &x){
    for (char i : text) {
        inserirlistadefrequencia(x,i);
    }
    return true;
}

bool ordenar(lista lista_original, lista &lista_ordenada){
    No *trv = lista_original.inicio;
    std::cout<<trv->frequencia;
    while (trv->direito != nullptr){
        inserirlista(lista_ordenada,trv->letter,1);
        trv = trv->direito;
    }
}

void mostrarLista (lista text){
    No *aux = text.inicio;
    while (aux != nullptr) {
        std::cout << aux->letter<< " : "<< aux->frequencia<< "\n";
        aux = aux->direito;
    }
}
