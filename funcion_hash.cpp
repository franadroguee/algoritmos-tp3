#include "funcion_hash.h"
//funcion mala
size_t hash_largo_nombre(const std::string& clave){
    size_t contador = 0;
    for(char c : clave){
        contador ++;
    }
    return contador;
}
//funcion media
size_t hash_suma(const std::string& clave){
    size_t contador = 0;
    for(char c : clave){
        contador = contador + static_cast<unsigned long>(c);
    }
    return contador;
}
//funcion buena
size_t hash_djb2(const std::string& clave) {
    size_t contador = 5381;
    for(char c: clave){
        contador = contador * 33 + static_cast<unsigned long>(c);
    }
    return contador;
}

size_t funcion_hash(const std::string& clave) {
    return hash_djb2(clave);
}

size_t funcion_hash(int clave) {
    return static_cast<size_t>(clave);
}
 