#include<stdio.h>
void main() {
	int plaza1 = 0, plaza2 = 0, i = 0; //Si plaza=0 esta vacia y si plaza=1 esta ocupada
	char opcion;
	char matricula[8], matricula1[8], matricula2[8];
	int fallo = 0; //variable bandera con valor falso inicialmente

	system("color 1E");

	do {

		printf("Bienvenido al aparcamiento, seleccione una de estas opciones:\n");
		printf("R- reservar plaza.\n");
		printf("A- abandonar plaza.\n");
		printf("E- estado del aparcamiento.\n");
		scanf_s("%c", &opcion);
		getchar();

		if (opcion >= 'a'&& opcion <= 'z') {
			opcion -= 32;
		}

		switch (opcion) {
		case'R':
			if (plaza1 == 1 && plaza2 == 1) {
				printf("El aparcamiento esta completo.\n");
			}
			else {
				printf("Indroduzca el numero de matricula: ");
				scanf_s("%s", matricula, 8);
				getchar();
				printf("\n");


				if (plaza1 == 0) {
					plaza1 = 1;
					for (int i = 0; i < 8; i++) {
						matricula1[i] = matricula[i];
					}
				}
				else {
					plaza2 = 1;
					for (int i = 0; i < 8; i++) {
						matricula2[i] = matricula[i];
					}
				}
			}
			break;

		case'A':
			if (plaza1 == 0 && plaza2 == 0)
				printf("Operacion no valida.\n");
			else {
				printf("Introduzca el numero de matricula:");
				scanf_s("%s", matricula, 8);
				getchar();
				printf("\n");
				
				if (plaza1 == 1) {
					for (i = 0; i <= 8; i++) {
						if (matricula[i] != matricula1[i]) {
							fallo = 1;
							break;
						}
						if (i == 8) {
							plaza1 = 0;
							printf("Gracias por su visita, esperamos que vuelva pronto.\n");
						}
					}
				}
				if ((plaza2==1 && plaza1==0)||(plaza1==1 && fallo==1)){
					for (i = 0; i <= 8; i++) {
						if (matricula[i] != matricula2[i]){
							printf("Matricula no valida. \n");
							break;
						}
						if (i == 8) {
							plaza2 = 0;
							printf("Gracias por su visita, esperamos que vuelva pronto.\n");
						}
					}
				}					
			}
			break;

		case'E':
			switch (plaza1) {
			case 0: printf("Plaza 1 - Libre\n");
				break;
			case 1: printf("Plaza 1 - Ocupada / Matricula: %s\n", matricula1, 8);
			}
			switch (plaza2) {
			case 0: printf("Plaza 2 - Libre\n");
				break;
			case 1: printf("Plaza 2 - Ocupada / Matricula: %s\n", matricula2, 8);
			}
			break;

		default:
			printf("Operacion denegada\n");
		}

		printf("\n \n");


	} while (i >= 0);

	system("PAUSE");
}

