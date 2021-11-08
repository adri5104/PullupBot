#define STEPS_PER_MM 80
#define step_pin 40
#define dir_pin 20
#define enable_pin 36

class stepper {
public:
    bool is_moving;
    long millisbetweensteps;  //probar con 25, si va muy rapido se aumenta
    long maxsteps;
    long step_count;
    float px;

    unsigned long prev_time;

    long obj; //numero de pasos a moverse
    long absobj; //numero de pasos en valor absoluto

    stepper();
    void setPosition(float npx);
    void prepareMove(float newx);
    void move();
    void disableMotor();
    void enableMotor();
};