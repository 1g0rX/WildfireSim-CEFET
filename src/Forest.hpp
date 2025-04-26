#ifndef FOREST_HPP
#define FOREST_HPP

#include "Animal.hpp"

class Forest {
private:
    int** mapa;
    int linhas;
    int colunas;
    int posFogoX, posFogoY;
    Animal animal;
    
    // Métodos auxiliares
    bool posicaoValida(int x, int y);
    void propagarFogo();
    void moverAnimal();
    void atualizarVizinhosAgua(int x, int y);
    void salvarSaida(int iteracao);
    
public:
    Forest();
    ~Forest();
    
    void simular();
    
    // Getters
    int getPassosAnimal() const;
    int getEncontrouAgua() const;
    bool getAnimalVivo() const;
    int getIteracaoMorteAnimal() const;
};

#endif