
void Start_Process(int process)
{
  lcd.clear();
  while(1)
  {
    lcd.clear();
    for (int i=0;i<ProcessTable[process].number_of_phases;i++)
    {    
      Start_Temperature(ProcessTable[process].phases[i].get_temperature());
      lcd.clear();
      long start = millis();
      lcd.print("Faza ");
      lcd.print(i+1);
      while ((millis()-start)/1000 < ProcessTable[process].phases[i].get_duration()*60)
      {
        Print_Time( ProcessTable[process].phases[i].get_duration()*60 - (millis()-start)/1000,1,0);
        Print_Temperature(1,8);
        Heater(process,i);
      }
      lcd.clear();
    }
  return;
  }
}

void Start_Temperature(int temp)
{
  const int delta = 2;
     sensors.requestTemperatures();
   float tempC = sensors.getTempC(Thermometer);
   lcd.clear();
   lcd.print("Uzyskiwanie temp");
   lcd.setCursor(8,1);
   lcd.print("z ");
   lcd.print(temp);
   lcd.print("C");
   while ( tempC < temp - delta)
   {  
      sensors.requestTemperatures();
      tempC = sensors.getTempC(Thermometer);
      
      lcd.setCursor(0,1);
      lcd.print(tempC);
      lcd.print("C");
      digitalWrite(HEATER,HIGH); digitalWrite(LED,HIGH);
   }
   while (tempC > temp  + delta )
   {
      sensors.requestTemperatures();
      tempC = sensors.getTempC(Thermometer);
            lcd.setCursor(0,1);
      lcd.print(tempC);
      lcd.print("C");
      digitalWrite(HEATER,LOW); digitalWrite(LED,LOW);
   }
   digitalWrite(HEATER,LOW); digitalWrite(LED,LOW);
}

void Heater(int process,int phase)
{
    const int delta = 2;
   sensors.requestTemperatures();
   float tempC = sensors.getTempC(Thermometer);
  if ( tempC >= ProcessTable[process].phases[phase].get_temperature()) {digitalWrite(HEATER,LOW); digitalWrite(LED,LOW);};
  if ( tempC < ProcessTable[process].phases[phase].get_temperature()-delta) {digitalWrite(HEATER,HIGH);digitalWrite(LED,HIGH);};
}
void Print_Temperature(int line,int column)
{
        sensors.requestTemperatures();
        float tempC = sensors.getTempC(Thermometer);
        lcd.setCursor(column,line);
        lcd.print(tempC);
        lcd.print((char)223);
        lcd.print("C");
}
void Print_Time(long time,int line,int column)
{
        lcd.setCursor(column,line);
        lcd.print(time/60);
        lcd.print(":");
        if (time % 60 <10)
        {
         lcd.print("0");
         lcd.print(time % 60) ;
        }
        else lcd.print(time % 60);
        ;
}

void Sub_Menu()
{
  int process = First_Non_Empty();
  lcd.print(ProcessTable[process].Get_Name());
  while (1) {
    if ( digitalRead(KEY_UP) == HIGH ) {
      while (digitalRead(KEY_UP) == HIGH);
      process = Next_Non_Empty(process);
      lcd.clear();
      lcd.print(ProcessTable[process].Get_Name());
    }
    else if ( digitalRead(KEY_DOWN) == HIGH ) {
      while (digitalRead(KEY_DOWN) == HIGH);
      process = Previous_Non_Empty(process);
      lcd.clear();
      lcd.print(ProcessTable[process].Get_Name());
    }
    else if ( digitalRead(KEY_OK) == HIGH ) {
      while (digitalRead(KEY_OK) == HIGH);
      lcd.clear();
      lcd.print("Potwierdz aby");
      lcd.setCursor(2, 1);
      lcd.print("uruchomic");
      while (1) {
        if ( digitalRead(KEY_OK) == HIGH) {
          while (digitalRead(KEY_OK) == HIGH);
          lcd.clear();
          Start_Process(process);
          lcd.print(ProcessTable[process].Get_Name());
          break;
        }
        else if ( digitalRead(KEY_BACK) == HIGH) {
          while (digitalRead(KEY_BACK) == HIGH);
          lcd.clear();
          lcd.print(ProcessTable[process].Get_Name());
          break;
        }
      }
    }
    else if ( digitalRead(KEY_BACK) == HIGH ) {
      while (digitalRead(KEY_BACK) == HIGH);
      lcd.clear();
      return;
    }
  }
}
