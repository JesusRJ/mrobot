#ifndef Motors_h
#define Motors_h

// Motor Pin definitions
#define IN1 4
#define IN2 3
#define IN3 8
#define IN4 7
#define ENA 6
#define ENB 5

class Motors
{
public:
    Motors();
    void forward(unsigned short speed);
    void backward(unsigned short speed);
    void left(unsigned short speed);
    void right(unsigned short speed);
    void stop();
};

#endif
