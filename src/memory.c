//Projeto - 1ª fase realizado pelo grupo 21:
// João Assis, fc56325
// José Brás, fc55449
// Ricardo Mateus, fc56366

#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "sys/mman.h"
#include "sys/stat.h" 
#include "sys/shm.h"   
#include "fcntl.h"  
#include "unistd.h"

void* create_shared_memory(char* name, int size) {
    int *ptr;
    int ret;
    int fd = shm_open(name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror(name);
        exit(1); 
    }

    ret = ftruncate(fd, size * sizeof(int));
    if (ret == -1){
        perror(name);
        exit(2); 
    }

    ptr = mmap(0,size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) { 
        perror(name); 
        exit(3);
    }
    return ptr;
}

void* create_dynamic_memory(int size) {
    return calloc(size, sizeof(int));
}

void destroy_shared_memory(char* name, void* ptr, int size) {
    munmap(ptr, size);
    shm_unlink(name);
}

void destroy_dynamic_memory(void* ptr) {
    free(ptr);
}

void write_main_rest_buffer(struct rnd_access_buffer* buffer, int buffer_size, struct operation* op) {
    int i;
    for (i = 0; i < buffer_size; i++) {
        if (*(buffer->ptrs + i) == 0) {
            buffer->buffer[i] = *op;
            buffer->ptrs[i]= 1;
            break;
        }
    }
}

void write_rest_driver_buffer(struct circular_buffer* buffer, int buffer_size, struct operation* op) {
    while (buffer->ptrs->in % buffer_size == buffer->ptrs->out) {
        *(buffer->buffer + buffer->ptrs->in) = *op;
        buffer->ptrs->in = (buffer->ptrs->in + 1) % buffer_size;
    }
}

void write_driver_client_buffer(struct rnd_access_buffer* buffer, int buffer_size, struct operation* op) {
    int i;
    for (i = 0; i < buffer_size; i++) {
        if (*(buffer->ptrs + i) == 0) {
            *(buffer->ptrs + i) = 1;
            *(buffer->buffer + i) = *op;
            break;
        }
    }
}

void read_main_rest_buffer(struct rnd_access_buffer* buffer, int rest_id, int buffer_size, struct operation* op) {
    int i;
    for(i = 0; i < buffer_size; i++) {
        if (*((buffer->ptrs) + i) == 1) {
            *op = *(buffer->buffer + i);
            *(buffer->ptrs + i) = 0;
            break;
        }
    }
}

void read_rest_driver_buffer(struct circular_buffer* buffer, int buffer_size, struct operation* op) {
      while (buffer->ptrs->in == buffer->ptrs->out) {
        op = buffer->buffer + buffer->ptrs->out;
        buffer->ptrs->out = (buffer->ptrs->out + 1) % buffer_size;
    }
}

void read_driver_client_buffer(struct rnd_access_buffer* buffer, int client_id, int buffer_size, struct operation* op) {
    int i;
    for(i = 0; i < buffer_size; i++) {
        if (*(buffer->ptrs + i) == 1) {
            *op = *(buffer->buffer + i);
            *(buffer->ptrs + i) = 0;
            break;
        }
    }
}
