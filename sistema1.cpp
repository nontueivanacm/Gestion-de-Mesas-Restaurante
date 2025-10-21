
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
void mostrarMesas();

void altaMesa(){

    FILE*archivo=fopen("mesas.dat", "ab");
    if (archivo == NULL) {
        cout <<"No se pudo abrir el archivo.\n";
        return;
    }

    Mesa m;
    cout<< "Número de mesa:";
    cin>>m.numero_mesa;
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
    cout << "LISTADO DE MESAS";
    while (fread(&m, sizeof(Mesa), 1, archivo) == 1) {
    cout << "Mesa número: " << m.numero_mesa << \n;
    cout << "Está libre?: " << m.esta_libre? "Sí": "No" << \n;
    cout << "Edad: " << estudiante.edad << \n;
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
    cout << "Numero de mesa a eliminar: \n";
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
        cout << "Mesa eliminada correctamente.\n";
    else
        cout << "Mesa no encontrada.\n";
}

void modifMesa(int codigoBuscado, int nuevaEdad) {
 FILE* archivo = fopen("estudiantes_binarios.dat", "rb+");
 if (archivo != NULL) {
 Estudiante estudiante;
 bool encontrado = false;
 while (!encontrado && fread(&estudiante, sizeof(Estudiante), 1, archivo) == 1) {
 if (estudiante.codigo == codigoBuscado) {
 encontrado = true;
 estudiante.edad = nuevaEdad;
 fseek(archivo, -sizeof(Estudiante), SEEK_CUR);
 fwrite(&estudiante, sizeof(Estudiante), 1, archivo);
 cout << "Edad actualizada exitosamente." << endl;
 }
 }
 if (!encontrado) {
 cout << "No se encontró un estudiante con ese código." << endl;
 }
 fclose(archivo);
 } else {
 cout << "No se pudo abrir el archivo para lectura y escritura." << endl;
 }
}
int main() {
 int codigoBuscado, nuevaEdad;
 cout << "Ingrese el código del estudiante a buscar: ";
 cin >> codigoBuscado;
 cout << "Ingrese la nueva edad: ";
 cin >> nuevaEdad;
 editarEdadEstudiante(codigoBuscado, nuevaEdad);
 return 0;
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