#include <stdio.h>

struct player{
	char name[16];
	int x_pos;
	int y_pos;
	double score;
};


void print_player_data(struct player p){
	printf("Player %s: x: %d, y: %d, score: %f\n",p.name, p.x_pos,p.y_pos,p.score);
}


int main(int argc, char *argv[]){
	
	// Datei im Lesemodus öffnen
	FILE* playerinfo = fopen("./playerdata.txt","r");

	// Speicherplatz für die gelesenen Variablen reservieren

	// Zeilenweise die Datei lesen,
	// dabei die Strings und Zahlen umwandeln und im struct speichern

	fclose(playerinfo);
	return 0;
}

