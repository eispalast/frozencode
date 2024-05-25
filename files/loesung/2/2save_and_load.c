#include <stdio.h>

struct player {
    int x_pos;
    int y_pos;
    double score;
};

void print_player_data(struct player p){
	printf("Player: x: %d, y: %d, score: %f\n",p.x_pos,p.y_pos,p.score);
}

int main(int argc, char *argv[]) {
	// 2 Player erzeugen und in gemeinsamen Array speichern
	struct player p1 = {.x_pos=4, .y_pos = 5, .score = 3.5};
	struct player p2 = {.x_pos=8, .y_pos = 2, .score = 7.1};

	struct player players[]={p1,p2};

	printf("Vorm schreiben in Datei:\n");
	print_player_data(players[0]);
	print_player_data(players[1]);


	// Datei öffnen im Schreibmodus, 
	// ganzes Array hineinschreiben, Datei schließen
	FILE *playerfile = fopen("./playerinfo","w");
	fwrite(players,sizeof(struct player),2,playerfile);
	fclose(playerfile);
	
	// Datei neu öffnen im Lesemodus, 
	// Daten lesen und in neuem Array speichern
	FILE* playerfile_reopened = fopen("./playerinfo", "r");
	struct player players_reopened[2];
	fread(players_reopened,sizeof(struct player),2,playerfile_reopened);
	fclose(playerfile_reopened);

	printf("\nNach schreiben und neu laden\n");
	print_player_data(players_reopened[0]);
	print_player_data(players_reopened[1]);
}
