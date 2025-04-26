#ifndef ANIMAL_HPP
#define ANIMAL_HPP

class Animal {
private:
    int posX;
    int posY;
    int passos;
    int encontrouAgua;
    bool vivo;
    int iteracaoMorte;
    int iteracoesParado;

public:
    Animal();
    
    // Setters
    void setPosicao(int x, int y);
    void marcarEncontroAgua();
    void morrer(int iteracao);
    void incrementarPassos();
    void incrementarIteracoesParado();
    void resetarIteracoesParado();
    
    // Getters
    int getPosX() const;
    int getPosY() const;
    int getPassos() const;
    int getEncontrouAgua() const;
    bool estaVivo() const;
    int getIteracaoMorte() const;
    int getIteracoesParado() const;
};

#endif