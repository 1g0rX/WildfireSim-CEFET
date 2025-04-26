# WildfireSim-CEFET - Simulador de fogo em uma floresta
<p align="center">
  <img src=".assets/Lobo Entre Chamas na Floresta.png" width="500"/>
</p>

## Introdução

Esse trabalho visa relembrar um pouco de tudo estudado até o momento e tem como objetivo simular um incêndio em uma floresta que e como um animal reagiria neste incêndio.

O programa funciona resumidamente da seguinte forma:

- Lê um arquivo chamado input.dat que contém uma matriz.
- O animal começa a movimentar, com prioridades de lugar e o incêndio propaga de acordo com os parâmetros de vento do arquico ´config.hpp´.
- O programa roda até o fogo não conseguir mais se propagar, o animal morrer ou o número máximo de interações for alcançado.
- O resultado de cada interação e o resumo final é salvo no arquivo ´output.dat´
