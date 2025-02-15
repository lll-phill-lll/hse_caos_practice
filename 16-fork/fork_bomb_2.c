/*
 * Код, который обрабатывает построчно что-то, используя fork
 *
 */
int main() {
    // Читаем построчно
    while (1) {
        // Каждую строку обрабатываем отдельно
        process();
    }

    while (count) {
        wait(NULL);
    }
}

void process() {
    // делаем что-то в ребенке
    if (fork() == 0) {
        doChildThings();
    }

    // делаем что-то в родителе
    doParentThings();
}
