/*
 * Код, который обрабатывает построчно что-то, используя fork
 *
 */
int main() {
    // Читаем построчно
    while (stringHasMoreLines()) {
        // Каждую строку обрабатываем отдельно
        processNextLine();
    }

    while (count) {
        wait(NULL);
    }
}

void processNextLine() {
    // делаем что-то в ребенке
    if (fork() == 0) {

        //////
        _exit(0);

    }

    // делаем что-то в родителе
    someOperation();
}
