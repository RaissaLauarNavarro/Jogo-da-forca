#include <iostream>
#include <string>
#include <algorithm>
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
void novoJogo(const std::vector<std::string>& palavras);
// void novasPalavras(std::vector<std::string> palavras);
void imprimirLetrasErradas(std::set<char> letrasErradas, std::string palavra);
std::vector<char> letraCorreta(std::queue<CharIntPair>& letrasCorretas, int tamanhoPalavra, std::vector<char>& palavraAcertos);
void verificarLetra(char letra, const std::string& palavra, std::set<char>& letrasErradas, std::queue<CharIntPair>& letrasCertas);
void bonequinho(int erros, std::string palavra);


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
    system("cls");
    std::cout << color::purples << "Bem vinda(o) ao Jogo da Forca!" << color::off << std::endl;
    std::cout << "Escolha uma opcao:" << std::endl;
    std::cout << "  1- novo jogo" << std::endl;
    std::cout << "  2- cadastrar palavras" << std::endl;
}


void novoJogo(const std::vector<std::string>& palavras) {
    int indiceSorteado = sortearNumero(palavras.size());
    std::string palavra = palavras[indiceSorteado];
    std::set<char> letrasErradas;
    std::queue<CharIntPair> letrasCorretas;
    std::vector<char> palavraCorreta;

    int tamanhoPalavra = palavra.length();
    int quantidadeJogadas = 20;
    char tentativa;
    int encontrado = 0;
    std::vector<char> palavraAcertos(tamanhoPalavra, '_');
    letraCorreta(letrasCorretas, tamanhoPalavra, palavraAcertos);

    system("cls");
    while (quantidadeJogadas > 0) {
        imprimirLetrasErradas(letrasErradas, palavra);
        std::cout << color::bluep << "_____________________________________ " << color::off << std::endl;
        std::cout << color::bluep << " Digite sua tentativa: " << color::off;
        std::cin >> tentativa;
        verificarLetra(tentativa, palavra, letrasErradas, letrasCorretas);
        letraCorreta(letrasCorretas, tamanhoPalavra, palavraAcertos);
        quantidadeJogadas--;

        if (std::count(palavraAcertos.begin(), palavraAcertos.end(), '_') == 0) {
            std::cout << color::yellow << "Parabens! Voce acertou a palavra!" << color::off << std::endl;
            break; 
        }
    }
    if(quantidadeJogadas == 0)
        std::cout << color::blue << "Acabaram suas tentativas... A palavra era: " << palavra << color::off << std::endl;
}


void verificarLetra(char letra, const std::string& palavra, std::set<char>& letrasErradas, std::queue<CharIntPair>& letrasCertas) {
    int contadorPosicao = -1;
    int contadorLetras = 0;

    for (char i : palavra) {
        contadorPosicao++;
        if (std::tolower(i) == std::tolower(letra)) {
            contadorLetras++;
            letrasCertas.push(CharIntPair(i, contadorPosicao));
        }
    }

    if(!contadorLetras) {
        if (letrasErradas.find(letra) == letrasErradas.end()) {
            letrasErradas.insert(letra);
        }   
    }
}


std::vector<char> letraCorreta(std::queue<CharIntPair>& letrasCorretas, int tamanhoPalavra, std::vector<char>& palavraAcertos) {
    while (!letrasCorretas.empty()) {
        CharIntPair j = letrasCorretas.front();
        letrasCorretas.pop();
        if (j.integer >= 0 && j.integer < tamanhoPalavra) {
            palavraAcertos[j.integer] = j.character;
        }
    }

    std::cout << std::endl;
    for (int i = 0; i < tamanhoPalavra; i++) {
        std::cout << color::green << palavraAcertos[i] << color::off;
    }
    std::cout << std::endl;
    return palavraAcertos;
}


void imprimirLetrasErradas(std::set<char> letrasErradas, std::string palavra){
    int contador = 0;
        std::cout << color::reds << "Erradas:" << color::off << " ";
        for (auto it = letrasErradas.begin(); it != letrasErradas.end(); ++it) {
            std::cout << color::reds << *it << color::off << " ";
            contador++;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        bonequinho(contador, palavra);
}


std::vector<std::string> cadastrarPalavras(std::vector<std::string> palavras){
    palavras.push_back("Sanduiche");
    palavras.push_back("Vermelho");
    palavras.push_back("Cavalo");
    palavras.push_back("Cherife");
    palavras.push_back("Mochila");
    palavras.push_back("Espada");
    palavras.push_back("Otorrino");
    palavras.push_back("Laranjeira");
    palavras.push_back("Parente");
    palavras.push_back("Bosque");

    return palavras;
}


// void novasPalavras(std::vector<std::string> palavras){

// }


int sortearNumero(int tamanhoPalavras){
    // Seed a função rand() com o tempo atual para obter números verdadeiramente aleatórios.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int indiceAleatorio = std::rand() % tamanhoPalavras;
    return indiceAleatorio;
}


void bonequinho(int erros, std::string palavra){
    switch (erros)
    {
    case 1:
        std::cout << " o " << std::endl;
        std::cout << std::endl;
        break;
    case 2:
        std::cout << " o " << std::endl;
        std::cout << " | " << std::endl;
        std::cout << std::endl;
        break;
    case 3:
        std::cout << " o " << std::endl;
        std::cout << "/| " << std::endl;
        std::cout << std::endl;
        break;
    case 4:
        std::cout << " o " << std::endl;
        std::cout << "/|/ " << std::endl;
        std::cout << std::endl;
        break;
    case 5:
        std::cout << " o " << std::endl;
        std::cout << "/|/ " << std::endl;
        std::cout << "/ " << std::endl;
        std::cout << std::endl;
        break;
    case 6:
        std::cout << " o " << std::endl;
        std::cout << "/|/ " << std::endl;
        std::cout << "// " << std::endl;
        std::cout << std::endl;
        break;
    case 7:
        std::cout << color::blue << "Acabaram suas tentativas... A palavra era: " << palavra << color::off << std::endl;
        exit(1);
        break;
    }
}