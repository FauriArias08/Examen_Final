#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <cctype>
#include <conio.h> 

using namespace std;

// Función para convertir un string a entero usando stringstream
int convertirStringAEntero(const string& str) {
    int numero;
    stringstream ss(str);
    ss >> numero;
    return numero;
}

// Función para establecer el color del texto
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Función para mover el cursor a una posición específica en la consola
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Función para validar que una cadena contiene solo números
bool validarSoloNumeros(const string& entrada) {
    for (size_t i = 0; i < entrada.length(); ++i) {
        if (!isdigit(static_cast<unsigned char>(entrada[i]))) return false;
    }
    return true;
}

// Función para validar que una cadena contiene solo letras
bool validarSoloLetras(const string& entrada) {
    for (size_t i = 0; i < entrada.length(); ++i) {
        if (!isalpha(static_cast<unsigned char>(entrada[i]))) return false;
    }
    return true;
}

// Función para mostrar mensajes en pantalla con un fondo de color y cuadro
void mostrarMensaje(const string& mensaje, bool pausa = true) {
    system("cls");
    setColor(12); 
    gotoxy(5, 5);
    cout << "+-----------------------------------------------+" << endl;
    gotoxy(5, 6);
    cout << "| " << mensaje;
    gotoxy(5, 7);
    cout << "+-----------------------------------------------+" << endl;
    setColor(7); 
    if (pausa) getch(); // Pausar la ejecución y esperar una tecla
}

// Función para mostrar un menú
void mostrarMenuConCuadro() {
    system("cls");
    setColor(12); 
    gotoxy(5, 3);
    cout << "+-----------------------------------------------+" << endl;
    gotoxy(5, 4);
    cout << "| Sistema de Control de Migracion               |" << endl;
    gotoxy(5, 5);
    cout << "+-----------------------------------------------+" << endl;
    gotoxy(5, 6);
    cout << "| 1. Ingreso de nuevo viajero                   |" << endl;
    gotoxy(5, 7);
    cout << "| 2. Registrar ingreso al pais                  |" << endl;
    gotoxy(5, 8);
    cout << "| 3. Registrar salida del pais                  |" << endl;
    gotoxy(5, 9);
    cout << "| 4. Consultar informacion de un viajero        |" << endl;
    gotoxy(5, 10);
    cout << "| 5. Generar reporte de entradas y salidas      |" << endl;
    gotoxy(5, 11);
    cout << "| 6. Borrar registros de un viajero             |" << endl;
    gotoxy(5, 12);
    cout << "| 7. Salir                                      |" << endl;
    gotoxy(5, 13);
    cout << "+-----------------------------------------------+" << endl;
    gotoxy(5, 14);
    cout << "Elige una opcion: ";
    setColor(7); 
}

//////// Estructuras ////////

struct Viajero {
    int id;
    string nombre;
    string direccion;
    string nacionalidad;
    string pasaporte;
};

struct Ingreso {
    int idViajero;
    string fechaIngreso;
    string lugarIngreso;
};

struct Salida {
    int idViajero;
    string fechaSalida;
    string lugarSalida;
};

struct Registro {
    int idViajero;
    string fecha;
    string tipo; // "Ingreso" o "Salida"
    string lugar;
};

struct Historial {
    int idViajero;
    string movimientos; // Resumen de entradas y salidas
};

//////// Arreglos ////////

Viajero viajeros[100];   // Arreglo de viajeros
Ingreso ingresos[100];   // Arreglo de ingresos
Salida salidas[100];     // Arreglo de salidas
Registro registros[200]; // Arreglo de registros
Historial historial[100];// Arreglo de historial de viajeros

int numViajeros = 0;     // Contador de viajeros
int numIngresos = 0;     // Contador de ingresos
int numSalidas = 0;      // Contador de salidas
int numRegistros = 0;    // Contador de registros

//////// Funciones ////////

void ingresarViajero() {
    system("cls");
    setColor(13); 
    gotoxy(5, 3);
    cout << "+-----------------------------------------------+" << endl;
    gotoxy(5, 4);
    cout << "| Ingreso de nuevo viajero                     |" << endl;
    gotoxy(5, 5);
    cout << "+-----------------------------------------------+" << endl;
    setColor(7); 

    Viajero nuevoViajero;
    nuevoViajero.id = numViajeros + 1;

    gotoxy(5, 6); cout << "Nombre: ";
    cin.ignore();
    getline(cin, nuevoViajero.nombre);
    if (nuevoViajero.nombre.empty()) {
        mostrarMensaje("El nombre no puede estar vacio.");
        return;
    }

    gotoxy(5, 7); cout << "Direccion: ";
    getline(cin, nuevoViajero.direccion);
    if (nuevoViajero.direccion.empty()) {
        mostrarMensaje("La direccion no puede estar vacia.");
        return;
    }

    gotoxy(5, 8); cout << "Nacionalidad: ";
    getline(cin, nuevoViajero.nacionalidad);
    if (nuevoViajero.nacionalidad.empty()) {
        mostrarMensaje("La nacionalidad no puede estar vacia.");
        return;
    }

    gotoxy(5, 9); cout << "Pasaporte: ";
    getline(cin, nuevoViajero.pasaporte);
    if (nuevoViajero.pasaporte.empty()) {
        mostrarMensaje("El pasaporte no puede estar vacio.");
        return;
    }

    viajeros[numViajeros++] = nuevoViajero;
    mostrarMensaje("Viajero agregado con exito!", true);
}

void registrarIngreso() {
    system("cls");
    setColor(13); 
    gotoxy(5, 3);
    cout << "+-----------------------------------------------+" << endl;
    gotoxy(5, 4);
    cout << "| Registro de ingreso                          |" << endl;
    gotoxy(5, 5);
    cout << "+-----------------------------------------------+" << endl;
    setColor(7);

    Ingreso nuevoIngreso;
    string idViajeroStr;

    gotoxy(5, 6); cout << "ID del viajero: ";
    cin >> idViajeroStr;

    if (!validarSoloNumeros(idViajeroStr)) {
        mostrarMensaje("El ID debe contener solo numeros.");
        return;
    }

    nuevoIngreso.idViajero = convertirStringAEntero(idViajeroStr);

    gotoxy(5, 7); cout << "Fecha de ingreso (DD/MM/AAAA): ";
    cin.ignore();
    getline(cin, nuevoIngreso.fechaIngreso);
    if (nuevoIngreso.fechaIngreso.empty()) {
        mostrarMensaje("La fecha de ingreso no puede estar vacia.");
        return;
    }

    gotoxy(5, 8); cout << "Lugar de ingreso: ";
    getline(cin, nuevoIngreso.lugarIngreso);
    if (nuevoIngreso.lugarIngreso.empty()) {
        mostrarMensaje("El lugar de ingreso no puede estar vacio.");
        return;
    }

    ingresos[numIngresos++] = nuevoIngreso;

    Registro nuevoRegistro = {nuevoIngreso.idViajero, nuevoIngreso.fechaIngreso, "Ingreso", nuevoIngreso.lugarIngreso};
    registros[numRegistros++] = nuevoRegistro;

    mostrarMensaje("Ingreso registrado con exito!");
}

void registrarSalida() {
    system("cls");
    setColor(13); 
    gotoxy(5, 3);
    cout << "+-----------------------------------------------+" << endl;
    gotoxy(5, 4);
    cout << "| Registro de salida                           |" << endl;
    gotoxy(5, 5);
    cout << "+-----------------------------------------------+" << endl;
    setColor(7); 

    Salida nuevaSalida;
    string idViajeroStr;

    gotoxy(5, 6); cout << "ID del viajero: ";
    cin >> idViajeroStr;

    if (!validarSoloNumeros(idViajeroStr)) {
        mostrarMensaje("El ID debe contener solo numeros.");
        return;
    }

    nuevaSalida.idViajero = convertirStringAEntero(idViajeroStr);

    gotoxy(5, 7); cout << "Fecha de salida (DD/MM/AAAA): ";
    cin.ignore();
    getline(cin, nuevaSalida.fechaSalida);
    if (nuevaSalida.fechaSalida.empty()) {
        mostrarMensaje("La fecha de salida no puede estar vacia.");
        return;
    }

    gotoxy(5, 8); cout << "Lugar de salida: ";
    getline(cin, nuevaSalida.lugarSalida);
    if (nuevaSalida.lugarSalida.empty()) {
        mostrarMensaje("El lugar de salida no puede estar vacio.");
        return;
    }

    salidas[numSalidas++] = nuevaSalida;

    Registro nuevoRegistro = {nuevaSalida.idViajero, nuevaSalida.fechaSalida, "Salida", nuevaSalida.lugarSalida};
    registros[numRegistros++] = nuevoRegistro;

    mostrarMensaje("Salida registrada con exito!");
}

void consultarViajero() {
    system("cls");
    setColor(13); 
    gotoxy(5, 3);
    cout << "+-----------------------------------------------+" << endl;
    gotoxy(5, 4);
    cout << "| Consulta de informacion del viajero           |" << endl;
    gotoxy(5, 5);
    cout << "+-----------------------------------------------+" << endl;
    setColor(7); 

    string idViajeroStr;

    gotoxy(5, 6); cout << "ID del viajero: ";
    cin >> idViajeroStr;

    if (!validarSoloNumeros(idViajeroStr)) {
        mostrarMensaje("El ID debe contener solo numeros.");
        return;
    }

    int idViajero = convertirStringAEntero(idViajeroStr);
    bool encontrado = false;

    for (int i = 0; i < numViajeros; i++) {
        if (viajeros[i].id == idViajero) {
            encontrado = true;
            gotoxy(5, 7); cout << "Nombre: " << viajeros[i].nombre;
            gotoxy(5, 8); cout << "Direccion: " << viajeros[i].direccion;
            gotoxy(5, 9); cout << "Nacionalidad: " << viajeros[i].nacionalidad;
            gotoxy(5, 10); cout << "Pasaporte: " << viajeros[i].pasaporte;
            getch();
            break;
        }
    }

    if (!encontrado) {
        mostrarMensaje("Viajero no encontrado.");
    }
}

void generarReporte() {
    system("cls");
    setColor(13); 
    gotoxy(5, 3);
    cout << "+-----------------------------------------------+" << endl;
    gotoxy(5, 4);
    cout << "| Reporte de entradas y salidas                |" << endl;
    gotoxy(5, 5);
    cout << "+-----------------------------------------------+" << endl;
    setColor(7); 

    int posY = 6; // Posición vertical inicial para los registros
    for (int i = 0; i < numRegistros; i++) {
        gotoxy(5, posY++);
        cout << "ID Viajero: " << registros[i].idViajero
             << ", Fecha: " << registros[i].fecha
             << ", Tipo: " << registros[i].tipo
             << ", Lugar: " << registros[i].lugar;
        getch();
    }

    if (numRegistros == 0) {
        gotoxy(5, posY);
        cout << "No hay registros para mostrar.";
    }

    mostrarMensaje("Reporte generado.");
}

void borrarRegistros() {
    system("cls");
    setColor(13); 
    gotoxy(5, 3);
    cout << "+-----------------------------------------------+" << endl;
    gotoxy(5, 4);
    cout << "| Borrado de registros de un viajero            |" << endl;
    gotoxy(5, 5);
    cout << "+-----------------------------------------------+" << endl;
    setColor(7); 

    string idViajeroStr;

    gotoxy(5, 6); cout << "ID del viajero: ";
    cin >> idViajeroStr;

    if (!validarSoloNumeros(idViajeroStr)) {
        mostrarMensaje("El ID debe contener solo numeros.");
        return;
    }

    int idViajero = convertirStringAEntero(idViajeroStr);
    bool encontrado = false;

    for (int i = 0; i < numViajeros; i++) {
        if (viajeros[i].id == idViajero) {
            viajeros[i] = {0, "", "", "", ""}; // Vaciar el registro
            encontrado = true;
            mostrarMensaje("Registros del viajero borrados.");
            getch();
            break;
        }
    }

    if (!encontrado) {
        mostrarMensaje("Viajero no encontrado.");
        getch();
    }
}

void mostrarMenu() {
    char opcion, continuar;
    do {
        mostrarMenuConCuadro();
        opcion = getch();

        switch(opcion) {
            case '1':
                ingresarViajero();
                break;
            case '2':
                registrarIngreso();
                break;
            case '3':
                registrarSalida();
                break;
            case '4':
                consultarViajero();
                break;
            case '5':
                generarReporte();
                break;
            case '6':
                borrarRegistros();
                break;
            case '7':
                system("cls");
                setColor(10); 
                gotoxy(10,10); printf("+-----------------------------------------------+");
                gotoxy(10,11); printf("| Estas seguro que quieres salir del sistema?  |");
                gotoxy(10,12); printf("| Desea salir del programa (S/N)?              |");
                gotoxy(10,13); printf("+-----------------------------------------------+");
                setColor(7); 
                continuar = getch();
                if (continuar=='N' || continuar=='n')
				mostrarMenu();
				else if (continuar=='S' || continuar=='s')
				break;
            default:
                mostrarMensaje("Opcion invalida, intenta de nuevo.");
        }
    } while(opcion != '7');
}

int main() {
    mostrarMenu();
    return 0;
}        
