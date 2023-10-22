#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <cmath>

using namespace std;
using namespace sf;

const int H = 600;
const int W = 900;
const float p = 0.05;

void LowToUpArray(int* array, int size, int minValue, int maxValue) {
    if (size >= (maxValue - minValue + 1)) {
        for (int i = 0; i < size; i++) {
            array[i] = minValue;
            if (minValue < maxValue)
                minValue++;
        }
    }
    else {
        int left = minValue;
        int right = maxValue - size + 1;
        for (int i = 0; i < size; i++) {
            array[i] = (double)rand() / RAND_MAX * (right - left) + left;
            left = array[i] + 1;
            right++;
        }
    }
}

void LowToUpArray(double* array, int size, int minValue, int maxValue) {
    if (size >= (maxValue - minValue + 1)) {
        for (int i = 0; i < size; i++) {
            array[i] = minValue;
            if (minValue < maxValue)
                minValue++;
        }
    }
    else {
        int left = minValue;
        int right = maxValue - size + 1;
        for (int i = 0; i < size; i++) {
            array[i] = (double)rand() / RAND_MAX * (right - left) + left;
            left = array[i] + 1;
            right++;
        }
    }
}

void UpToLowArray(int* array, int size, int minValue, int maxValue) {
    if (size >= (maxValue - minValue + 1)) {
        for (int i = 0; i < size; i++) {
            array[i] = maxValue;
            if (minValue < maxValue)
                maxValue--;
        }
    }
    else {
        int left = maxValue - size + 1;
        int right = maxValue;
        for (int i = 0; i < size; i++) {
            array[i] = (double)rand() / RAND_MAX * (right - left) + left;
            right = array[i] - 1;
            if (left > size)
                left = right - size + 1;
            else
                left--;
        }
    }
}

void UpToLowArray(double* array, int size, int minValue, int maxValue) {
    if (size >= (maxValue - minValue + 1)) {
        for (int i = 0; i < size; i++) {
            array[i] = maxValue;
            if (minValue < maxValue)
                maxValue--;
        }
    }
    else {
        int left = maxValue - size + 1;
        int right = maxValue;
        for (int i = 0; i < size; i++) {
            array[i] = (double)rand() / RAND_MAX * (right - left) + left;
            right = array[i] - 1;
            if (left > size)
                left = right - size + 1;
            else
                left--;
        }
    }
}

void RandomArray(int* array, int size, int minValue, int maxValue) {
    for (int i = 0; i < size; i++) {
        array[i] = (double)rand() / RAND_MAX * (maxValue - minValue) + minValue;
    }
}

void RandomArray(double* array, int size, int minValue, int maxValue) {
    for (int i = 0; i < size; i++) {
        array[i] = (double)rand() / RAND_MAX * (maxValue - minValue) + minValue;
    }
}

void SawArray(int* array, int size, int minValue, int maxValue, int step) {
    int dif = (maxValue - minValue) / step;
    array[0] = minValue;
    for (int i = 1; i < size; i++) {
        if (array[i - 1] == maxValue || array[i - 1] > maxValue) {
            array[i] = minValue;
        }
        else {
            array[i] = array[i - 1] + dif;
        }
    }
}

void SawArray(double* array, int size, int minValue, int maxValue, int step) {
    double dif = (maxValue - minValue) / step;
    array[0] = minValue;
    for (int i = 1; i < size; i++) {
        if (array[i - 1] == maxValue || array[i - 1] > maxValue) {
            array[i] = minValue;
        }
        else {
            array[i] = array[i - 1] + dif;
        }
    }
}

void SinArray(int* array, int size, int minValue, int maxValue, int step) {
    int ymove = (minValue + maxValue) / 2;
    int arc = maxValue - ymove;
    for (int i = 0; i < size; i++) {
        array[i] = sin(i) * arc + ymove;
    }
}

void SinArray(double* array, int size, int minValue, int maxValue, int step) {
    int ymove = (minValue + maxValue) / 2;
    int arc = maxValue - ymove;
    for (int i = 0; i < size; i++) {
        array[i] = sin(i) * arc + ymove;
    }
}

void StepArray(int* array, int size, int minValue, int maxValue, int step) {
    int h;
    if (size % step == 0) h = size / step;
    else h = size / step + 1;

    float v = static_cast<float>(maxValue - minValue) / h;
    float left = minValue;
    float right;
    for (int j = 0; j < h; j++) {
        right = minValue + v * (j + 1);
        for (int i = step * j; i < step * (j + 1); i++) {
            array[i] = (double)rand() / RAND_MAX * (right - left) + left;
        }
        left = right;
    }
}

void StepArray(double* array, int size, int minValue, int maxValue, int step) {
    double h;
    h = size / step;

    float v = static_cast<float>(maxValue - minValue) / h;
    float left = minValue;
    float right;
    for (int j = 0; j < h; j++) {
        right = minValue + v * (j + 1);
        for (int i = step * j; i < step * (j + 1); i++) {
            array[i] = (double)rand() / RAND_MAX * (right - left) + left;
        }
        left = right;
    }
}

void FunctionCall(void(*funcArr[])(int*, int, int, int), void(*funcStepArr[])(int*, int, int, int, int), int size) {
    
    int* arr = new int[size];
    chrono::steady_clock::time_point begin, end;
    chrono::microseconds timeDiff;
    
    srand(time(NULL) + GetTickCount());
    
    ofstream ftime;
    ftime.open("time.txt");

    ftime << "LowToUp\tUpToLow\tRandom\tSaw\tStep\tSin" << endl;

    if (ftime.is_open()) {
        for (int j = 0; j < 100; j++) {
            for (int i = 0; i < 3; i++) {
                begin = chrono::steady_clock::now();
                funcArr[i](arr, size, 0, 100);
                end = chrono::steady_clock::now();
                timeDiff = chrono::duration_cast<chrono::microseconds>(end - begin);
                ftime << timeDiff.count() << '\t';
            }

            for (int i = 0; i < 3; i++) {
                begin = chrono::steady_clock::now();
                funcStepArr[i](arr, size, 0, 100, 8);
                end = chrono::steady_clock::now();
                timeDiff = chrono::duration_cast<chrono::microseconds>(end - begin);
                ftime << timeDiff.count() << '\t';
            }

            ftime << '\n';
        }
    }

    ftime.close();
}

void ArrayCreate(void(*funcArr[])(int*, int, int, int), void(*funcStepArr[])(int*, int, int, int, int), int size) {
    int* arr = new int[size];
    
    srand(time(NULL) + GetTickCount());

    ofstream fvalue;
    fvalue.open("funcValue.txt");


    if (fvalue.is_open()) {
        
        for (int i = 0; i < 3; i++) {
            funcArr[i](arr, size, 0, 100);
            for (int i = 0; i < size; i++) {
                fvalue << arr[i] << '\t';
            }
            fvalue << '\n';

        }

        for (int i = 0; i < 3; i++) {
            funcStepArr[i](arr, size, 40, 60, 30);
            for (int i = 0; i < size; i++) {
                fvalue << arr[i] << '\t';
            }
            fvalue << '\n';
        }
    }

    fvalue.close();
}

void ArrayCreate(void(*funcArr[])(double*, int, int, int), void(*funcStepArr[])(double*, int, int, int, int), int size) {
    double* arr = new double[size];

    srand(time(NULL) + GetTickCount());

    ofstream fvaluefloat;
    fvaluefloat.open("funcValueFloat.txt");


    if (fvaluefloat.is_open()) {

        for (int i = 0; i < 3; i++) {
            funcArr[i](arr, size, 0, 100);
            for (int i = 0; i < size; i++) {
                fvaluefloat << arr[i] << '\t';
            }
            fvaluefloat << '\n';

        }

        for (int i = 0; i < 3; i++) {
            funcStepArr[i](arr, size, 30, 90, 30);
            for (int i = 0; i < size; i++) {
                fvaluefloat << arr[i] << '\t';
            }
            fvaluefloat << '\n';
        }
    }

    fvaluefloat.close();
}

int main()
{
    int size = 300;

    void(*funcArr[])(int*, int, int, int) = {LowToUpArray, UpToLowArray, RandomArray};
    void(*funcStepArr[])(int*, int, int, int, int) = {SawArray, StepArray, SinArray };

    void(*funcArrFloat[])(double*, int, int, int) = { LowToUpArray, UpToLowArray, RandomArray };
    void(*funcStepArrFloat[])(double*, int, int, int, int) = { SawArray, StepArray, SinArray };

    ArrayCreate(funcArr, funcStepArr, size);
    FunctionCall(funcArr, funcStepArr, size);
    ArrayCreate(funcArrFloat, funcStepArrFloat, size);

#pragma region Graphic
    /*RenderWindow window(VideoMode(W, H), "Graphic");

    int x0 = W * p;
    int y0 = H / 2;

    CircleShape point(2.f);
    point.setFillColor(Color::Blue);

    Event event;

    float x, y;
    RectangleShape OX(Vector2f(W - x0 * 2, 1));
    RectangleShape OY(Vector2f(1, H - (H * p) * 2));

    OX.setFillColor(Color::Black);
    OY.setFillColor(Color::Black);

    OX.setPosition(x0, y0);
    OY.setPosition(x0, H * p);

    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);

        for (int j = 0; j < size; j++) {
            point.setPosition(x0 + j * 5, y0 - arr[j]);
            window.draw(point);
        }

        window.draw(OY);
        window.draw(OX);
        window.display();
    }

    return 0;*/
#pragma endregion

}