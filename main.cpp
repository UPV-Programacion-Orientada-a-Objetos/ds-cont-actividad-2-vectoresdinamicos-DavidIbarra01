#include <iostream>

int* id_Paquete;
float* peso_Paquete;
char** destino_Paquete; 
int* nivel_Prioridad_Paquete;
char* estado_Paquete;

// Capacidadess
int capacidad_Paquetes = 50;
int total_paquetes = 0;

int top_pila = -1;
int frente_cola = -1;
int final_cola = -1;

void copiarString(char* destino, const char* origen, int maxLen) {
    int i = 0;
    while (origen[i] != '\0' && i < maxLen - 1) {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

void leerDestino(char* buffer, int maxLen) {
    std::cin.ignore();
    std::cin.getline(buffer, maxLen);
}

// --- Inici ---
int main() {
    std::cout << "--- Sistema de Despacho Logistico MegaEnvio ---\n";
    std::cout << "Inicializando sistema con capacidad para " << capacidad_Paquetes << " paquetes...\n";

    id_Paquete = new int[capacidad_Paquetes];
    peso_Paquete = new float[capacidad_Paquetes];
    destino_Paquete = new char*[capacidad_Paquetes];
    for (int i = 0; i < capacidad_Paquetes; ++i) {
        destino_Paquete[i] = new char[100];
    }
    nivel_Prioridad_Paquete = new int[capacidad_Paquetes];
    estado_Paquete = new char[capacidad_Paquetes];

    bool seguirCorriendo = true;

   //MENU
    while (seguirCorriendo) {
        std::cout << "\n--- Menu Principal ---\n";
        std::cout << "1. Recibir Nuevo Paquete (PUSH a Pila)\n";
        std::cout << "2. Procesar Recepcion (POP de Pila y ENCOLAR a Cola)\n";
        std::cout << "3. Despachar Paquete (DESENCOLAR de Cola con Prioridad)\n";
        std::cout << "4. Reporte de Estados\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione una opcion: ";

        int opcion = 0;
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                
         if (total_paquetes >= capacidad_Paquetes) {
    
          std::cout << "\n¡Capacidad maxima alcanzada! Expandiendo memoria...\n";

    int nueva_capacidad = capacidad_Paquetes * 2;

        int* aux_id = new int[nueva_capacidad];
        float* aux_peso = new float[nueva_capacidad];
        char** aux_destino = new char*[nueva_capacidad];
        for (int i = 0; i < nueva_capacidad; ++i) {
         aux_destino[i] = new char[100];
         }
         int* aux_prioridad = new int[nueva_capacidad];
         char* aux_estado = new char[nueva_capacidad];

      for (int i = 0; i < capacidad_Paquetes; ++i) {
          aux_id[i] = id_Paquete[i];
          aux_peso[i] = peso_Paquete[i];
          copiarString(aux_destino[i], destino_Paquete[i], 100);
          aux_prioridad[i] = nivel_Prioridad_Paquete[i];
          aux_estado[i] = estado_Paquete[i];
                    }

     delete[] id_Paquete;
           delete[] peso_Paquete;
           for (int i = 0; i < capacidad_Paquetes; ++i) {
            delete[] destino_Paquete[i];
           }
           delete[] destino_Paquete;
           delete[] nivel_Prioridad_Paquete;
           delete[] estado_Paquete;

       id_Paquete = aux_id;
       peso_Paquete = aux_peso;
       destino_Paquete = aux_destino;
       nivel_Prioridad_Paquete = aux_prioridad;
       estado_Paquete = aux_estado;

      capacidad_Paquetes = nueva_capacidad;
      std::cout << "¡Expansion completa! Nueva capacidad: " << capacidad_Paquetes << " paquetes.\n\n";
                }
            
                std::cout << "Ingrese el ID del paquete: ";
                std::cin >> id_Paquete[total_paquetes];

                std::cout << "Ingrese el Peso: ";
                std::cin >> peso_Paquete[total_paquetes];

                std::cout << "Ingrese el Destino: ";
                leerDestino(destino_Paquete[total_paquetes], 100);

                std::cout << "Ingrese la Prioridad (1=Alta, 2=Media, 3=Baja): ";
                std::cin >> nivel_Prioridad_Paquete[total_paquetes];

                estado_Paquete[total_paquetes] = 'R';

                std::cout << "\nPaquete ID " << id_Paquete[total_paquetes] 
              << " recibido y agregado a la Pila de Recepcion.\n";
                std::cout << "Estado: 'R'. Pila.top_pila = " << total_paquetes << ".\n";

                top_pila = total_paquetes;
                total_paquetes++;
                
                break;
            }
            case 2: {
                
                if (top_pila == -1) {
                    std::cout << "\nError: No hay paquetes en la Pila de Recepcion.\n";
                    break;
                } 
                estado_Paquete[top_pila] = 'E';
                
                std::cout << "\nPOP de Pila: Paquete ID " << id_Paquete[top_pila] 
             << " transferido a Cola.\n";
                std::cout << "Estado: 'E'. ";
                if (frente_cola == -1) {
                    frente_cola = top_pila;
                }
                final_cola = top_pila;

                int nuevo_top = -1;
                for (int i = top_pila - 1; i >= 0; i--) {
                    if (estado_Paquete[i] == 'R') {
                        nuevo_top = i;
                        break;
                    }
                }
                top_pila = nuevo_top;

                std::cout << "frente_cola=" << frente_cola << ", final_cola=" << final_cola << ".\n";
                
                std::cout << "(Cola: [";
                bool primero = true;
                for (int i = 0; i < total_paquetes; i++) {
                    if (estado_Paquete[i] == 'E') {
                        if (!primero) std::cout << ", ";
                        std::cout << id_Paquete[i];
                        primero = false;
                    }
                }
                std::cout << "])\n";
                
                break;
            }
            case 3: {
            
                if (frente_cola == -1) {
                    std::cout << "\nError: No hay paquetes en la Cola de Despacho.\n";
                    break;
                }

                std::cout << "\nAnalizando Cola...\n";

                int indice_prioritario = -1;
                for (int i = 0; i < total_paquetes; i++) {
                    if (estado_Paquete[i] == 'E' && nivel_Prioridad_Paquete[i] == 1) {
                        indice_prioritario = i;
                        break;
                    }
                }

                int indice_a_despachar;
                if (indice_prioritario != -1) {
                    std::cout << "Detectada ALTA PRIORIDAD.\n";
                    indice_a_despachar = indice_prioritario;
                } else {

                    indice_a_despachar = frente_cola;
                }

                // Despachar el paquete
                std::cout << "DESPACHADO: Paquete ID " << id_Paquete[indice_a_despachar]
                          << " (Prioridad " << nivel_Prioridad_Paquete[indice_a_despachar] << ").\n";
                
                estado_Paquete[indice_a_despachar] = 'D';

                int nuevo_frente = -1;
                bool encontrado = false;
                for (int i = 0; i < total_paquetes; i++) {
                    if (estado_Paquete[i] == 'E') {
                        nuevo_frente = i;
                        encontrado = true;
                        break;
                    }
                }

                if (!encontrado) {
                    // No hay más en cola
                    frente_cola = -1;
                    final_cola = -1;
                    std::cout << "Cola vacia. No hay mas paquetes por despachar.\n";
                } else {
                    frente_cola = nuevo_frente;
                    std::cout << "frente_cola actualizado a: " << frente_cola << ".\n";
                }

                break;
            }
            case 4: {
                // REPORTE
                int count_R = 0, count_E = 0, count_D = 0;
                
                for (int i = 0; i < total_paquetes; i++) {
                    if (estado_Paquete[i] == 'R') count_R++;
                    else if (estado_Paquete[i] == 'E') count_E++;
                    else if (estado_Paquete[i] == 'D') count_D++;
                }

                std::cout << "\n--- Reporte de Estados ---\n";
                std::cout << "Total de paquetes en el sistema: " << total_paquetes << "\n";
                std::cout << "Capacidad actual: " << capacidad_Paquetes << "\n\n";
                
                std::cout << "Paquetes RECIBIDOS (Pila 'R'): " << count_R << "\n";
                std::cout << "Paquetes EN COLA (Cola 'E'): " << count_E << "\n";
                std::cout << "Paquetes DESPACHADOS ('D'): " << count_D << "\n\n";

                if (count_R > 0) {
                    std::cout << "--- Pila de Recepcion (LIFO) ---\n";
                    for (int i = total_paquetes - 1; i >= 0; i--) {
             if (estado_Paquete[i] == 'R') {
             std::cout << "  ID: " << id_Paquete[i] 
              << ", Peso: " << peso_Paquete[i]
              << ", Destino: " << destino_Paquete[i]
              << ", Prioridad: " << nivel_Prioridad_Paquete[i] << "\n";
                        }
                    }
                }

                if (count_E > 0) {
           std::cout << "\n--- Cola de Despacho (FIFO con Prioridad) ---\n";
           for (int i = 0; i < total_paquetes; i++) {
              if (estado_Paquete[i] == 'E') {
                  std::cout << "  ID: " << id_Paquete[i] 
                << ", Peso: " << peso_Paquete[i]
                << ", Destino: " << destino_Paquete[i]
                << ", Prioridad: " << nivel_Prioridad_Paquete[i] << "\n";
                        }
                    }
                }

                if (count_D > 0) {
          std::cout << "\n--- Paquetes Despachados ---\n";
             for (int i = 0; i < total_paquetes; i++) {
                 if (estado_Paquete[i] == 'D') {
            std::cout << "  ID: " << id_Paquete[i] 
             << ", Peso: " << peso_Paquete[i]
             << ", Destino: " << destino_Paquete[i]
             << ", Prioridad: " << nivel_Prioridad_Paquete[i] << "\n";
                        }
                    }
                }

                break;
            }
            case 5: {
                seguirCorriendo = false;
                break;
            }
            default: {
                std::cout << "Error: Opcion no valida. Intente de nuevo.\n";
                break;
            }
        }
    }

    std::cout << "\nLiberando memoria asignada...\n";
    
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