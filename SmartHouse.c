#include <stdio.h>
#include <assert.h>

//Zustaende
enum Klappe{geoeffnet, geschlossen};
enum Schalter{an, aus, hochMachen, runter};

//Automatisierte Geräte
enum Klappe fenster;
enum Klappe haustuer;

enum Schalter licht;
enum Schalter heizung;
enum Schalter kaffee;
enum Schalter musik;

//Sensoren enums
enum Fenstersensor{offen, zu};
enum Laserschranke{imRaum, nichtImRaum};
enum GeoFencer{imHaus, nichtImHaus};
enum Uhrzeit{tag, nacht};

//Sensoren Deklaration
enum Fenstersensor fensterSensor;
enum Laserschranke laserschranke;
enum GeoFencer geoFencer;
enum Uhrzeit uhrzeit;
int temperatur;

int sensorInitizlize(){
	fensterSensor = zu;
	laserschranke = nichtImRaum;
	geoFencer = nichtImHaus;
	uhrzeit = tag;
	temperatur = 23;

	return 0;
}

int initialize(){
	fenster = geschlossen;
	haustuer = geschlossen;

	licht = aus;
	heizung = aus;
	kaffee = aus;
	musik = aus;
	


	return 0;
}


char* klappeToString(enum Klappe klappe){
	switch(klappe)
	{
		case geschlossen: return "geschlossen";
		case geoeffnet: return "geoeffnet";
	}
}
char* schalterToString(enum Schalter schalter){
	switch(schalter)
	{
		case aus: return "aus";
		case an: return "an";
		case hochMachen: return "hochMachen";
		case runter: return "runter";
	}
}

//Safety Properties
int checkSafetyProperty(){
	assert(fenster==geschlossen || heizung== aus);
	assert(laserschranke==imRaum || heizung== aus);
	assert(temperatur<19 || heizung== aus);

	assert(geoFencer==nichtImHaus || fenster== geschlossen);
	return 0;
}

void printStateInformation(){
	printf("Das Fenster ist %s.\n", klappeToString(fenster));
	printf("Die Haustuer ist %s.\n", klappeToString(haustuer));
	printf("Das Licht ist %s.\n", schalterToString(licht));
	printf("Das Heizung ist %s.\n", schalterToString(heizung));
	printf("Die Kaffeemaschine ist %s.\n", schalterToString(kaffee));
	printf("Die Musik ist %s.\n", schalterToString(musik));
}

void changeStatePerSensor(){
	// if(personenImH)
	if(geoFencer != imHaus){
		fenster = geschlossen;
		kaffee  = aus;
		musik = aus;
		licht = aus;
	}
	
	if(geoFencer == imHaus){
		if(uhrzeit == nacht){
			kaffee  = aus;
		}
		musik = an;
	}
	
	if(laserschranke == imRaum){
		if(uhrzeit == nacht){
			licht = an;
		}
		if(fensterSensor == geschlossen){
			if(temperatur <= 19){
				heizung = an;
			}
		}
	}

	if(laserschranke == nichtImRaum || temperatur>=28 || fensterSensor == offen){
		heizung = aus;
	}
	
	if(laserschranke == nichtImRaum){
		licht = aus;
	}

	if(heizung != aus){
		if(temperatur<22){
			heizung = hochMachen;
		}

		if(temperatur>25){
			heizung = runter;
		}
	}
	
	
	
}

int info(){
	// printf()
	printf("***Instruction***\n");
	printf("sensor f: fensterSensor, control 0: offen, control 1: zu\n");
	printf("sensor t:temperatur, control int: Temperatur Grad\n");
	printf("sensor l: laserschranke, control 0: Person im Raum, control 1: keine Person im Raum\n");
	printf("sensor g: geoFencing, control 0: Person im Haus, control 1: keine Person im Haus\n");
	printf("sensor u: uhrzeit, control 0: Tag, control 1: Nacht\n");
	printf("Simulation example: f 1\n");
	printf("Simulation example: t 25\n");	
	return 0;
}

int input(char sensor, int control){
	switch(sensor){
		case 'f':
			switch(control){
				case 0:
					fenster = geoeffnet;
					fensterSensor = offen;
					break;
				case 1:
					fenster = geschlossen;
					fensterSensor = zu;
					break;
			}; 
			break;

		case 't':
			temperatur = control;
			break;

		case 'l':
			switch(control){
				case 0:
					laserschranke = imRaum;
					break;
				case 1:
					laserschranke = nichtImRaum;
					break;
			}
			break;

		case 'g':
			switch(control){
				case 0:
					geoFencer = imHaus;
					break;
				case 1:
					geoFencer = nichtImHaus;
					break;
			}
			break;

		case 'u':
			switch(control){
				case 0:
					uhrzeit = tag;
					break;
				case 1:
					uhrzeit = nacht;
					break;
			}
			break;
	}

	return 0;
}

int main(){
	initialize();
	printStateInformation();

	char sensor;
	int control;
	while(1){
		info();
		printf("Please change the sensor state as simulation!\n");
		scanf("%c %d", &sensor, &control);
		input(sensor, control);
		changeStatePerSensor();
		checkSafetyProperty();
		printStateInformation();
	}
	


	return 0;
}
