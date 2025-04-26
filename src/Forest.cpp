#include "Forest.hpp"
#include "../config.hpp"
#include <fstream>
#include <iostream>
using namespace std;

Forest::Forest() {
    ifstream entrada("input.dat");
    if (!entrada) {
        cerr << "Erro ao abrir input.dat" << endl;
        exit(1);
    }
    ofstream saida("output.dat", ios::trunc);
    saida.close();

    entrada >> linhas >> colunas >> posFogoX >> posFogoY;

    // Ajustar para índice 0
    posFogoX--;
    posFogoY--;

    // Alocar mapa
    mapa = new int*[linhas];
    for (int i = 0; i < linhas; i++) {
        mapa[i] = new int[colunas];
    }

    // Ler mapa e encontrar animal
    bool animalColocado = false;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            entrada >> mapa[i][j];
            
            // Colocar animal na primeira posição segura (0)
            if (!animalColocado && mapa[i][j] == 0) {
                animal.setPosicao(i, j);
                animalColocado = true;
            }
        }
    }
    if (mapa[posFogoX][posFogoY] != 1) {
    cerr << "Erro: O fogo deve começar em uma árvore saudável (valor 1)!" << endl;
    exit(1);
    }
    
    if (!animalColocado) {
        cerr << "Nenhuma posição segura para o animal!" << endl;
        exit(1);
    }
    
    entrada.close();
}

Forest::~Forest() {
    for (int i = 0; i < linhas; i++) {
        delete[] mapa[i];
    }
    delete[] mapa;
}

bool Forest::posicaoValida(int x, int y) {
    return x >= 0 && x < linhas && y >= 0 && y < colunas;
}

void Forest::propagarFogo() {
    bool** novoFogo = new bool*[linhas];
    for (int i = 0; i < linhas; i++) {
        novoFogo[i] = new bool[colunas]{false};
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (mapa[i][j] == 1) {
                if (posicaoValida(i-1, j) && mapa[i-1][j] == 2 && VENTO_NORTE) novoFogo[i][j] = true;
                if (posicaoValida(i+1, j) && mapa[i+1][j] == 2 && VENTO_SUL) novoFogo[i][j] = true;
                if (posicaoValida(i, j-1) && mapa[i][j-1] == 2 && VENTO_OESTE) novoFogo[i][j] = true;
                if (posicaoValida(i, j+1) && mapa[i][j+1] == 2 && VENTO_LESTE) novoFogo[i][j] = true;
                
                if (!VENTO_NORTE && !VENTO_SUL && !VENTO_OESTE && !VENTO_LESTE) {
                    if (posicaoValida(i-1, j) && mapa[i-1][j] == 2) novoFogo[i][j] = true;
                    if (posicaoValida(i+1, j) && mapa[i+1][j] == 2) novoFogo[i][j] = true;
                    if (posicaoValida(i, j-1) && mapa[i][j-1] == 2) novoFogo[i][j] = true;
                    if (posicaoValida(i, j+1) && mapa[i][j+1] == 2) novoFogo[i][j] = true;
                }
            }
        }
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (mapa[i][j] == 2) mapa[i][j] = 3;
            if (novoFogo[i][j]) mapa[i][j] = 2;
        }
        delete[] novoFogo[i];
    }
    delete[] novoFogo;
}

void Forest::atualizarVizinhosAgua(int x, int y) {
    if (posicaoValida(x-1, y)) mapa[x-1][y] = 1;
    if (posicaoValida(x+1, y)) mapa[x+1][y] = 1;
    if (posicaoValida(x, y-1)) mapa[x][y-1] = 1;
    if (posicaoValida(x, y+1)) mapa[x][y+1] = 1;
}

void Forest::moverAnimal() {
    int posX = animal.getPosX();
    int posY = animal.getPosY();

    // Se está na água
    if (mapa[posX][posY] == 4) {
        mapa[posX][posY] = 0;
        atualizarVizinhosAgua(posX, posY);
        animal.marcarEncontroAgua();
        animal.resetarIteracoesParado();
        return;
    }

    // Se está parado em área segura
    if (mapa[posX][posY] == 0) {
        animal.incrementarIteracoesParado();
        if (animal.getIteracoesParado() <= MAX_ITERACOES_PARADO) {
            return;
        }
    }

    // Procurar melhor movimento
    int melhorValor = -1;
    int melhorX = posX, melhorY = posY;
    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    for (int i = 0; i < 4; i++) {
        int nx = posX + dx[i];
        int ny = posY + dy[i];
        
        if (posicaoValida(nx, ny)) {
            int valorAtual = mapa[nx][ny];
            
            if (valorAtual == 4) {
                melhorX = nx;
                melhorY = ny;
                break;
            }
            else if (valorAtual > melhorValor && valorAtual != 2) {
                melhorValor = valorAtual;
                melhorX = nx;
                melhorY = ny;
            }
        }
    }
    
    if (melhorX != posX || melhorY != posY) {
        animal.setPosicao(melhorX, melhorY);
        animal.incrementarPassos();
        animal.resetarIteracoesParado();
    }
}

void Forest::salvarSaida(int iteracao) {
    ofstream saida("output.dat", ios::app);
    saida << "Iteracao " << iteracao << ":\n";
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (i == animal.getPosX() && j == animal.getPosY() && animal.estaVivo()) {
                saida << "A "; // Marca a posição do animal
            } else {
                saida << mapa[i][j] << " ";
            }
        }
        saida << "\n";
    }
    saida << "\n";
    saida.close();
}

void Forest::simular() {
    if (posicaoValida(posFogoX, posFogoY)) {
        mapa[posFogoX][posFogoY] = 2;
    }
    
    salvarSaida(0);
    
    for (int iteracao = 1; iteracao <= MAX_ITERACOES; iteracao++) {
        moverAnimal();
        propagarFogo();
        
        if (mapa[animal.getPosX()][animal.getPosY()] == 2 || 
            mapa[animal.getPosX()][animal.getPosY()] == 3) {
            moverAnimal();
            
            if (mapa[animal.getPosX()][animal.getPosY()] == 2 || 
                mapa[animal.getPosX()][animal.getPosY()] == 3) {
                animal.morrer(iteracao);
                break;
            }
        }
        
        salvarSaida(iteracao);
        
        bool temFogo = false;
        for (int i = 0; i < linhas && !temFogo; i++) {
            for (int j = 0; j < colunas && !temFogo; j++) {
                if (mapa[i][j] == 2) temFogo = true;
            }
        }
        
        if (!temFogo) break;
    }
    
    ofstream saida("output.dat", ios::app);
    saida << "Resultado final:\n";
    saida << "Passos do animal: " << animal.getPassos() << "\n";
    saida << "Vezes que encontrou agua: " << animal.getEncontrouAgua() << "\n";
    saida << "Animal " << (animal.estaVivo() ? "sobreviveu" : "morreu na iteracao " + to_string(animal.getIteracaoMorte())) << "\n";
    saida.close();
}

int Forest::getPassosAnimal() const { return animal.getPassos(); }
int Forest::getEncontrouAgua() const { return animal.getEncontrouAgua(); }
bool Forest::getAnimalVivo() const { return animal.estaVivo(); }
int Forest::getIteracaoMorteAnimal() const { return animal.getIteracaoMorte(); }