#include <stdio.h>
#include <stdlib.h>

typedef struct
{

    char *buffer;
    int size;
    int *read;
    int *write;
} buf_t;

void create(buf_t *buf, int size);
void write(buf_t *buf, char ch);
void read(buf_t *bug, char *ch);
int calcIndex(buf_t *buf);

void create(buf_t *buf, int size)
{

    buf->size = 0;
    buf->buffer = malloc(sizeof(char) * size);
    buf->read = malloc(sizeof(int));
    buf->write = malloc(sizeof(int));
    *(buf->read) = 0;
    *(buf->write) = 0;

    for (int i = 0; i < size; i++)
    {
        buf->buffer[i] = ' ';
    }
}

void write(buf_t *buf, char ch)
{

    buf->buffer[*(buf->write)] = ch;
    *(buf->write) = calcIndex(buf);
    buf->size++;
}

int calcIndex(buf_t *buf)
{
    return (*(buf->write) + 1) % buf->size;
}

void read(buf_t *buf, char *ch)
{
    *ch = buf->buffer[*(buf->read)];
    *(buf->read) = calcIndex(buf);
}

int main()
{
    buf_t *ring;
    ring = malloc(sizeof(buf_t));
    char *ch = malloc(sizeof(char));
    create(ring, 4);
    write(ring, 'a');
    read(ring, ch);
    printf("%c", *ch);
    return 0;
}
