#include "goleadores.h"

#include <iostream>

Goleadores::Goleadores() {
    // COMPLETAR (si hace falta)
}

void Goleadores::anotar_gol(const std::string& jugador) {
    // COMPLETAR
    goles_por_jugador.insertar(jugador, goles(jugador) + 1);

    if (goles(jugador) > goles(maximo) || maximo == "") {maximo = jugador;}
}

int Goleadores::goles(const std::string& jugador) {
    // COMPLETAR
    if (!goles_por_jugador.pertenece(jugador)) {return 0;}
    return goles_por_jugador.obtener(jugador);
}

size_t Goleadores::cantidad_de_jugadores() {
    // COMPLETAR
    return goles_por_jugador.cantidad();
}

std::string Goleadores::maximo_goleador() {
    // COMPLETAR
    return maximo;
}

void Goleadores::imprimir_por_nombre() {
    // OPTATIVO
}

void Goleadores::imprimir_por_goles() {
    // OPTATIVO
}
