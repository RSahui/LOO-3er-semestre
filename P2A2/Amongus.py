class Jugador:
    def __init__(self, id, nombre, color):
        self.nombre = nombre
        self.color = color
        self._vivo = True
        self._ubicacion = "Cafeteria"
        self.__id = id
 
    def get_id(self):
        return self.__id
 
    def esta_vivo(self):
        return self._vivo
 
    def mover(self, destino):
        if self._vivo:
            self._ubicacion = destino
            print(self.nombre, "se movio a", destino)
        else:
            print(self.nombre, "esta muerto y no puede moverse")
 
    def reportar_cuerpo(self, victima):
        print(self.nombre, "reporto el cuerpo de", victima.nombre, "en", victima._ubicacion)
 
    def votar(self, sospechoso):
        print(self.nombre, "voto contra", sospechoso.nombre)
 
    def morir(self):
        self._vivo = False
        print(self.nombre, "ha muerto")
 
 
class Tripulante(Jugador):
    def __init__(self, id, nombre, color, tareas_totales):
        super().__init__(id, nombre, color)
        self.tareas_totales = tareas_totales
        self._tareas_completadas = 0
 
    def hacer_tarea(self, tarea):
        self._tareas_completadas = self._tareas_completadas + 1
        print(self.nombre, "hizo la tarea", tarea)
 
    def progreso(self):
        print(self.nombre, "lleva", self._tareas_completadas, "de", self.tareas_totales, "tareas")
 
 
class Impostor(Jugador):
    def __init__(self, id, nombre, color, enfriamiento):
        super().__init__(id, nombre, color)
        self.enfriamiento = enfriamiento
        self.__eliminaciones = 0
 
    def eliminar(self, victima):
        if victima.esta_vivo():
            print(self.nombre, "elimino a", victima.nombre)
            victima.morir()
            self.__eliminaciones = self.__eliminaciones + 1
 
    def sabotear(self, sistema):
        print(self.nombre, "sabotea", sistema)
 
    def usar_ventilacion(self, destino):
        print(self.nombre, "entra a la ventilacion")
        self.mover(destino)
 
    def get_eliminaciones(self):
        return self.__eliminaciones
 
 
t1 = Tripulante(1, "Ana", "Azul", 5)
t2 = Tripulante(2, "Luis", "Verde", 4)
imp = Impostor(3, "Carlos", "Rojo", 3)
 
t1.mover("Electricidad")
t1.hacer_tarea("Arreglar cables")
t2.mover("Navegacion")
t2.hacer_tarea("Trazar curso")
imp.mover("Electricidad")
imp.sabotear("Luces")
imp.eliminar(t1)
t2.reportar_cuerpo(t1)
t2.votar(imp)
imp.usar_ventilacion("Reactor")
 
t1.progreso()
t2.progreso()
print("Eliminaciones de", imp.nombre, ":", imp.get_eliminaciones())