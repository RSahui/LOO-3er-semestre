/******************************************************************************
Ricardo Sahui, Valeria Urrutia, Jesus Abreu
*******************************************************************************/
using System;

public class PersonajeMinecraft
{
    private string nombre;
    private int vida;
    private int nivel;

    public PersonajeMinecraft()
    {
        this.nombre = "Steve";
        this.vida = 20;
        this.nivel = 1;
    }

    public PersonajeMinecraft(string nombre)
    {
        this.nombre = nombre;
        this.vida = 20;
        this.nivel = 1;
    }

    public PersonajeMinecraft(string nombre, int vida, int nivel)
    {
        this.nombre = nombre;
        this.vida = vida;
        this.nivel = nivel;
    }

    public string Nombre
    {
        get { return nombre; }
    }

    public int Vida
    {
        get { return vida; }
    }

    public int Nivel
    {
        get { return nivel; }
    }

    public override string ToString()
    {
        return "Personaje: " + nombre + " | Vida: " + vida + " | Nivel: " + nivel;
    }

    public void Atacar()
    {
        Console.WriteLine(nombre + " realiza un ataque básico.");
    }

    public void Atacar(int danio)
    {
        Console.WriteLine(nombre + " realiza un ataque causando " + danio + " de daño.");
    }

    public void Atacar(string objetivo, int danio)
    {
        Console.WriteLine(nombre + " ataca a " + objetivo + " causando " + danio + " de daño.");
    }
}

public class Guerrero : PersonajeMinecraft
{
    private string tipoEspada;

    public Guerrero(string nombre, int vida, int nivel, string tipoEspada)
        : base(nombre, vida, nivel)
    {
        this.tipoEspada = tipoEspada;
    }

    public void GolpeEspecial()
    {
        Console.WriteLine(Nombre + " realiza un golpe especial con su espada de " + tipoEspada + ".");
    }

    public override string ToString()
    {
        return base.ToString() + " | Tipo de espada: " + tipoEspada;
    }
}

public class Constructor : PersonajeMinecraft
{
    private string materialFavorito;

    public Constructor(string nombre, int vida, int nivel, string materialFavorito)
        : base(nombre, vida, nivel)
    {
        this.materialFavorito = materialFavorito;
    }

    public void Construir()
    {
        Console.WriteLine(Nombre + " está construyendo una estructura utilizando " + materialFavorito + ".");
    }

    public override string ToString()
    {
        return base.ToString() + " | Material favorito: " + materialFavorito;
    }
}

public class Prueba
{
    public static void Main(string[] args)
    {
        PersonajeMinecraft p1 = new PersonajeMinecraft();
        PersonajeMinecraft p2 = new PersonajeMinecraft("Alex");
        PersonajeMinecraft p3 = new PersonajeMinecraft("Herobrine", 50, 10);

        Console.WriteLine("--- Personajes base ---");
        Console.WriteLine(p1);
        Console.WriteLine(p2);
        Console.WriteLine(p3);

        Console.WriteLine("\n--- Sobrecarga de Atacar ---");
        p1.Atacar();
        p2.Atacar(5);
        p3.Atacar("Creeper", 12);

        Guerrero guerrero = new Guerrero("Arthur", 40, 5, "diamante");
        Console.WriteLine("\n--- Guerrero ---");
        Console.WriteLine(guerrero);
        guerrero.Atacar();
        guerrero.Atacar(8);
        guerrero.Atacar("Zombie", 10);
        guerrero.GolpeEspecial();

        Constructor constructor = new Constructor("Bob", 30, 3, "piedra");
        Console.WriteLine("\n--- Constructor ---");
        Console.WriteLine(constructor);
        constructor.Atacar();
        constructor.Atacar(2);
        constructor.Atacar("Esqueleto", 4);
        constructor.Construir();
    }
}
