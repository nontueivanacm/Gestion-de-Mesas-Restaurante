// Sistema 2
// 1. Se carga una lista de mesas al iniciar el programa.
// Se usan las funciones del sistema 1 y se procede a:
// Recibir nuevos clientes (si hay mesas libres entonces se asigna una. Si todas están ocupadas, se agrega a una **cola de espera**)
// Liberar mesas:
//  - Se actualiza la ganancia acumulada y se marca como libre.
// - Si hay clientes esperando, se asigna automáticamente al primero.
// Guardar cambios al archivo mesas.dat antes de salir.

#include <iostream>
#include <string>
#include <cstring> 
using namespace std;

struct Mesa{
      int numero_mesa;
      bool esta_libre;
      int ganancia_acumulada;
};

struct Nodo {
      int numero_mesa;
      bool esta_libre;
      int ganancia_acumulada;
      Nodo* siguiente;
};

struct ClienteEnEspera {
  int idcliente;
  ClienteEnEspera* siguiente;
};

int proximoIdCliente = 1;

Nodo* crearNodo (int num, bool libre, int ganancia);
void agregarMesa (Nodo*& lista, Nodo* nuevo);
void mostrarMesas(Nodo* lista);
void liberarLista(Nodo*& lista);
Nodo* cargarDesdeArchivo();
void guardarEnArchivo(Nodo* lista);

// Declaraciones de funciones para cola
bool colaEstaVacia();
void encolar();
int desencolar();

// Declaracion de funciones de patrones algoritmicos del sistema
void recibirCliente(Nodo*& lista);
void liberarMesa(Nodo*& lista);



Nodo* crearNodo (int num, bool libre, int ganancia) {
  Nodo* nuevo = new Nodo;
  nuevo -> numero_mesa = num;
  nuevo -> esta_libre = libre;
  nuevo -> ganancia_acumulada = ganancia;
  nuevo -> siguiente = NULL;
  return nuevo;
};

void agregarMesa (Nodo*& lista, Nodo* nuevo) {
  if (lista == NULL) {
      lista = nuevo;
  } else {
    Nodo* aux = lista;
    while (aux -> siguiente != NULL) {
          aux = aux -> siguiente;
    }
    aux -> siguiente = nuevo;
  } 
};

Nodo* cargarDesdeArchivo (){
  FILE* archivo = fopen ("mesas.dat", "rb");
  if (archivo == NULL) {
      cout << "No se pudo abrir mesas.dat, ya que no hay mesas guardadas.\n";
      return NULL;
  }

  Nodo* lista = NULL;
    Mesa m;
  while (fread(&m, sizeof(Mesa), 1, archivo) ==1) {
      Nodo* nuevo = crearNodo (m.numero_mesa, m.esta_libre, m.ganancia_acumulada);
      agregarMesa (lista, nuevo);
  }

  fclose(archivo);
  cout << "Mesas cargadas desde mesas.dat\n";
  return lista;
}

void mostrarMesas(Nodo* lista) {
    if (lista == NULL) {
      cout << "No hay mesas cargadas.\n";
      return;
    }
    cout << "\n--- LISTADO DE MESAS ---\n";
    Nodo* aux = lista;
    while (aux != NULL) {
        cout << "Mesa: " << aux ->numero_mesa
              << " | Estado: " << (aux -> esta_libre ? "Libre" : "Ocupada")
              << " | Ganancia: $" << aux -> ganancia_acumulada << endl; 
              aux = aux -> siguiente;
    }
}

void guardarEnArchivo(Nodo* lista) {
  FILE* archivo = fopen("mesas.dat", "wb");
  if (archivo == NULL) {
    cout << "Error al abrir mesas.dat para guardar.\n";
    return;
  }
  Nodo* aux = lista;
  while (aux != NULL) { 
      Mesa m;
      m.numero_mesa = aux->numero_mesa;
      m.esta_libre = aux->esta_libre;
      m.ganancia_acumulada = aux->ganancia_acumulada;
      fwrite(&m, sizeof(Mesa), 1, archivo);
      aux = aux -> siguiente;
  }
  fclose(archivo);
  cout << "Mesas guardadas correctamente en mesas.dat\n";
}

void liberarLista(Nodo*& lista) {
  Nodo* aux;
  while (lista != NULL) {
    aux = lista;
    lista = lista -> siguiente;
    delete aux;
  }
}

// Funciones de la Cola

bool colaEstaVacia(ClienteEnEspera* frenteCola){
  return (frenteCola == nullptr);
}

ClienteEnEspera* crearCliente(int id){
  ClienteEnEspera* nuevoCliente = new ClienteEnEspera;
  nuevoCliente->idcliente=id;
  nuevoCliente->siguiente=nullptr;
  return nuevoCliente;
}

void encolar(ClienteEnEspera*& frente, ClienteEnEspera*& final, int id){
  ClienteEnEspera* nuevoCliente = crearCliente(id);
  if (final == nullptr)
  { 
    frente = final = nuevoCliente;
  }else{
    final->siguiente = nuevoCliente;
    final = nuevoCliente;
  }
}

int desencolar(ClienteEnEspera*& frente, ClienteEnEspera*& final){
  if(frente ==  nullptr){
    return -1;
  }
  int idValor = frente ->idcliente;
  ClienteEnEspera* temp = frente;
  frente = frente ->siguiente;
  if (frente == nullptr)
  {
    final=nullptr;
  }
  delete temp;
  return idValor;
}

void recibirCliente(Nodo*& lista, ClienteEnEspera*& frenteCola, ClienteEnEspera*& fondoCola){
  if (lista == nullptr)
  {
    cout <<"Todavia no hay mesas cargadas en el sistema"<< endl;
    return;
  }
  
  // inicializamos
  Nodo* actual = lista;
  bool mesaEncontrada = false;

  while (actual != nullptr && !mesaEncontrada)
  {
    if(actual->esta_libre){ // esta libre?
      actual ->esta_libre = false; //asignar mesa
      mesaEncontrada = true;
    }
    actual = actual->siguiente;
  }

  //Ahora logica para por si no se encontro mesa, se encole el cliente
  if(!mesaEncontrada){
    encolar(frenteCola, fondoCola, proximoIdCliente);
  }
  proximoIdCliente++; //incrementar 1 para el numero del proximo cliente
}

void liberarMesa(Nodo*& lista, ClienteEnEspera*& frenteCola, ClienteEnEspera*& finalCola){
  int numMesa, monto; // variables locales
  cout << "Ingrese el numero de la mesa para liberar: ";
  if (!(cin >> numMesa)) return;
  cout << "Ingrese el monto consumido: ";
  if(!(cin>>monto)) return;
  
  Nodo* actual = lista;
  bool mesaEncontrada = false;

  // busqueda
  while(actual != nullptr && !mesaEncontrada){
    if (actual->numero_mesa == numMesa){
      if (actual->esta_libre)
      {
        cout << "la mesa numero: " << numMesa << " ya estaba libre" << endl;
        return;
      }
      actual->ganancia_acumulada += monto;
      actual->esta_libre = true;
      cout << "mesa numero: " << numMesa << "LIBERADA, ganacia acumulada: " << actual->ganancia_acumulada << endl;
      mesaEncontrada = true;
      if (!colaEstaVacia(frenteCola)){
        int idClienteReasignado = desencolar(frenteCola, finalCola);
        actual->esta_libre = false;
        cout << "cliente numero: " << idClienteReasignado << " REASIGNADO a la mesa numero: " << actual->numero_mesa << endl;
      }
      return;
    }
    actual = actual->siguiente;
  }
  if (!mesaEncontrada)
  {
    cout << "No se encontro la mesa numero: " << numMesa << endl;
  }
  
}
int main(){
  ClienteEnEspera* frenteCola = nullptr;
  ClienteEnEspera* Finalcola = nullptr;
  
}
