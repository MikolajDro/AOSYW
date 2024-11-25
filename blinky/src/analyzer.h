#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdint.h>


int is_data_valid(const uint32_t *data);
int analyze_data(const uint8_t *data, uint8_t length);

#endif // ANALYZER_H
