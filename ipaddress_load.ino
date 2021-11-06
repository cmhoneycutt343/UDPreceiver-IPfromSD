void load_ip_fromfile(char filename[]){
  File textFile;
  const int chipSelect = BUILTIN_SDCARD;
  uint8_t incomingByte;
  int load_inc = 0;
  bool readbusy = false; 
  
  int ipoctetschars[12];

  iploadbusy=true;
  
  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    //return;
  }
  Serial.println("initialization done.");
  
  // if the file opened okay, write to it:
  
  // re-open the file for reading:
  textFile = SD.open(filename);
  if (textFile) {

    load_inc = 0;
    
    // read from the file until there's nothing else in it:
    readbusy=true;
    
    while (readbusy==true) 
    {
     incomingByte = textFile.read();

     Serial.println("");

     //load header and pixel arrays
     Serial.print("byte #:");
     Serial.print(load_inc); 
     Serial.print("-");
     Serial.println( (char) incomingByte);

     //load octet buffer
     switch(load_inc){
      case 0:
        ipoctetschars[0] = incomingByte - '0';
      break;  
      case 1:
        ipoctetschars[1] = incomingByte - '0';
      break;
      case 2:
        ipoctetschars[2] = incomingByte - '0';
      break;
      case 4:
        ipoctetschars[3] = incomingByte - '0';
      break;
      case 5:
        ipoctetschars[4] = incomingByte - '0';
      break;
      case 6:
        ipoctetschars[5] = incomingByte - '0';
      break;
      case 8:
        ipoctetschars[6] = incomingByte - '0';
      break;
      case 9:
        ipoctetschars[7] = incomingByte - '0';
      break;
      case 10:
        ipoctetschars[8] = incomingByte - '0';
      break;
      case 12:
        ipoctetschars[9] = incomingByte - '0';
      break;
      case 13:
        ipoctetschars[10] = incomingByte - '0';
      break;
      case 14:
        ipoctetschars[11] = incomingByte - '0';
      break;
     }

     load_inc++;

     //only read first 16 bytes
     if(load_inc==15){
        readbusy=false; 
     }
    }

    //calculate octets from chars
    ipoctets[0]=100*ipoctetschars[0]+10*ipoctetschars[1]+ipoctetschars[2];
    ipoctets[1]=100*ipoctetschars[3]+10*ipoctetschars[4]+ipoctetschars[5];
    ipoctets[2]=100*ipoctetschars[6]+10*ipoctetschars[7]+ipoctetschars[8];
    ipoctets[3]=100*ipoctetschars[9]+10*ipoctetschars[10]+ipoctetschars[11];
    Serial.print("Octect 1 - ");
    Serial.println(ipoctets[0]);
    Serial.print("Octect 2 - ");
    Serial.println(ipoctets[1]);
    Serial.print("Octect 3 - ");
    Serial.println(ipoctets[2]);
    Serial.print("Octect 4 - ");
    Serial.println(ipoctets[3]);

    textFile.close();    

    iploadbusy = false;
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
