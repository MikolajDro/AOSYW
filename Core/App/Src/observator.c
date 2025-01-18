#include "../Inc/observator.h"
#include <stdlib.h>

#define MAX_OBSERVERS 10

static observer_t *observers[MAX_OBSERVERS];
static int observer_count = 0;

void
attach_observer(observer_t *observer)
{
    if (observer_count < MAX_OBSERVERS)
    {
        observers[observer_count++] = observer;
    }
}

void
detach_observer(observer_t *observer)
{
    for (int i = 0; i < observer_count; ++i)
    {
        if (observers[i] == observer)
        {
            for (int j = i; j < observer_count - 1; ++j)
            {
                observers[j] = observers[j + 1];
            }
            observer_count--;
            break;
        }
    }
}

void
notify_observers(void *data)
{
    for (int i = 0; i < observer_count; ++i)
    {
        observers[i]->update(data);
    }
}

