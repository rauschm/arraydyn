#ifndef _INC_STOPWATCH_H
#define _INC_STOPWATCH_H

#include <time.h>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define CLOCK_MONOTONIC 1
#ifdef _MSC_VER
#if _MSC_VER < 1900
struct timespec {
  time_t tv_sec;   /* Seconds - >= 0 */
  long   tv_nsec;  /* Nanoseconds - [0, 999999999] */
};
#endif
#endif
#endif

#ifdef __cplusplus
class
#else
typedef struct
#endif
               StopWatch {
#ifdef __cplusplus
  private:
#endif
    struct timespec startTime;
    struct timespec stopTime;
#ifdef __cplusplus
    bool
#else
    int
#endif
         running;
#ifndef __cplusplus
} StopWatch;
#define StopWatch(s) StopWatch s = {0, 0, 0};
#endif

#ifdef _WIN32
    static int clock_gettime(int clk_id, struct timespec *tp) {
      LARGE_INTEGER         t;
      static LARGE_INTEGER  performanceFrequency;  // ticks per second
      static LARGE_INTEGER  offset;
      static int            initialized = 0;

      if (!initialized) {
        initialized = 1;
        if (!QueryPerformanceFrequency(&performanceFrequency)) {
          fprintf(stderr, "STOP: high-resolution performance counter not supported\n");
          ExitProcess(1);
        }
        QueryPerformanceCounter(&offset);
      }

      QueryPerformanceCounter(&t);
      t.QuadPart -= offset.QuadPart;
      t.QuadPart = (1000000000 * t.QuadPart) / performanceFrequency.QuadPart;
      tp->tv_sec = (time_t) (t.QuadPart / 1000000000);
      tp->tv_nsec = (long) (t.QuadPart % 1000000000);
      return 0;
    }
#endif

#ifdef __cplusplus
  public:
    StopWatch() {
      startTime.tv_sec = startTime.tv_nsec = 0;
      stopTime.tv_sec = stopTime.tv_nsec = 0;
      running = false;
    }
#endif

    void start(
#ifndef __cplusplus
               StopWatch* this
#endif
                              ) {
      clock_gettime(CLOCK_MONOTONIC, &this->startTime);
      this->running = (0 == 0);
    }

    void stop(
#ifndef __cplusplus
               StopWatch* this
#endif
                              ) {
      clock_gettime(CLOCK_MONOTONIC, &this->stopTime);
      this->running = (0 != 0);
    }

    long getElapsedTime(
#ifndef __cplusplus
                        StopWatch* this
#endif
                                       ) {
      if (this->running) {
        clock_gettime(CLOCK_MONOTONIC, &this->stopTime);
      }
      return (long) (this->stopTime.tv_sec - this->startTime.tv_sec) * 1000000
           + (this->stopTime.tv_nsec - this->startTime.tv_nsec) / 1000;
    }

    double getElapsedTimeSecs(
#ifndef __cplusplus
                              StopWatch* this
#endif
                                             ) {
      if (this->running) {
        clock_gettime(CLOCK_MONOTONIC, &this->stopTime);
      }
      return (this->stopTime.tv_sec - this->startTime.tv_sec)
           + (this->stopTime.tv_nsec - this->startTime.tv_nsec) / 1000000000.0;
    }
#ifdef __cplusplus
};
#endif

#endif
