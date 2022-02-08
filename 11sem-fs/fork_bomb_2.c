int main() {
    // load some huge string to be processed
    while (stringHasMoreLines()) {
        processNextLine();
    }
}

void processNextLine() {
    if (fork() == 0) {
        // Do some parallel processing in the child
        exit(0);
    }
    // Do some parallel processing in the parent
}
