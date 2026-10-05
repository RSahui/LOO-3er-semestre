#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ---------- Coche ----------
struct Coche {
    string matricula;
    string marca;
    string modelo;
};

// ---------- Empleado (clase base) ----------
class Empleado {
protected:
    string nombre, apellidos, dni, direccion, telefono;
    int antiguedad;
    double salario;
    Empleado* supervisor;

public:
    Empleado(string n, string a, string d, string dir, string tel, double sal) {
        nombre = n;
        apellidos = a;
        dni = d;
        direccion = dir;
        telefono = tel;
        salario = sal;
        antiguedad = 0;
        supervisor = NULL;
    }

    virtual ~Empleado() {}

    // Cada tipo de empleado sube el salario de forma distinta
    virtual void incrementarSalario() = 0;

    virtual void imprimir(ostream& os) const {
        os << "Nombre: " << nombre << " " << apellidos << endl;
        os << "DNI: " << dni << endl;
        os << "Direccion: " << direccion << endl;
        os << "Telefono: " << telefono << endl;
        os << "Antiguedad: " << antiguedad << " anios" << endl;
        os << "Salario: " << salario << endl;
        if (supervisor != NULL)
            os << "Supervisor: " << supervisor->nombre << " " << supervisor->apellidos << endl;
        else
            os << "Supervisor: ninguno" << endl;
    }

    void cambiarSupervisor(Empleado* s) { supervisor = s; }
    double getSalario() const { return salario; }
    string getNombre() const { return nombre; }

    friend ostream& operator<<(ostream& os, const Empleado& e) {
        e.imprimir(os);
        return os;
    }
};

// ---------- Secretario ----------
class Secretario : public Empleado {
private:
    string despacho;
    string fax;

public:
    Secretario(string n, string a, string d, string dir, string tel, double sal,
               string desp, string f)
        : Empleado(n, a, d, dir, tel, sal) {
        despacho = desp;
        fax = f;
    }

    void incrementarSalario() { salario = salario * 1.05; }

    void imprimir(ostream& os) const {
        os << "Puesto: Secretario" << endl;
        Empleado::imprimir(os);
        os << "Despacho: " << despacho << endl;
        os << "Fax: " << fax << endl;
    }
};

// ---------- Vendedor ----------
class Vendedor : public Empleado {
private:
    Coche coche;
    string movil;
    string area;
    vector<string> clientes;
    double comision;

public:
    Vendedor(string n, string a, string d, string dir, string tel, double sal,
             Coche c, string mov, string ar, double com)
        : Empleado(n, a, d, dir, tel, sal) {
        coche = c;
        movil = mov;
        area = ar;
        comision = com;
    }

    void incrementarSalario() { salario = salario * 1.10; }

    void altaCliente(string cliente) { clientes.push_back(cliente); }

    void bajaCliente(string cliente) {
        for (int i = 0; i < (int)clientes.size(); i++) {
            if (clientes[i] == cliente) {
                clientes.erase(clientes.begin() + i);
                return;
            }
        }
    }

    void cambiarCoche(Coche c) { coche = c; }

    void imprimir(ostream& os) const {
        os << "Puesto: Vendedor" << endl;
        Empleado::imprimir(os);
        os << "Coche: " << coche.marca << " " << coche.modelo
           << " (" << coche.matricula << ")" << endl;
        os << "Movil: " << movil << endl;
        os << "Area de venta: " << area << endl;
        os << "Comision: " << comision << "%" << endl;
        os << "Clientes: ";
        for (int i = 0; i < (int)clientes.size(); i++)
            os << clientes[i] << "; ";
        os << endl;
    }
};

// ---------- Jefe de zona ----------
class JefeZona : public Empleado {
private:
    string despacho;
    Secretario* secretario;
    vector<Vendedor*> vendedores;
    Coche coche;

public:
    JefeZona(string n, string a, string d, string dir, string tel, double sal,
             string desp, Secretario* sec, Coche c)
        : Empleado(n, a, d, dir, tel, sal) {
        despacho = desp;
        secretario = sec;
        coche = c;
        if (secretario != NULL)
            secretario->cambiarSupervisor(this);
    }

    void incrementarSalario() { salario = salario * 1.20; }

    void cambiarSecretario(Secretario* sec) {
        secretario = sec;
        if (secretario != NULL)
            secretario->cambiarSupervisor(this);
    }

    void cambiarCoche(Coche c) { coche = c; }

    void altaVendedor(Vendedor* v) {
        vendedores.push_back(v);
        v->cambiarSupervisor(this);
    }

    void bajaVendedor(Vendedor* v) {
        for (int i = 0; i < (int)vendedores.size(); i++) {
            if (vendedores[i] == v) {
                vendedores.erase(vendedores.begin() + i);
                v->cambiarSupervisor(NULL);
                return;
            }
        }
    }

    void imprimir(ostream& os) const {
        os << "Puesto: Jefe de zona" << endl;
        Empleado::imprimir(os);
        os << "Despacho: " << despacho << endl;
        os << "Coche: " << coche.marca << " " << coche.modelo
           << " (" << coche.matricula << ")" << endl;
        if (secretario != NULL)
            os << "Secretario: " << secretario->getNombre() << endl;
        os << "Vendedores a cargo: ";
        for (int i = 0; i < (int)vendedores.size(); i++)
            os << vendedores[i]->getNombre() << "; ";
        os << endl;
    }
};

// ---------- Programa de prueba ----------
int main() {
    Coche c1 = {"1234ABC", "Seat", "Ibiza"};
    Coche c2 = {"5678DEF", "Renault", "Clio"};
    Coche c3 = {"9012GHI", "Audi", "A4"};

    Secretario sec("Ana", "Lopez", "11111111A", "Calle Sol 1", "600111111", 1000,
                   "Despacho 1", "911111111");
    Vendedor v1("Luis", "Perez", "22222222B", "Calle Luna 2", "600222222", 1000,
                c1, "655222222", "Norte", 5);
    Vendedor v2("Marta", "Gil", "33333333C", "Calle Mar 3", "600333333", 1000,
                c2, "655333333", "Sur", 7);
    JefeZona jefe("Pedro", "Ruiz", "44444444D", "Calle Rio 4", "600444444", 1000,
                  "Despacho 2", &sec, c3);

    jefe.altaVendedor(&v1);
    jefe.altaVendedor(&v2);
    v1.altaCliente("Cliente A");
    v1.altaCliente("Cliente B");
    v2.altaCliente("Cliente C");

    cout << "===== ANTES DE LA SUBIDA =====" << endl;
    cout << sec << endl;
    cout << v1 << endl;
    cout << v2 << endl;
    cout << jefe << endl;

    // Prueba del polimorfismo: un solo vector de Empleado*
    vector<Empleado*> todos;
    todos.push_back(&sec);
    todos.push_back(&v1);
    todos.push_back(&v2);
    todos.push_back(&jefe);

    for (int i = 0; i < (int)todos.size(); i++)
        todos[i]->incrementarSalario();

    cout << "===== SALARIOS DESPUES DE LA SUBIDA (base 1000) =====" << endl;
    for (int i = 0; i < (int)todos.size(); i++)
        cout << todos[i]->getNombre() << ": " << todos[i]->getSalario() << endl;
    cout << endl;

    // Otras operaciones
    v1.bajaCliente("Cliente A");
    v1.cambiarCoche(c3);
    jefe.bajaVendedor(&v2);

    cout << "===== DESPUES DE CAMBIOS =====" << endl;
    cout << v1 << endl;
    cout << v2 << endl;
    cout << jefe << endl;

    return 0;
}
