//Paula Arellano
#include<stdio.h>
#include<string.h>
void main() {
	int plazaC = 0, plazaM = 0, i = 0; //Si plaza=0 esta vacia y si plaza=1 esta ocupada
	char opcion, tipo;
	char matricula[8], matriculaC[8], matriculaM[8], matBuscar[8];
	int salir = 0, compMat_abandonar1, compMat_abandonar2, compMat_buscar1, compMat_buscar2; //variable bandera con valor falso inicialmente

	system("color 1E");

	do {

		printf("Bienvenido al aparcamiento, seleccione una de estas opciones:\n");
		printf("R- reservar plaza.\n");
		printf("A- abandonar plaza.\n");
		printf("E- estado del aparcamiento.\n");
		printf("B- buscar matricula. \n");
		printf("S- salir. \n");
		scanf_s("%c", &opcion);
		getchar();

		if (opcion >= 'a'&& opcion <= 'z') {
			opcion -= 32;
		}

		switch (opcion) {
		case'R':
			if (plazaC == 1 && plazaM == 1) {
				printf("El aparcamiento esta completo.\n");
			}
			else {
				printf("Seleccione el tipo de vehiculo: \n");
				printf("C- coche\n");
				printf("M- moto\n");
				scanf_s("%c", &tipo);
				getchar();

				if (tipo >= 'a'&& tipo <= 'z') {
					tipo -= 32;
				}

				switch (tipo) {
					case 'C': 
						if (plazaC == 0) {
							plazaC = 1;
								printf("Indroduzca el numero de matricula: ");
								gets(matriculaC);
						}
						else printf("La plaza de coche esta ocupada. \n");
						break;
					case 'M':
						if (plazaM == 0) {
							plazaM = 1;
								printf("Indroduzca el numero de matricula: ");
								gets(matriculaM);
						}
						else printf("La plaza de moto esta ocupada. \n");
						break;
					default:
						printf("Opcion no valida. \n");
				}
			}
			break;

		case'A':
			if (plazaC == 0 && plazaM == 0)
				printf("Operacion no valida.\n");
			else {
				printf("Introduzca el numero de matricula:");
				gets(matricula);
				printf("\n");

				if (plazaC == 1) {
					compMat_abandonar1 = strcmp(matriculaC, matricula);
					if (compMat_abandonar1 == 0) {
						plazaC = 0;
						printf("Gracias por su visita, esperamos que vuelva pronto.\n");
					}

				}
				if (plazaM == 1) {
					compMat_abandonar2 = strcmp(matriculaM, matricula);
					if (compMat_abandonar2 == 0) {
						plazaM = 0;
						printf("Gracias por su visita, esperamos que vuelva pronto.\n");
					}
				}

				if (compMat_abandonar1 != 0 && compMat_abandonar2 != 0)
					printf("Matricula no valida.\n");
			}
			break;

		case'E':
			switch (plazaC) {
			case 0: printf("Plaza 1 / Coche - Libre\n");
				break;
			case 1: printf("Plaza 1 / Coche - Ocupada / Matricula: %s\n", matriculaC, 8);
			}
			switch (plazaM) {
			case 0: printf("Plaza 2 / Moto - Libre\n");
				break;
			case 1: printf("Plaza 2 / Moto - Ocupada / Matricula: %s\n", matriculaM, 8);
			}
			break;

		case 'B':
			printf("Introduzca la matricula de desea buscar: ");
			gets(matBuscar);

			compMat_buscar1 = strcmp(matBuscar, matriculaC);
			if (compMat_buscar1 == 0) {
				printf("Su vehiculo esta aparcado en la plaza 1.\n");
				break;
			}
			compMat_buscar2 = strcmp(matBuscar, matriculaM);
			if (compMat_buscar2 == 0) {
				printf("Su vehiculo esta aparcado en la plaza 2.\n");
				break;
			}

			if (compMat_buscar1 != 0 && compMat_buscar2 != 0) {
				printf("Su vehiculo no esta aparcado.\n");
				break;
			}
			
		case 'S':
			salir = 1;
			break;

		default:
			printf("Operacion denegada\n");
		}

		printf("\n \n");

		if (salir == 1)
			break;

	} while (i >= 0);

	system("PAUSE");
}
