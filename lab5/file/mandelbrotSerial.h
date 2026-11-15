#ifndef MANDELBROT_SERIAL_H
#define MANDELBROT_SERIAL_H

void mandelbrotSerial(float x0, float y0, float x1, float y1,
                      int width, int height,
                      int startRow, int totalRows,
                      int maxIterations, int output[]);

#endif