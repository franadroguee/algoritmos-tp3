#include <iostream>
#include <string>

#include "goleadores.h"

// Cambiar a true si hicieron la parte optativa (los dos listados).
const bool CON_LISTADOS = false;

// Lee de la entrada estandar la lista de goles del grupo (un gol por linea:
// el nombre del jugador que lo hizo) e imprime el resumen.
//
// Uso: ./goleadores < datos/ejemplo.txt
int main() {
    // COMPLETAR: crear la estructura donde se van a cargar los goles.
    Goleadores goleadores;
    std::string jugador;
    while (std::getline(std::cin, jugador)) {
        if (jugador != "") {
            // En este punto, jugador tiene el nombre de quien hizo el gol.
            // COMPLETAR: anotarle el gol.
            goleadores.anotar_gol(jugador);
        }
    }

    // COMPLETAR: imprimir, con el formato del enunciado, la cantidad de
    // jugadores con goles y el maximo goleador (con sus goles).

    std::cout << "Jugadores con goles: " << goleadores.cantidad_de_jugadores() << std::endl;
    std::cout << "Maximo goleador: " << goleadores.maximo_goleador() << " (" << goleadores.goles(goleadores.maximo_goleador()) << " goles)" << std::endl;

    if (CON_LISTADOS) {
        std::cout << std::endl;
        std::cout << "Goleadores por nombre:" << std::endl;
        // OPTATIVO: imprimir el listado por nombre.
        std::cout << std::endl;
        std::cout << "Goleadores por goles:" << std::endl;
        // OPTATIVO: imprimir el listado por goles.
    }

    return 0;
}
