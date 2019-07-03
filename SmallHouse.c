#include <stdio.h>

extern void __VERIFIER_error();
extern int __VERIFIER_nondet_int();
extern void __VERIFIER_assume(int condition);

//Enum Deklaration
enum Schalter{an, aus};
enum Fenstersensor{offen, zu};

enum Schalter heizung;
enum Fenstersensor fensterSensor;

int initialize(){
	heizung = an;
	return 0;
}

void changeStatePerSensor(){
	if(fensterSensor == offen){
		heizung = aus;
	} 
}

int main(){

	while(1){

		initialize();

		//CPA Checker

		fensterSensor = __VERIFIER_nondet_int();

		
		__VERIFIER_assume(fensterSensor== offen | fensterSensor == zu);


		changeStatePerSensor();

		if (!(fensterSensor==zu || heizung== aus))
		{
			__VERIFIER_error();
		}

	}

	return 0;


}
