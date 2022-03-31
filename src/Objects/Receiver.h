#ifndef RECEIVER_H
    #define RECEIVER_H

    class Receiver {

        public:
            int pin;
            int ch[6]; short i = 0; 
            unsigned long last_time_receiver_fall, receiver_now, receiver_delta;

            /*
            micros -> receiver_now (unsigned long)
            unsigned long is 32 bits on arduino uno
            2^32 = 4 294 967 296 = 4294seconds = 71minutes.
            The receiver can be on 71 minutes before a doing something not anticipated by overpassing the maximum value.
            */

            #ifdef ENABLE_RECEIVER_FILTERING
                int filtered[2];
                int previous[2][10];
                int previous_index[2];
            #endif

            Receiver(int pin, void(*callback)(void));

            void interruptCallback(void);

            void print(void);

            void tick(void);
    };

#endif