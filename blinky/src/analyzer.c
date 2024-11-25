#include "analyzer.h"

int is_data_valid(const uint32_t *data)
{
    if (!data) {
        return -1; // Wrong value
    }

    return 0; // Returns 0 if data is valid
}

int analyze_data(const uint8_t *data, uint8_t length) {
    if (!data || length == 0) {
        return -1; // Wrong value
    }
    
    //TODO: Analyze data

    return length; // Returns length
}
