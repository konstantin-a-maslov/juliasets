# Julia Sets


![](anim.gif)


This is a small legacy C++ toy project that renders animated Julia set fractals using OpenGL/GLUT for visualisation and OpenMP for parallel computation. 
Each frame computes the color of every pixel independently based on iterative complex dynamics, allowing the workload to scale efficiently across all CPU cores. 
The project originally served as an experiment in numerical methods and multithreaded rendering, and has been lightly modernized (minor cleanup) for archival and demonstration purposes. 
It is not intended as production-quality code, but rather as a compact example of parallel pixel computation, basic real-time rendering, and the evolution of my early C++ coding practices.


Compile and run with
```
g++ -std=c++20 -O3 main.cpp Complex.cpp -o juliasets -fopenmp -lfreeglut -lopengl32 -lglu32
./juliasets.exe
```
