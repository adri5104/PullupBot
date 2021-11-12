#define STEPS_PER_MM 5
#define step_pin 40
#define dir_pin 20
#define reset 10

class Stepper {

public:
    bool is_moving;
    long millisbetweensteps;  //probar con 25, si va muy rapido se aumenta
    long maxsteps;
    long step_count;
    float px;
    float previa;

    unsigned long prev_time;

    long obj; //numero de pasos a moverse
    long absobj; //numero de pasos en valor absoluto

    Stepper();
    void setPosition(float npx);
    float getPosition(); //la que envia la posicion en cada instante a matlab
    void prepareMove(float newx);
    void move();
    void enableStepper();
    void disableStepper();

};