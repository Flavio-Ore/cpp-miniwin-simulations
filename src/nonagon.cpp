#include "../lib/miniwin.h"
#include <cmath>
#include <vector>
#include <algorithm>

// Define M_PI if not already defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace miniwin;

struct Point {
    float x, y;
};

// Helper to convert HSV color space to RGB for smooth rainbow transitions
// h: [0, 1], s: [0, 1], v: [0, 1]
void color_hsv(float h, float s, float v) {
    float r, g, b;
    
    int i = (int)(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch (i % 6) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }
    
    color_rgb((int)(r * 255), (int)(g * 255), (int)(b * 255));
}

// Recursive function to draw the fractal nonagon
// x, y: center position
// radius: current radius
// angle: current rotation angle
// depth: recursion depth
// time_offset: for animation
void draw_fractal(float x, float y, float radius, float angle, int depth, float time_offset) {
    // Base case: stop if too small or max depth reached
    if (depth <= 0 || radius < 2.0f) return;

    int sides = 9;
    std::vector<Point> vertices;

    // Calculate vertices for the current nonagon
    for (int i = 0; i < sides; ++i) {
        float theta = angle + (2.0f * M_PI * i) / sides;
        vertices.push_back({x + radius * std::cos(theta), y + radius * std::sin(theta)});
    }

    // Set color based on depth and time for a "hypnotic" effect
    // The hue shifts over time and varies by depth level
    float hue = std::fmod(time_offset * 0.2f + depth * 0.15f, 1.0f);
    if (hue < 0) hue += 1.0f;
    color_hsv(hue, 1.0f, 1.0f);

    // Draw the nonagon edges
    for (int i = 0; i < sides; ++i) {
        linea(vertices[i].x, vertices[i].y, vertices[(i + 1) % sides].x, vertices[(i + 1) % sides].y);
    }

    // Recursive step: draw smaller nonagons at each vertex
    // They rotate in the opposite direction for visual complexity
    float next_radius = radius * 0.35f; // Shrink factor
    float rotation_speed = 0.8f;
    
    for (int i = 0; i < sides; ++i) {
        // Calculate angle for the child nonagon
        // It rotates based on time and its position in the parent
        float child_angle = angle + time_offset * rotation_speed + (2.0f * M_PI * i) / sides;
        
        // Add a twist based on depth
        child_angle += depth * 0.5f;

        draw_fractal(vertices[i].x, vertices[i].y, next_radius, child_angle, depth - 1, time_offset);
    }
}

int _main_() {
    // Set a larger window for better detail
    vredimensiona(800, 800);
    
    float time = 0.0f;
    float base_rotation = 0.0f;
    float mx, my;

    // Main animation loop
    while (tecla() != ESCAPE) {
        borra(); // Clear screen
        
        float center_x = 400.0f;
        float center_y = 400.0f;
        
        // Default animation parameters
        float rot_speed = 0.01f;
        float pulse_speed = 2.0f;

        // Interactive element: Mouse controls rotation speed and pulse
        if (raton(mx, my)) {
             // X position controls rotation speed
             rot_speed = (mx - 400) / 2000.0f; 
             // Y position controls pulse speed
             pulse_speed = 1.0f + (my / 800.0f) * 4.0f;
        }

        // Calculate pulsing radius (heartbeat effect)
        float pulse = 200.0f + 40.0f * std::sin(time * pulse_speed);
        
        // Update rotation
        base_rotation += rot_speed;
        
        // Draw the fractal
        // Depth 4 provides good detail without killing performance
        draw_fractal(center_x, center_y, pulse, base_rotation, 4, time);
        
        refresca(); // Update display
        espera(16); // ~60 FPS cap
        
        time += 0.02f; // Advance time
    }
    
    vcierra();
    return 0;
}
