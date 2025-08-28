// ** Условие **
// Написать двоичное дерево поиска, в котором элементы будут сравниваться
// с помощью компаратора, передающегося как указатель на функцию.

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// comparator_t - указатель на функцию: принимающую 2 аргумета типа const char* и
// возващающую int
// Мы хотим функцию, которая будет принимать 2 строки и возврашать число, по которому
// будет определяться, какая строка больше: если первая, то вернется число > 0,
// если вторая, то число < 0, если строки одинаковые, то вернется 0.
typedef int (*comparator_t)(const char*, const char*);

// Напишем свой компаратор, который будет сравнивать строки как числа.
int int_comp(const char* l, const char* r) {
    int int_l, int_r;
    // не самый лучший способ превратить строку в число.
    // sscanf работает медленно и лучше подходит для форматированного ввода
    // например, если бы строка была какой-то сложной.
    sscanf(l, "%d", &int_l);
    sscanf(r, "%d", &int_r);
    return int_l - int_r;
}

typedef struct Node {
    struct Node *left, *right;
    char* string;
} Node;

// У аргумента tree 2 указателя. Они тут находятся, потому что мы хотим менять
// саму переменную tree (а все параметры передаются в функцию с помощью копироования).
// Поэтому нужно передавать в функцию указатель на tree, а так как tree сам по себе
// указатель, то нам нужен указатель на указатель.
//
// Вторым аргументом передается строка, которую мы хотим добавить в дерево.
//
// Третьим аргументом передается функция-компаратор, которая по 2м строкам умеет
// определять, какая из строк больше.
void insert(Node** tree, char* string, comparator_t comp) {
    // Если tree == NULL то создадим корень дерева.
    if (!(*tree)) {
        *tree = calloc(1, sizeof(Node));
        (*tree)->string = string;
        return;
    }

    Node* new_node = calloc(1, sizeof(Node));
    new_node->string = string;

    Node* tmp = *tree;
    int cmp_res;

    while(1) {
        cmp_res = comp(string, tmp->string);

        if (cmp_res < 0) {
            if (!tmp->right) {
                tmp->right = new_node;
                return;
            }
            tmp = tmp->right;
        } else if (cmp_res > 0) {
            if (!tmp->left) {
                tmp->left = new_node;
                return;
            }
            tmp = tmp->left;
        } else {
            return;
        }
    }
}

void print_tree(Node* tree) {
    if (!tree) {
        return;
    }
    print_tree(tree->right);
    printf("%s\n", tree->string);
    print_tree(tree->left);
}


void delete(Node* tree) {
    if (!tree) {
        return;
    }
    delete(tree->right);
    delete(tree->left);

    // сначала нужно дойти до листа, а потом уже удалять. Если мы удалим раньше,
    // то не сможем удалить ребенка.
    //
    // Также важно не забыть удалить саму строку, под которую за нас память выделил
    // scanf.
    free(tree->string);
    free(tree);
}

int main() {
    Node* tree = NULL;
    char* input = NULL;

    // Спецификатор m позволяет считать строку в буффер, который выделится динамически. После нужно не забыть освободить память.
    while (scanf("%ms", &input) != EOF) {
        // вместо int_comp мы можем передать в функцию strcmp из заголовочного
        // файла string.h. Это функцию имеет точно такую же сигнатуру, как и
        // comparator_t. В таком случае строки будут сравниваться лексикографически.
        insert(&tree, input, int_comp);
    }

    print_tree(tree);
    delete(tree);
}
