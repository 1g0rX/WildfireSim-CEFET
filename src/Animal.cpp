#include "Animal.hpp"

Animal::Animal() : 
    posX(-1), posY(-1), passos(0), encontrouAgua(0), 
    vivo(true), iteracaoMorte(-1), iteracoesParado(0) {}

void Animal::setPosicao(int x, int y) {
    posX = x;
    posY = y;
}

void Animal::marcarEncontroAgua() {
    encontrouAgua++;
}

void Animal::morrer(int iteracao) {
    vivo = false;
    iteracaoMorte = iteracao;
}

void Animal::incrementarPassos() {
    passos++;
}

void Animal::incrementarIteracoesParado() {
    iteracoesParado++;
}

void Animal::resetarIteracoesParado() {
    iteracoesParado = 0;
}

int Animal::getPosX() const { return posX; }
int Animal::getPosY() const { return posY; }
int Animal::getPassos() const { return passos; }
int Animal::getEncontrouAgua() const { return encontrouAgua; }
bool Animal::estaVivo() const { return vivo; }
int Animal::getIteracaoMorte() const { return iteracaoMorte; }
int Animal::getIteracoesParado() const { return iteracoesParado; }