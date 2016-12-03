
void getValues(){
  Serial.println("RECUPERANDO VALORES...");
  EEPROM_readAnything(0, configuration);
  Serial.print("ESCRITO:");
  Serial.println(configuration.writed);
  Serial.print("VALOR GRAVADO NA EEPROM");
  Serial.println(moeda);
  Serial.println(configuration.moeda);


  if(configuration.writed == 1){
    moeda = configuration.moeda;
    Serial.println("VALORES RECUPERADOS");
  }
  else{
    Serial.println("NÃO INICIALIZADO");
  }
  Serial.println("TERMINADO");

}

boolean saveValues(){
  Serial.println("SALVANDO VALORES...");
  configuration.writed = 1;
  configuration.moeda = moeda;


  Serial.print("Writed:");
  Serial.println(configuration.writed);
  Serial.print(moeda);
  Serial.println(configuration.moeda);

  EEPROM_writeAnything(0, configuration);
  Serial.println("Done");
}















