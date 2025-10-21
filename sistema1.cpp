
// 1. Configurador de mesas. El sistema debe permitir al usuario crear alta, baja y modificación de mesas y
// registrarlas en un archivo. Donde cada mesa tiene la siguiente información:
// Número de la mesa
// Estado de la mesa (libre/ocupada)
// Ganancia acumulada de la mesa (el dinero que ha generado hasta el momento)
// El archivo debe tener el siguiente formato:
// numero_mesa (int) esta_libre (bool) ganancia_acumulada(int)

#include <iostream>
#include <cstring>
using namespace std;

struct Mesa {
    int numero_mesa;
    bool esta_libre;
    int ganancia_acumulada;
};

void altaMesa();
void bajaMesa();
void modificarMesa();
void mostrarMesas();

void altaMesa(){

    FILE*archivo=fopen("mesas.dat", "ab");
    if (archivo == NULL) {
        cout <<"No se pudo abrir el archivo.\n";
        return;
    }

    Mesa m;
    cout<< "Ingrese número de mesa:";
    cin>>m.numero_mesa;

    FILE* check = fopen("mesas.dat", "rb");
    if (check != NULL) {
        Mesa temp;
        while (fread(&temp, sizeof(Mesa), 1, check) == 1) {
            if (temp.numero_mesa == m.numero_mesa) {
                cout << "Ya existe una mesa con ese número.\n";
                fclose(check);
                fclose(archivo);
                return;
            }
        }
        fclose(check);
    }

    m.esta_libre = true;
    m.ganancia_acumulada = 0;

    fwrite(&m, sizeof(Mesa), 1, archivo);
    fclose(archivo);

    cout<<"Mesa registrada.";
}

int mostrarMesas(){
    FILE* archivo = fopen("mesas.dat","rb");
    if (archivo == NULL) {
        cout <<"No se pudo abrir el archivo.\n";
        return;
    }

    Mesa m;
    cout << "LISTADO DE MESAS\n";
    while (fread(&m, sizeof(Mesa), 1, archivo) == 1) {
    cout << "Mesa número: " << m.numero_mesa << endl;
    cout << "Está libre?: " << m.esta_libre? "Sí": "No" << ednl;
    cout << "Ganancia acumulada: " << m.ganancia_acumulada << endl;
    cout << "__________________________\n";
    }
    fclose(archivo);
}

void bajaMesa() {
    FILE* archivo = fopen("mesas.dat", "rb");
    if (archivo == NULL) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    FILE* temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        cout << "No se pudo crear archivo temporal.\n" << endl;
        fclose(archivo);
        return;
    }

    int numero;
    cout << "Número de mesa a eliminar: \n";
    cin >> numero;

    Mesa m;
    bool eliminado = false;
    while (fread(&m, sizeof(Mesa), 1, archivo) == 1) {
        if (m.numero_mesa == numero) {
            eliminado = true;
            } else {
            fwrite(&m, sizeof(Mesa), 1, temp);
        }
    }

    fclose(archivo);
    fclose(temp);

    remove("mesas.dat");
    rename("temp.dat", "mesas.dat");

    if (eliminado)
        cout << "Mesa eliminada.\n";
    else
        cout << "Mesa no encontrada.\n";
}

void modificarMesa(int numeroBuscado, int nuevoNumero, bool nuevoEstado, int nuevaGanancia) {
    FILE* archivo = fopen("mesas.dat", "rb+");
    if (archivo != NULL) {
        Mesa mesa;
        bool encontrado = false;

        while (!encontrado && fread(&mesa, sizeof(Mesa), 1, archivo) == 1) {
            if (mesa.numero == numeroBuscado) {
                encontrado = true;

                cout << "Mesa encontrada\n";
                cout << "Número actual: " << mesa.numero << endl;
                cout << "Estado actual: " << (mesa.libre ? "Libre" : "Ocupada") << endl;
                cout << "Ganancia actual: $" << mesa.ganancia << endl;

                cout << "\nIngrese el nuevo número: ";
                cin >> mesa.numero;
                cout << "¿Está libre? (1=Sí, 0=No): ";
                cin >> mesa.libre;
                cout << "Ingrese la nueva ganancia acumulada: ";
                cin >> mesa.ganancia;
                
                fseek(archivo, -sizeof(Mesa), SEEK_CUR);
                fwrite(&mesa, sizeof(Mesa), 1, archivo);
                cout << "Mesa modificada." << endl;
            }
        }

        if (!encontrado) {
            cout << "No se encontró una mesa con ese número." << endl;
        }

        fclose(archivo);
    } else {
        cout << "No se pudo abrir el archivo para lectura y escritura." << endl;
    }
}

int main() {
    int opcion;

    do {
        cout << "\n=== CONFIGURADOR DE MESAS ===\n";
        cout << "1. Alta de mesa\n";
        cout << "2. Baja de mesa\n";
        cout << "3. Mostrar mesas\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: altaMesa(); break;
            case 2: bajaMesa(); break;
            case 3: mostrarMesas(); break;
        }

    } while (opcion != 0);

    cout << "Fin del programa.\n";
    return 0;
}