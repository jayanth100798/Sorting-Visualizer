#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
const int BAR_WIDTH = 10;
const int NUM_BARS = WIDTH / BAR_WIDTH;

void drawBars(sf::RenderWindow &window, const std::vector<int> &arr, int highlight1 = -1, int highlight2 = -1) {
    window.clear();
    
    for (int i = 0; i < arr.size(); i++) {
        sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH, arr[i]));
        bar.setPosition(i * BAR_WIDTH, HEIGHT - arr[i]);
        if (i == highlight1 || i == highlight2) {
            bar.setFillColor(sf::Color::Red);
        } else {
            bar.setFillColor(sf::Color::White);
        }
        window.draw(bar);
    }
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void shuffleArray(std::vector<int> &arr) {
    std::srand(std::time(nullptr));
    for (int &val : arr) {
        val = std::rand() % HEIGHT;
    }
}

void bubbleSort(sf::RenderWindow &window, std::vector<int> &arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = 0; j < arr.size() - i - 1; j++) {
            drawBars(window, arr, j, j + 1);
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                drawBars(window, arr, j, j + 1);
            }
        }
    }
}

void selectionSort(sf::RenderWindow &window, std::vector<int> &arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < arr.size(); j++) {
            drawBars(window, arr, minIndex, j);
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
        drawBars(window, arr, i, minIndex);
    }
}

void insertionSort(sf::RenderWindow &window, std::vector<int> &arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            drawBars(window, arr, j, j + 1);
            j--;
        }
        arr[j + 1] = key;
        drawBars(window, arr, j + 1, i);
    }
}

void merge(std::vector<int> &arr, int left, int mid, int right) {
    std::vector<int> temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);
    for (int k = left; k <= right; k++) arr[k] = temp[k - left];
}

void mergeSort(sf::RenderWindow &window, std::vector<int> &arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(window, arr, left, mid);
        mergeSort(window, arr, mid + 1, right);
        merge(arr, left, mid, right);
        drawBars(window, arr);
    }
}

int partition(std::vector<int> &arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            std::swap(arr[++i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(sf::RenderWindow &window, std::vector<int> &arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        drawBars(window, arr, pi);
        quickSort(window, arr, low, pi - 1);
        quickSort(window, arr, pi + 1, high);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sorting Visualizer");
    std::vector<int> arr(NUM_BARS);
    
    while (window.isOpen()) {
        shuffleArray(arr);
        drawBars(window, arr);
        
        std::cout << "Select sorting algorithm:\n";
        std::cout << "1. Bubble Sort\n";
        std::cout << "2. Selection Sort\n";
        std::cout << "3. Insertion Sort\n";
        std::cout << "4. Quick Sort\n";
        std::cout << "5. Merge Sort\n";
        std::cout << "6. Shuffle & Choose Again\n";
        std::cout << "0. Exit\n";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1: bubbleSort(window, arr); break;
            case 2: selectionSort(window, arr); break;
            case 3: insertionSort(window, arr); break;
            case 4: quickSort(window, arr, 0, arr.size() - 1); break;
            case 5: mergeSort(window, arr, 0, arr.size() - 1); break;
            case 6: continue;
            case 0: window.close(); return 0;
            default: std::cout << "Invalid choice!\n"; break;
        }
    }
    return 0;
}

