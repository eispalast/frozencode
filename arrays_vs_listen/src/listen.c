#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************\
*        FUNKTIONEN FÜR DIE LISTE           *
\*******************************************/

struct _list_element {
    int value;
    struct _list_element *next;
    struct _list_element *prev;
};
typedef struct _list_element list_element;

struct _list_meta {
    list_element *head;
    list_element *tail;
    int len;
};
typedef struct _list_meta list_meta;

list_element *new_list_element(int num) {
    list_element *new_elem = malloc(sizeof(list_element));
    new_elem->value = num;
    new_elem->next = new_elem->prev = NULL;
    return new_elem;
}

void print_list(list_element *le) {
    while (le != NULL) {
        printf("%d, ", le->value);
        le = le->next;
    }
    printf("\n");
}

/*
 * Sucht nach einer Zahl x in der Liste, die am Element le beginnt
 * Gibt einen Pointer auf das entsprechende Listenelement zurück, falls die Zahl gefunden wurde,
 * oder NULL, falls die Zahl nicht in der Liste ist
 */
list_element *search_list(list_element *le, int x) {
    while (le != NULL) {
        if (le->value == x)
            return le;
        le = le->next;
    }
    return NULL;
}

/*
 * Sucht nach einer Zahl x in der Liste lm
 * Gibt einen Pointer auf das entsprechende Listenelement zurück, falls die Zahl gefunden wurde,
 * oder NULL, falls die Zahl nicht in der Liste ist
 */
list_element* search_list_meta(list_meta *lm, int x){
    return search_list(lm->head, x);
}

/*
 * Löscht ein Element *to_delete aus der Liste und gibt einen Pointer auf das
 * erste Element der Liste zurück. Dieses ist das gleiche Element wie das
 * vormals erste Element oder dessen Nachfolger, falls das erste Element
 * gelöscht wurde.
 */
list_element *delete_from_list(list_element *first,list_element *to_delete) {
    if (to_delete->prev != NULL) {
        to_delete->prev->next = to_delete->next;
    } else {
        first = to_delete->next;
    }

    if (to_delete->next != NULL) {
        to_delete->next->prev = to_delete->prev;
    }
    return first;
}

/*
 * Löscht ein Element *to_delete aus der Liste
 * Gegebenenfalls werden head und tail und die Länge der Liste angepasst.
 * Das zu löschende Element muss teil der Liste sein.
 */
void delete_from_list_with_meta(list_meta *lm, list_element* to_delete){
    if(lm->head == to_delete){
        lm->head = to_delete->next;
    }
    if(to_delete->next != NULL){
        to_delete->next->prev = to_delete->prev;
    }
    if(lm->tail == to_delete){
        lm->tail = to_delete->prev;
    }
    if(to_delete->prev != NULL){
        to_delete->prev->next = to_delete->next;
    }
    
    lm->len --;
}

/*
 * Fügt eine Zahl am Ende der List lm ein.
 * Für die neue Zahl wird ein Listenelement angelegt (Speicher reserviert)
 */
void insert_list_end(list_meta *lm, int new_number) {
    list_element *new_elem = new_list_element(new_number);
    if (lm->tail == NULL) {
        lm->head = new_elem;
        lm->tail = new_elem;
    } else {
        lm->tail->next = new_elem;
        new_elem->prev = lm->tail;
        lm->tail = new_elem;
    }
    lm->len++;
}

/*
 * gibt den gesamten Speicher der Liste, inklusive des Meta-Elements frei
 */
void free_list(list_meta *lm){
    list_element* to_free = lm->head;
    while(to_free != NULL){
        lm->head = lm->head->next;
        free(to_free);
        to_free = lm->head;
    }
    free(lm);
}
/*******************************************\
*        FUNKTIONEN FÜR DAS ARRAY	    *
\*******************************************/

void print_array(int arr[], int len) {
    for (size_t i = 0; i < len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

int search_array(int arr[], int len, int x) {
    for (size_t i = 0; i < len; i++) {
        if (arr[i] == x)
            return i;
    }
    return -1;
}

int delete_from_array(int arr[], int index, int len) {
    if (index >= len || index < 0)
        return len;
    for (size_t i = index; i < len - 1; i++) {
        arr[i] = arr[i + 1];
    }
    return len - 1;
}

int *insert_array_end(int *arr, int *len, int new_number) {
    int *new_array = realloc(arr, sizeof(int) * (*len + 1));
    new_array[*len] = new_number;
    (*len)++;
    return new_array;
}

int main(int argc, char *argv[]) {

    /***********************
     * Array initialisieren *
     ************************/
    int arr[] = {4, 8, 15, 16, 23, 42};
    int len = 6;

    /***********************
     * Liste initialisieren *
     ************************/
    list_element first = {.value = 4, .next = NULL, .prev = NULL};
    list_element second = {.value = 8, .next = NULL, .prev = &first};
    list_element third = {.value = 15, .next = NULL, .prev = &second};
    first.next = &second;
    second.next = &third;

    /***********************
     *   Sequenz ausgeben   *
     ************************/

    print_array(arr, len);
    print_list(&first);

    /***********************
     *        Suchen        *
     ************************/
    printf("Index von 15 im Array: %d\n", search_array(arr, len, 15));
    printf("Index von 17 im Array: %d\n", search_array(arr, len, 17));

    printf("Adresse von 15 in der Liste: %p\n", search_list(&first, 15));
    printf("(Müsste sein: %p)\n", &third);
    printf("Adresse von 17 in der Liste: %p\n", search_list(&first, 17));

    /***********************
     *        Löschen       *
     ************************/

    delete_from_array(arr, 2, len);
    print_array(arr, len);

    delete_from_list(&first, &second);
    print_list(&first);

    /***********************
     *       Einfügen       *
     ************************/

    // erzeuge das gleiche Array wie vorher, aber jetzt auf dem Heap
    int *new_arr = malloc(1);
    int new_arr_len = 0;
    for (size_t i = 0; i < len; i++) {
        new_arr = insert_array_end(new_arr, &new_arr_len, arr[i]);
    }

    // füge noch ein weiteres Element ein und gib es aus
    new_arr = insert_array_end(new_arr, &new_arr_len, 100);
    printf("\nArray auf dem Heap, erzeugt durch einfügen\n");
    print_array(new_arr, new_arr_len);

    // erzeuge eine Liste auf dem Heap, die die gleichen Elemente enthält wie
    // das Array, indem die Elemente nacheinander eingefügt werden.
    list_meta *lm = malloc(sizeof(list_meta));
    lm->tail = lm->head = NULL;
    lm->len = 0;

    for (size_t i = 0; i < new_arr_len; i++) {
        insert_list_end(lm, new_arr[i]);
    }

    // füge noch ein weiteres Element ein und gib die Liste aus
    insert_list_end(lm, 200);
    printf("Liste auf dem Heap, erzeugt durch einfügen\n");
    print_list(lm->head);



    // size_t arr_size = INT_MAX-1;
    //
    // int *long_arr = malloc(arr_size*(size_t)sizeof(int));
    //
    // int *new_arr = malloc((arr_size+1)*(size_t)sizeof(int));
    //
    // for (size_t i = 0; i < arr_size; i++) {
    // 	new_arr[i] = long_arr[i];
    // }
    //
    // memcpy(long_arr, new_arr, arr_size*sizeof(int));
    //
    // printf("long_arr = %p\n", long_arr);
    // long_arr = realloc(long_arr,(arr_size+1)*sizeof(int));
    // printf("long_arr = %p\n", long_arr);
    //
    //


    /*********************
    * Speicher freigeben *
    *********************/
    //Array
    free(new_arr);

    //Liste
    free_list(lm);
}
