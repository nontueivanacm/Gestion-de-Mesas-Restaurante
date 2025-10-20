
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

void AltaMesa();
void BajaMesa();
void ModifMesa();
void registro();

