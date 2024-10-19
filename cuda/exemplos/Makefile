CC = gcc
NVCC = nvcc

CFILES = 1_vector_add.c
CUFILES = 0_cuda_hello.cu 2_vector_add.cu 3_vector_add.cu 4_vector_add.cu 5_vector_add.cu 6_vector_add.cu

all: cuda_programs c_programs

c_programs: $(CFILES)
	$(CC) -o vector_add $(CFILES)

cuda_programs: $(CUFILES)
	for cu_file in $(CUFILES); do \
		$(NVCC) -o $${cu_file%.cu} $$cu_file; \
	done

clean:
	rm -f vector_add 0_cuda_hello 2_vector_add 3_vector_add 4_vector_add 5_vector_add 6_vector_add