void Main_Menu()
{
  const int NUMBER_OF_MODES = 2;
  int mode = 0;
  String tab[NUMBER_OF_MODES];
  tab[0] = "Wybierz Proces";
  tab[1] = "Zarzadzaj";
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
            Sub_Menu();
            lcd.print(tab[mode]);
            break;
          }
        case 1: {
            Process_Manager();
            lcd.print(tab[mode]);
            break;
          }
      }
    }
  }
}
