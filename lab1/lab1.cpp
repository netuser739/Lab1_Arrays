#include <iostream>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <windows.h>
//#include <cmath>

using namespace std;
using namespace sf;

const int H = 600;
const int W = 900;
const float p = 0.05;

void LowToUpArray(int *array, int size, int minValue, int maxValue) {
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

void UpToLowArray(int *array, int size, int minValue, int maxValue) {
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

void RandomArray(int *array, int size, int minValue, int maxValue) {
    for (int i = 0; i < size; i++) {
        array[i] = (double)rand() / RAND_MAX * (maxValue - minValue) + minValue;
    }
}

void SawArray(int *array, int size, int minValue, int maxValue, int step) {
    int h;
    if (size % step == 0) h = size / step;
    else h = size / step + 1;

    for (int j = 0; j < h; j++) {
        if (step >= (maxValue - minValue + 1)) {
            for (int i = step * j; i < step * (j + 1) || i < size; i++) {
                array[i] = minValue;
                if (minValue < maxValue)
                    minValue++;
            }
        }
        else {
            int left = minValue;
            int right = maxValue - size + 1;
            for (int i = step * j; i < step * (j + 1) || i < size; i++) {
                array[i] = (double)rand() / RAND_MAX * (right - left) + left;
                left = array[i] + 1;
                right++;
            }
        }
    }
}

void SinArray(int *array, int size, int minValue, int maxValue, int step) {
    int h;
    if (size % step == 0) h = size / step;
    else h = size / step + 1;

    int h2, h3;
    if (step % 2 == 0) h2 = h3 = step / 2;
    else {
        h2 = step / 2;
        h3 = h2 + 1;
    }

    int left = minValue;
    int right = maxValue;

    for (int j = 0; j < h; j++) {
        if (h2 >= (right - left + 1)) {
            for (int i = (h2 + h3) * j; i < h2 * (j + 1) + h3 * j; i++) {
                array[i] = left;
                if (left < right)
                    left++;
            }
        }
        else {
            left = minValue;
            right = maxValue - size + 1;
            for (int i = (h2 + h3) * j; i < h2 * (j + 1) + h3 * j; i++) {
                array[i] = (double)rand() / RAND_MAX * (right - left) + left;
                left = array[i] + 1;
                right++;
            }
        }

        if (h3 >= (right - left + 1)) {
            for (int i = h2 * (j + 1) + h3 * j; i < h2 * (j + 1) + h3 * (j + 1); i++) {
                array[i] = right;
                if (left < right)
                    right--;
            }
        }
        else {
            left = maxValue - size + 1;
            right = maxValue;
            for (int i = h2 * (j + 1) + h3 * j; i < h2 * (j + 1) + h3 * (j + 1); i++) {
                array[i] = (double)rand() / RAND_MAX * (right - left) + left;
                right = array[i] - 1;
                if (left > size)
                    left = right - size + 1;
                else
                    left--;
            }
        }
    }
}
 
void StepArray(int *array, int size, int minValue, int maxValue, int step) {
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

int main()
{

    int size = 150;
    int* arr = new int[size];
    srand(time(NULL) + GetTickCount());
    //LowToUpArray(arr, size, 1, 99);
    //UpToLowArray(arr, size, 1, 99);
    //RandomArray(arr, size, 1, 99);
    //SawArray(arr, size, 1, 200, 10);
    //StepArray(arr, size, 0, 200, 15);
    SinArray(arr, size, 10, 300, 4);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << ' ';
    }

    RenderWindow window(VideoMode(W, H), "Graphic");

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

    return 0;
}