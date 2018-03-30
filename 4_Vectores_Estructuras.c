//Paula Arellano
#include<stdio.h>
#include<string.h>
#define NUSUARIOS 5
#define NPLAZAS 10

struct usuario {
	char username[50];
	char password[15];
};

struct plaza {
	int estado; // 0 - Libre / 1 - Ocupada
	char tipo; // M - Moto / C - Coche
	char matricula[8]; // Formato de la matrícula: NNNNLLL
};

void main() {
	struct usuario usuario[NUSUARIOS] = { { "admin", "1234" },{ "user2", "2" },{ "user3", "3" },{ "user4", "4" },{ "user5", "5" } };
	struct usuario usuarioAutent;
	struct plaza plaza[NPLAZAS] = { { 0, 'C' },{ 0, 'C' },{ 0, 'C' },{ 0, 'C' },{ 0, 'C' },{ 0, 'C' },{ 0, 'C' },{ 0, 'M' },{ 0, 'M' },{ 0, 'M' } };
	char opcion, tipo;
	char matricula[8], matBuscar[8];
	int salir = 0, j, i, m, k; //variable bandera con valor falso inicialmente

	system("color 1E");

	do {


		for (i = 0; i < 3; i++) {
			printf(" Nombre de usuario: ");
			scanf_s("%s", &usuarioAutent.username, 50);
			printf(" Contrasena: ");
			scanf_s("%s", &usuarioAutent.password, 15);

			for (m = 0; m < NUSUARIOS; m++) {
				j = 0, k = 0;
				j = strcmp(usuario[m].username, usuarioAutent.username);
				k = strcmp(usuario[m].password, usuarioAutent.password);

				if (j == 0 && k == 0)
					break;
			}
			if (j == 0 && k == 0)
				break;
			else {
				printf("    Nombre de usuario o contrasena incorrectos. Le quedan %d intentos.\n\n", 3 - (i + 1));
				if (i == 2)
					return;
			}
		}


		getchar();
		printf("\nBienvenido al aparcamiento, seleccione una de estas opciones:\n");
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
					for (i = 0; i < NPLAZAS; i++) {
						if ((plaza[i].estado == 0)&&(plaza[i].tipo =='C')) {
							plaza[i].estado = 1;
							printf("Indroduzca el numero de matricula: ");
							gets(plaza[i].matricula);
							printf("Vehiculo aparcado en la plaza %d. \n", i + 1);
							break;
						}
						if (i==(NPLAZAS-1))
							printf("Las plazas de coche estan ocupadas. \n");
					}
					break;
				case 'M':
					for (i = 0; i < NPLAZAS; i++) {
						if ((plaza[i].estado == 0)&&(plaza[i].tipo =='M')) {
							plaza[i].estado = 1;
							printf("Indroduzca el numero de matricula: ");
							gets(plaza[i].matricula);
							printf("Vehiculo aparcado en la plaza %d. \n", i + 1);
							break;
						}
						if (i == (NPLAZAS - 1))
							printf("Las plazas de moto estan ocupadas. \n");
					}
					break;
				default:
					printf("Opcion no valida. \n");
				}
			break;
		
		case'A':
			for (i = 0; i < NPLAZAS; i++) {
				if (plaza[i].estado != 0)
					break;
			}
			if ((i == (NPLAZAS - 1))&& (plaza[i].estado == 0)) {
				printf("Operacion no valida.\n");
				break;
			}

			printf("Introduzca el numero de matricula:");
			gets(matricula);
			printf("\n");

				for(i=0;i<NPLAZAS;i++){
					j = 0;
					j = strcmp(plaza[i].matricula, matricula);
						if (j == 0) {
							plaza[i].estado = 0;
							printf("Gracias por su visita, esperamos que vuelva pronto.\n");
							break;
						}
						if (i==(NPLAZAS-1))
							printf("Matricula no valida.\n");

				}		
			break;

		case'E':
			for (i = 0; i < NPLAZAS; i++) {
				switch (plaza[i].estado) {
				case 0: printf("Plaza %d / %c - Libre\n", i + 1, plaza[i].tipo);
					break;
				case 1: printf("Plaza %d / %c - Ocupada / Matricula: %s\n", i + 1, plaza[i].tipo, plaza[i].matricula);
				}
			}
			break;

		case 'B':
			printf("Introduzca la matricula de desea buscar: ");
			gets(matBuscar);

			for (i = 0; i < NPLAZAS; i++) {
				j = 0;
				j = strcmp(matBuscar, plaza[i].matricula);
				if (j == 0) {
					printf("Su vehiculo esta aparcado en la plaza %d.\n", i + 1);
					break;
				}
				if (i == (NPLAZAS - 1))
					printf("Su vehiculo no esta aparcado en el aparcamiento.\n");
			}
			break;

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