void Process_Manager()
{
  const int NUMBER_OF_MODES = 3;
  int mode = 0;
  String tab[NUMBER_OF_MODES];
  tab[0] = "Dodaj Proces";
  tab[1] = "Edytuj Proces";
  tab[2] = "Usun Proces";
  lcd.print(tab[mode]);
  while (1) {
    if ( digitalRead(KEY_UP) == HIGH ) {
      while (digitalRead(KEY_UP) == HIGH);
      mode++;
      mode = mode % NUMBER_OF_MODES;
      lcd.clear();
      lcd.print(tab[mode]);
    }
    else if ( digitalRead(KEY_DOWN) == HIGH ) {
      while (digitalRead(KEY_DOWN) == HIGH);
      if (mode == 0) mode = NUMBER_OF_MODES;
      mode--;
      lcd.clear();
      lcd.print(tab[mode]);
    }
    else if ( digitalRead(KEY_OK) == HIGH ) {
      while (digitalRead(KEY_OK) == HIGH);
      lcd.clear();
      switch (mode) {
        case 0: {
            Add_Process();
            lcd.print(tab[mode]);
            break;
          }
        case 1: {
            Edit_Process();
            lcd.print(tab[mode]);
            break;
          }
        case 2: {
            Delete_Process();
            lcd.print(tab[mode]);
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




void Add_Process()
{
  int process = First_Empty();
  lcd.clear();
  if (Number_Of_Empty() == 0 ) {
    lcd.print("Brak Pustych");
    lcd.setCursor(4, 1);
    lcd.print("miejsc");
  }
  else {
    lcd.print(ProcessTable[process].Get_Name());
  }
  while (1) {
    if (Number_Of_Empty() > 0) {
      if ( digitalRead(KEY_UP) == HIGH ) {
        while (digitalRead(KEY_UP) == HIGH);
        process = Next_Empty(process);
        lcd.clear();
        lcd.print(ProcessTable[process].Get_Name());
      }
      else if ( digitalRead(KEY_DOWN) == HIGH ) {
        while (digitalRead(KEY_DOWN) == HIGH);
        process = Previous_Empty(process);
        lcd.clear();
        lcd.print(ProcessTable[process].Get_Name());
      }
      else if ( digitalRead(KEY_OK) == HIGH) {
        while (digitalRead(KEY_OK) == HIGH);
        lcd.clear();
        String tmp = Add_Process_Get_Name();
        if ( tmp != "-1") {
          ProcessTable[process].Set_Name(tmp);
          ProcessTable[process].Set_Non_Empty();
          lcd.clear();
          ProcessTable[process].number_of_phases=0;
          int number_of_phases = Get_Number_Of_Phases();
          for (int i=0;i<number_of_phases;i++)
          {
             int dur = Add_Phase_Duration(i+1);
             int temp = Add_Phase_Temperature(i+1);
             ProcessTable[process].phases[i].set_temperature(temp);
             ProcessTable[process].phases[i].set_duration(dur);
             ProcessTable[process].number_of_phases++;
          }
              Serial.print("Dodanie: ");
          Serial.println(ProcessTable[process].Get_Number_Of_Phases());
          return;
          }
          else {
            ProcessTable[process].Set_Non_Empty();
            lcd.print(ProcessTable[process].Get_Name());
            
            };
        }
      }
      if ( digitalRead(KEY_BACK) == HIGH) {
        while (digitalRead(KEY_BACK) == HIGH);
        lcd.clear();
        return;
      }
    }
  }


void Delete_Process()
{
  int process = First_Non_Empty();
  lcd.print(ProcessTable[process].Get_Name());
  while (1) {
    if (Number_Of_Empty() <MAX_PROCESS_NUMBER){
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
    else if ( digitalRead(KEY_OK) == HIGH) {
      while (digitalRead(KEY_OK) == HIGH);
      lcd.clear();
      lcd.print("Potwierdz aby");
      lcd.setCursor(4, 1);
      lcd.print("usunac");
      while (1) {
        if ( digitalRead(KEY_OK) == HIGH) {
          while (digitalRead(KEY_OK) == HIGH);
          ProcessTable[process].Set_Name((String)"----Wolny-" + process + "---");
          ProcessTable[process].Set_Empty();
          lcd.clear();
          process = First_Non_Empty();
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
    else{
      lcd.clear();
      lcd.print("Brak Procesow");
      while(1){
        if ( digitalRead(KEY_BACK) == HIGH ) {
      while (digitalRead(KEY_BACK) == HIGH);
      lcd.clear();
      return;
    }
      }
    }

    
  }
}

void Edit_Process()
{
  
  int process = First_Non_Empty();
  lcd.print(ProcessTable[process].Get_Name());
  while (1) {
    if (Number_Of_Empty() <MAX_PROCESS_NUMBER){
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
    else if ( digitalRead(KEY_OK) == HIGH) {
      while (digitalRead(KEY_OK) == HIGH);
        String tmp_name = Edit_Process_Get_Name(process);
        if (tmp_name != "-1"){
        int number_of_phases = ProcessTable[process].Get_Number_Of_Phases();
        for (int i=0;i<number_of_phases;i++)
          {
             ProcessTable[process].phases[i].set_duration(Edit_Phase_Duration(process,i+1));
             ProcessTable[process].phases[i].set_temperature( Edit_Phase_Temperature(process,i+1));
          }
          }
           lcd.clear();
      lcd.print(ProcessTable[process].Get_Name());
    }
    else if ( digitalRead(KEY_BACK) == HIGH ) {
      while (digitalRead(KEY_BACK) == HIGH);
      lcd.clear();
      return;
    }
    
    }
    else{
      lcd.clear();
      lcd.print("Brak Procesow");
      while(1){
        if ( digitalRead(KEY_BACK) == HIGH ) {
      while (digitalRead(KEY_BACK) == HIGH);
      lcd.clear();
      return;
    }
      }
    }

    
  }
}
int Edit_Phase_Temperature(int process ,int index) {
  const int MAX_TEMPERATURE = 100;
  int time = ProcessTable[process].phases[index-1].get_temperature();
  lcd.clear();
  lcd.print("Temperatura ");
  lcd.print(index);
  lcd.setCursor(0, 1);
  lcd.print(time);
  while (1) {
    if ( digitalRead(KEY_UP) == HIGH ) {
      while (digitalRead(KEY_UP) == HIGH);
      time++;
      time = time % (MAX_TEMPERATURE+1);
      lcd.setCursor(0, 1);
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print(time);
    }
    else if ( digitalRead(KEY_DOWN) == HIGH ) {
      while (digitalRead(KEY_DOWN) == HIGH);
      if (time == 0) time = MAX_TEMPERATURE;
      else  time--;
      lcd.setCursor(0, 1);
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print(time);
    }
    else if (digitalRead(KEY_OK) == HIGH ) {
      while (digitalRead(KEY_OK) == HIGH);
      lcd.clear();
      return time;
    }
    else if ( digitalRead(KEY_BACK) == HIGH ) {
      while (digitalRead(KEY_BACK) == HIGH);
    }
  }
}

int Edit_Phase_Duration(int process ,int index) {
  const int MAX_DURATION = 300;
  int time =ProcessTable[process].phases[index-1].get_duration();
  lcd.clear();
  lcd.print("Czas Fazy ");
  lcd.print(index);
  lcd.setCursor(0, 1);
  lcd.print(time);
  while (1) {
    if ( digitalRead(KEY_UP) == HIGH ) {
      while (digitalRead(KEY_UP) == HIGH);
      time++;
      time = time % (MAX_DURATION+1);
      lcd.setCursor(0, 1);
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print(time);
    }
    else if ( digitalRead(KEY_DOWN) == HIGH ) {
      while (digitalRead(KEY_DOWN) == HIGH);
      if (time == 0) time = MAX_DURATION;
      else  time--;
      lcd.setCursor(0, 1);
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print(time);
    }
    else if (digitalRead(KEY_OK) == HIGH ) {
      while (digitalRead(KEY_OK) == HIGH);
      lcd.clear();
      return time;
    }
    else if ( digitalRead(KEY_BACK) == HIGH ) {
      while (digitalRead(KEY_BACK) == HIGH);
    }
  }
}
String Edit_Process_Get_Name(int index) {
  char letter = 65;
  String name = ProcessTable[index].Get_Name();
  int number_of_letters = name.length();
  lcd.clear();
  lcd.print("Podaj Nazwe:");
  lcd.setCursor(0,1);
  lcd.print(name);
  lcd.print(letter);
  while (1) {
    lcd.setCursor(number_of_letters, 1);
    lcd.blink();
    if ( digitalRead(KEY_UP) == HIGH ) {
      while (digitalRead(KEY_UP) == HIGH);
      letter = Next_Char(letter);
      lcd.setCursor(number_of_letters, 1);
      lcd.print(letter);
    }
    else if ( digitalRead(KEY_DOWN) == HIGH ) {
      while (digitalRead(KEY_DOWN) == HIGH);
      letter = Previous_Char(letter);
      lcd.setCursor(number_of_letters, 1);
      lcd.print(letter);
    }
    else if ( digitalRead(KEY_OK) == HIGH && number_of_letters < 16 && letter != (char)1) {
      while (digitalRead(KEY_OK) == HIGH);
      name += letter;
      delay(10);
      number_of_letters++;
      delay(10);
      letter = 65;
      lcd.setCursor(number_of_letters, 1);
      lcd.print(letter);
    }
    else if (digitalRead(KEY_OK) == HIGH && number_of_letters < 16&& number_of_letters >0 && letter == (char)1) {
      while (digitalRead(KEY_OK) == HIGH);
      lcd.noBlink();
      lcd.clear();
      return name;
    }
    else if ( digitalRead(KEY_BACK) == HIGH ) {
      while (digitalRead(KEY_BACK) == HIGH);
      if (number_of_letters > 0) {
        number_of_letters--;
        letter = name.charAt(number_of_letters);
        name.remove(number_of_letters);
        lcd.clear();
        lcd.print("Podaj Nazwe:");
        lcd.setCursor(0, 1);
        lcd.print(name);
        lcd.print(letter);
      }
      else
      {
        name = "";
        lcd.noBlink();
        lcd.clear();
        return "-1";
      }
    }
  }
}

  char Next_Char(char index) {
    if (index == 57) return (char)1;
    else if (index == (char)1) return 65;
    else if (index == 90) return 97;
    else if (index == 122) return 48;
    return ++index;
  }
  char Previous_Char(char index) {
    if (index == 48) return 122;
    else if (index == 97) return 90;
    else if (index == 65) return (char)1;
    else if (index == (char)1) return 57;
    return --index;
  }

String Add_Process_Get_Name() {
  char letter = 65;
  String name = "";
  int number_of_letters = 0;
  lcd.clear();
  lcd.print("Podaj Nazwe:");
  lcd.setCursor(number_of_letters, 1);
  lcd.print(letter);
  while (1) {
    lcd.setCursor(number_of_letters, 1);
    lcd.blink();
    if ( digitalRead(KEY_UP) == HIGH ) {
      while (digitalRead(KEY_UP) == HIGH);
      letter = Next_Char(letter);
      lcd.setCursor(number_of_letters, 1);
      lcd.print(letter);
    }
    else if ( digitalRead(KEY_DOWN) == HIGH ) {
      while (digitalRead(KEY_DOWN) == HIGH);
      letter = Previous_Char(letter);
      lcd.setCursor(number_of_letters, 1);
      lcd.print(letter);
    }
    else if ( digitalRead(KEY_OK) == HIGH && number_of_letters < 16 && letter != (char)1) {
      while (digitalRead(KEY_OK) == HIGH);
      name += letter;
      delay(10);
      number_of_letters++;
      delay(10);
      letter = 65;
      lcd.setCursor(number_of_letters, 1);
      lcd.print(letter);
    }
    else if (digitalRead(KEY_OK) == HIGH && number_of_letters < 16 && letter == (char)1) {
      while (digitalRead(KEY_OK) == HIGH);
      lcd.noBlink();
      lcd.clear();
      return name;
    }
    else if ( digitalRead(KEY_BACK) == HIGH ) {
      while (digitalRead(KEY_BACK) == HIGH);
      if (number_of_letters > 0) {
        number_of_letters--;
        letter = name.charAt(number_of_letters);
        name.remove(number_of_letters);
        lcd.clear();
        lcd.print("Podaj Nazwe:");
        lcd.setCursor(0, 1);
        lcd.print(name);
        lcd.print(letter);
      }
      else
      {
        name = "";
        lcd.noBlink();
        lcd.clear();
        return "-1";
      }
    }
  }
}

  int Get_Number_Of_Phases() {
  const int MAX_DURATION = 6;
  int phases =1;
  lcd.clear();
  lcd.print("Podaj ilosc faz");
  lcd.setCursor(0, 1);
  lcd.print(phases);
  while (1) {
    if ( digitalRead(KEY_UP) == HIGH ) {
      while (digitalRead(KEY_UP) == HIGH);
      if (phases ==MAX_DURATION) phases = 1;
      else phases++;
      lcd.setCursor(0, 1);
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print(phases);
    }
    else if ( digitalRead(KEY_DOWN) == HIGH ) {
      while (digitalRead(KEY_DOWN) == HIGH);
      if (phases == 1) phases = MAX_DURATION;
      else  phases--;
      lcd.setCursor(0, 1);
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print(phases);
    }
    else if (digitalRead(KEY_OK) == HIGH ) {
      while (digitalRead(KEY_OK) == HIGH);
      lcd.clear();
      return phases;
    }
  }
}
int Add_Phase_Temperature(int index) {
  const int MAX_TEMPERATURE = 100;
  int time =0;
  lcd.clear();
  lcd.print("Temperatura ");
  lcd.print(index);
  lcd.setCursor(0, 1);
  lcd.print(time);
  while (1) {
    if ( digitalRead(KEY_UP) == HIGH ) {
      while (digitalRead(KEY_UP) == HIGH);
      time++;
      time = time % (MAX_TEMPERATURE+1);
      lcd.setCursor(0, 1);
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print(time);
    }
    else if ( digitalRead(KEY_DOWN) == HIGH ) {
      while (digitalRead(KEY_DOWN) == HIGH);
      if (time == 0) time = MAX_TEMPERATURE;
      else  time--;
      lcd.setCursor(0, 1);
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print(time);
    }
    else if (digitalRead(KEY_OK) == HIGH ) {
      while (digitalRead(KEY_OK) == HIGH);
      lcd.clear();
      return time;
    }
    else if ( digitalRead(KEY_BACK) == HIGH ) {
      while (digitalRead(KEY_BACK) == HIGH);
    }
  }
}

int Add_Phase_Duration(int index) {
  const int MAX_DURATION = 300;
  int time =0;
  lcd.clear();
  lcd.print("Czas Fazy ");
  lcd.print(index);
  lcd.setCursor(0, 1);
  lcd.print(time);
  while (1) {
    if ( digitalRead(KEY_UP) == HIGH ) {
      while (digitalRead(KEY_UP) == HIGH);
      time++;
      time = time % (MAX_DURATION+1);
      lcd.setCursor(0, 1);
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print(time);
    }
    else if ( digitalRead(KEY_DOWN) == HIGH ) {
      while (digitalRead(KEY_DOWN) == HIGH);
      if (time == 0) time = MAX_DURATION;
      else  time--;
      lcd.setCursor(0, 1);
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print(time);
    }
    else if (digitalRead(KEY_OK) == HIGH ) {
      while (digitalRead(KEY_OK) == HIGH);
      lcd.clear();
      return time;
    }
    else if ( digitalRead(KEY_BACK) == HIGH ) {
      while (digitalRead(KEY_BACK) == HIGH);
    }
  }
}



int Number_Of_Empty()
{
  int sum = 0;
  for (int i = 0; i < MAX_PROCESS_NUMBER; i++)
  {
    if (ProcessTable[i].Is_Empty())sum++;
  }
  return sum;
}
int First_Empty()
{
  for (int i = 0; i < MAX_PROCESS_NUMBER; i++)
  {
    if (ProcessTable[i].Is_Empty()) return i;
  }
  return -1;
}
int Next_Empty(int index)
{
  for (int i = index + 1; i < MAX_PROCESS_NUMBER; i++)
  {
    if (ProcessTable[i].Is_Empty()) return i;
  }
  for (int i = 0; i < index; i++)
  {
    if (ProcessTable[i].Is_Empty()) return i;
  }
  return index;
}
int Previous_Empty(int index)
{
  for (int i = index - 1; i >= 0; i--)
  {
    if (ProcessTable[i].Is_Empty()) return i;
  }
  for (int i = MAX_PROCESS_NUMBER - 1; i > index; i--)
  {
    if (ProcessTable[i].Is_Empty()) return i;
  }

  return index;
}
int First_Non_Empty()
{
  for (int i = 0; i < MAX_PROCESS_NUMBER; i++)
  {
    if (!ProcessTable[i].Is_Empty()) return i;
  }
  return -1;
}
int Next_Non_Empty(int index)
{
  for (int i = index + 1; i < MAX_PROCESS_NUMBER; i++)
  {
    if (!ProcessTable[i].Is_Empty()) return i;
  }
  for (int i = 0; i < index; i++)
  {
    if (!ProcessTable[i].Is_Empty()) return i;
  }
  return index;
}
int Previous_Non_Empty(int index)
{
  for (int i = index - 1; i >= 0; i--)
  {
    if (!ProcessTable[i].Is_Empty()) return i;
  }
  for (int i = MAX_PROCESS_NUMBER - 1; i > index; i--)
  {
    if (!ProcessTable[i].Is_Empty()) return i;
  }

  return index;
}

