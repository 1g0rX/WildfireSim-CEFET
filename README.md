# WildfireSim-CEFET - Simulador de fogo em uma floresta
<p align="center">
  <img src=".assets/Lobo Entre Chamas na Floresta.png" width="500"/>
</p>

## Autor

Desenvolvido por Igor.

--- 
## Introdução


Esse trabalho visa relembrar um pouco de tudo estudado até o momento e tem como objetivo simular um incêndio em uma floresta que e como um animal reagiria neste incêndio.

O programa funciona resumidamente da seguinte forma:

  - Lê um arquivo chamado `input.dat`` que contém uma matriz.
  - O animal começa a movimentar, com prioridades de lugar e o incêndio propaga de acordo com os parâmetros de vento do arquico `config.hpp`.
  - O programa roda até o fogo não conseguir mais se propagar, o animal morrer ou o número máximo de interações for alcançado.
  - O resultado de cada interação e o resumo final é salvo no arquivo `output.dat`.

## Metodologia

<details> <summary> Clique para mostrar um fluxograma com o funcionamento geral do programa </summary>

[![](https://www.mermaidchart.com/raw/00f4be7d-aa73-4235-8c2f-db17582f7f5c?theme=light&version=v0.1&format=svg)

</details>

### Funcionamento de cada classe

#### [config.hpp](config.hpp) 

Este é o arquivo que define as seguintes configurações do código:

  - MAX_ITERACOES ->  define o máximo de interações/ciclos do código.
  - VENTO_NORTE -> se "true", define a direção do vento para NORTE.
  - VENTO_SUL -> se "true", deine a direção do vento para SUL
  - VENTO_LESTE -> se "true", define a direção do vento para LESTE.
  - VENTO_OESTE -> se "true", define a direção do vento para OESTE.

> [!IMPORTANT]
> Alterar essas configurações será necessário compilar novamente o programa, pois **o arquivo é lido em tempo de compilação apenas**.

#### [Forest.cpp](src/Forest.cpp)

Esta é a classe principal do programa, aqui é feita a leitura e escrita nos arquivos, montado a floresta e implementado a propagação do fogo e onde as funções de movimentação do animal são chamadas.

#### Classes principais

| Método                     | Parâmetros               | Retorno | Descrição                                                                 |
|----------------------------|--------------------------|---------|---------------------------------------------------------------------------|
| `Forest()`                 | -                        | -       | Construtor que inicializa a floresta e lê o arquivo `input.dat`          |
| `~Forest()`                | -                        | -       | Destrutor que libera a memória da matriz                                 |
| `simular()`                | -                        | void    | Controla o loop principal da simulação                                   |
| `propagarFogo()`           | -                        | void    | Atualiza o estado das células conforme as regras de propagação           |
| `moverAnimal()`            | -                        | void    | Gerencia toda a lógica de movimentação do animal                         |
| `salvarSaida(int iteracao)`| `iteracao`: número atual | void    | Grava o estado atual da floresta no arquivo `output.dat`                 |
| `posicaoValida(int x, int y)` | `x,y`: coordenadas    | bool    | Verifica se a posição está dentro dos limites da matriz                  |

### [Animal.cpp](src/Animal.cpp)
| Método                     | Parâmetros               | Retorno | Descrição                                                                 |
|----------------------------|--------------------------|---------|---------------------------------------------------------------------------|
| `Animal()`                 | -                        | -       | Construtor que inicializa os atributos do animal                         |
| `setPosicao(int x, int y)` | `x,y`: novas coordenadas | void    | Atualiza a posição atual do animal                                       |
| `marcarEncontroAgua()`     | -                        | void    | Incrementa o contador de encontros com água                              |
| `incrementarPassos()`      | -                        | void    | Adiciona +1 ao contador de passos                                        |
| `getPosX()`                | -                        | int     | Retorna a coordenada X atual                                             |
| `estaVivo()`               | -                        | bool    | Verifica se o animal ainda está vivo


## Estrutura do Projeto

```
.
├── src/
│   ├── Forest.cpp      # Gerencia matriz e simulação    
│   ├── Animal.cpp      # Lógica do animal   
│   ├── main.cpp        # Inicialização   
│   ├── Forest.hpp      # Interface da floresta  
│   └── Animal.hpp      # Definição do animal  
├── config.hpp          # Parâmetros ajustáveis  
├── input.dat           # Matriz de entrada    
├── Makefile            # Arquivo com a "receita" para a compilação
└── output.dat          # Saída do programa

```

## Estudo de casos/ resultados
> [!NOTE]
> `A` Representa o animal  
> `0` Representa lugar vazio  
> `1` Representa árvore saudável  
> `2` Representa árvore em chamas  
> `3` Representa árvore queimada  
> `4` Representa água  

### Caso 1: Sem vento
<details> <summary> Clique para mostrar </summary>

- Matriz inicial

```

5 5 2 3
1 1 1 0 4
1 1 1 1 1
1 1 1 1 4
0 0 1 1 1
1 4 1 0 4

Iteracao 0:
1 1 1 A 4 
1 1 2 1 1 
1 1 1 1 4 
0 0 1 1 1 
1 4 1 0 4 

Iteracao 1:
1 1 2 A 4 
1 2 3 2 1 
1 1 2 1 4 
0 0 1 1 1 
1 4 1 0 4 

Iteracao 2:
1 2 3 A 4 
2 3 3 3 2 
1 2 3 2 4 
0 0 2 1 1 
1 4 1 0 4 

Iteracao 3:
2 3 3 A 4 
3 3 3 3 3 
2 3 3 3 4 
0 0 3 2 1 
1 4 2 0 4 

Iteracao 4:
3 3 3 0 A 
3 3 3 3 3 
3 3 3 3 4 
0 0 3 3 2 
1 4 3 0 4 

Iteracao 5:
3 3 3 1 A 
3 3 3 3 1 
3 3 3 3 4 
0 0 3 3 3 
1 4 3 0 4 

Resultado final:
Passos do animal: 1
Vezes que encontrou agua: 1
Animal sobreviveu
```

Podemos notar que o incêndio começa na linha 2 e coluna 3, em uma árvore saudável, a cada iteração, o fogo se espalha para os 4 lados, o animal, por nascer no 0, pode ficar lá por três iterações e ao fazer seu movimento, ele dá preferência para o `4` que é água, ao chegar lá, as ávores adjascentes viram `1` (árvores saudáveis) e o animal sobrevive porque não há mais árvores em chamas para propagar o fogo

</details>


### Caso 2: matriz 10x10 sem água

<details> 
<summary> Clique para mostrar o caso 2 </summary>

Usaremos a mesma matriz anterior, mas com o vento para o sul ativado.

```
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 2 1 1 1 1 1 
1 1 1 1 0 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1

Iteracao 0:
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 2 1 1 1 1 1 
1 1 1 1 A 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 

Iteracao 1:
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 2 1 1 1 1 1 
1 1 1 2 3 2 1 1 1 1 
1 1 1 1 A 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 

Iteracao 2:
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 2 1 1 1 1 1 
1 1 1 2 3 2 1 1 1 1 
1 1 2 3 3 3 2 1 1 1 
1 1 1 2 A 2 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 

Iteracao 3:
1 1 1 1 2 1 1 1 1 1 
1 1 1 2 3 2 1 1 1 1 
1 1 2 3 3 3 2 1 1 1 
1 2 3 3 3 3 3 2 1 1 
1 1 2 3 A 3 2 1 1 1 
1 1 1 2 1 2 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 

Iteracao 4:
1 1 1 2 3 2 1 1 1 1 
1 1 2 3 3 3 2 1 1 1 
1 2 3 3 3 3 3 2 1 1 
2 3 3 3 3 3 3 3 2 1 
1 2 3 3 0 3 3 2 1 1 
1 1 2 3 2 3 2 1 1 1 
1 1 1 2 A 2 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 

Iteracao 5:
1 1 2 3 3 3 2 1 1 1 
1 2 3 3 3 3 3 2 1 1 
2 3 3 3 3 3 3 3 2 1 
3 3 3 3 3 3 3 3 3 2 
2 3 3 3 0 3 3 3 2 1 
1 2 3 3 3 3 3 2 1 1 
1 1 2 3 2 3 2 1 1 1 
1 1 1 2 A 2 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 

Iteracao 6:
1 2 3 3 3 3 3 2 1 1 
2 3 3 3 3 3 3 3 2 1 
3 3 3 3 3 3 3 3 3 2 
3 3 3 3 3 3 3 3 3 3 
3 3 3 3 0 3 3 3 3 2 
2 3 3 3 3 3 3 3 2 1 
1 2 3 3 3 3 3 2 1 1 
1 1 2 3 2 3 2 1 1 1 
1 1 1 2 A 2 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 

Iteracao 7:
2 3 3 3 3 3 3 3 2 1 
3 3 3 3 3 3 3 3 3 2 
3 3 3 3 3 3 3 3 3 3 
3 3 3 3 3 3 3 3 3 3 
3 3 3 3 0 3 3 3 3 3 
3 3 3 3 3 3 3 3 3 2 
2 3 3 3 3 3 3 3 2 1 
1 2 3 3 3 3 3 2 1 1 
1 1 2 3 2 3 2 1 1 1 
1 1 1 2 A 2 1 1 1 1 

Resultado final:
Passos do animal: 6
Vezes que encontrou agua: 0
Animal morreu na iteracao 8

```
Aqui podemos ver que o animal nasceu no único 0 disponível e ficou lá por 3 iterações que é o limite definido, então ele foi saindo e andando para baixo, até que ele ficou cercado pelo fogo e acabou morrendo.

</details>


--- 

## Conclusão

Este projeto foi desenvolvido para demonstrar o comportamento de um incêndio florestal e como um animal tenta escapar de uma situação de perigo. A simulação é simples, mas permite ajustes nos parâmetros e oferece uma boa base para expandir o modelo com mais complexidade (por exemplo, mais tipos de animais, diferentes tipos de fogo, etc.).

Para Melhorias futuras, seriam as correções de bugs existentes, um melhor método de busca como o bfs e algumas otimizações do código, como diminuição dos for.

--- 


## Método de uso

Para usar o programa, primeiramente ajuste o arquivo `config.cpp` com as configurações desejadas e em seguida, rode na seguinte ordem:
```

make clean
make
make run

```

Os comandos anteriores, fazem o seguinte: 

- `make clean`  limpa todos os objetos de compilações anteriores, caso haja alguma.
- `make` compila o código
- `make run` roda o código compilado

