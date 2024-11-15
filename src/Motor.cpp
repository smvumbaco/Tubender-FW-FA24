#ifndef MOTOR_HPP
#define MOTOR_HPP


class Motor {
  private:
    int pulPin;
    int dirPin;
    int enaPin;
    int stepsPerRevolution;
    int currentPosition;

  public:
    Motor();
    Motor(int pul, int dir, int ena, int stepsPerRev) {
      pulPin = pul;
      dirPin = dir;
      enaPin = ena;
      stepsPerRevolution = stepsPerRev;
      currentPosition = 0;
      pinMode(pulPin, OUTPUT);
      pinMode(dirPin, OUTPUT);
      pinMode(enaPin, OUTPUT);
      digitalWrite(enaPin, LOW);  // Enable the driver
    
    ~Motor();
    }

    void move(int steps, bool direction) {
      digitalWrite(dirPin, direction);
      for (int i = 0; i < steps; i++) {
        digitalWrite(pulPin, HIGH);
        delayMicroseconds(500);  // Adjust speed as needed
        digitalWrite(pulPin, LOW);
        delayMicroseconds(500);
      }
      currentPosition += (direction ? steps : -steps);
    }

    void enable() {
      digitalWrite(enaPin, LOW);
    }

    void disable() {
      digitalWrite(enaPin, HIGH);
    }

    int getCurrentPosition() {
      return currentPosition;
    }

    void resetPosition() {
      currentPosition = 0;
    }
};
#endif