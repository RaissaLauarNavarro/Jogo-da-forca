#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <ctime>  
#include <cstdlib>
#include "TerminalPalette.hpp"

struct CharIntPair {
    char character;
    int integer;
    
    CharIntPair(char c, int i) : character(c), integer(i) {}
};

void inicializacoao();
std::vector<std::string> cadastrarPalavras(std::vector<std::string> palavras);
int sortearNumero(int tamanhoPalavras);
void novoJogo(std::vector<std::string> palavras);
// void novasPalavras(std::vector<std::string> palavras);
void imprimirLetras(int tamanhoPalavra, int tentativas, std::set<char> letrasErradas);
std::set<char> verificarLetra(char letra, std::string palavra, std::set<char> letrasErradas);
void letraCorreta(std::queue<CharIntPair> letrasCorretas, int tamanhoPalavra);


int main() {
    std::vector<std::string> Palavras;
    int opcao;

    inicializacoao();
    Palavras = cadastrarPalavras(Palavras);
    std::cin >> opcao;

    switch (opcao){
        case 1:
            novoJogo(Palavras);
            break;
        case 2:
            // novasPalavras(Palavras);
            break;
        default:
            std::cout << "Escolha novamente:" << std::endl;
            std::cin >> opcao;
            break;
    }
}


void inicializacoao(){
    std::cout << color::purples << "Bem vinda(o) ao Jogo da Forca!" << color::off << std::endl;
    std::cout << "Escolha uma opcao:" << std::endl;
    std::cout << "  1- novo jogo" << std::endl;
    std::cout << "  2- cadastrar palavras" << std::endl;
}


void novoJogo(std::vector<std::string> palavras){
    int indiceSorteado = sortearNumero(palavras.size());
    std::string palavra = palavras[indiceSorteado];
    std::set<char> letrasErradas;

    int tamanhoPalavra = palavra.length();
    int quantidadeJogadas = 20;
    char tentativa;
    while(quantidadeJogadas >= 0){
        imprimirLetras(tamanhoPalavra, quantidadeJogadas, letrasErradas);
        std::cout << color::bluep << "Digite sua tentativa: " << color::off;
        std::cin >> tentativa;
        letrasErradas = verificarLetra(tentativa, palavra, letrasErradas);
        quantidadeJogadas--;
    }

    // std::cout << palavra << std::endl;
}


// void novasPalavras(std::vector<std::string> palavras){

// }


std::vector<std::string> cadastrarPalavras(std::vector<std::string> palavras){
    palavras.push_back("Sanduiche");
    palavras.push_back("Vermelho");
    palavras.push_back("Cavalo");
    palavras.push_back("Nave Espacial");
    palavras.push_back("Mochila");

    return palavras;
}


void imprimirLetras(int tamanhoPalavra, int tentativas, std::set<char> letrasErradas){
    if(tentativas == 20){
        for(int i = 0; i <= tamanhoPalavra; i++){
            std::cout << "_ ";
        }
        std::cout << std::endl;
    }else{
        std::cout << color::reds << "Erradas: " << color::off;
        for (auto it = letrasErradas.begin(); it != letrasErradas.end(); ++it) {
            std::cout << color::reds << *it << " " << color::off;
        }
        std::cout << std::endl;
    }
}


std::set<char> verificarLetra(char letra, std::string palavra, std::set<char> letrasErradas){
    int contadorPosicao = -1;
    int contadorLetras = 0;
    std::queue<CharIntPair> letrasCorretas;
    for(char i: palavra){
        contadorPosicao++;
        if (i == letra){
            letrasCorretas.push(CharIntPair(i, contadorPosicao));
            contadorLetras++;
        }
    }

    if(contadorLetras == 0){
        letrasErradas.insert(letra);
    }else {
        letraCorreta(letrasCorretas, palavra.size());
    }
    return letrasErradas;
}


int sortearNumero(int tamanhoPalavras){
    // Seed a função rand() com o tempo atual para obter números verdadeiramente aleatórios.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int indiceAleatorio = std::rand() % tamanhoPalavras;
    return indiceAleatorio;
}


void letraCorreta(std::queue<CharIntPair> letrasCorretas, int tamanhoPalavra){
    std::vector<char> palavraAcertos;
    for(int i=0; i <= tamanhoPalavra; i++){
        palavraAcertos[i] = '_';
    }

    if(letrasCorretas.size() != 0){
        for(CharIntPair j: letrasCorretas){
            palavraAcertos[j.integer] = j.character;
        }

        for(int i=0; i <= tamanhoPalavra; i++){
            std::cout << color::green << palavraAcertos << color::off;
        }
        std::cout << std::endl;

    }else{
        for(int i = 0; i <= tamanhoPalavra; i++){
            std::cout << "_ ";
        }
        std::cout << std::endl;
    }
}