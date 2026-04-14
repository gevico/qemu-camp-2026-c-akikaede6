#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5
#define MAX_SIZE MAX_ROW * MAX_COL

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

/* =========================
   打印路径
   ========================= */
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
    Position data[MAX_SIZE];
    int front;
    int rear;
} Queue;

void init_queue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int queue_empty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, Position p) {
    q->data[q->rear++] = p;
}

Position dequeue(Queue *q) {
    return q->data[q->front++];
}

int solve_maze_queue(Position path[], int *path_len) {
    Queue q;
    init_queue(&q);

    int visited[MAX_ROW][MAX_COL] = {0};
    Position parent[MAX_ROW][MAX_COL];

    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            parent[i][j].x = -1;
            parent[i][j].y = -1;
        }
    }

    /* 上、右、下、左 */
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    Position start = {0, 0};
    enqueue(&q, start);
    visited[0][0] = 1;

    while (!queue_empty(&q)) {
        Position cur = dequeue(&q);

        if (cur.x == MAX_ROW - 1 && cur.y == MAX_COL - 1) {
            break;
        }

        for (int d = 0; d < 4; d++) {
            int nx = cur.x + dx[d];
            int ny = cur.y + dy[d];

            if (is_valid(nx, ny) && !visited[nx][ny]) {
                visited[nx][ny] = 1;
                parent[nx][ny] = cur;

                Position next = {nx, ny};
                enqueue(&q, next);
            }
        }
    }

    if (!visited[MAX_ROW - 1][MAX_COL - 1]) {
        return 0;
    }

    /* 逆向恢复路径 */
    Position reverse_path[MAX_SIZE];
    int cnt = 0;

    Position cur = {MAX_ROW - 1, MAX_COL - 1};
    while (!(cur.x == -1 && cur.y == -1)) {
        reverse_path[cnt++] = cur;
        cur = parent[cur.x][cur.y];
    }

    /* 反转 */
    *path_len = cnt;
    for (int i = 0; i < cnt; i++) {
        path[i] = reverse_path[cnt - 1 - i];
    }

    return 1;
}

int main(void)
{
	Position path[MAX_SIZE];
    int len;

    if (solve_maze_queue(path, &len)) {
        print_path(path, len);
    } else {
        printf("没有找到路径\n");
    }

	return 0;
}