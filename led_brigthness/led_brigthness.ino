const int LED_PIN = 10;

const int WAITTIME = 50;
const int STEP = 5;

void setup(){
    pinMode( LED_PIN, OUTPUT );
}

void loop(){
    int i;

    i = 0;
    while ( i <= 255 ){
        analogWrite( LED_PIN, i );
        delay( WAITTIME );
        i = i + STEP;
    }

    i = 255;
    while ( i >= 0 ){
        analogWrite( LED_PIN, i );
        delay( WAITTIME );
        i = i - STEP;
    }
}
