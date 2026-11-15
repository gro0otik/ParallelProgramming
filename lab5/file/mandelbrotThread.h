#ifndef MANDELBROT_THREAD_H
#define MANDELBROT_THREAD_H

void mandelbrotThread(int numThreads, float x0, float y0, float x1, float y1,
                      int width, int height, int maxIterations, int* output);

#endif