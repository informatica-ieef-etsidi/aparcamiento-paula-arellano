//Paula Arellano
#include<stdio.h>
#include<string.h>

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
	struct usuario usuario1 = { "admin", "1234" };
	struct usuario usuarioAutent;
	struct plaza plaza1 = { 0, "C" }, plaza2 = { 0, "M" };
	char opcion, tipo;
	char matricula[8],  matBuscar[8];
	int salir = 0, j, i, k; //variable bandera con valor falso inicialmente

	system("color 1E");

	do {

		for (i = 0; i < 3; i++) {
			printf(" Nombre de usuario: ");
			scanf_s("%s", &usuarioAutent.username, 50);
			printf(" Contrasena: ");
			scanf_s("%s", &usuarioAutent.password, 15);

			j = strcmp(usuario1.username, usuarioAutent.username);
			k = strcmp(usuario1.password, usuarioAutent.password);

			if (j == 0 && k == 0)
				break;
			else {
				printf("    Nombre de usuario o contrasena incorrectos. Le quedan %d intentos.\n", 3 - (i + 1));
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
			if (plaza1.estado == 1 && plaza2.estado == 1) {
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
					if (plaza1.estado == 0) {
						plaza1.estado = 1;
						printf("Indroduzca el numero de matricula: ");
						gets(plaza1.matricula);
					}
					else printf("La plaza de coche esta ocupada. \n");
					break;
				case 'M':
					if (plaza2.estado == 0) {
						plaza2.estado = 1;
						printf("Indroduzca el numero de matricula: ");
						gets(plaza2.matricula);
					}
					else printf("La plaza de moto esta ocupada. \n");
					break;
				default:
					printf("Opcion no valida. \n");
				}
			}
			break;

		case'A':
			if (plaza1.estado == 0 && plaza2.estado == 0)
				printf("Operacion no valida.\n");
			else {
				printf("Introduzca el numero de matricula:");
				gets(matricula);
				printf("\n");

				j = 0, k = 0;
				if (plaza1.estado == 1) {
					j = strcmp(plaza1.matricula, matricula);
					if (j == 0) {
						plaza1.estado = 0;
						printf("Gracias por su visita, esperamos que vuelva pronto.\n");
					}

				}
				if (plaza2.estado == 1) {
					k = strcmp(plaza2.matricula, matricula);
					if (k == 0) {
						plaza2.estado = 0;
						printf("Gracias por su visita, esperamos que vuelva pronto.\n");
					}
				}

				if (j != 0 && k != 0)
					printf("Matricula no valida.\n");
			}
			break;

		case'E':
			switch (plaza1.estado) {
			case 0: printf("Plaza 1 / Coche - Libre\n");
				break;
			case 1: printf("Plaza 1 / Coche - Ocupada / Matricula: %s\n", plaza1.matricula, 8);
			}
			switch (plaza2.estado) {
			case 0: printf("Plaza 2 / Moto - Libre\n");
				break;
			case 1: printf("Plaza 2 / Moto - Ocupada / Matricula: %s\n", plaza2.matricula, 8);
			}
			break;

		case 'B':
			printf("Introduzca la matricula de desea buscar: ");
			gets(matBuscar);

			j = 0, k = 0;
			j = strcmp(matBuscar, plaza1.matricula);
			if (j == 0) {
				printf("Su vehiculo esta aparcado en la plaza 1.\n");
				break;
			}
			k = strcmp(matBuscar, plaza2.matricula);
			if (k == 0) {
				printf("Su vehiculo esta aparcado en la plaza 2.\n");
				break;
			}

			if (j != 0 && k != 0) {
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