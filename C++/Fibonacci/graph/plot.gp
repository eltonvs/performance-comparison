set fit quiet
set title 'Fibonacci (Interactive vs Recursive)' font ",20"
set ylabel "Elapsed Time (ns)"
set key left nobox
set term png
set output "graph/graph.png"
plot 'graph/interactive.dat' with lines title 'Interactive' ,'graph/recursive.dat' with lines title 'Recursive'
