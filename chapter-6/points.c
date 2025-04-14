#include <stdio.h>


#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point pt1;
    Point pt2;
} Rect;


Point make_point(int x, int y) {
    Point temp;

    temp.x = x;
    temp.y = y;
    return temp;
}

Point addpoint(Point p1, Point p2) {
    p1.x += p2.x;
    p1.y += p2.x;

    return p1;
}

int ptinrect(Point p, Rect r) {
    return p.x >= r.pt1.x && p.x <= r.pt2.x
            && p.y >= r.pt1.y && p.y < r.pt2.y;
}

Rect canonrect(Rect r) {
    Rect temp;
    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);

    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);

    return temp;
}

