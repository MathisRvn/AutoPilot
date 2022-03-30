#ifndef RECEIVER_H
    #define RECEIVER_H

    class Receiver {

        public:
            int pin;
            int ch[6]; short i = 0; 
            unsigned long last_time_receiver_fall, receiver_now, receiver_delta;

            int filtered[6];
            int previous[6][10];
            int previous_index[6];

            Receiver(int pin, void(*callback)(void));

            void interruptCallback(void);

            void print(void);

            void tick(void);
    };

#endif