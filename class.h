#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Pregunta {
private:
    string pregunta;
    string tipo;         // "VF" o "OM"
    string respuesta;
    string nivelBloom;
    int tiempo;
    int anio;

public:
    Pregunta(string pregunta, string tipo, string respuesta, string nivelBloom, int tiempo, int anio);
    ~Pregunta();

    // Getters
    string getPregunta();
    string getTipo();
    string getRespuesta();
    string getNivelBloom();
    int getTiempo();
    int getAnio();

    // Setters
    void setPregunta(string nuevaPregunta);
    void setRespuesta(string nuevaRespuesta);
    void setNivelBloom(string nuevoNivel);
    void setTiempo(int nuevoTiempo);
    void setAnio(int nuevoAnio);

    void mostrar();
};

class Item {
private:
    Pregunta* preguntas[100];
    int cantidad;

public:
    Item();
    ~Item();

    void agregarPregunta(string pregunta, string tipo, string respuesta, string nivelBloom, int tiempo, int anio);
    void mostrarPreguntas();
    void buscarNivelBloom(string nivelBloom);
    void buscarAnio(int anio);
    void calcularTiempoTotal();
    bool preguntaRepetida(string pregunta, int anio);

    // NUEVAS FUNCIONES
    void actualizarPregunta(string pregunta, int anio);
    void eliminarPregunta(string pregunta, int anio);
};

void ejecutarMenu();

#endif
