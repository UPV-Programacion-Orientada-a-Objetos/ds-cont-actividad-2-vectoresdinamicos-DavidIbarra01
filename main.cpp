#include <iostream>

int* id_Paquete;
float* peso_Paquete;
char** destino_Paquete; 
int* nivel_Prioridad_Paquete;
char* estado_Paquete;

// Capacidades
int capacidad_Paquetes = 50;
int total_paquetes = 0;

int top_pila = -1;
int frente_cola = 0;
int final_cola = -1;

// --- Inicio del Programa ---
int main() {
    // --- Bloque de Inicialización ---
    std::cout << "--- Sistema de Despacho Logístico MegaEnvío ---\n";
    std::cout << "Inicializando sistema con capacidad para " << capacidad_Paquetes << " paquetes...\n";

 
    id_Paquete = new int[capacidad_Paquetes];
    peso_Paquete = new float[capacidad_Paquetes];
    destino_Paquete = new char*[capacidad_Paquetes];
    for (int i = 0; i < capacidad_Paquetes; ++i) {
        destino_Paquete[i] = new char[50]; 
    }
    nivel_Prioridad_Paquete = new int[capacidad_Paquetes];
    estado_Paquete = new char[capacidad_Paquetes];

    bool seguirCorriendo = true;

    // --- Bucle Principal del Menú ---
    while (seguirCorriendo) {
        std::cout << "\n--- Menú Principal ---\n";
        std::cout << "1. Recibir Nuevo Paquete (PUSH a Pila)\n";
        std::cout << "2. Procesar Recepción (POP de Pila y ENCOLAR a Cola)\n";
        std::cout << "3. Despachar Paquete (DECOLAR de Cola con Prioridad)\n";
        std::cout << "4. Reporte de Estados\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione una opción: ";

        int opcion = 0;
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                if (total_paquetes == capacidad_Paquetes)
                {
                    std::cout << "ERROR: Capacidad llena. Duplicando capacidad:\n";
                    
                }else{
                    std::cout << "\nIngrese el ID: "; std::cin >> id_Paquete[total_paquetes];
                    std::cout << "\nPeso: "; std::cin >> peso_Paquete[total_paquetes];
                    std::cout << "\nDestino: "; std::cin >> destino_Paquete[total_paquetes];
                    std::cout << "\nNivel de prioridad: "; std::cin >> nivel_Prioridad_Paquete[total_paquetes];
                    estado_Paquete[total_paquetes] = 'R';
                total_paquetes++;
                top_pila++;
                }
                
                
                
                break;
            }
            case 2: {
          
                std::cout << "Opción 2 seleccionada (aún por implementar).\n";
                break;
            }
            case 3: {
              
                std::cout << "Opción 3 seleccionada (aún por implementar).\n";
                break;
            }
            case 4: {
             
                std::cout << "Opción 4 seleccionada (aún por implementar).\n";
                break;
            }
            case 5: {
                seguirCorriendo = false;
                break;
            }
            default: {
                std::cout << "Error: Opción no válida. Intente de nuevo.\n";
                break;
            }
        }
    }

    std::cout << "\nLiberando memoria asignada...\n";
    
    // Liberar memoria de los vectores
    delete[] id_Paquete;
    delete[] peso_Paquete;

    for (int i = 0; i < capacidad_Paquetes; ++i) {
        delete[] destino_Paquete[i];
    }
    delete[] destino_Paquete;
    delete[] nivel_Prioridad_Paquete;
    delete[] estado_Paquete;

    std::cout << "Sistema cerrado. ¡Memoria liberada!\n";

    return 0;
}