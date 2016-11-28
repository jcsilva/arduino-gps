void power_on(){

    uint8_t answer=0;

    // checks if the module is started
    answer = sendATcommand("AT", "OK", 2000);
    if (answer == 0)
    {
        // power on pulse
        digitalWrite(onModulePin,HIGH);
        delay(3000);
        digitalWrite(onModulePin,LOW);

        // waits for an answer from the module
        while(answer == 0){    
            // Send AT every two seconds and wait for the answer
            answer = sendATcommand("AT", "OK", 2000);    
        }
    }
}


int8_t sendATcommand(const char* ATcommand, const char* expected_answer1, unsigned int timeout)
{

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;

    // Initialize the string
    memset(response, '\0', 100);

    delay(100);

    // Clean the input buffer
    while( Serial.available() > 0) Serial.read();
    
    // Send the AT command 
    Serial.println(ATcommand);
    
    previous = millis();

    // this loop waits for the answer
    do{

        if(Serial.available() != 0){    
            response[x] = Serial.read();
            x++;
            // check if the desired answer is in the response of the module
            if (strstr(response, expected_answer1) != NULL)    
            {
                answer = 1;
            }
        }
        // Waits for the answer with time out
    }
    while((answer == 0) && ((millis() - previous) < timeout));    

    return answer;
}

int8_t sendATcommand2(const char* ATcommand, const char* expected_answer1,
   const char* expected_answer2, unsigned int timeout)
{

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;

    memset(response, '\0', 100);    // Initialize the string

    delay(100);

    while( Serial.available() > 0) Serial.read();    // Clean the input buffer

    Serial.println(ATcommand);    // Send the AT command 


    x = 0;
    previous = millis();

    // this loop waits for the answer
    do{

        if(Serial.available() != 0){    
            response[x] = Serial.read();
            x++;
            // check if the desired answer is in the response of the module
            if (strstr(response, expected_answer1) != NULL)    
            {
                answer = 1;
            }
            // check if the desired answer is in the response of the module
            if (strstr(response, expected_answer2) != NULL)    
            {
                answer = 2;
            }
        }
        // Waits for the asnwer with time out
    }
    while((answer == 0) && ((millis() - previous) < timeout));    

    return answer;
}

void get_GPS_params(char* params, char* frame){

    char aux[30];
    
    // Parses the string
    strcpy(params, "lat=");
    strcpy(aux, strtok(frame, ",")); // Gets latitude
    strcat(aux, "\0");
    //convertFromNmeaSentenceToDecimalCoord(aux);
    if(strcmp(strtok(NULL, ","), "S") == 0){
      strcat(params, "-");
    }   
    strcat(params,aux);

    strcat(params, "&lon=");
    strcpy(aux, strtok(NULL, ",")); // Gets longitude
    strcat(aux, "\0");
    //convertFromNmeaSentenceToDecimalCoord(aux);
    if(strcmp(strtok(NULL, ","), "W") == 0){
      strcat(params, "-");
    }
    strcat(params,aux);
    /*
    strcat(params, "&alt=");
    strcat(params,strtok(NULL, ".")); // Gets altitude 
    strtok(NULL, ",");
    strcat(params, "&dat=");
    strcat(params, strtok(NULL, ".")); // Gets date
    strtok(NULL, ",");
    strtok(NULL, ",");
    strcat(params, "&stl=");
    strcat(params, strtok(NULL, ",")); // Gets satellites
    strcat(params, "&spd=");
    strcat(params, strtok(NULL, ",")); // Gets speed over ground. Unit is knots.
    strcat(params, "&cou=");
    strcat(params, strtok(NULL, "\r")); // Gets course
    strcat(params, "\0");
    */
    
    
}



void debugPrint(const char* debugString){
    if(debugMode) { 
        Serial.println(debugString); 
    }
}
