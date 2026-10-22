#include "funcion_hash.h"

size_t funcion_hash(const std::string& clave) {
    size_t contador = 5381;
    for(char c: clave){
        contador = contador * 33 + static_cast<unsigned long>(c);
    }
    return contador;
}

size_t funcion_hash(int clave) {
    return static_cast<size_t>(clave);
}
 