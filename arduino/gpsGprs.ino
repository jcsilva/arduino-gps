// SCHEMA
// SETUP > LOOP > GET GPS > PUSH TO API > OK

/* PIN VARIABLES */
int onModulePin = 2;

/* DEBUG OMODE */
boolean debugMode = true;

/* SERVER API VARIALBLES */
char url[]         = "arduino-gps.herokuapp.com";
char host[]        = "arduino-gps.herokuapp.com";
char apiEndpoint[] = "/insert-record.php?";
int port           = 80;

enum state {
  RUNNING,
  PREPARE_TO_SLEEP,
  SLEEPING
};

const unsigned int LOOP_DELAY_MS = 5000;
const uint8_t SPEED_THRESHOLD_KNOT = 10; // 1 knot = 1.852 km/h
state currentState;
unsigned int msCounter, minCounter; //milisseconds and seconds counters

/* SETUP AND INIT */
void setup(){

  pinMode(onModulePin, OUTPUT);
  Serial.begin(115200);    

  debugPrint("Starting...");

  // power our SIM5128
  power_on();

  delay(5000);
  
  // sets the PIN code
  //sendATcommand("AT+CPIN=1111", "OK", 2000);
  
  delay(3000);

  // connect to the mobile network
  debugPrint("Connecting to the network...");

  while( (sendATcommand("AT+CREG?", "+CREG: 0,1", 500) || 
          sendATcommand("AT+CREG?", "+CREG: 0,5", 500)) == 0 );

  sendATcommand("AT+CGSOCKCONT=1,\"IP\",\"timbrasil.br\"","OK",1000); 
  //sendATcommand("AT+CSOCKAUTH=1,1,,\"web\",\"web\"","OK",1000);

  // set GPS server without certificate
  sendATcommand("AT+CGPSURL=\"supl.google.com:7276\"","OK",1000);
  sendATcommand("AT+CGPSSSL=0","OK",1000);
  
  // start gps node in GPS-MS
  int8_t answer = sendATcommand("AT+CGPS=1,2","OK",1000);
  if (answer == 0){
    debugPrint("Error starting the GPS");
    debugPrint("The code stucks here!!");
    while(1);
  }

  msCounter = 0;
  minCounter = 0;
  
  currentState = RUNNING;
  debugPrint("RUNNING state");
}

/* MAIN LOOP */
void loop(){

  char gps_data[250];
  float velocity = 0;  
  int8_t answer = get_GPS_data(gps_data, &velocity);
  
  if(answer == 0){
    switch (currentState){
      case RUNNING:
        state_run(gps_data, velocity);
        break;
      case PREPARE_TO_SLEEP:
        state_prep_to_sleep(gps_data, velocity);
        break;
      case SLEEPING:
        state_sleep(gps_data, velocity);
        break;
    }
  } // [TODO]: do something when an error happens??
  // For example, send SMS??

  debugPrint("Loop finished!");
  delay(LOOP_DELAY_MS);

}

void state_run(char* gps_data, float velocity){

  // reset milisseconds and seconds counters
  msCounter = 0;
  minCounter = 0;

  // push location to api
  push_to_api(gps_data);
  
  if(velocity < SPEED_THRESHOLD_KNOT){
   currentState = PREPARE_TO_SLEEP;
   debugPrint("PREPARE_TO_SLEEP state");
  }

}

void state_prep_to_sleep(char* gps_data, float velocity){
  // push location to api
  push_to_api(gps_data);
  
  if(velocity < SPEED_THRESHOLD_KNOT){
    msCounter = msCounter + LOOP_DELAY_MS;
    if (msCounter >= 60000){
      minCounter++;
    }
    if (minCounter > 60){
      currentState = SLEEPING;
      debugPrint("SLEEPING state");
    }
  }else{
    currentState = RUNNING;
    debugPrint("RUNNING state");
  }
}

void state_sleep(char* gps_data, float velocity){

  // [TODO]: turn off internet connection??

  // reset milisseconds and seconds counters
  // I know theses counters will be reset in running state.
  // This is just a "double check"
  msCounter = 0;
  minCounter = 0;
  
  if(velocity > SPEED_THRESHOLD_KNOT){
    currentState = RUNNING;
    debugPrint("RUNNING state");
  }
  
}

