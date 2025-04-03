#include <iostream>
#include <vector>

using namespace std;

class Persona{
  private:
          string nombre;
          int rut;
  public:
          Persona(string nombre, int rut);
          ~Persona();
          string getNombre();
          void setNombre(string nombre);
          int getRut();
          void setRut(int rut);
};

Persona::Persona(string nombre, int rut){
  this->nombre = nombre;
  this->rut = rut;                       
}

Persona::~Persona(){
  cout << "destruyendo" << endl;                   
}

string Persona::getNombre(){
   return this->nombre;      
}

void Persona::setNombre(string nombre){
   this->nombre = nombre;      
}


int Persona::getRut(){
   return this->rut;      
}

void Persona::setRut(int rut){
   this->rut = rut;      
}

class Estudiante : public Persona{
private:
  string carrera;
  float ppa;
public:
  Estudiante(string nombre, string carrera, int rut, float ppa); 
  Estudiante(string nombre, int rut);
  void aprender(string contenido);
  string getCarrera();
  void setCarrera(string carrera);
};

class Profesor{
private:
  string nombre;
  string asignatura;
  int rut;
public:
  Profesor(string nombre, string asignatura, int rut);
  Profesor(string nombre, int rut);
  ~Profesor();
  string getNombre();
  string getAsignatura();
  void setAsignatura(string asignatura);
  void ensenar(string contenido);
  void ayudar(Estudiante* e);
  void cambiarCarrera(Estudiante* e, string carrera);
};

Profesor::Profesor(string nombre, string asignatura, int rut){
  this->nombre = nombre;
  if(asignatura != "ingles"){
    this->asignatura = asignatura;
  }
  else{
    this->asignatura = "No tiene asignatura";
  }

  this->rut = rut;
}

Profesor::Profesor(string nombre, int rut){
  this->nombre = nombre;
  this->rut = rut;
  this->asignatura = "No tiene asignatura";
}

Profesor::~Profesor(){
  cout << "Destruyendo objeto de tipo Profesor" << endl;
}

string Profesor::getNombre(){
  return this->nombre;
}

string Profesor::getAsignatura(){
  return this->asignatura;
}
void Profesor::setAsignatura(string asignatura){
  if(asignatura != "ingles"){
    this->asignatura = asignatura;
  }
}

void Profesor::ensenar(string contenido){
  cout << "El profesor " << nombre << " esta enseñando " << contenido << endl;
}

void Profesor::ayudar(Estudiante* e){
  cout << this->nombre << " esta ayudando al estudiante " << e->getNombre() << endl;
}

void Profesor::cambiarCarrera(Estudiante* e, string carrera){
  if(carrera != "antropologia"){
      e->setCarrera(carrera);
  }
}



Estudiante::Estudiante(string nombre, string carrera, int rut, float ppa) : Persona(nombre,rut){
  this->carrera = carrera;
  this->ppa = ppa;
}

Estudiante::Estudiante(string nombre, int rut) : Persona(nombre,rut){
  this->carrera = "No tiene carrera";
  this->ppa = 1.0;
}

string Estudiante::getCarrera(){
  return this->carrera;
}

void Estudiante::setCarrera(string carrera){
  this->carrera = carrera;
}


void Estudiante::aprender(string contenido){
  cout << "El estudiante " << this->getNombre() << " esta aprendiendo " << contenido << endl;
}

class Curso{
private:
  int nrc;
  string nombre;
  Profesor* docente;
  vector<Estudiante*> estudiantes;
public:
  Curso(int nrc, string nombre, Profesor* docente);
  ~Curso();
  void inscribirEstudiante(Estudiante* estudiante);
  void comenzarImparticion();
  void mostrarListaEstudiantes();
};

Curso::Curso(int nrc, string nombre, Profesor* docente){
  this->nrc = nrc;
  this->nombre = nombre;
  this->docente = docente;
}

Curso::~Curso(){
  cout << "Destruyendo objeto de tipo Curso" << endl;
}

void Curso::comenzarImparticion(){
  cout << "Empezando curso de " << this->nombre << endl;
}

void Curso::inscribirEstudiante(Estudiante* estudiante){
  this->estudiantes.push_back(estudiante);
}

void Curso::mostrarListaEstudiantes(){
  cout << "Estudiantes inscritos curso " << this->nombre << " - Profesor " << this->docente->getNombre() << endl;
  for(int i = 0; i < this->estudiantes.size(); i++){
    cout << this->estudiantes[i]->getNombre() << endl;
  }
}

int main() { 

  Profesor* p1 = new Profesor("Juan Pedro", "Matematicas", 123456);
  Profesor* p2 = new Profesor("Pedro", 654321);
  //Profesor* p3 = new Profesor("Lorena", "matemática", 654876);
  Estudiante* e1 = new Estudiante("Lorena",5636);
  Estudiante* e2 = new Estudiante("Juan Luis",65365365);

  Curso* curso1 = new Curso(101, "Matematicas", p1);
  curso1->inscribirEstudiante(e1);
  curso1->inscribirEstudiante(e2);
  curso1->comenzarImparticion();
  curso1->mostrarListaEstudiantes();

  Curso* curso2 = new Curso(102, "Lenguaje", p2);
  curso2->inscribirEstudiante(e1);
  curso2->mostrarListaEstudiantes();

  p1->ayudar(e2);
  p2->ayudar(e1);
  p1->cambiarCarrera(e1, "Ingenieria");
  p1->cambiarCarrera(e2, "antropologia");
  cout << e1->getCarrera() << endl;
  cout << e2->getCarrera() << endl;



}
