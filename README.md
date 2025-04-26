# WildfireSim-CEFET - Simulador de fogo em uma floresta
<p align="center">
  <img src=".assets/Lobo Entre Chamas na Floresta.png" width="500"/>
</p>

## Introdução

Esse trabalho visa relembrar um pouco de tudo estudado até o momento e tem como objetivo simular um incêndio em uma floresta que e como um animal reagiria neste incêndio.

O programa funciona resumidamente da seguinte forma:

  - Lê um arquivo chamado `input.dat`` que contém uma matriz.
  - O animal começa a movimentar, com prioridades de lugar e o incêndio propaga de acordo com os parâmetros de vento do arquico `config.hpp`.
  - O programa roda até o fogo não conseguir mais se propagar, o animal morrer ou o número máximo de interações for alcançado.
  - O resultado de cada interação e o resumo final é salvo no arquivo `output.dat`.

## Metodologia

Abaixo, um fluxograma com o funcionamento geral do programa.
[![](https://mermaid.ink/img/pako:eNptVt1u4kYUfpWRK8SuNBsBJiRYVSrzl7CBQAL5w0TVxB7DNGYGjU02CeG2Um_7BquqWrXSXvaml8ub7JP0eMYGJ6m5gDPznXO-c-bzGZaGKzxqWEYut2ScRRZa5qMpndG8hfK3JKR5jPTCBZGM3AY0hJ0lys8lmxH5WBeBkDH2B9_34Inh1JvQDrmlQY24dxMpFtzLWzEgfvKr1SqXG3M_EJ_cKZERGjbGHMGTy6E2MGAkYE8kYoLrZfud0-brry4TN-_Rhw8HqOZ0qESMzxfRjkeiGw2rqb06YJmrQ0g0I5FkT-jkoZuA6grUcPoiBJTggPHFRCA6Q1f4OgE1FKiZBREOxQaIC1T89i8qJMCmAraW7YhKsv6y_kOgH1HXvvq5PWye2fVec_DTasw3xXUJ46gjxFyvtGLv5wGbPaNDpwWdRp5Atkp0k0WcQNxnNHrntNgMeQSBxyLQ6W7eZ8JrV9SfQii9eKj4HS2THSiyHBOKt462ydtOXfB7KqEIVP7-6--F8ZhfsCfGpyIEswhmm7sSFMAjaMX682RBEoJtleCjM4L6JXIFADwh0ZxI-L7JZtJFHGeoFFIqx1sqnU0r_6FhEgZ9_-1PZKbgzhbcdVpCrr_ExyzuWcwuTdnJpDxxsuRfMDvOwHqOfQ-iiY_a-4W4gKZhAuuqInvaOFFGXxs9bTh9yYRkHvFoaKHyQeGgeGDGXZtwEfellATqK_jpspvSRffrzwHzRFrc6ba4MwdQNBXeqyOYkzAUKb3TTBUDp0t4fI5zkK5WiAadqdRDbQxSYyOdFpM0K5yhQpxvVNmCdySJdK62Lpw-dBK5BPTorv8KQJCoZAHNLpEuMATdIDPxuFAel__jUYw9BhTda7WhEoLfqjG9YxUi7tyGZIOSaIrqU-re6bVLFfgqo6kSEoutVq627bx2St_-RjBuuAsF0TeKuVahbHtpMw4E34Sy7W0su-YkGWdCbiIkCH0Odj3LYLu2qWVI5YxxNeSyFdl6PtmN5VBA2_VoeogYEN0waWyZjF4sJWmaLwTPNqMp5ZkMrQyZ3iKCUarNkSbQcg7VKy3UVjxl4aSaYUSi9dcwYi4JkQ_8WSpCu6X9DtWUejGWBtFjwPhE224A0m1QH7xBcT4LAguuBRceHEZS3NHYLMDzCp7MX-0Qw31_4xDDff-VwycSvwYpPk6RwVerbxJ41CeLIEopVePPxsM0zbQg5YBsXMN13MBN3MIjbB-m7lnMIT7CbfwRH-MO7uIT3MN9fIrP8CB9pzPYc3yBLzHcQNi2sV1T3cnut3U9BjYmMGcMK5ILio0ZiIjEprGMwWNDXdNjw4KfHpF3Y2PMV-AzJ3wkxCx1g_t4MjUsnwQhWIs5HC5tMDKRZAuh3KOyDhd3ZFjF4q6KYVhL4wHMSnVnt2KaJbO6V64UquY-Nh4Na7e0Uynu7e7vF8pmqVjar66w8aSyFneKpb290l6lWq3slsvliokN6rFIyK7-56H-gKz-A8NJtz8?type=png)](https://mermaid.live/edit#pako:eNptVt1u4kYUfpWRK8SuNBsBJiRYVSrzl7CBQAL5w0TVxB7DNGYGjU02CeG2Um_7BquqWrXSXvaml8ub7JP0eMYGJ6m5gDPznXO-c-bzGZaGKzxqWEYut2ScRRZa5qMpndG8hfK3JKR5jPTCBZGM3AY0hJ0lys8lmxH5WBeBkDH2B9_34Inh1JvQDrmlQY24dxMpFtzLWzEgfvKr1SqXG3M_EJ_cKZERGjbGHMGTy6E2MGAkYE8kYoLrZfud0-brry4TN-_Rhw8HqOZ0qESMzxfRjkeiGw2rqb06YJmrQ0g0I5FkT-jkoZuA6grUcPoiBJTggPHFRCA6Q1f4OgE1FKiZBREOxQaIC1T89i8qJMCmAraW7YhKsv6y_kOgH1HXvvq5PWye2fVec_DTasw3xXUJ46gjxFyvtGLv5wGbPaNDpwWdRp5Atkp0k0WcQNxnNHrntNgMeQSBxyLQ6W7eZ8JrV9SfQii9eKj4HS2THSiyHBOKt462ydtOXfB7KqEIVP7-6--F8ZhfsCfGpyIEswhmm7sSFMAjaMX682RBEoJtleCjM4L6JXIFADwh0ZxI-L7JZtJFHGeoFFIqx1sqnU0r_6FhEgZ9_-1PZKbgzhbcdVpCrr_ExyzuWcwuTdnJpDxxsuRfMDvOwHqOfQ-iiY_a-4W4gKZhAuuqInvaOFFGXxs9bTh9yYRkHvFoaKHyQeGgeGDGXZtwEfellATqK_jpspvSRffrzwHzRFrc6ba4MwdQNBXeqyOYkzAUKb3TTBUDp0t4fI5zkK5WiAadqdRDbQxSYyOdFpM0K5yhQpxvVNmCdySJdK62Lpw-dBK5BPTorv8KQJCoZAHNLpEuMATdIDPxuFAel__jUYw9BhTda7WhEoLfqjG9YxUi7tyGZIOSaIrqU-re6bVLFfgqo6kSEoutVq627bx2St_-RjBuuAsF0TeKuVahbHtpMw4E34Sy7W0su-YkGWdCbiIkCH0Odj3LYLu2qWVI5YxxNeSyFdl6PtmN5VBA2_VoeogYEN0waWyZjF4sJWmaLwTPNqMp5ZkMrQyZ3iKCUarNkSbQcg7VKy3UVjxl4aSaYUSi9dcwYi4JkQ_8WSpCu6X9DtWUejGWBtFjwPhE224A0m1QH7xBcT4LAguuBRceHEZS3NHYLMDzCp7MX-0Qw31_4xDDff-VwycSvwYpPk6RwVerbxJ41CeLIEopVePPxsM0zbQg5YBsXMN13MBN3MIjbB-m7lnMIT7CbfwRH-MO7uIT3MN9fIrP8CB9pzPYc3yBLzHcQNi2sV1T3cnut3U9BjYmMGcMK5ILio0ZiIjEprGMwWNDXdNjw4KfHpF3Y2PMV-AzJ3wkxCx1g_t4MjUsnwQhWIs5HC5tMDKRZAuh3KOyDhd3ZFjF4q6KYVhL4wHMSnVnt2KaJbO6V64UquY-Nh4Na7e0Uynu7e7vF8pmqVjar66w8aSyFneKpb290l6lWq3slsvliokN6rFIyK7-56H-gKz-A8NJtz8)

### Funcionamento de cada classe

#### [config.hpp](config.hpp) 

Este é o arquivo que define as seguintes configurações do código:

  - MAX_ITERACOES ->  define o máximo de interações/ciclos do código.
  - VENTO_NORTE -> se "true", define a direção do vento para NORTE.
  - VENTO_SUL -> se "true", deine a direção do vento para SUL
  - VENTO_LESTE -> se "true", define a direção do vento para LESTE.
  - VENTO_OESTE -> se "true", define a direção do vento para OESTE.

> [!IMPORTANTE]
> Alterar essas configurações será necessário compilar novamente o programa, pois **o arquivo é lido em tempo de compilação apenas**.

### [Forest.cpp](src/Forest.cpp)

Esta é a classe principal do programa, aqui é feita a leitura e escrita nos arquivos, montado a floresta e implementado a propagação do fogo e onde as funções de movimentação do animal são chamadas.

#### Classes principais

1. 