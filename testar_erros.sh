# Roda uma bateria de casos invalidos e verifica se o programa
# responde com mensagem de erro (nao deve gerar arquivos de saida)

BIN="./mandelbrot"
LOG="relatorio/testes_erros.log"

echo "===== Testes de erro - $(date '+%Y-%m-%d %H:%M:%S') =====" > "$LOG"

rodar_caso() {
    local descricao="$1"
    shift
    echo "" >> "$LOG"
    echo "--- $descricao ---" >> "$LOG"
    echo "Comando: $BIN $*" >> "$LOG"
    "$BIN" "$@" >> "$LOG" 2>&1
    local codigo=$?
    echo "Codigo de saida: $codigo" >> "$LOG"
}

rodar_caso "Sem argumentos"                 
rodar_caso "Argumentos insuficientes"       800 600
rodar_caso "Largura nao numerica"           abc 600 1000 4
rodar_caso "Altura negativa"                800 -50 1000 4
rodar_caso "Max_iteracoes zero"             800 600 0 4
rodar_caso "Num_threads zero"               800 600 1000 0
rodar_caso "Largura acima do limite"        999999 600 1000 4
rodar_caso "Max_iteracoes acima do limite"  800 600 99999999 4
rodar_caso "Num_threads acima do limite"    800 600 1000 99999

echo "" >> "$LOG"
echo "===== Fim dos testes de erro =====" >> "$LOG"

cat "$LOG"