// Long-term locks for processes
#ifndef SLEEPLOCK_H
#define SLEEPLOCK_H

#include "spinlock.h"  // Necesario para `struct spinlock`

struct sleeplock {
  uint locked;       // Is the lock held?
  struct spinlock lk; // spinlock protecting this sleep lock
  
  // For debugging:
  char *name;        // Name of lock.
  int pid;           // Process holding lock
};
#endif // SLEEPLOCK_H
