# Sistema de Busca de Passagens Aéreas

## Descrição
Este projeto implementa um sistema de busca de passagens aéreas baseado em expressões lógicas e critérios de ordenação. O sistema recebe uma lista de voos e permite consultas personalizadas com base em filtros e ordenação definida pelo usuário.

## Estrutura do Projeto
A estrutura do diretório segue o padrão exigido:
```
TP/
|-- src/        # Arquivos-fonte (*.cpp)
|-- include/    # Arquivos de cabeçalho (*.h)
|-- obj/        # Arquivos objeto (*.o) gerados pelo compilador
|-- bin/        # Diretório do executável gerado
|-- Makefile    # Arquivo de build para compilação
```

## Compilação e Execução

### Compilar o projeto:
```sh
make all
```

### Executar o programa:
```sh
bin/tp3.out <arquivo_entrada>
```

## Formato do Arquivo de Entrada
O arquivo de entrada contém informações sobre os voos e as consultas. O formato é:
```
<n>
<origem> <destino> <preco> <assentos_disponiveis> <data_partida> <data_chegada> <paradas>
...
<c>
<num_resultados> <criterio_ordenacao> <expressao_logica>
...
```

Exemplo:
```
1000
DEN ORD 68.60 9 2022-11-01T17:54:00.000-06:00 2022-11-01T21:12:00.000-05:00 0
...
1
10 pds (((org==DEN)&&(dst==ORD))&&((prc<=500)&&(dur<=8400)))
```

## Formato do Arquivo de Saída
A saída consiste nos voos que atendem aos critérios da consulta, formatados como na entrada:
```
<origem> <destino> <preco> <assentos_disponiveis> <data_partida> <data_chegada> <paradas>
...
```

## Regras e Restrições
- O código deve ser implementado em **C++11**.
- **Não** é permitido o uso de estruturas de dados da STL (como `vector`, `queue`, `stack`).
- O programa deve rodar corretamente em um ambiente Linux.
- As consultas devem ser processadas utilizando **árvores balanceadas** para armazenamento de índices.

## Avaliação
O projeto será avaliado considerando:
- Corretude na execução dos casos de teste.
- Qualidade do código (indentacção, organização, boas práticas).
- Documentação e análise experimental.
- Implementação correta das estruturas de dados e algoritmos.

## Autor
- Nome: Leonardo Chiari
