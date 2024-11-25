#include "analyzer.h"

int analyze_data(const uint8_t *data, size_t length) {
    if (!data || length == 0) {
        return -1; // Błąd
    }
    // Analiza danych
    return length; // Zwraca liczbę przeanalizowanych bajtów
}
