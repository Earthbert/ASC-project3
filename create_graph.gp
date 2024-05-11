set datafile separator ","
set xlabel "Matrix Size(N)"
set ylabel "Time(s)"
set title "Time vs Matrix Size(NxN) for C=(At×B+B×A)×Bt"
set grid
set term png
set output "graph.png"
plot "results/neopt.csv" using 1:2 with linespoints title "Unoptimized", \
	 "results/opt.csv" using 1:2 with linespoints title "Optimized", \
	 "results/cblas.csv" using 1:2 with linespoints title "BLAS"
