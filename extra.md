# Топологическая сортировка с ДФС
```c
int graph[V][V] = {...}
int state[V];
int result[V];
int result_idx = V - 1;

int dfs(int u){
    state[u] = 1;
    for(int v = 0; v < V; ++v){
        if(graph[u][v] != 0) {
            if(state[v] == 1) return 0;
            if(state[v] == 0) {
                if(!dfs(v)) return 0;
            }
        }
    }
    state[u] = 2;
    result[result_idx--] = u;
    return 1;
}

int topological_sort() {
    for(int i = 0; i < V; ++i){
        state[i] = 0;
    }
    for(int i = 0; i < V; ++i){
        if(state[i] == 0) {
            if(!dfs(i)) return 0;
        }
    }
    return 1;
}
```

# Инфикс в постфикс
```c
#include <ctype.h>

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infix_to_postfix(char *infix, char *postfix) {
    char stack[100];
    int top = -1;
    int k = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];
        if (isalnum(token)) {
            postfix[k++] = token;
        } 
        else if (token == '(') {
            stack[++top] = token;
        } 
        else if (token == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = stack[top--];
            }
            top--;
        } 
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (top != -1 && priority(stack[top]) >= priority(token)) {
                postfix[k++] = stack[top--];
            }
            stack[++top] = token;
        }
    }

    while (top != -1) {
        postfix[k++] = stack[top--];
    }
    postfix[k] = '\0';
}
```

# Вычислить по постфиксу
```c
int eval_postfix(char *postfix) {
    int stack[100];
    int top = -1;
    for (int i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];
        if (isdigit(token)) {
            stack[++top] = token - '0';
        } else {
            int b = stack[top--];
            int a = stack[top--];
            switch (token) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/': stack[++top] = a / b; break;
            }
        }
    }
    return stack[top];
}
```

# Вычислить по префиксу
Короче то же самое но нужно цикл делать с конца при помощи strlen и получать a и b в обычном порядке.
```c
#include <string.h>
#include <ctype.h>

int eval_prefix(char *prefix) {
    int stack[100];
    int top = -1;
    int len = strlen(prefix);
    for (int i = len - 1; i >= 0; i--) {
        char token = prefix[i];
        if (token == ' ') continue;
        if (isdigit(token)) {
            stack[++top] = token - '0';
        } 
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            int a = stack[top--]; 
            int b = stack[top--]; 
            switch (token) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/': stack[++top] = a / b; break;
            }
        }
    }
    return stack[top];
```

# Постфикс в инфикс
```c
#include <string.h>
#include <ctype.h>

void postfix_to_infix(char *postfix, char *infix) {
    char stack[100][100];
    int top = -1;
    for (int i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];
        if (isalnum(token)) {
            char str[2] = {token, '\0'};
            strcpy(stack[++top], str);
        } else {
            char b[100], a[100];
            strcpy(b, stack[top--]);
            strcpy(a, stack[top--]);
            char temp[100];
            sprintf(temp, "(%s%c%s)", a, token, b);
            strcpy(stack[++top], temp);
        }
    }
    strcpy(infix, stack[top]);
}
```
Чтобы не запутаться:
- Центр-Конец - дефолт
- Конец-Центр - дрочево со строками
- Начало-Центр - дрочево со строками в другом порядке
- Начало-Конец - дрочево со строками в другом порядке, склеивание: a, b, token

# (Пре/ин/пост)фикс из дерева
```c
typedef struct Node {
    char type;
    char op;
    int val;
    struct Node *left;
    struct Node *right;
} Node;

void generate_prefix(Node *root) {
    if (root == NULL) return;
    // далее конкретно КЛП (префикс), но тут можно поменять порядок
    if (root->type == 'N') {
        printf("%c ", root->var);
    } else {
        printf("%c ", root->op);
    }
    generate_prefix(root->left);
    generate_prefix(root->right);
}
```

# Удаление из БСТ на массиве (хитровыебанное, план Б)
```c
bool deleted[MAX_SIZE];

void init_tree() {
    for (int i = 0; i < MAX_SIZE; i++) {
        tree[i] = EMPTY;
        deleted[i] = false;
    }
}

bool lazy_delete(int val) {
    int i = 0;
    while (i < MAX_SIZE && tree[i] != EMPTY) {
        if (tree[i] == val) {
            if (deleted[i]) return false;
            deleted[i] = true;
            return true;
        }
        i = (val < tree[i]) ? (2 * i + 1) : (2 * i + 2);
    }
    return false;
}
```
И типа при поиске если элемент найден но deleted[i] = true то не найден
При вставке если наткнулись на такую, перезаписываем и снимаем флаг
Еще вспомнить обычное бинарное дерево на массиве, но там пиво

# Проверка на свойства КЧ
1. Корень черный
2. У красного узла нет красных потомков
3. Кол-во черных узлов на всех путях от корня до листа одинаково
```c
int check_black_height(Node* root) {
    if (!root) return 1;
    if (root->color == 'R' && ((root->left && root->left->color == 'R') || (root->right && root->right->color == 'R'))) return -1;
    int left_h = check_black_height(root->left);
    int right_h = check_black_height(root->right);
    if (left_h == -1 || right_h == -1 || left_h != right_h) return -1;
    return left_h + (root->color == 'B' ? 1 : 0);
}
bool is_rbt(Node* root) {
    if (root && root->color != 'B') return false;
    return check_black_height(root) != -1;
}
```

# Ширина и глубина
```c
int depth(Node* root) {
    if(!root) return 0;
    int l = depth(root->left);
    int r = depth(root->right);
    return 1 + max(l, r);
}

void get_width(Node* root, int level, int* count){
    if(!root) return;
    count[level]++;
    get_width(root->left, level+1, count);
    get_width(root->right, level+1, count);
}

int max_width(Node* root){
    int count[100] = {0};
    get_width(root, 0, count);
    int max = 0;
    for(int i = 0; i < 100; ++i) if(count[i] > max) max = count[i];
    return max;
}
```

# Проверка на BST
```c
bool is_bst_util(Node* root, int min, int max) {
    if (!root) return true;
    if (root->data < min || root->data > max) return false;
    return is_bst_util(root->left, min, root->data - 1) &&
           is_bst_util(root->right, root->data + 1, max);
}
bool is_bst(Node* root) { return is_bst_util(root, -1000000, 1000000); }
```

# Найти "сток"
```c
int find_sink(int n, int graph[100][100]) {
    for (int i = 0; i < n; i++) {
        bool is_sink = true;
        for (int j = 0; j < n; j++) {
            if (graph[i][j] != 0) { is_sink = false; break; }
            if (i != j && graph[j][i] == 0) { is_sink = false; break; }
        }
        if (is_sink) return i;
    }
    return -1;
}
```

# Сумма на заданном уровне бинарного дерева на массиве
```c
int sum_at_level(int *tree, int size, int L) {
    int start_idx = (1 << L) - 1; // 2^L - 1
    int end_idx = (1 << (L + 1)) - 1;
    int sum = 0;
    for (int i = start_idx; i < end_idx && i < size; i++) {
        if (tree[i] != -1) sum += tree[i];
    }
    return sum;
}
```

# Отзеркаливание двоичное дерево
```c
Node* mirror_tree(Node* root) {
    if (!root) return NULL;
    Node* tmp = root->left;
    root->left = mirror_tree(root->right);
    root->right = mirror_tree(tmp);
    return root;
}
```