bool is_high = false;

int toggle(String args)
{
    if(is_high == true)
    {
        digitalWrite(D0, LOW);
        is_high = false;
    }
    else
    {
        digitalWrite(D0, HIGH);
        is_high = true;
    }
    
    return 0;
}

void setup() {
    pinMode(D0, OUTPUT);
    Spark.function("toggle", toggle);
}

void loop() {
    //Nothing here
}