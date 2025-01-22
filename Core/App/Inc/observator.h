
#ifndef OBSERVATOR_H
#define OBSERVATOR_H

typedef struct Observer {
    void (*update)(void *data);
} observer_t;

void attach_observer(observer_t *observer);
void detach_observer(observer_t *observer);
void notify_observers(void *data);

#endif // OBSERVATOR_H
