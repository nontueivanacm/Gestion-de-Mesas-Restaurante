
// 1. Configurador de mesas. El sistema debe permitir al usuario crear alta, baja y modificación de mesas y
// registrarlas en un archivo. Donde cada mesa tiene la siguiente información:
// Número de la mesa
// Estado de la mesa (libre/ocupada)
// Ganancia acumulada de la mesa (el dinero que ha generado hasta el momento)
// El archivo debe tener el siguiente formato:
// numero_mesa (int) esta_libre (bool) ganancia_acumulada(int)

#include <iostream>
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
        cout <<"\nNo se pudo abrir el archivo.\n";
        return;
    }

    Mesa m;
    cout << "\nIngrese numero de mesa: \n";
    while (!(cin >> m.numero_mesa)) {
    cout << "\nEntrada invalida. Ingrese un numero valido:\n";
    cin.clear();
    cin.ignore(10000, '\n');
}

    FILE* check = fopen("mesas.dat", "rb");
    if (check != NULL) {
        Mesa temp;
        while (fread(&temp, sizeof(Mesa), 1, check) == 1) {
            if (temp.numero_mesa == m.numero_mesa) {
                cout << "Ya existe una mesa con ese numero.\n";
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
    cout << "\n";
    cout<<"Mesa registrada.\n";
}

void mostrarMesas(){
    FILE* archivo = fopen("mesas.dat","rb");
    if (archivo == NULL) {
        cout << "\n";
        cout <<"No se pudo abrir el archivo.\n";
        return;
    }

    Mesa m;
    cout << "\n-----------LISTADO DE MESAS------------\n";
    cout << "---------------------------------------\n";
    while (fread(&m, sizeof(Mesa), 1, archivo) == 1) {
    cout << "\nMesa numero: " << m.numero_mesa << "\n";
    cout << "\nEstado de la mesa: " << (m.esta_libre? "Libre": "Ocupada") << "\n";
    cout << "\nGanancia acumulada: " << m.ganancia_acumulada << "\n";
    cout << "\n---------------------------------------\n";
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
    cout << "Numero de mesa a eliminar: ";
    while (!(cin >> numero)) {
    cout << "Entrada invalida. Ingrese un numero valido: ";
    cin.clear();
    cin.ignore(10000, '\n');
}

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

void modificarMesa() {
    FILE* archivo = fopen("mesas.dat", "rb+");
    if (archivo != NULL) {
        int numeroBuscado;

        cout << "Ingrese el numero de mesa a modificar: ";

    while (!(cin >> numeroBuscado)) {
    cout << "Entrada invalida. Ingrese un numero valido: ";
    cin.clear();
    cin.ignore(10000, '\n');
}
        Mesa m;
        bool encontrado = false;

        while (!encontrado && fread(&m, sizeof(Mesa), 1, archivo) == 1) {
        if (m.numero_mesa == numeroBuscado) {
            encontrado = true;

            int opcionMod;
            cout << "Elija una opcion: ";

            do {
                cout << "\nMesa encontrada:\n";
                cout << "\n";
                cout << "1. Numero de mesa:" << m.numero_mesa << "\n";
                cout << "\n";
                cout << "2. Estado de la mesa:" << (m.esta_libre ? "Libre" : "Ocupada") <<endl;
                cout << "\n";
                cout << "3. Ganancia acumulada:" << m.ganancia_acumulada << "\n";
                cout << "\n";
                cout << "0. Guardar y salir\n";
                cout << "\n";
                cout << "Elija una opcion: ";
                cout << "\n";

                while (!(cin >> opcionMod)) {
                cout << "Entrada invalida. Ingrese un numero valido: ";
                cin.clear();
                cin.ignore(10000, '\n');
                }

                switch(opcionMod) {
                    case 1:
                    cout << "Nuevo numero de mesa: ";
                    while (!(cin >> m.numero_mesa)) {
                    cout << "Entrada invalida. Ingrese un numero valido: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                break;

                case 2:
                cout << "Nuevo estado (1=Libre, 0=Ocupada): ";
                while (!(cin >> m.esta_libre)) {
                cout << "Entrada invalida. Ingrese 1 o 0: ";
                cin.clear();
                cin.ignore(10000, '\n');
                }
                break;

                case 3:
                cout << "Nueva ganancia acumulada: ";
                while (!(cin >> m.ganancia_acumulada)) {
                cout << "Entrada invalida. Ingrese un numero valido: ";
                cin.clear();
                cin.ignore(10000, '\n');
                }
                break;
                    case 0:
                        break;
                    default:
                        cout << "Opcion invalida.\n";
                        break;
                }
            } while(opcionMod != 0);

            fseek(archivo, -sizeof(Mesa), SEEK_CUR);
            fwrite(&m, sizeof(Mesa), 1, archivo);
            cout << "\n";
            cout << "Mesa modificada correctamente.\n";
            break;
        }
    }

        if (!encontrado) {
            cout << "No existe esa mesa." << endl;
        }

        fclose(archivo);
    } else {
        cout << "No se pudo abrir el archivo para lectura y escritura." << endl;
    }
}

int main() {
    int opcion;

do {
    cout << "\n-----------REGISTRO DE MESAS------------\n";
    cout << "\n";
    cout << "1. Alta de mesa\n";
    cout << "\n";
    cout << "2. Baja de mesa\n";
    cout << "\n";
    cout << "3. Mostrar mesas\n";
    cout << "\n";
    cout << "4. Modificar mesa\n";
    cout << "\n";
    cout << "0. Salir\n";
    cout << "\n";
    cout << "Opcion: ";

//Para evitar crasheo del menu
    if (!(cin >> opcion)) {
        cout << "\n";
        cout << "Entrada invalida. Por favor, ingrese otro numero.\n";
        cin.clear();
        cin.ignore(10000,'\n');
        continue;
    }

    switch(opcion) {
        case 1: altaMesa(); break;
        case 2: bajaMesa(); break;
        case 3: mostrarMesas(); break;
        case 4: modificarMesa(); break;
        case 0: cout << "Fin del programa.\n"; break;
        default: cout << "Opcion invalida.\n"; break;
    }

} while(opcion != 0);

    return 0;
}