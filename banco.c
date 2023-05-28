#include <stdio.h>
#include <string.h>

// ACCOUNT 1
double oldBalance1 = 30000.0;
double newBalance1;
char numberAccount1[1] = "1";
char typeAccount1[30] = "Cuenta Ahorro";
// ACCOUNT 2
double oldBalance2 = 500000.0;
double newBalance2;
char numberAccount2[1] = "2";
char typeAccount2[30] = "Cuenta Corriente";
// ACCOUNT 3
double oldBalance3 = 1500000.0;
double newBalance3;
char numberAccount3[1] = "3";
char typeAccount3[30] = "Cuenta Ahorro";

void loginScreen(char *userNameInput, char *passwordInput);
void errorLoginScreen(char *userNameInput, char *passwordInput);
void validCredentialAccess(char *userNameInput, char *passwordInput);
void optionsGeneralScreen();
void doDepositScreen();
void listOfAccountScreen();
void resumeMovementScreen(char *action, double amount, char *account, char * type, double oldBalance, double newBalance);

int main() {
    char userNameInput[30];
    char passwordInput[4];
    printf("<---    BANCO X     --->\n");
    loginScreen(userNameInput, passwordInput);
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
	printf("Intentar nuevamente (1 = Si/0 = No): ");
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
void doDepositScreen() {
	printf("\n<---	Vas a realizar un deposito	--->\n");
	int numberSelected;
	double depositInput;
	listOfAccountScreen();
	printf("Escribe el numero de Cuenta: ");
	scanf("%d", &numberSelected);
	printf("Escribe el valor a depositar: ");
	scanf("%lf", &depositInput);
	if (numberSelected == 1) {
	    newBalance1 = depositInput + oldBalance1;
	    resumeMovementScreen("Deposito", depositInput, numberAccount1, typeAccount1, oldBalance1, newBalance1);
	    oldBalance1 = newBalance1;
	} else if (numberSelected == 2) {
	    newBalance2 = depositInput + oldBalance2;
	    resumeMovementScreen("Deposito", depositInput, numberAccount2, typeAccount2, oldBalance2, newBalance2);
	    oldBalance2 = newBalance2;
	} else if (numberSelected == 3) {
	    newBalance3 = depositInput + oldBalance3;
	    resumeMovementScreen("Deposito", depositInput, numberAccount3, typeAccount3, oldBalance3, newBalance3);
	    oldBalance3 = newBalance3;
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
	printf("\n<---	Vas a realizar un deposito	--->\n");
	printf("    Acción: %s\n", action);
	printf("    Monto: %2.f\n", amount);
	printf("    Cuenta: %s\n", account);
	printf("    %s\n", type);
	printf("    Saldo anterior: %2.f\n", oldBalance);
	printf("    Saldo nuevo: %2.f\n", newBalance);
	printf("<---	--->\n");
}
