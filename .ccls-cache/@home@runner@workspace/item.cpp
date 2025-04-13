#include "class.h"

Pregunta::Pregunta(string pregunta, string tipo, string respuesta, string nivelBloom, int tiempo, int anio) {
    this->pregunta = pregunta;
    this->tipo = tipo;
    this->respuesta = respuesta;
    this->nivelBloom = nivelBloom;
    this->tiempo = tiempo;
    this->anio = anio;
}

Pregunta::~Pregunta() {
    cout << "Destruyendo pregunta: " << pregunta << endl;
}

string Pregunta::getPregunta() { return pregunta; }
string Pregunta::getTipo() { return tipo; }
string Pregunta::getRespuesta() { return respuesta; }
string Pregunta::getNivelBloom() { return nivelBloom; }
int Pregunta::getTiempo() { return tiempo; }
int Pregunta::getAnio() { return anio; }

void Pregunta::setPregunta(string nueva) { pregunta = nueva; }
void Pregunta::setRespuesta(string nueva) { respuesta = nueva; }
void Pregunta::setNivelBloom(string nuevo) { nivelBloom = nuevo; }
void Pregunta::setTiempo(int nuevo) { tiempo = nuevo; }
void Pregunta::setAnio(int nuevo) { anio = nuevo; }

void Pregunta::mostrar() {
    cout << "Pregunta: " << pregunta << endl;
    cout << "Tipo: " << tipo << endl;
    cout << "Respuesta: " << respuesta << endl;
    cout << "Nivel Bloom: " << nivelBloom << endl;
    cout << "Tiempo: " << tiempo << " minutos" << endl;
    cout << "Año: " << anio << endl;
    cout << "-------------------------------" << endl;
}

Item::Item() {
    cantidad = 0;
    for (int i = 0; i < 100; i++)
        preguntas[i] = nullptr;
}

Item::~Item() {
    for (int i = 0; i < cantidad; i++)
        delete preguntas[i];
}

bool Item::preguntaRepetida(string pregunta, int anio) {
    for (int i = 0; i < cantidad; i++) {
        int a = preguntas[i]->getAnio();
        if (preguntas[i]->getPregunta() == pregunta && (a == anio || a == anio - 1 || a == anio + 1))
            return true;
    }
    return false;
}

void Item::agregarPregunta(string pregunta, string tipo, string respuesta, string nivelBloom, int tiempo, int anio) {
    if (cantidad >= 100) {
        cout << "Límite de preguntas alcanzado.\n";
        return;
    }

    if (preguntaRepetida(pregunta, anio)) {
        cout << "Pregunta repetida en años consecutivos.\n";
        return;
    }

    if (tipo != "VF" && tipo != "OM") {
        cout << "Tipo inválido (solo 'VF' o 'OM').\n";
        return;
    }

    vector<string> niveles = {"Recordar", "Entender", "Aplicar", "Analizar", "Evaluar", "Crear"};
    bool valido = false;
    for (auto& nivel : niveles)
        if (nivel == nivelBloom)
            valido = true;

    if (!valido) {
        cout << "Nivel Bloom inválido.\n";
        return;
    }

    preguntas[cantidad++] = new Pregunta(pregunta, tipo, respuesta, nivelBloom, tiempo, anio);
    cout << "Pregunta agregada con éxito.\n";
}

void Item::mostrarPreguntas() {
    if (cantidad == 0) {
        cout << "No hay preguntas registradas.\n";
        return;
    }
    for (int i = 0; i < cantidad; i++)
        preguntas[i]->mostrar();
}

void Item::buscarNivelBloom(string nivel) {
    bool encontrado = false;
    for (int i = 0; i < cantidad; i++) {
        if (preguntas[i]->getNivelBloom() == nivel) {
            preguntas[i]->mostrar();
            encontrado = true;
        }
    }
    if (!encontrado)
        cout << "No hay preguntas para ese nivel.\n";
}

void Item::buscarAnio(int anio) {
    bool encontrado = false;
    for (int i = 0; i < cantidad; i++) {
        if (preguntas[i]->getAnio() == anio) {
            preguntas[i]->mostrar();
            encontrado = true;
        }
    }
    if (!encontrado)
        cout << "No hay preguntas para ese año.\n";
}

void Item::calcularTiempoTotal() {
    int total = 0;
    for (int i = 0; i < cantidad; i++)
        total += preguntas[i]->getTiempo();
    cout << "Tiempo total estimado: " << total << " minutos.\n";
}

void Item::actualizarPregunta(string pregunta, int anio) {
    for (int i = 0; i < cantidad; i++) {
        if (preguntas[i]->getPregunta() == pregunta && preguntas[i]->getAnio() == anio) {
            string nuevoTipo, nuevaRespuesta, nuevoNivel;
            int nuevoTiempo;

            cout << "Nuevo tipo (VF / OM): ";
            getline(cin, nuevoTipo);
            cout << "Nueva respuesta: ";
            getline(cin, nuevaRespuesta);
            cout << "Nuevo nivel Bloom: ";
            getline(cin, nuevoNivel);
            cout << "Nuevo tiempo (min): ";
            cin >> nuevoTiempo;
            cin.ignore();

            preguntas[i]->setRespuesta(nuevaRespuesta);
            preguntas[i]->setNivelBloom(nuevoNivel);
            preguntas[i]->setTiempo(nuevoTiempo);

            cout << "Pregunta actualizada con éxito.\n";
            return;
        }
    }
    cout << "Pregunta no encontrada para ese año.\n";
}

void Item::eliminarPregunta(string pregunta, int anio) {
    for (int i = 0; i < cantidad; i++) {
        if (preguntas[i]->getPregunta() == pregunta && preguntas[i]->getAnio() == anio) {
            delete preguntas[i];
            for (int j = i; j < cantidad - 1; j++) {
                preguntas[j] = preguntas[j + 1];
            }
            preguntas[--cantidad] = nullptr;
            cout << "Pregunta eliminada con éxito.\n";
            return;
        }
    }
    cout << "Pregunta no encontrada para ese año.\n";
}

void ejecutarMenu() {
    Item banco;
    int opcion;

    do {
        cout << "\n===== MENÚ =====" << endl;
        cout << "1. Agregar pregunta\n2. Mostrar preguntas\n3. Buscar por nivel\n4. Buscar por año\n5. Calcular tiempo\n6. Actualizar pregunta\n7. Eliminar pregunta\n0. Salir\nOpción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                string pregunta, tipo, respuesta, nivel;
                int tiempo, anio;

                cout << "Pregunta: ";
                getline(cin, pregunta);
                cout << "Tipo (VF / OM): ";
                getline(cin, tipo);
                cout << "Respuesta: ";
                getline(cin, respuesta);
                cout << "Nivel Bloom: ";
                getline(cin, nivel);
                cout << "Tiempo (min): ";
                cin >> tiempo;
                cout << "Año: ";
                cin >> anio;
                cin.ignore();

                banco.agregarPregunta(pregunta, tipo, respuesta, nivel, tiempo, anio);
                break;
            }
            case 2:
                banco.mostrarPreguntas();
                break;
            case 3: {
                string nivel;
                cout << "Nivel Bloom a buscar: ";
                getline(cin, nivel);
                banco.buscarNivelBloom(nivel);
                break;
            }
            case 4: {
                int anio;
                cout << "Año a buscar: ";
                cin >> anio;
                cin.ignore();
                banco.buscarAnio(anio);
                break;
            }
            case 5:
                banco.calcularTiempoTotal();
                break;
            case 6: {
                string pregunta;
                int anio;
                cout << "Pregunta a actualizar: ";
                getline(cin, pregunta);
                cout << "Año: ";
                cin >> anio;
                cin.ignore();
                banco.actualizarPregunta(pregunta, anio);
                break;
            }
            case 7: {
                string pregunta;
                int anio;
                cout << "Pregunta a eliminar: ";
                getline(cin, pregunta);
                cout << "Año: ";
                cin >> anio;
                cin.ignore();
                banco.eliminarPregunta(pregunta, anio);
                break;
            }
            case 0:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}
