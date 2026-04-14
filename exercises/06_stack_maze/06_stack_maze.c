#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 5
#define MAX_COL 5
#define MAX_SIZE (MAX_ROW * MAX_COL)

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

typedef struct {
    int x;
    int y;
} Position;

void print_path(Position path[], int len) {
    for (int i = len - 1; i >= 0; i--) {
        printf("(%d,%d)", path[i].x, path[i].y);
		printf("\n");
    }
    printf("\n");
}

int is_valid(int x, int y) {
    return x >= 0 && x < MAX_ROW &&
           y >= 0 && y < MAX_COL &&
           maze[x][y] == 0;
}

typedef struct {
    int x;
    int y;
    int dir;   // 当前点已经尝试到第几个方向
} StackNode;

int solve_maze_stack(Position path[], int *path_len) {
    StackNode stack[MAX_SIZE];
    int top = -1;
    int visited[MAX_ROW][MAX_COL] = {0};

    /* 上、右、下、左 */
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    top++;
    stack[top].x = 0;
    stack[top].y = 0;
    stack[top].dir = 0;
    visited[0][0] = 1;

    while (top >= 0) {
        StackNode *cur = &stack[top];

        if (cur->x == MAX_ROW - 1 && cur->y == MAX_COL - 1) {
            *path_len = top + 1;
            for (int i = 0; i <= top; i++) {
                path[i].x = stack[i].x;
                path[i].y = stack[i].y;
            }
            return 1;
        }

        if (cur->dir >= 4) {
            top--;   // 四个方向都试完，回溯
            continue;
        }

        int d = cur->dir;
        cur->dir++;

        int nx = cur->x + dx[d];
        int ny = cur->y + dy[d];

        if (is_valid(nx, ny) && !visited[nx][ny]) {
            visited[nx][ny] = 1;
            top++;
            stack[top].x = nx;
            stack[top].y = ny;
            stack[top].dir = 0;
        }
    }

    return 0;
}

int main(void)
{
    Position path[MAX_SIZE];
    int len;

    if (solve_maze_stack(path, &len)) {
        print_path(path, len);
    } else {
        printf("没有找到路径\n");
    }

    return 0;
}
