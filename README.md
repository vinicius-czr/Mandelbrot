# Implementação 2 — Threads

## Descrição

Este projeto implementa o cálculo do Conjunto de Mandelbrot em C, utilizando diferentes abordagens de paralelização para comparar seus desempenhos. São executadas quatro implementações: serial, OpenMP, Pthreads1 e Pthreads2.

Todas as implementações recebem os mesmos parâmetros e geram uma imagem em formato PGM. Ao final da execução, os tempos de cada implementação são registrados no arquivo `times.txt`.

## Requisitos

Para compilar e executar o projeto, é necessário ter:

* GCC
* GNU Make
* OpenMP
* POSIX Threads (Pthreads)
* Ambiente Linux ou WSL com Ubuntu

O projeto foi desenvolvido utilizando **VS Code com WSL (Ubuntu)**.

## Estrutura do projeto

```text
.
├── Makefile
├── README.md
├── args.c
├── evidencias.log
├── io.c
├── main.c
├── mandelbrot.c
├── mandelbrot.h
├── medir_desempenho.sh
├── pthreads1.c
├── pthreads2.c
├── relatorio
│   ├── desempenho.log
│   ├── testes.md
│   └── testes_erros.log
├── testar_erros.sh
└── testar_oficial.sh
```

### Principais arquivos

* `main.c` — controla a execução das quatro implementações e realiza a medição dos tempos.
* `args.c` — realiza o processamento e a validação dos argumentos da linha de comando.
* `mandelbrot.c` — contém o cálculo do Conjunto de Mandelbrot e as implementações serial e OpenMP.
* `mandelbrot.h` — contém as estruturas, constantes e declarações utilizadas pelo projeto.
* `io.c` — responsável pela geração dos arquivos de saída em formato PGM.
* `pthreads1.c` — implementação utilizando Pthreads com divisão prévia das linhas da imagem entre as threads.
* `pthreads2.c` — implementação utilizando Pthreads com uma fila compartilhada de linhas protegida por mutex.
* `testar_oficial.sh` — realiza uma execução de teste e verifica os arquivos gerados e a igualdade das imagens.
* `testar_erros.sh` — executa casos com argumentos inválidos e registra os resultados.
* `medir_desempenho.sh` — executa diferentes combinações de tamanho de imagem e quantidade de threads para coletar os tempos de execução.
* `relatorio/` — contém os arquivos gerados durante os testes e as informações de desempenho.

## Compilação

A compilação é realizada utilizando o `Makefile`.

Para limpar arquivos gerados anteriormente e recompilar o projeto:

```bash
make clean && make
```

O `Makefile` utiliza as opções `-Wall`, `-Wextra`, `-O2` e `-std=c11`, além das bibliotecas necessárias para OpenMP e Pthreads.

## Execução

Após a compilação, o programa pode ser executado utilizando:

```bash
./mandelbrot <largura> <altura> <max_iteracoes> <num_threads>
```

Exemplo:

```bash
./mandelbrot 800 600 1000 4
```

Os parâmetros correspondem a:

| Parâmetro       | Descrição                                                 |
| --------------- | --------------------------------------------------------- |
| `largura`       | Largura da imagem em pixels                               |
| `altura`        | Altura da imagem em pixels                                |
| `max_iteracoes` | Número máximo de iterações utilizadas no cálculo          |
| `num_threads`   | Número de threads utilizadas nas implementações paralelas |

A largura e a altura aceitam valores entre `1` e `20000`, o número máximo de iterações entre `1` e `100000`, e a quantidade de threads entre `1` e `256`.

## Implementações

O programa executa quatro versões do cálculo:

### Serial

A implementação serial percorre todas as linhas da imagem sequencialmente, calculando cada pixel sem utilizar paralelismo.

### OpenMP

A implementação com OpenMP utiliza `parallel for` para distribuir as linhas da imagem entre as threads. Foi utilizado escalonamento dinâmico (`schedule(dynamic, 1)`).

### Pthreads1

Nesta abordagem, as linhas da imagem são divididas previamente entre as threads. Cada thread recebe um bloco de linhas e processa exclusivamente esse bloco.

### Pthreads2

Nesta abordagem, as linhas são distribuídas dinamicamente por meio de uma fila compartilhada. As threads obtêm a próxima linha disponível utilizando um mutex para proteger o acesso à fila.

Essa abordagem permite que uma thread que termine uma linha possa buscar outra linha para processar, evitando a necessidade de uma divisão fixa das linhas.

## Arquivos de saída

Cada implementação gera uma imagem PGM:

```text
mandelbrot_vcrc_serial.pgm
mandelbrot_vcrc_openmp.pgm
mandelbrot_vcrc_pthreads1.pgm
mandelbrot_vcrc_pthreads2.pgm
```

Também é gerado o arquivo:

```text
times.txt
```

que contém o tempo de execução de cada implementação.

## Testes

### Teste oficial

O script `testar_oficial.sh` executa o programa com:

```bash
./mandelbrot 800 600 1000 4
```

Em seguida, verifica:

* se o programa terminou com código de saída `0`;
* se as quatro imagens foram geradas;
* se o arquivo `times.txt` foi gerado;
* se as quatro imagens produzidas são idênticas;
* o conteúdo do arquivo `times.txt`.

Para executar:

```bash
./testar_oficial.sh
```

### Testes de erro

O script `testar_erros.sh` verifica diferentes situações de entrada inválida, incluindo:

* ausência de argumentos;
* quantidade insuficiente de argumentos;
* largura não numérica;
* altura negativa;
* número de iterações igual a zero;
* número de threads igual a zero;
* valores acima dos limites permitidos.

Os resultados são armazenados em:

```text
relatorio/testes_erros.log
```

Para executar:

```bash
./testar_erros.sh
```

### Testes de desempenho

O script `medir_desempenho.sh` realiza diferentes execuções para comparar o tempo das implementações.

São avaliadas duas situações principais:

1. **Variação do número de threads**, mantendo a imagem em `1000x1000` e `2000` iterações, utilizando `1`, `2`, `4` e `8` threads.
2. **Variação do tamanho da imagem**, mantendo `4` threads e `2000` iterações, utilizando imagens de `500x500`, `1000x1000` e `2000x2000`.

Os resultados são armazenados em:

```text
relatorio/desempenho.log
```

Para executar:

```bash
./medir_desempenho.sh
```

## Limpeza dos arquivos gerados

Para remover o executável e os arquivos de saída gerados durante as execuções:

```bash
make clean
```

Esse comando remove o executável `mandelbrot`, os arquivos `.pgm` e o arquivo `times.txt`.
