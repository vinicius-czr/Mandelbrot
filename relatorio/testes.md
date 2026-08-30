# Registro de Testes — Mandelbrot Threads

Este arquivo registra os testes executados durante o desenvolvimento, para uso na elaboração do relatório final.

## Serial

### Teste 1
- **Comando:** `./bin/mandelbrot_serial 800 600 1000 1`
- **Resultado:** sucesso, `mandelbrot_vcrc_serial.pgm` e `times.txt` gerados corretamente.
- **Tempo registrado:** `Serial: 0.633971 segundos`
- **Observações:** primeira execução funcional da versão serial.

### Testes de validação de argumentos

| Comando | Resultado |
|---|---|
| `./bin/mandelbrot_serial` | `Erro: numero incorreto de argumentos.` |
| `./bin/mandelbrot_serial 800 600` | `Erro: numero incorreto de argumentos.` |
| `./bin/mandelbrot_serial abc 600 1000 1` | `Erro: largura invalida 'abc'. Deve ser um inteiro positivo.` |
| `./bin/mandelbrot_serial 800 -50 1000 1` | `Erro: altura invalida '-50'. Deve ser um inteiro positivo.` |
| `./bin/mandelbrot_serial 800 600 0 1` | `Erro: max_iteracoes invalido '0'. Deve ser um inteiro positivo.` |

Todos os casos tratados corretamente, sem crash, com mensagens coerentes via stderr, e sem geração de arquivos de saída.