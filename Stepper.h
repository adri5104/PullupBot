#define STEPS_PER_MM 80
#define MAX_FEEDRATE 1000000
#define MIN_FEEDRATE 1
#define step_pin 40
#define dir_pin 20
#define enable_pin 36

class stepper {
public:
    bool is_moving;
    float feed_rate;
    long step_delay;
    unsigned long delay_t;
    long maxsteps;
    long step_count;
    long accel;
    float px;

    long steps_to_accel;
    long steps_to_decel;

    unsigned long prev_time;

    long obj; //numero de pasos a moverse
    long absobj; //numero de pasos en valor absoluto
    long over; //no se

    stepper();
    void setFeedrate(float nfr);
    void setPosition(float npx);
    void prepareMove(float newx);
    void move();
    void disableMotor();
    void enableMotor();
};