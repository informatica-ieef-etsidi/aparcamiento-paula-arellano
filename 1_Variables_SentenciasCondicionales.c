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
			break;
			if (plaza1 == 1) {
				plaza1 = 0;
			}
			else {
				plaza2 = 0;
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
