float sinVal;
int toneVal;

void setup(){
    pinMode(D1, OUTPUT);
}

void loop(){
    for(int x=0; x<180; x++){
        sinVal = (sin(x*(3.1412/180)));
        toneVal = 2000 + (int(sinVal*1000));
        tone(D1, toneVal);
        delay(2);
    }
}