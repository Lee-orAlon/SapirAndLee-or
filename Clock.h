#ifndef EX33_CLOCK_H
#define EX33_CLOCK_H

/**
 * Clock class- a class that represents the time in the world (the program).
 */
class Clock {
private:
    int time;
public:
    /**
     * Constructor.
     */
    Clock();

    /**
     * increaseTimeByOne- increase the value of time by 1.
     */
    void increaseTimeByOne();

    /**
     * getTime.
     * @return time.
     */
    int getTime();

    /**
     * Destructor.
     */
    ~Clock();
};

#endif //EX33_CLOCK_H
