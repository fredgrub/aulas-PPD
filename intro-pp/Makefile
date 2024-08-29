CC = gcc

pth_example00: pth_example00.c
	$(CC) $< -o $@

pth_example01: pth_example01.c
	$(CC) $< -o $@

pth_example02: pth_example02.c
	$(CC) $< -o $@

pth_example03: pth_example03.c
	$(CC) $< -o $@ -lm

pth_example04: pth_example04.c
	$(CC) $< -o $@

pth_example05: pth_example05.c
	$(CC) $< -o $@ -lm

omp_example00: omp_example00.c
	$(CC) -fopenmp $< -o $@

omp_example01: omp_example01.c
	$(CC) -fopenmp $< -o $@

omp_example02: omp_example02.c
	$(CC) -fopenmp $< -o $@

omp_example03: omp_example03.c
	$(CC) -fopenmp $< -o $@

clean:
	rm -f *example[0-9][0-9]