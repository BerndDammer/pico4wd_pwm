void motor_init();
void motor_set(int pwm_val);

enum WHEEL
{
    FRONT_LEFT,
    FRONT_RIGHT,
    REAR_LEFT,
    REAR_RIGHT
};

#define DRIVE_MAX 100
#define DRIVE_OFF 0
#define DRIVE_MIN -100

