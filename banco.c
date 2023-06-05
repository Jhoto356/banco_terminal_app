#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/** 
NOTA:
En C no existen los string como tal, en C eun string en un array de char[X]
¡¡IMPORTANTE!!
- strcpy(typeSelectedSource, typeAccount2) -> FUNCIÓN DE C PARA ASUGNAR UN STRING(CHAR[X])
- exit(0) -> FUNCIÓN DE C PARA FINALIZAR LA EJECIÓN DE UN PROGRAMA
- strcmp(intentAgainLogin, "S") -> FUNCIÓN DE C PARA COMPARAR CHAR[x] SI EL RESULTADO ES 0 SON IGUALES DEPENDE DE LA LIBRERIA string.h
- scanf("%d", &numberSelectedSource); -> EL SIGNO "&" ES PARA PODER OBTENER EL NÚMERO ENTERO O DECIMAL ESCRITO
- toupper(returnToMenu) -> FUNCIÓN DE C PARA CONVERTIR LA CADENA A MAYUSCULAS
- printf("    Monto: %2.f\n", amount); -> EL %2.F ES PARA DAR FORMATO DE 2 DECIMALES
**/

// VARIABLES TEMPORALES PARA GUARDAR EL VALOR ANTES DE UN TRANSFRENCIA, PARA EVITAR AFECTACIÓN SI ESTA NO ES REALIZADA
double oldBalanceTemp1;
double oldBalanceTemp2;
double oldBalanceTemp3;

double oldBalanceTempD1;
double oldBalanceTempD2;
double oldBalanceTempD3;

FILE *loginData; // VARIABLE APUNTADOR AL ARCHIVO PARA EL LOGIN
FILE *accountData; // VARIABLE APUNTADOR AL ARCHIVO PARA EL LOGIN

// CREDENCIALES DE INICIO DE SESIÓN
char userNameInput[30];
int passwordInput;

char userNameValid[30];
int passwordValid;

// MATRIZ DE CUENTAS
int accountInfo[3][3];

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

// DEFINICIÓN DE FUNCIONES
void loginScreen();
void errorLoginScreen();
void validCredentialAccess();
void optionsGeneralScreen();
void doDepositScreen();
void listOfAccountScreen();
void resumeMovementScreen(char *action, double amount, char *account, char * type, double oldBalance, double newBalance);
void doWithdrawalScreen();
void doTransferScreen();
void returnToMenu();
void resumeMovementDepositScreen(int amount, int account, int type, int oldBalance, int newBalance);
void resumeMovementTransferScreen(double amount, int account1, int account2, char * type1, char * type2,  double oldBalance1, double oldBalance2, double newBalance1, double newBalance2);

int main() {
    oldBalance1 = 30000.0;
	oldBalance2 = 500000.0;
	oldBalance3 = 1500000.0;
	loginData = fopen("userInfoLogin.txt", "rb");
	if (loginData == NULL) {
		printf("Archivo no disponible");
		exit(0);
	} else {
		while (feof(loginData) == 0) {
			fscanf(loginData, "%s%d", &userNameValid, &passwordValid);
		}
		fclose(loginData);
		accountInfo[0][0] = 1001;
		accountInfo[0][1] = 1;
		accountInfo[0][2] = 30000;
		accountInfo[1][0] = 2001;
		accountInfo[1][1] = 2;
		accountInfo[1][2] = 1600000;
		accountInfo[2][0] = 1002;
		accountInfo[2][1] = 1;
		accountInfo[2][2] = 450000;
		printf("<---    BANCO X     --->\n");
    	loginScreen();
	}
    return 0;
}

// FUNCIÓN PARA MOSTRAR EL LOGIN
void loginScreen() {
	printf("\n<---	--->\n");
    printf("-> Usuario: ");
    scanf("%s", userNameInput);
    printf("-> Contrasena: ");
    scanf("%d", &passwordInput);
    printf("<---	--->\n");
	validCredentialAccess(); 
}
// FUNCIÓN PARA VALIDAR LA CREDENCIALES
void validCredentialAccess() {
	int resultUserName = strcmp(userNameInput, userNameValid);
	if (resultUserName == 0 && passwordInput == passwordValid) { // VALIDA SI EL USUARIO Y CONSTRASEÑA SON CORRECTOs
		optionsGeneralScreen();	
	} else {
		errorLoginScreen();
	}
}
// FUNCIÓN PARA PREGUNTAR SI DESEA REINTETAR EL LOGIN
void errorLoginScreen() {
	char intentAgainLogin[1];
	printf("<--- 	Usuario o contrasena incorrectos	--->\n");
	printf("Intentar nuevamente (S/N): ");
	scanf("%s", intentAgainLogin);
	int result = strcmp(intentAgainLogin, "S");
	if (result == 0) {
		loginScreen(userNameInput, passwordInput);
	} 
}
// FUNCIÓN PARA MOSTRAR Y SELECCIONAR LA OPCIÓN DEL MENU PRINCIAPL
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
	if (strcmp(optionToDo, "1") == 0) { // REALIZAR UN DEPOSITO
		doDepositScreen();
	}
	if (strcmp(optionToDo, "2") == 0) { // REALIZAR UN RETIRO
		doWithdrawalScreen();
	}
	if (strcmp(optionToDo, "3") == 0) { // REALIZAR UNA TRANSFERENCIA
		doTransferScreen();
	}
	if (strcmp(optionToDo, "4") == 0) { // MOSTRAR EL LISTADO DE CUENTA
		printf("\n<---	Listado de cuentas disponibles	--->\n");
		listOfAccountScreen();
		returnToMenu();
		printf("<---	--->\n");
	}
	if (strcmp(optionToDo, "5") == 0) { // OPCIÓN PARA SALIR
		printf("\n<---	Finalizando programa	--->\n");
		exit(0);
	}
}
// FUNCIÓN PARA MOSTRAR LAS CUENTAS DISPONIBLES Y SU INFORMACIÓN
void listOfAccountScreen() {
	int positionRow = 0;
	printf("	Cuenta numero - Tipo - Saldo\n");
	for (positionRow; positionRow < 3; positionRow++) {
		printf("		%d	%d	$%d\n", accountInfo[positionRow][0], accountInfo[positionRow][1], accountInfo[positionRow][2]);
	}
}
// FUNCIÓN PARA REALIZAR UN DEPOSITO Y VALIDARLO
void doDepositScreen() {
	printf("\n<---	Vas a realizar un deposito	--->\n");
	int numberSelected, depositInput, newBalanceTemp;
	listOfAccountScreen();
	accountData = fopen("userAccount.txt", "a");
	if (accountData == NULL) {
		printf("Archivo no disponible");
		exit(0);
	} 
	printf("Escribe el numero de Cuenta: ");
	scanf("%d", &numberSelected);
	printf("Escribe el valor a depositar: ");
	scanf("%d", &depositInput);
	if (depositInput < 0) { // VALIDA QUE EL VALOR A DEPOSITAR NO SEA NEGATIVO
		printf("El valor a depositar es negativo.\n");
		returnToMenu();
	} 
	int r = 0;
	int existAccount = 0;
	for (r; r < 3; r++) {
		int numberAccount, typeAccount, balance;
		numberAccount = accountInfo[r][0];
		typeAccount = accountInfo[r][1];
		balance = accountInfo[r][2];
		if (numberAccount == numberSelected) {
			existAccount = 1;
			accountInfo[r][2] = balance + depositInput;
			fprintf(accountData, "%d %d %d\n", numberAccount, typeAccount, newBalanceTemp);
			resumeMovementDepositScreen(depositInput, numberAccount, typeAccount, balance, accountInfo[r][2]);
		} else {
			fprintf(accountData, "%d %d %d\n", numberAccount, typeAccount, balance);
		}
		if (r == 2 && existAccount == 0) {
			printf("La cuenta no existe\n");
			returnToMenu();
		}
	}
	fflush(accountData);
	fclose(accountData);
	printf("\n<---	--->\n");
}
// FUNCIÓN PARA MOSTRAR EL RESUMEN DE UN RETIRO O DEPOSITO
void resumeMovementDepositScreen(int amount, int account, int type, int oldBalance, int newBalance) {
	printf("\n<---	Resumen de movimiento	--->\n");
	printf("    Accion: Deposito\n");
	printf("    Monto: %d\n", amount);
	printf("    Cuenta: %d\n", account);
	printf("    Tipo: %d\n", type);
	printf("    Saldo anterior: %d\n", oldBalance);
	printf("    Saldo nuevo: %d\n", newBalance);
	printf("<---	--->\n");
	returnToMenu();
}
// FUNCIÓN PARA MOSTRAR EL RESUMEN DE UN RETIRO O DEPOSITO
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
	if (strcmp(returnToMenu, "S") == 0) {
			optionsGeneralScreen();
	}
}
//FUNCIÓN PARA REALIZAR UNA TRANFERENCIA Y VALIDARLA
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
// FUNCIÓN PARA RETORNAR AL MENU PRINCIPAL
void returnToMenu() {
	printf("<---	--->\n");
	char returnToMenu[1];
	printf("\nDesea realizar otra operacion(S/N): ");
	scanf("%s", returnToMenu);
	if (strcmp(returnToMenu, "S") == 0) {
		optionsGeneralScreen();
	}
}

// FUNCIÓN PARA MOSTRAR EL RESUMEN DE TRANFERENCIA
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
	if (strcmp(returnToMenu, "S") == 0) {
			optionsGeneralScreen();
	}
}
// FUNCIÓN PARA REALIZAR UN RETIRO Y VALIDARLO
void doWithdrawalScreen() {
	printf("\n<---	Vas a realizar un retiro	--->\n");
	int numberSelected;
	double withdrawalInput;
	listOfAccountScreen();
	printf("Escribe el numero de Cuenta: ");
	scanf("%d", &numberSelected);
	printf("Escribe el valor a retirar: ");
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
	    	resumeMovementScreen("Retiro", withdrawalInput, numberAccount3, typeAccount3, oldBalance, newBalance);
		}
	} else {
		printf("La cuenta no existe");
		returnToMenu();
	}

	printf("\n<---	--->\n");
}
