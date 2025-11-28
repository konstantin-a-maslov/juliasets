#include <GL/glut.h>
#include <omp.h>
#include <cmath>
#include <iostream>
#include "Complex.hpp"

void display();
void timer(int);
void updateBuffer();

const int windowSize = 640;
const size_t iterLimit = 100;
const double maxCoord = 1.6;
const double radiusOfC = 0.8;
const bool animated = true;
double angleOfC = 0.0;

struct RGBColor {
    float r;
    float g;
    float b;
};
RGBColor coloringBuffer[windowSize+1][windowSize+1];

int main(int argc, char** argv) {
    omp_set_dynamic(0);
    omp_set_num_threads(omp_get_max_threads());
    #pragma omp parallel
    {
        #pragma omp single
        std::cout << "OpenMP running with " << omp_get_num_threads() << " threads" << std::endl;
    }

    updateBuffer();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowSize+1, windowSize+1);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Julia Sets");
    glutReshapeFunc([](int w, int h){
        glutReshapeWindow(windowSize + 1, windowSize + 1);
    });
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-windowSize/2, windowSize/2, windowSize/2, -windowSize/2, -1, 1);
    glutDisplayFunc(display);
    glutTimerFunc(10, timer, 0);
    glutMainLoop();

    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for(int i = -windowSize/2; i <= windowSize/2; ++i) {
        for(int j = -windowSize/2; j <= windowSize/2; ++j) {
            const double r = coloringBuffer[i + windowSize/2][j + windowSize/2].r;
            const double g = coloringBuffer[i + windowSize/2][j + windowSize/2].g;
            const double b = coloringBuffer[i + windowSize/2][j + windowSize/2].b;

            glColor3f(r, g, b);
            glVertex2f(i, j);
        }
    }
    glEnd();

    glutSwapBuffers();
    glFlush();
}

void timer(int i = 0) {
    if(animated) {
        angleOfC += 0.0025;
        updateBuffer();
        glutTimerFunc(10, timer, 0);
    }
    display();
}

void updateBuffer() {
    const double cx = radiusOfC * cos(angleOfC);
    const double cy = radiusOfC * sin(angleOfC);
    const Complex c(cx, cy);

    #pragma omp parallel for shared(coloringBuffer) collapse(2) schedule(dynamic, 32)
    for(int i = -windowSize/2; i <= windowSize/2; ++i) {
        for(int j = -windowSize/2; j <= windowSize/2; ++j) {
            const double x = (double)i / (windowSize/2) * maxCoord;
            const double y = (double)j / (windowSize/2) * maxCoord;

            Complex z(x, y);

            size_t n = 0;
            for(; n < iterLimit; ++n) {
                z = z.mul(z).add(c);

                if(z.absSquared() > 4) {
                    break;
                }
            }

            float r;
            float g;
            float b;

            // There are some magic numbers (acknowledged), ignored for this toy example
            int h = (int)((float)n / iterLimit * 360);
            int s = 100;
            int v = (n == iterLimit ? 0 : h/2 + 25);

            int hi = (h / 60) % 6;
            int vmin = (100 - s) * v / 100.0;
            int a = (v - vmin) * (h % 60) / 60.0;
            int vinc = vmin + a;
            int vdec = v - a;

            switch(hi) {
                case 0:  { r = v;    g = vinc; b = vmin; } break;
                case 1:  { r = vdec; g = v;    b = vmin; } break;
                case 2:  { r = vmin; g = v;    b = vinc; } break;
                case 3:  { r = vmin; g = vdec; b = v;    } break;
                case 4:  { r = vinc; g = vmin; b = v;    } break;
                case 5:  { r = v;    g = vmin; b = vdec; } break;
                default: { r = 0.0;  g = 0.0;  b = 0.0;  }
            }

            coloringBuffer[i + windowSize/2][j + windowSize/2].r = r / 100.0;
            coloringBuffer[i + windowSize/2][j + windowSize/2].g = g / 100.0;
            coloringBuffer[i + windowSize/2][j + windowSize/2].b = b / 100.0;
        }
    }
}
