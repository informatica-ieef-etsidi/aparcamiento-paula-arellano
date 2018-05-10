//Paula Arellano
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
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
void recuento(struct plaza aparcamiento[], int dim, int *nLibresCoches, int *nLibresMotos);
void inicializar(struct plaza aparcamiento[], int dim);
int buscarPlazaLibre(struct plaza aparcamiento[], int dim, char tipo);
int buscarVehiculo(struct plaza aparcamiento[], int dim, char matricula[]);
void leerFichero(char nombre_fichero[], struct plaza aparcamiento[], int * dim);
void salvarFichero(char nombre_fichero[], struct plaza aparcamiento[], int dim);

void main() {
	struct usuario usuarioValido = { "admin", "1234" };
	struct plaza aparcamiento[NPLAZAS];
	char opcion, tipo;
	char matricula[8], matBuscar[8];
	char username[20], password[20];
	int salir = 0, i, m, j, matOk, userOk; //variable bandera con valor falso inicialmente
	int plazaC, plazaM, n;
	int nLibresCoches, nLibresMotos;
	int *dim;
	char nombre_fichero[40]="fichero.txt";
	inicializar(aparcamiento, NPLAZAS);


	system("color 1E");

	n = NPLAZAS;
	dim = &n;

	leerFichero(nombre_fichero, aparcamiento, &n); // dim

	do {

		for (i = 0; i < 3; i++) {
			printf(" Nombre de usuario: ");
			scanf_s("%s", &username, 20);
			printf(" Contrasena: ");
			scanf_s("%s", &password, 20);
			getchar();

			userOk = existeUsuario(usuarioValido, username, password);

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

				i = 0;

				i = buscarPlazaLibre(aparcamiento, NPLAZAS, tipo);

				if (i != -1) {
					
					printf("Introduzca el numero de matricula: ");
					gets(aparcamiento[i].matricula);

					matOk = esMatriculaValida(aparcamiento[i].matricula);

					if (matOk == 1) {
						printf("Vehiculo aparcado en la plaza %d. \n", i);
						aparcamiento[i].estado = 1;
					}
					else
						printf("Matricula no valida\n");
					break;
				}

				else if (i == -1) {
					printf("Todas las plazas reservadas para tu vehiculos estan ocupadas. \n");
				}

				break;
			

			case'A':
				for (i = 0; i < NPLAZAS; i++) {
					if (aparcamiento[i].estado != 0)
						break;
				}
				if ((i == (NPLAZAS - 1)) && (aparcamiento[i].estado == 0)) {
					printf("Operacion no valida.\n");
					break;
				}

				printf("Introduzca el numero de matricula:");
				gets(matricula);
				printf("\n");

				for (i = 0; i<NPLAZAS; i++) {
					j = 0;
					j = strcmp(aparcamiento[i].matricula, matricula);
					if (j == 0) {
						aparcamiento[i].estado = 0;
						printf("Gracias por su visita, esperamos que vuelva pronto.\n");
						break;
					}
					if (i == (NPLAZAS - 1))
						printf("Matricula no valida.\n");

				}
				break;

			case'E':

				recuento(aparcamiento, NPLAZAS, &nLibresCoches, &nLibresMotos);

				printf("Plazas libres Coche: %d\n", nLibresCoches);
				printf("Plazas libres Moto: %d\n", nLibresMotos);

				for (i = 0; i < NPLAZAS; i++) {
					switch (aparcamiento[i].estado) {
					case 0: printf("Plaza %d / %c - Libre\n", i, aparcamiento[i].tipo);
						break;
					case 1: printf("Plaza %d / %c - Ocupada / Matricula: %s\n", i, aparcamiento[i].tipo, aparcamiento[i].matricula);
					}
				}
				break;

			case 'B':
				printf("Introduzca la matricula de desea buscar: ");
				gets(matBuscar);

				i = buscarVehiculo(aparcamiento, NPLAZAS, matBuscar);
			
					if (i != -1) {
						printf("Su vehiculo esta aparcado en la plaza %d.\n", i);
						break;
					}
					else if (i == -1)
						printf("Su vehiculo no esta aparcado en el aparcamiento.\n");
					break;

			case 'S':
				salir = 1;
				salvarFichero(nombre_fichero, aparcamiento, *dim);
				break;

			default:
				printf("Operacion denegada\n");
		}

		printf("\n \n");

		if (salir == 1)
			break;

	} while (1);

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

	int k = 0, i = 0; //variable bandera inicialmente nula

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

int existeUsuario(struct usuario usuarioValido, char username[], char password[]) {//comprueba que el username y password introducidos coinciden con los datos de un usuarioValido. Esta función será invocada para comprobar que los datos introducidos por teclado coinciden con el usuario ya registrado en el sistema. 

	int j = 0, k = 0, i = 0;

	j = strcmp(usuarioValido.username, username);
	k = strcmp(usuarioValido.password, password);

	if (j == 0 && k == 0)
		return 1;
}

void recuento(struct plaza aparcamiento[], int dim, int *nLibresCoches, int *nLibresMotos) {//calcula el número de plazas libres de coches y motos que hay disponibles.
	int i;
	*nLibresCoches = 0;
	*nLibresMotos = 0;

	for (i = 0; i < dim; i++) {
		if (aparcamiento[i].tipo == 'C') {
			if (aparcamiento[i].estado == 0) {
				*nLibresCoches++;
			}
		}
			
		else if (aparcamiento[i].tipo == 'M') {
			if (aparcamiento[i].estado == 0) {
				*nLibresMotos++;
			}
		}
	}

}

void inicializar(struct plaza aparcamiento[], int dim) { //dar un valor inicial al aparcamiento, en la cual se inicialicen los estados como libres y los tipos de cada una de las plazas
	int j;
	int i;

	for (i = 0; i < dim; i++) {
		 aparcamiento[i].estado = 0;
	}

	for (i = 0; i < (dim / 3); i++) {
		aparcamiento[i].tipo = 'M';
	}
	for (i = (dim / 3); i < dim; i++) {
		aparcamiento[i].tipo = 'C';
	}

	for (i = 0; i < dim; i++) {
		for (j = 0; j < 7; j++) {
			aparcamiento[i].matricula[j]= '0';
		}
		aparcamiento[i].matricula[7] = '\0';
	}
}

int buscarPlazaLibre(struct plaza aparcamiento[], int dim, char tipo) { //devuelve el número de plaza libre del aparcamiento para un determinado tipo de vehículo. Si no hay ninguna plaza libre, la función devuelve -1
	int i;
	for (i = 0; i < dim; i++) {
		if ((aparcamiento[i].tipo == tipo)&&(aparcamiento[i].estado==0)) {
			
			return i;
		}
	}
	return -1;
}

int buscarVehiculo(struct plaza aparcamiento[], int dim, char matricula[]) { //devuelve el número de plaza donde se encuentra aparcado el vehículo. Si no encuentra ningún vehículo con dicha matrícula, la función devuelve -1
	int i, j;

	for (i = 0; i < dim; i++) {
		j = 0;
		j = strcmp(matricula, aparcamiento[i].matricula);
		if (j == 0) {
			return i;
		}
	}
	return -1;
}

void leerFichero(char nombre_fichero[], struct plaza aparcamiento[], int * dim) {
	FILE *pf;
	int i;
	errno_t error;
	int dimension;
	dimension = *dim;
	error = fopen_s(&pf, nombre_fichero, "r");

	if (error == 0) {
		printf("Fichero abierto correctamente\n");
	}

	else {
		printf("Ha habido un error %d al abrir el fichero\n", error);
		return; 
	}

	/*i = 0;
	while (fscanf_s(pf, "%d %c %s", &aparcamiento[i].estado, &aparcamiento[i].tipo, aparcamiento[i].matricula) != EOF) {
		i++;
	}*/
	i = 0;
	for(i = 0; i < dimension;i++) {
		fscanf_s(pf, "%d:%c:%s\n", &aparcamiento[i].estado, &aparcamiento[i].tipo, aparcamiento[i].matricula);
	}

	fclose(pf);
}

void salvarFichero(char nombre_fichero[], struct plaza aparcamiento[], int dim) {
	FILE * pf;
	errno_t error;
	int i;

	error = fopen_s(&pf, nombre_fichero, "w");

	if (error == 0) {
		printf("Fichero abierto correctamente\n");
	}

	else {
		printf("Ha habido un error %d al abrir el fichero\n", error);
		return; 
	}

	//Escribir los datos en el fichero

	for (i = 0; i < dim; i++) {
		fprintf(pf, "%d %c %s\n", aparcamiento[i].estado, aparcamiento[i].tipo, aparcamiento[i].matricula);
	}

	// Tercer paso: cerrar el fichero

	fclose(pf);
}
