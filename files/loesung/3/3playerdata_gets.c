#include <stdio.h>

int main(int argc, char *argv[]){
	
	// Datei öffnen im Lesemodus 
	FILE* playerinfo = fopen("./playerdata.txt","r");

	// Buffer mit genügend Speicherplatz erzeugen
	char current_line[100];

	// Zeilenweise aus der Datei lesen, Inhalt printen
	while(fgets(current_line,100,playerinfo)){
		printf("%s",current_line);
	}

	fclose(playerinfo);
	return 0;
}

