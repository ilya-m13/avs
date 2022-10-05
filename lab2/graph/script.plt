#!/usr/bin/gnuplot


set termoption enhanced
set terminal svg size 800,600 font "Arial, 16"
set output "plot.svg"

set terminal svg enhanced background rgb 'white'

set style line 1 lc rgb "0x00FF00" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set style line 3 lc rgb "0xFF0000" lt 1 lw 4 pt 5 ps 1
set style line 4 lc rgb "0x000000" lt 1 lw 4 pt 5 ps 1

set border lw 2
set grid
set key top left

set xlabel "The number of task"
set ylabel "Task performance" rotate by 90
set xtics 1
set ytics 5000000000
set mxtics
set format x "%.0f"
set format y "%.0f"

plot "data.dat" using 1:2 title "None" with linespoints ls 1, \
"data.dat" using 1:3 title "O1" with linespoints ls 2, \
"data.dat" using 1:4 title "O2" with linespoints ls 3, \
"data.dat" using 1:5 title "O3" with linespoints ls 4