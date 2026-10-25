#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include <cstddef>
#include <vector>
#include "funcion_hash.h"

// TAD TablaHash<K, V>: tabla de hash con direccionamiento cerrado.
//
// Guarda pares <clave, valor> repartidos en buckets: el par de una clave esta
// en el bucket numero funcion_hash(clave) % capacidad().
//
// Requisitos sobre los tipos:
//   - K: se puede copiar, comparar con == y existe funcion_hash(K).
//   - V: se puede copiar.
//
// Invariante de representacion:
//   buckets.size() >= 1
//   todos lso pares provienen de funcion_hash(par.clave) % buckets.size() == indice(bucket donde se guarda el par)
//   no pueden haber dos pares con la misma clave
//   cantidades es la cantidad de pares guardados entre todos los buckets y es <= factor de carga maximo * buckets.size()
//   redimensionar duplica el buckets.size() cuando al cantidad de pares guardados supera el factor de carga maximo * buckets.size()
//      
// 
// Complejidades: n es la cantidad de claves guardadas y c la capacidad.
// "Promedio" supone que la funcion de hash reparte las claves de manera
// uniforme y que calcularla (y comparar dos claves) cuesta O(1).
template <typename K, typename V>
class TablaHash {
  private:
    // la representacion la eligen ustedes (que guardan, y que hay
    // en cada bucket). Pueden agregar tambien funciones auxiliares privadas.
    // Lo que el Iterador necesite de aca tiene que estar declarado antes que el.
    struct Par{
        K clave;
        V valor;

    };
    size_t cantidades;
    std::vector<std::vector<Par>> buckets;
    void redimensionar();  


  public:
    static const size_t FACTOR_DE_CARGA_MAXIMO = 2;

    // Pre:  capacidad_inicial >= 1.
    // Post: crea una tabla vacia, con capacidad_inicial buckets.
    // Costo: O(capacidad_inicial).
    TablaHash(size_t capacidad_inicial);

    // Post: libera toda la memoria pedida por la tabla.
    // Costo: O(n + c) en peor caso.
    ~TablaHash();

    // Copiar una tabla copiaria los punteros y no su contenido: lo prohibimos.
    TablaHash(const TablaHash&) = delete;
    TablaHash& operator=(const TablaHash&) = delete;

    // Pre:  la clave NO esta en la tabla.
    // Post: la tabla tiene ademas el par <clave, valor>, y
    //       cantidad() <= FACTOR_DE_CARGA_MAXIMO * capacidad().
    // Costo: O(1) amortizado (en peor caso O(n), cuando toca redimensionar).
    void insertar(const K& clave, const V& valor);

    // Pre:  la clave esta en la tabla.
    // Post: la tabla ya no tiene la clave (ni su valor).
    // Costo: O(1) en promedio, O(n) en peor caso.
    void eliminar(const K& clave);

    // Pre:  -
    // Post: si la clave esta, devuelve un puntero a su valor (que se puede
    //       usar para leerlo o modificarlo); si no, devuelve nullptr.
    //       El puntero deja de ser valido al insertar o eliminar.
    // Costo: O(1) en promedio, O(n) en peor caso.
    V* buscar(const K& clave);

    // Post: devuelve la cantidad de claves guardadas. Costo: O(1).
    size_t cantidad();

    // Post: devuelve la cantidad de buckets. Costo: O(1).
    size_t capacidad();

    // Post: devuelve la cantidad de claves que comparten bucket con alguna
    //       clave que llego antes, es decir:
    //       cantidad() - (cantidad de buckets que no estan vacios).
    // Costo: O(c) en peor caso.
    size_t colisiones();

    // Iterador de la tabla: recorre todos los pares <clave, valor>, cada uno
    // exactamente una vez, en algun orden (ver TAD Iterador en el enunciado).
    // Deja de ser valido si se inserta o se elimina en la tabla.
    //

    // Invariante de representacion:
    //      tabla apunta a la tabla que recorremos
    //      0 < i <= tabla-> buckets.size()
    //      el par actual es el tabla-> buckets[i][j] si i < tabla->buckets.size() y j < tabla -> buckets[i].size()
    //      si i == buckets.size() es el ultimo bucket de la tabla 
    //      los buckets ya recorridos son [0; i-1] y los pares ya recorridos son [0;j-1] 
    class Iterador {
      private:
        // usar la parte privada de la tabla.
        TablaHash* tabla = nullptr;
        size_t i = 0;
        size_t j = 0;

        // Para que crear_iterador() pueda armar el iterador.
        friend class TablaHash;

      public:
        // Pre:  -
        // Post: indica si quedan pares por recorrer.
        // Costo: O(1).
        bool hay_mas() {
            return i < tabla -> buckets.size();
        }

        // Pre:  hay_mas().
        // Post: devuelve la clave del par actual, sin modificar el iterador.
        // Costo: O(1).
        K clave() {
            return tabla ->buckets[i][j].clave;
        }

        // Pre:  hay_mas().
        // Post: devuelve el valor del par actual, sin modificar el iterador.
        // Costo: O(1).
        V valor() {
            return tabla ->buckets[i][j].valor;
        }

        // Pre:  hay_mas().
        // Post: el iterador pasa al par siguiente (o al final, si no hay mas).
        // Costo: O(c) en peor caso. Recorrer la tabla entera (crear el
        //        iterador y avanzar hasta el final) cuesta O(n + c).
        void avanzar() {
            if(j + 1  == tabla->buckets[i].size()){
                j = 0;
                i ++;
                while(i < tabla-> buckets.size() && tabla->buckets[i].size() == 0){
                    i++;
                }
            } else{
                j++;
            }

        }
    };

    // Pre:  -
    // Post: devuelve un iterador al primer par de la tabla (si la tabla esta
    //       vacia, el iterador ya esta al final).
    // Costo: O(c) en peor caso.
    Iterador crear_iterador();
};

// ---------------------------------------------------------------------------
// Implementacion. Al ser una clase template, va en el mismo .h.
// ---------------------------------------------------------------------------

template <typename K, typename V>
TablaHash<K, V>::TablaHash(size_t capacidad_inicial) {
    cantidades = 0;
    buckets.assign(capacidad_inicial , {});
}

template <typename K, typename V>
TablaHash<K, V>::~TablaHash() {
    // no usamos lista enlazada osea que no hayq ye liberar memeoria ya que no usamos new
}
template <typename K, typename V>
void TablaHash<K, V>::redimensionar(){
    std::vector<std::vector<Par>> buckets_viejos = buckets;
    buckets.assign(buckets.size() * 2, {});
    for(auto& b: buckets_viejos){
        for(auto& par: b){
            size_t i = funcion_hash(par.clave) % buckets.size();
            buckets[i].push_back(par);
        }
        
    }
}
template <typename K, typename V>
void TablaHash<K, V>::insertar(const K& clave, const V& valor) {
    if(cantidades + 1 > FACTOR_DE_CARGA_MAXIMO * buckets.size() ){
        redimensionar();
    }
    size_t i = funcion_hash(clave) % buckets.size();
    buckets[i].push_back(Par{clave,valor});
    cantidades++;
}

template <typename K, typename V>
void TablaHash<K, V>::eliminar(const K& clave) {
    size_t i = funcion_hash(clave) % buckets.size();
    auto& bucket_del_indice = buckets[i];
    for(size_t j = 0; j < bucket_del_indice.size(); j++){
        if(bucket_del_indice[j].clave == clave){
            bucket_del_indice.erase(bucket_del_indice.begin() + j);
            cantidades--;
            return;
        }
    }
}

template <typename K, typename V>
V* TablaHash<K, V>::buscar(const K& clave) {
    size_t i = funcion_hash(clave) % buckets.size();
    auto& bucket_del_indice = buckets[i];
    for(size_t j = 0; j < bucket_del_indice.size(); j++){
        if(bucket_del_indice[j].clave == clave){
            V*puntero = &bucket_del_indice[j].valor;
            return puntero;
        }
    }
    return nullptr;
}

template <typename K, typename V>
size_t TablaHash<K, V>::cantidad() {
    return cantidades;
}

template <typename K, typename V>
size_t TablaHash<K, V>::capacidad() {
    return buckets.size();
    
}

template <typename K, typename V>
size_t TablaHash<K, V>::colisiones() {
    size_t contador = 0;
    for(auto&b : buckets){
        if(b.size() > 0){
            contador ++;
        }
    }
    return cantidad() - contador;

}

// El "typename" le avisa al compilador que TablaHash<K, V>::Iterador es un tipo.
template <typename K, typename V>
typename TablaHash<K, V>::Iterador TablaHash<K, V>::crear_iterador() {
    Iterador it;
    it.tabla = this;
    while(it.i < buckets.size() && buckets[it.i].size() == 0){
        it.i ++;
    }   
    return it;
}

#endif
