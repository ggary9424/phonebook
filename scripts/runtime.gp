reset
set ylabel 'time(sec)'
set style fill solid 0.5
set style histogram cluster gap 1
set title 'hash function using Djb2'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][:0.060]'output.txt' using 2:xtic(1) with histogram title 'original' , \
'' using ($0-0.3):($2+0.0015):2 with labels title ' ', \
'' using 3:xtic(1) with histogram title 'djb2'  , \
'' using ($0+0.06):($3+0.0030):3 with labels title ' ', \
'' using 4:xtic(1) with histogram title 'djb2 with memory pool'  , \
'' using ($0+0.3):($4+0.0015):4 with labels title ' '
