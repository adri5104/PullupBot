
class Stepper {

public:
    bool is_moving;
    long maxsteps;
    long step_count;
    float px;
    float previa;

    unsigned long prev_time;

    long obj; //numero de pasos a moverse
    long absobj; //numero de pasos en valor absoluto

    Stepper(int,int,int,int);
    void setPosition(float npx);
    float getPosition(); //la que envia la posicion en cada instante a matlab
    void prepareMove(float newx);
    void move();
    void enableStepper();
    void disableStepper();
    void Sinit();
private:
    int step_pin;
    int dir_pin;
    int reset;
    int sleep;
};