#include "cleanup.h"
#include "shared.h"

void runTimekeeper() {
  log_message(LOG_LEVEL_INFO, "Starting timekeeping service.");

  simClock = attachSharedMemory();
  if (simClock == (void *)-1) {
    log_message(LOG_LEVEL_ERROR, "Failed to attach to shared memory.");
    exit(EXIT_FAILURE);
  }

  clockSem = sem_open(clockSemName, 0);
  if (clockSem == SEM_FAILED) {
    log_message(LOG_LEVEL_ERROR, "Failed to open semaphore.");
    exit(EXIT_FAILURE);
  }

  while (keepRunning) {
    sleep(1);

    sem_wait(clockSem);
    unsigned int increment = 250;
    simClock->nanoseconds += increment * 1000000L;
    if (simClock->nanoseconds >= NANOSECONDS_IN_SECOND) {
      simClock->seconds += simClock->nanoseconds / NANOSECONDS_IN_SECOND;
      simClock->nanoseconds %= NANOSECONDS_IN_SECOND;
    }
    sem_post(clockSem);

    log_message(LOG_LEVEL_DEBUG, "Time updated: %lu sec, %lu nsec",
                simClock->seconds, simClock->nanoseconds);
  }
}

int main() {
  gProcessType = PROCESS_TYPE_TIMEKEEPER;

  setupSignalHandlers();
  runTimekeeper();
  return EXIT_SUCCESS;
}
