#include "../lib/miniwin.h"
#include <cmath> // Para std::cos y std::sin
#include <vector> // Para std::vector

// Definimos M_PI si no está definido (común en MSVC)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int _main_() {
    // 1. Establecer el tamaño de la ventana
    miniwin::vredimensiona(600, 600);

    // 2. Definir el centro y el radio del nonágono
    float centro_x = 300.0f;
    float centro_y = 300.0f;
    float radio = 250.0f;
    int num_lados = 9; // Un nonágono tiene 9 lados

    // 3. Calcular los vértices del nonágono
    std::vector<std::pair<float, float>> vertices;
    for (int i = 0; i < num_lados; ++i) {
        float angulo = 2.0f * M_PI * i / num_lados; // Ángulo en radianes
        // Ajustamos el ángulo para que el nonágono "apunte" hacia arriba (opcional)
        // angulo -= M_PI / 2.0f; 
        float x = centro_x + radio * std::cos(angulo);
        float y = centro_y + radio * std::sin(angulo);
        vertices.push_back({x, y});
    }

    // 4. Dibujar el nonágono conectando los vértices
    miniwin::color(miniwin::BLANCO); // Color de las líneas

    if (vertices.size() >= 2) {
        for (size_t i = 0; i < vertices.size(); ++i) {
            miniwin::linea(
                vertices[i].first, vertices[i].second,
                vertices[(i + 1) % vertices.size()].first, // Conecta con el siguiente, y el último con el primero
                vertices[(i + 1) % vertices.size()].second
            );
        }
    }

    // 5. Refrescar la pantalla para mostrar el dibujo
    miniwin::refresca();

    // 6. Esperar hasta que se presione la tecla ESC para cerrar
    while (miniwin::tecla() != miniwin::ESCAPE) {
        miniwin::espera(10); // Pequeña pausa para no consumir CPU innecesariamente
    }

    miniwin::vcierra(); // Cerrar la ventana

    return 0;
}