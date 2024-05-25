#include <stdio.h>

int main(int argc, char *argv[]) {
    // öffnet eine Datei im Schreibmodus ("w" = write)
    FILE *f = fopen("./myfile.txt", "w");

    // Schreibt die Zeichenkette Helloworld in die Datei
    fprintf(f, "Hello World\n");

    // Schreibt die Zahl x in die Datei.
    // Nicht als Zeichenkette, sondern als Zahl an sich.
    int x = 123456789;
    fwrite(&x, sizeof(int), 1, f);

    // Datei schließen, wenn sie nicht mehr benötigt wird.
    fclose(f);
}
