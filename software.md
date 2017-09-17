# ![](https://www.arduino.cc/en/pub/skins/arduinoWide/img/ArduinoAPP-01.svg)

# IDE do Arduino

Para a manipulação do código foi utilizado uma plataforma de desenvolvimento criada pela Arduino. O programa permite edição de código e gravação dos mesmos via USB para o Arduino. Com isso, o sistema é totalmente programável e seus componentes podem ser manipulados dessa maneira.

## Bibliotecas

Nosso projeto requer algumas bibliotecas de código customizadas para o propósito de controlar o Hardware específico que foi selecionado.

#### LyquidCrystal I2C

Tem como propósito controlar a tela LCD 16x2 selecionada. A biblioteca foi escolhida no lugar da LyquidCrystal que é pré instalada por causa de sua simplicidade maior de interação com adaptadores. Essa biblioteca economiza fios conectores em relação a original.

#### MFRC522

Biblioteca que gerencia o leitor de dados RFID.

#### RFID-Master

Biblioteca que gerencia o gravador de dados RFID.

## Código

### Manipulação da tela

```
// Programa : Display LCD 16x2 e modulo I2C

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o display no endereco 0x27 ou 0x3f
LiquidCrystal_I2C lcd(0x3f,2,1,0,4,5,6,7,3, POSITIVE);
 
void setup()
{
 lcd.begin (16,2);
}
 
void loop()
{
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Foodtece!!!");
  lcd.setCursor(0,1);
  lcd.print("Sejam Bem-vindo");
  delay(4000);
  lcd.setBacklight(LOW);
  delay(1000);
}
```

### Manipulação de componentes a Rádio Frequencia \(RFID\)

```
// Programa: CONTROLE DE ACESSO VIA RFID. 
 
//Bibliotecas
#include <SPI.h>
#include <MFRC522.h>
 
//Pinos
#define SS_PIN 10
#define RST_PIN 9
 
String IDtag = ""; //Variável que armazenará o ID da Tag
bool Permitido = false; //Variável que verifica a permissão 
 
//Vetor responsável por armazenar os ID's das Tag's cadastradas
String TagsCadastradas[] = {"ID_1", 
                            "ID_2",
                            "ID_3"};
 
MFRC522 LeitorRFID(SS_PIN, RST_PIN);    // Cria uma nova instância para o leitor e passa os pinos como parâmetro
 
 
void setup() {
        Serial.begin(9600);             // Inicializa a comunicação Serial
        SPI.begin();                    // Inicializa comunicacao SPI 
        LeitorRFID.PCD_Init();          // Inicializa o leitor RFID
}
 
void loop() {  
  Leitura();  //Chama a função responsável por fazer a leitura das Tag's
}
 
void Leitura(){
 
        IDtag = ""; //Inicialmente IDtag deve estar vazia.
        
        // Verifica se existe uma Tag presente
        if ( !LeitorRFID.PICC_IsNewCardPresent() || !LeitorRFID.PICC_ReadCardSerial() ) {
            delay(50);
            return;
        }
        
        // Pega o ID da Tag através da função LeitorRFID.uid e Armazena o ID na variável IDtag        
        for (byte i = 0; i < LeitorRFID.uid.size; i++) {        
            IDtag.concat(String(LeitorRFID.uid.uidByte[i], HEX));
        }        
        
        //Compara o valor do ID lido com os IDs armazenados no vetor TagsCadastradas[]
        for (int i = 0; i < (sizeof(TagsCadastradas)/sizeof(String)); i++) {
          if(  IDtag.equalsIgnoreCase(TagsCadastradas[i])  ){
              Permitido = true; //Variável Permitido assume valor verdadeiro caso o ID Lido esteja cadastrado
          }
        }       
 
        if(Permitido == true) acessoLiberado(); //Se a variável Permitido for verdadeira será chamada a função acessoLiberado()        
        else acessoNegado(); //Se não será chamada a função acessoNegado()
 
        delay(2000); //aguarda 2 segundos para efetuar uma nova leitura
}
 
void acessoLiberado(){
  Serial.println("Tag Cadastrada: " + IDtag); //Exibe a mensagem "Tag Cadastrada" e o ID da tag não cadastrada
    Permitido = false;  //Seta a variável Permitido como false novamente
}
 
void acessoNegado(){
  Serial.println("Tag NAO Cadastrada: " + IDtag); //Exibe a mensagem "Tag NAO Cadastrada" e o ID da tag cadastrada
  
}
 

```

![](https://www.android.com/static/2016/img/logo-android-green_1x.png)

# Aplicativo para Android

Em adição ao sistema apresentado, será desenvolvido em conjunto um protótipo de Aplicativo de Android que auxilia o usuário a interagir no processo de compra e venda. Isso irá garantir mais eficiência no sistema Point of Sale e um engajamento de usuários maior.

![](https://www.python.org/static/community_logos/python-logo.png)

## Python

Escolhemos a linguagem Python para o nosso projeto por ser uma linguagem de fácil implementação e simples de se trabalhar, com funções fáceis e também é orientada a objetos. Usaremos essa linguagem para programar a parte mobile do nosso projeto que trabalhará em conjunto com nosso hardware rodando em Arduíno.

Quanto as especificações do Python, usaremos a sua terceira versão, o Python3 por ser a mais nova desenvolvida até o momento e a mais simples de se trabalhar, ja que ela apresenta melhoras em funções que eram mais complicadas em suas versões anteriores, tendo também, caso necessário, IDEs online para a codificação, caso seja algo simples e que não precise de muitas linhas de código para executar a tarefa

