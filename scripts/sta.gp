reset
set ylabel 'slots'
set style fill solid 0.5
set title ''
set term png enhanced font 'Verdana,10'
set output 'sta.png'
set size 1,1

plot [0:26][7000:18000]'statistics.txt' lt rgb "#D2691E"
