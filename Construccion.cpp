#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

// Clase para representar una pieza de Lego
class PiezaLego
{
public:
    PiezaLego(const string &tipo, int cantidad) : tipoPieza(tipo), cantidadPiezas(cantidad) {}
    string tipoPieza;
    int cantidadPiezas;
};

// Clase base para representar una parte de la casa
class CasaPart
{
public:
    CasaPart(const string &nombre, const vector<PiezaLego> &piezas) : nombreParte(nombre), piezasNecesarias(piezas) {}
    string nombreParte;
    vector<PiezaLego> piezasNecesarias;
};

// Función para construir una casa
void ConstruirCasa(const unordered_map<string, int> &partesDeseadas, unordered_map<string, int> &piezasDisponibles)
{
    // Definir las partes de la casa y la cantidad de piezas de cada tipo
    vector<CasaPart> partesCasa;
    partesCasa.push_back(CasaPart("Cimientos", {PiezaLego("J", 4)}));                          // 2x2
    partesCasa.push_back(CasaPart("Pared", {PiezaLego("A", 4)}));                              // 2x2
    partesCasa.push_back(CasaPart("Techo", {PiezaLego("D", 8)}));                              // 3x2
    partesCasa.push_back(CasaPart("ParedConPuerta", {PiezaLego("A", 4), PiezaLego("B", 1)}));  // 1x1,5
    partesCasa.push_back(CasaPart("ParedConVentana", {PiezaLego("A", 4), PiezaLego("C", 1)})); // 1,5x0,5
    partesCasa.push_back(CasaPart("Piso", {PiezaLego("E", 4)}));                               // 3x3
    partesCasa.push_back(CasaPart("Terraza", {PiezaLego("F", 6)}));                            // 6x6
    partesCasa.push_back(CasaPart("Piscina", {PiezaLego("H", 5)}));                            // 4x4

    unordered_map<string, int> partesConstruidas;

    // Inicializar las partes de la casa y sus piezas necesarias
    for (const CasaPart &parte : partesCasa)
    {   
        cout << parte << endl;
        partesConstruidas[parte.nombreParte] = 0;
    }

    // Mostrar la cantidad de piezas disponibles
    cout << "Cantidad de piezas disponibles:" << endl;
    for (const auto &par : piezasDisponibles)
    {
        cout << par.first << ": " << par.second << endl;
    }

    // Ordenar las partes de la casa según prioridad
    vector<string> prioridad = {"Cimientos","Pared", "ParedConPuerta", "ParedConVentana", "Piso", "Techo", "Terraza", "Piscina"};

    for (const string &parteActual : prioridad)
    {
        if (partesDeseadas.find(parteActual) == partesDeseadas.end())
        {
            // La parte no está en la lista de partes deseadas, omitir
            continue;
        }

        int cantidadDeseada = partesDeseadas.at(parteActual);

        const CasaPart *casaPart = nullptr; // Puntero a CasaPart, inicializado a nullptr

        // Buscar la CasaPart correspondiente en el vector
        for (const CasaPart &parte : partesCasa)
        {
            if (parte.nombreParte == parteActual)
            {
                casaPart = &parte;
                break;
            }
        }

        if (casaPart == nullptr)
        {
            cout << "Parte deseada no encontrada: " << parteActual << endl;
            continue;
        }

        // Resto del código...

        // Verificar si la parte puede construirse
        bool construible = true;

        for (const PiezaLego &pieza : casaPart->piezasNecesarias)
        {
            if (piezasDisponibles[pieza.tipoPieza] < pieza.cantidadPiezas)
            {
                construible = false;
                break;
            }
        }

        if (construible)
        {
            // Construir la parte y actualizar las piezas construidas
            cout << "Construyendo " << parteActual << "..." << endl;

            for (const PiezaLego &pieza : casaPart->piezasNecesarias)
            {
                piezasDisponibles[pieza.tipoPieza] -= pieza.cantidadPiezas;
            }

            // Si se construye una ventana o una puerta, quitar una pared disponible
            if (parteActual == "ParedConVentana" || parteActual == "ParedConPuerta")
            {
                partesConstruidas["Pared"]--;
            }
        }
        else
        {
            cout << "No se puede construir " << parteActual << " debido a restricciones." << endl;
            if (parteActual == "ParedConVentana" || parteActual == "ParedConPuerta")
            {
                cout << "Se requiere una Pared adicional para construir Ventanas o Puertas." << endl;
                return; // Finalizar el programa debido a restricciones
            }
        }
    }

    // Verificar si todas las partes seleccionadas se han construido
    bool construccionExitosa = true;

    for (const auto &parteDeseada : partesDeseadas)
    {
        if (partesConstruidas.find(parteDeseada.first) == partesConstruidas.end() || partesConstruidas[parteDeseada.first] < parteDeseada.second)
        {
            construccionExitosa = false;
            break;
        }
    }

    if (construccionExitosa)
    {
        cout << "La construcción de la casa se ha completado con éxito." << endl;
    }
    else
    {
        cout << "No se pudo completar la construcción de la casa debido a restricciones o partes no seleccionadas." << endl;
    }
}

int main()
{
    // Indica las partes de la casa que deseas construir y su cantidad aquí
    unordered_map<string, int> partesDeseadas = {
        {"Cimientos", 1},
        {"Pared", 1}
    };

    // Indica la cantidad de piezas disponibles
    unordered_map<string, int> piezasDisponibles = {
        {"A", 50},
        {"J", 6},
        {"B", 5},
        {"C", 3},
        {"D", 15},
        {"E", 10},
        {"F", 8},
        {"H", 5}
    };

    ConstruirCasa(partesDeseadas, piezasDisponibles);

    return 0;
}