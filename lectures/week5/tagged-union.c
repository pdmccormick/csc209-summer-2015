#include <stdio.h>

struct Shape {
    enum {
        SQUARE,
        RECT,
        CIRCLE,
    } kind;

    union {
        struct {
            int size;
        } square;
        struct {
            int width;
            int height;
        } rect;
        struct {
            int radius;
        } circle;
    } u;
};

void describe_shape(struct Shape *s)
{
    switch (s->kind) {
    case SQUARE:
        printf("Square %dx%d\n", s->u.square.size, s->u.square.size);
        break;

    case RECT:
        printf("Rect %dx%d\n", s->u.rect.width, s->u.rect.height);
        break;

    case CIRCLE:
        printf("Circle radius %d\n", s->u.circle.radius);
        break;
    }
}

void make_square(struct Shape *s, int size)
{
    s->kind = SQUARE;
    s->u.square.size = size;
}

void make_rect(struct Shape *s, int width, int height)
{
    s->kind = RECT;
    s->u.rect.width = width;
    s->u.rect.height = height;
}

void make_circle(struct Shape *s, int radius)
{
    s->kind = CIRCLE;
    s->u.circle.radius = radius;
}

int main(int argc, char *argv[])
{
    struct Shape s;

    make_square(&s, 209);
    describe_shape(&s);

    make_rect(&s, 20, 9);
    describe_shape(&s);

    make_circle(&s, 209);
    describe_shape(&s);

    return 0;
}
