#include <stdio.h>
#include <string.h>

double oldBalanceTemp1;
double oldBalanceTemp2;
double oldBalanceTemp3;
double oldBalanceTempD1;
double oldBalanceTempD2;
double oldBalanceTempD3;

// ACCOUNT 1
double oldBalance1;
char numberAccount1[1] = "1";
char typeAccount1[30] = "Cuenta Ahorro";
// ACCOUNT 2
double oldBalance2;
char numberAccount2[1] = "2";
char typeAccount2[30] = "Cuenta Corriente";
// ACCOUNT 3
double oldBalance3;
char numberAccount3[1] = "3";
char typeAccount3[30] = "Cuenta Ahorro";

void loginScreen(char *userNameInput, char *passwordInput);
void errorLoginScreen(char *userNameInput, char *passwordInput);
void validCredentialAccess(char *userNameInput, char *passwordInput);
void optionsGeneralScreen();
void doDepositScreen();
void listOfAccountScreen();
void resumeMovementScreen(char *action, double amount, char *account, char * type, double oldBalance, double newBalance);
void doWithdrawalScreen();
void returnToMenu();
void resumeMovementTransferScreen(double amount, int account1, int account2, char * type1, char * type2,  double oldBalance1, double oldBalance2, double newBalance1, double newBalance2);

int main() {
    char userNameInput[30];
    char passwordInput[4];
    oldBalance1 = 30000.0;
	oldBalance2 = 500000.0;
	oldBalance3 = 1500000.0;
    printf("<---    BANCO X     --->\n");
    loginScreen(userNameInput, passwordInput);
    printf("%d", oldBalance1);
    return 0;
}
void loginScreen(char *userNameInput, char *passwordInput) {
	printf("\n<---	--->\n");
    printf("-> Usuario: ");
    scanf("%s", userNameInput);
    printf("-> Contrasena: ");
    scanf("%s", passwordInput);
    printf("<---	--->\n");
	validCredentialAccess(userNameInput, passwordInput);
}
void errorLoginScreen(char *userNameInput, char *passwordInput) {
	char intentAgainLogin[1];
	printf("<--- 	Usuario o contrasena incorrectos	--->\n");
	printf("Intentar nuevamente (S/N): ");
	scanf("%s", intentAgainLogin);
	if (strcmp(intentAgainLogin, "S") == 0) {
		loginScreen(userNameInput, passwordInput);
	}
}
void validCredentialAccess(char *userNameInput, char *passwordInput) {
if (strcmp(userNameInput, "Jhoto356") == 0) {
		if (strcmp(passwordInput, "1234") == 0) {
			optionsGeneralScreen();
		} else {
			errorLoginScreen(userNameInput, passwordInput);
		}
	} else {
		errorLoginScreen(userNameInput, passwordInput);
	}
}
void optionsGeneralScreen() {
	char optionToDo[1];
	printf("\n<---	MENU DE OPCIONES	--->\n");
	printf("	1. Depositar\n");
	printf("	2. Retirar\n");
	printf("	3. Tranferir\n");
	printf("	4. Listas de cuentas\n");
	printf("	5. Salir\n");
	printf("<---	--->\n");
	printf("Selecciona una opcion -> ");
	scanf("%s", optionToDo);
	printf("<---	--->\n");
	if (strcmp(optionToDo, "1") == 0) {
		doDepositScreen();
	}
	if (strcmp(optionToDo, "2") == 0) {
		doWithdrawalScreen();
	}
	if (strcmp(optionToDo, "3") == 0) {
		doTransferScreen();
	}
	if (strcmp(optionToDo, "4") == 0) {
		char returnToMenu[1];
		printf("\n<---	Listado de cuentas disponibles	--->\n");
		listOfAccountScreen();
		printf("Regrsar al menu de opciones(S/N) -> ");
		scanf("%s", returnToMenu);
		if (strcmp(toupper(returnToMenu), "S") == 0) {
			optionsGeneralScreen();
		}
		printf("<---	--->\n");
	}
	if (strcmp(optionToDo, "5") == 0) {
		printf("\n<---	Finalizando programa	--->\n");
		exit(0);
	}
}
void doTransferScreen() {
	printf("\n<---	Vas a realizar un transferencia	--->\n");
	int numberSelectedSource;
	int numberSelectedDestination;
	char typeSelectedSource[30];
	char typeSelectedDestination[30];
	double oldBlanceSource;
	double oldBlanceDestination;
	double newBlanceSource;
	double newBlanceDestination;
	double withdrawalInput;
	listOfAccountScreen();
	printf("Escribe el numero de Cuenta de origen: ");
	scanf("%d", &numberSelectedSource);
	printf("Escribe el numero de Cuenta de destino: ");
	scanf("%d", &numberSelectedDestination);
	printf("Escribe el monto a tranferir: ");
	scanf("%lf", &withdrawalInput);
	// VALIDA SI LA CUENTA DE ORIGEN EXISTE
	if (numberSelectedSource == 1) {
		oldBalanceTemp1 = oldBalance1;
		oldBlanceSource = oldBalanceTemp1;
		newBlanceSource = oldBalance1 - withdrawalInput;
		oldBalance1 = newBlanceSource;
		strcpy(typeSelectedSource, typeAccount1);
	} else if (numberSelectedSource == 2) {
		oldBalanceTemp2 = oldBalance2;
		oldBlanceSource = oldBalanceTemp2;
		newBlanceSource = oldBalance2 - withdrawalInput;
		oldBalance2 = newBlanceSource;
		strcpy(typeSelectedSource, typeAccount2);
	} else if (numberSelectedSource == 3) {
		oldBalanceTemp3 = oldBalance3;
		oldBlanceSource = oldBalanceTemp3;
		newBlanceSource = oldBalance3 - withdrawalInput;
		oldBalance3 = newBlanceSource;
		strcpy(typeSelectedSource, typeAccount3);
	} else {
		printf("La cuenta de origen no existe\n");
		returnToMenu();
	}
	// VALIDA SI LA TRANSFERENCIA NO ES ENTRE LA MISMA CUENTA
	if (numberSelectedSource == numberSelectedDestination) {
		oldBalance1 = oldBalanceTemp1;
		oldBalance2 = oldBalanceTemp2;
		oldBalance3 = oldBalanceTemp3;
		printf("No es posible transferir entre las misma cuenta\n");
		returnToMenu();
	} else {
		// VALIDA SI LA CUENTA DE DESTINO EXISTE
		if (numberSelectedDestination == 1) {
			oldBalanceTempD1 = oldBalance1;
			oldBlanceDestination = oldBalanceTempD1;
			newBlanceDestination = oldBalance1 + withdrawalInput;
			oldBalance1 = newBlanceDestination;
			strcpy(typeSelectedDestination, typeAccount1);
		} else if (numberSelectedDestination == 2) {
			oldBalanceTempD2 = oldBalance2;
			oldBlanceDestination = oldBalanceTempD2;
			newBlanceDestination = oldBalance2 + withdrawalInput;
			oldBalance2 = newBlanceDestination;
			strcpy(typeSelectedDestination, typeAccount2);
		} else if (numberSelectedDestination == 3) {
			oldBalanceTempD3 = oldBalance3;
			oldBlanceDestination = oldBalanceTempD3;
			newBlanceDestination = oldBalance3 + withdrawalInput;
			oldBalance3 = newBlanceDestination;
			strcpy(typeSelectedDestination, typeAccount3);
		} else {
			oldBalance1 = oldBalanceTemp1;
			oldBalance2 = oldBalanceTemp2;
			oldBalance3 = oldBalanceTemp3;
			printf("La cuenta de destino o existe\n");
			returnToMenu();
		}
		resumeMovementTransferScreen(withdrawalInput, numberSelectedSource, numberSelectedDestination, typeSelectedSource, typeSelectedDestination, oldBlanceSource, oldBlanceDestination, newBlanceSource, newBlanceDestination);
	}
	printf("<---	--->\n");
}
void returnToMenu() {
	printf("<---	--->\n");
	char returnToMenu[1];
	printf("\nDesea realizar otra operacion(S/N): ");
	scanf("%s", returnToMenu);
	if (strcmp(toupper(returnToMenu), "S") == 0) {
		optionsGeneralScreen();
	}
}
void resumeMovementTransferScreen(double amount, int account1, int account2, char * type1, char * type2,  double oldBalance1, double oldBalance2, double newBalance1, double newBalance2) {
	printf("\n<---	Resumen de movimiento	--->\n");
	printf("    Accion: Retiro\n");
	printf("    Monto: %.2f\n", amount);
	printf("    Cuenta: %d\n", account1);
	printf("    %s\n", type1);
	printf("    Saldo anterior: %2.f\n", oldBalance1);
	printf("    Saldo nuevo: %2.f\n", newBalance1);
	printf("<---	Resumen de movimiento	--->\n");
	printf("    Accion: Deposito\n");
	printf("    Monto: %2.f\n", amount);
	printf("    Cuenta: %d\n", account2);
	printf("    %s\n", type2);
	printf("    Saldo anterior: %2.f\n", oldBalance2);
	printf("    Saldo nuevo: %2.f\n", newBalance2);
	printf("<---	--->\n");
	char returnToMenu[1];
	printf("\nDesea realizar otra operacion(S/N): ");
	scanf("%s", returnToMenu);
	if (strcmp(toupper(returnToMenu), "S") == 0) {
			optionsGeneralScreen();
	}
}
void doWithdrawalScreen() {
	printf("\n<---	Vas a realizar un retiro	--->\n");
	int numberSelected;
	double withdrawalInput;
	listOfAccountScreen();
	printf("Escribe el numero de Cuenta: ");
	scanf("%d", &numberSelected);
	printf("Escribe el valor a depositar: ");
	scanf("%lf", &withdrawalInput);
	double newBalance;
	double oldBalance;
	if (numberSelected == 1) {
		oldBalance = oldBalance1;
	    if (withdrawalInput > oldBalance) {
	    	newBalance = oldBalance1;
	    	withdrawalInput = 0.0;
	    	printf("<---	Saldo insuficiente	--->\n");
		} else {
			newBalance = oldBalance - withdrawalInput;
			oldBalance1 = newBalance;
		}
		resumeMovementScreen("Retiro", withdrawalInput, numberAccount1, typeAccount1, oldBalance, newBalance);
	} else if (numberSelected == 2) {
		oldBalance = oldBalance2;
		if (withdrawalInput > oldBalance) {
			newBalance = oldBalance2;
	    	withdrawalInput = 0.0;
	    	printf("<---	Saldo insuficiente	--->\n");
		} else {
			newBalance = oldBalance - withdrawalInput;
	    	oldBalance2 = newBalance;
		}
	    resumeMovementScreen("Retiro", withdrawalInput, numberAccount2, typeAccount2, oldBalance, newBalance);
	} else if (numberSelected == 3) {
		oldBalance = oldBalance3;
		if (withdrawalInput > oldBalance) {
			newBalance = oldBalance3;
	    	withdrawalInput = 0.0;
	    	printf("<---	Saldo insuficiente	--->\n");
		} else {
			newBalance = oldBalance - withdrawalInput;
	    	oldBalance3 = newBalance;
		}
	    resumeMovementScreen("Retiro", withdrawalInput, numberAccount3, typeAccount3, oldBalance, newBalance);
	} else {
		printf("La cuenta no existe");
	}
	printf("<---	--->\n");
}
void doDepositScreen() {
	printf("\n<---	Vas a realizar un deposito	--->\n");
	int numberSelected;
	double depositInput;
	listOfAccountScreen();
	printf("Escribe el numero de Cuenta: ");
	scanf("%d", &numberSelected);
	printf("Escribe el valor a depositar: ");
	scanf("%lf", &depositInput);
	double newBalance;
	double oldBalance;
	if (numberSelected == 1) {
		oldBalance = oldBalance1;
	    newBalance = depositInput + oldBalance1;
	    oldBalance1 = newBalance;
	    resumeMovementScreen("Deposito", depositInput, numberAccount1, typeAccount1, oldBalance, newBalance);
	} else if (numberSelected == 2) {
		oldBalance = oldBalance2;
	    newBalance = depositInput + oldBalance2;
	    oldBalance2 = newBalance;
	    resumeMovementScreen("Deposito", depositInput, numberAccount2, typeAccount2, oldBalance, newBalance);
	} else if (numberSelected == 3) {
		oldBalance = oldBalance3;
	    newBalance = depositInput + oldBalance3;
	    oldBalance3 = newBalance;
	    resumeMovementScreen("Deposito", depositInput, numberAccount3, typeAccount3, oldBalance, newBalance);
	} else {
		printf("La cuenta no existe");
	}
	printf("<---	--->\n");
}
void listOfAccountScreen() {
	setCountData(typeAccount1, numberAccount1, oldBalance1);
	setCountData(typeAccount2, numberAccount2, oldBalance2);
	setCountData(typeAccount3, numberAccount3, oldBalance3);
}
void setCountData(char *typeAccount, char *numberOfAccount, double balance) {
	printf("	Cuenta Numero: %s - %s - Saldo: %2.f\n", numberOfAccount, typeAccount, balance);
}
void resumeMovementScreen(char *action, double amount, char *account, char * type, double oldBalance, double newBalance) {
	printf("\n<---	Resumen de movimineto	--->\n");
	printf("    Accion: %s\n", action);
	printf("    Monto: %2.f\n", amount);
	printf("    Cuenta: %s\n", account);
	printf("    %s\n", type);
	printf("    Saldo anterior: %2.f\n", oldBalance);
	printf("    Saldo nuevo: %2.f\n", newBalance);
	printf("<---	--->\n");
	char returnToMenu[1];
	printf("\nDesea realizar otra operacion(S/N): ");
	scanf("%s", returnToMenu);
	if (strcmp(toupper(returnToMenu), "S") == 0) {
			optionsGeneralScreen();
	}
}
