#ifndef COOLDOWN_H
#define COOLDOWN_H

class Cooldown {
public:
    // Constructor
    explicit Cooldown(float maxTime)
        : maxTime(maxTime), currentTime(0), isActive(false) {}

    // Resets the cooldown
    void Reset() {
        currentTime = 0;
        isActive = true;
    }

    // Updates the cooldown timer
    void Update(float deltaTime) {
        if (isActive) {
            currentTime += deltaTime;
            if (currentTime >= maxTime) {
                currentTime = maxTime;
                isActive = false;
            }
        }
    }

    // Checks if the cooldown is ready
    bool IsReady() const {
        return !isActive;
    }

    // Attributes
    float maxTime;        // Maximum cooldown time
    float currentTime;    // Current elapsed time
    bool isActive;        // Indicates if cooldown is active
};

#endif // COOLDOWN_H
