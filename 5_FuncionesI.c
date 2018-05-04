//Paula Arellano
#include<stdio.h>
#include<string.h>
#define NUSUARIOS 5
#define NPLAZAS 10

struct usuario {
	char username[20];
	char password[20];
};

struct plaza {
	int estado; // 0 - Libre / 1 - Ocupada
	char tipo; // M - Moto / C - Coche
	char matricula[8]; // Formato de la matrícula: NNNNLLL
};

char menu();
int esDigitoValido(char caracter);
int esLetraValida(char caracter);
int esMatriculaValida(char matricula[]);
int existeUsuario(struct usuario usuarioValido, char username[], char password[]);

void main() {
	struct usuario usuarioValido = { "admin", "1234" };
	struct plaza plaza[NPLAZAS] = { { 0, 'C' },{ 0, 'C' },{ 0, 'C' },{ 0, 'C' },{ 0, 'C' },{ 0, 'C' },{ 0, 'C' },{ 0, 'M' },{ 0, 'M' },{ 0, 'M' } };
	char opcion, tipo;
	char matricula[8], matBuscar[8];
	char username[20], password[20];
	int salir = 0, i, m, j, matOk, userOk; //variable bandera con valor falso inicialmente

	system("color 1E");

	do {
		
		for (i = 0; i < 3; i++) {
			printf(" Nombre de usuario: ");
			scanf_s("%s", &username, 20);
			printf(" Contrasena: ");
			scanf_s("%s", &password, 20);
			getchar();

			userOk=existeUsuario(usuarioValido, username, password);
			
			if (userOk == 1) {
				printf("Nombre de usuario y contrasena correctos.\n");
				break;
			}

			else {
				printf("Nombre de usuario o contrasena incorrectos. Le quedan %d intentos.\n\n", 3 - (i + 1));
				if (i == 2)
					return;
			}
		}

		opcion = menu();

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
							printf("Introduzca el numero de matricula: ");
							gets(plaza[i].matricula);

							matOk= esMatriculaValida(plaza[i].matricula);
							
							if (matOk == 1)
								printf("Vehiculo aparcado en la plaza %d. \n", i + 1);
							else
								printf("Matricula no valida\n");
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
							printf("Introduzca el numero de matricula: ");
							gets(plaza[i].matricula);

							matOk= esMatriculaValida(plaza[i].matricula);
							
							if (matOk == 1)
								printf("Vehiculo aparcado en la plaza %d. \n", i + 1);
							else
								printf("Matricula no valida\n");
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

char menu() {  //muestra el menu de opciones al usuario, pide la opcion por pantalla y devuelve el valor de la opción seleccionada.
	
	char opcion;
	
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

	return opcion;
}

int esMatriculaValida(char matricula[]) { //comprueba que la matrícula del vehículo tenga el formato correcto: DDDDLLL, siendo D un caracter dígito del 0 al 9 y L una consonante. La función devuelve un booleano 
	
	int k = 0, i=0; //variable bandera inicialmente nula

	for (i = 0; i < 4; i++) {
		k = esDigitoValido(matricula[i]);
			if (k != 1)
				return 0;
	}

	k = 0;
	for (i = 4; i < 7; i++) {
		k = esLetraValida(matricula[i]);
		if (k != 1)
			return 0;
	}

	return 1;
}

int esDigitoValido(char caracter) { //comprueba que sea un caracter dígito del 0 al 9
	if ((caracter < '0') || (caracter > '9')) {
		return 0;
	}
	return 1;
}

int esLetraValida(char caracter) { //comprueba que sea un caracter consonante
	if (caracter >= 'a' && caracter <= 'z') {
		caracter -= 32;
	}
	if ((caracter == 65) || (caracter == 69) || (caracter == 73) || (caracter == 79) || (caracter == 85) || (caracter < 65) || (caracter > 90)) {
		return 0;
	}
	return 1;
}

int existeUsuario(struct usuario usuarioValido, char username[], char password[]) {//comprueba que el username y password introducidos coinciden con los datos de un usuarioValido. Esta función será invocada para comprobar que los datos introducidos por teclado coinciden con el usuario ya registrado en el sistema. Para ello, el usuario debe crear la siguiente estructura y modificar el código necesario:
	
	int j = 0, k = 0, i=0;
	
		j = strcmp(usuarioValido.username, username);
		k = strcmp(usuarioValido.password, password);

		if (j == 0 && k == 0)
			return 1;
}