#ifndef PID_H
    #define PID_H

    class PID {

        public:

            double kp;
            double kd;

            double last_error;
            unsigned long last_tick;

            unsigned long now;
            double error;
            double derivative_error;

            PID (double initial_kp, double initial_kd, double target, double current_position);
            double output (double target, double current_position);

    };

#endif