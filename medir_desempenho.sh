#!/bin/bash
# Roda o programa com varias combinacoes de tamanho/threads
# e acumula os resultados de times.txt em um relatorio de desempenho

BIN="./mandelbrot"
SAIDA="relatorio/desempenho.log"

echo "===== Testes de desempenho - $(date '+%Y-%m-%d %H:%M:%S') =====" > "$SAIDA"

rodar_medicao() {
    local largura="$1"
    local altura="$2"
    local max_iter="$3"
    local threads="$4"

    echo "" >> "$SAIDA"
    echo "--- Tamanho: ${largura}x${altura}, max_iter: ${max_iter}, threads: ${threads} ---" >> "$SAIDA"
    "$BIN" "$largura" "$altura" "$max_iter" "$threads" > /dev/null 2>> "$SAIDA"
    cat times.txt >> "$SAIDA"
}

# Variando numero de Threads, porem com tamanho fixo
rodar_medicao 1000 1000 2000 1
rodar_medicao 1000 1000 2000 2
rodar_medicao 1000 1000 2000 4
rodar_medicao 1000 1000 2000 8


# Variando o tamanho da imagem, mas com as Threads fixas
rodar_medicao 500  500  2000 4
rodar_medicao 1000 1000 2000 4
rodar_medicao 2000 2000 2000 4

echo "" >> "$SAIDA"
echo "===== Fim dos testes de desempenho =====" >> "$SAIDA"

cat "$SAIDA"
