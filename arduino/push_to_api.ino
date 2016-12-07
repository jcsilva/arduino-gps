void push_to_api(char* target_gps_data){
    int aux;
    int data_size = 0;
    int8_t answer;
    const unsigned int BUF_SIZE = 250;
    char request[BUF_SIZE];
    char aux_str[BUF_SIZE];
    
    // request the url
    snprintf(aux_str, BUF_SIZE, "AT+CHTTPACT=\"%s\",%d", url, port);
    answer = sendATcommand(aux_str, "+CHTTPACT: REQUEST", 60000);

    if (answer == 1){
        snprintf(request, BUF_SIZE, "GET %s%s HTTP/1.1\r\nHost: %s\r\n\r\n", apiEndpoint, target_gps_data, host);
        Serial.println(request);
        // Sends <Ctrl+Z>
        aux_str[0] = 0x1A;
        aux_str[1] = 0x00;
        answer = sendATcommand(aux_str, "+CHTTPACT: DATA,", 60000);

        int x=0;
        do{
            if (answer == 1)
            {
                data_size = 0;
                while(Serial.available()==0);
                aux = Serial.read();
                do{
                    data_size *= 10;
                    data_size += (aux-0x30);
                    while(Serial.available()==0);
                    aux = Serial.read();        
                }
                while(aux != 0x0D);

                debugPrint("Data received");
                
            }
            else
            {
                debugPrint("Error getting the url");
                data_size = 0;
            }
            
        } while (answer != 1);

    }
    else
    {
        debugPrint("Error waiting the request");    
    }

    delay(1000);
}
