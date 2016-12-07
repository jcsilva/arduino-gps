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

    //Serial.println(response);

    return answer;
}


int8_t get_GPS_data(char* retrieved_gps_data, float* velocity){
  int counter = 0;
  int8_t answer;
  char gps_data[100];

  
  
  answer = sendATcommand("AT+CGPSINFO","+CGPSINFO:",1000);
  
  if (answer == 1){
    do{
      while(Serial.available() == 0);
      gps_data[counter] = Serial.read();
      counter++;
    }while(gps_data[counter - 1] != '\r');
    
    gps_data[counter] = '\0';
    
    if(gps_data[0] == ','){
      debugPrint("No GPS data available");
      return -1; // no gps data  
    }
    else{
      debugPrint("GPS data:");
      debugPrint(gps_data);    
      get_GPS_params(retrieved_gps_data, velocity, gps_data);                  
      debugPrint(retrieved_gps_data);
      //temporarily holds data from vals
      char charVelocity[10];
      //4 is mininum width, 3 is precision; float value is copied onto buff
      dtostrf(*velocity, 4, 3, charVelocity);
      debugPrint(charVelocity);
      debugPrint("All Good!");      
      return 0; // ok
    }       
  }else{
    debugPrint("Error");
    return -2; // Error 
  }
}

void get_GPS_params(char* params, float* velocity, char* frame){

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
    strcat(params, "&date=");
    strcat(params,strtok(NULL, ",")); // Gets date. Format: ddmmyy
    strcat(params, "&utctime=");
    strcat(params, strtok(NULL, ",")); // Gets UTC time. Format: hhmmss.s
    strcat(params, "&alt=");
    strcat(params, strtok(NULL, ",")); // Gets altitude in meters
    strcat(params, "&speed=");
    strcpy(aux, strtok(NULL, ",")); // Gets speed over ground. Unit is knots.
                                    // 1 knot = 1.852 km/h
    strcat(aux, "\0");      
    *velocity = atof(aux);
    strcat(params, aux);
    strcat(params, "&time=");
    strcat(params, strtok(NULL, "\r")); // Gets time (The  range  is  0-255,  
                                        // unit  is  second,  after  set  <time> 
                                        // will  report  the  GPS  information  
                                        // every  the  seconds. )
    strcat(params, "\0");
    
}

int8_t get_speed(const char* const gps_data){
  return 1;
}

void debugPrint(const char* debugString){
    if(debugMode) { 
        Serial.println(debugString); 
    }
}
