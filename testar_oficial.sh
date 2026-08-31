#!/bin/bash
# Simula uma execucao "oficial" do programa, como a que provavelmente
# sera usada na correcao, e confere se as saidas esperadas existem.

BIN="./mandelbrot"
LARGURA=800
ALTURA=600
MAX_ITER=1000
THREADS=4

ARQUIVOS_ESPERADOS=(
    "mandelbrot_vcrc_serial.pgm"
    "mandelbrot_vcrc_openmp.pgm"
    "mandelbrot_vcrc_pthreads1.pgm"
    "mandelbrot_vcrc_pthreads2.pgm"
    "times.txt"
)

echo "Executando: $BIN $LARGURA $ALTURA $MAX_ITER $THREADS"
"$BIN" "$LARGURA" "$ALTURA" "$MAX_ITER" "$THREADS"
CODIGO=$?

if [ $CODIGO -ne 0 ]; then
    echo "FALHA: o programa encerrou com codigo $CODIGO (esperado 0)."
    exit 1
fi

FALTOU=0
for arquivo in "${ARQUIVOS_ESPERADOS[@]}"; do
    if [ ! -f "$arquivo" ]; then
        echo "FALHA: arquivo esperado '$arquivo' nao foi gerado."
        FALTOU=1
    else
        echo "OK: '$arquivo' gerado ($(stat -c%s "$arquivo") bytes)."
    fi
done

if [ $FALTOU -ne 0 ]; then
    exit 1
fi

echo ""
echo "Verificando se as 4 imagens sao identicas..."
if diff -q mandelbrot_vcrc_serial.pgm mandelbrot_vcrc_openmp.pgm > /dev/null && \
   diff -q mandelbrot_vcrc_serial.pgm mandelbrot_vcrc_pthreads1.pgm > /dev/null && \
   diff -q mandelbrot_vcrc_serial.pgm mandelbrot_vcrc_pthreads2.pgm > /dev/null; then
    echo "OK: as 4 imagens sao identicas."
else
    echo "FALHA: as imagens geradas nao sao identicas entre si."
    exit 1
fi

echo ""
echo "Conteudo de times.txt:"
cat times.txt

echo ""
echo "===== Teste oficial concluido com sucesso ====="