// 라이브러리 해더 
#include <SPI.h>
#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#define POT_PIN_1 A0
#define POT_PIN_2 A1

int buzzer = 8;  // buzzer을 9로 설정합니다

int val1 = 0;
int val2 = 0;
int num1 = 0;
int num2 = 0;

byte temp1[4] = {0xC6, 0x0E, 0x77, 0x2B};
int check = 0;

// SS(Chip Select)과 RST(Reset) 핀 설정
// 나머지 PIN은 SPI 라이브러리를 사용하기에 별도의 설정이 필요없다.
#define SS_PIN 10
#define RST_PIN 9
 
// 라이브러리 생성
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

//이전 ID와 비교하기위한 변수
byte nuidPICC[4];


void setup() { 
  Serial.begin(9600); // 시리얼 통신 시작
  
  SPI.begin(); // SPI 시작
  rfid.PCD_Init(); // RFID 시작

  //초기 키 ID 초기화
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  
//  Serial.println(F("This code scan the MIFARE Classsic NUID."));
//  Serial.println(F("Using the following key:"));
//  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
//  Serial.println("");
}



 
void loop() {



  // 조도센서
  
  val1 = analogRead(POT_PIN_1);
  
  

  if(val1 < 20) { // 어두울때
    num1 = 1;
//    Serial.print("num1:");
//    Serial.print(num1);
//    Serial.print("/");
//    delay(1000);
  } 
  else {  // 밝을 때 즉, 일어났을 때
    num1 = 0;
//    Serial.print("num1:");
//    Serial.print(num1);
//    Serial.print("/");
//    delay(1000);
    }
  

  val2 = analogRead(POT_PIN_2);
  
  if(val2 < 20) { // 어두울때
    num2 = 1;
    pinMode(POT_PIN_2, OUTPUT);              // buzzer를 출력핀으로 설정합니다.
    digitalWrite(POT_PIN_2, HIGH);
    pinMode(POT_PIN_2, INPUT);
//    Serial.print("num2:");
//    Serial.print(num2);
//    Serial.print("/");
//    delay(1000);
    
  } else { // 밝을 때 즉, 일어났을 때
    num2 = 0;
//    Serial.print("num2:");
//    Serial.print(num2);
//    Serial.print("/");
//    delay(1000);
    }

    Serial.print("num1:");
    Serial.print(num1);
    Serial.print("/");
    Serial.print("num2:");
    Serial.print(num2);
    Serial.print("/");
    delay(100);
  

  // 카드가 인식되었다면 다음으로 넘어가고 아니면 더이상 
  // 실행 안하고 리턴
  if ( ! rfid.PICC_IsNewCardPresent()){
    return;
  }

  // ID가 읽혀졌다면 다음으로 넘어가고 아니면 더이상 
  // 실행 안하고 리턴
  if ( ! rfid.PICC_ReadCardSerial()){
     return;
  }
    

  Serial.print(F("PICC type: "));

  //카드의 타입을 읽어온다.
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

  //모니터에 출력
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // MIFARE 방식인지 확인하고 아니면 리턴
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  // 만약 바로 전에 인식한 RF 카드와 다르다면..
  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

//    pinMode(buzzer, OUTPUT);              // buzzer를 출력핀으로 설정합니다.
//    digitalWrite(buzzer, HIGH);
//    digitalWrite(buzzer, HIGH);
//    delay(500);                               // buzzer에 0.5초간 HIGH를 출력합니다.
//    pinMode(buzzer, INPUT);              // buzzer를 입력핀으로 설정합니다.
    

    // ID를 저장해둔다.    
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
    //모니터 출력
    Serial.println(F("The NUID tag is:"));

    Serial.print(F("In hex: "));
    //16진수로 변환해서 출력
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();


    Serial.print(F("In dec: "));
    //10진수로 출력
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }
  else Serial.println(F("Card read previously.")); //바로 전에 인식한 것과 동일하다면 

  // PICC 종료
  rfid.PICC_HaltA();

  // 암호화 종료(?)
  rfid.PCD_StopCrypto1();

  //다시 처음으로 돌아감.
}

//16진수로 변환하는 함수
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    if (temp1[i] != buffer[i]) 
      check = 1;
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
  if(check == 0) {
    Serial.println("Incorrect card!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    pinMode(buzzer, OUTPUT);              // buzzer를 출력핀으로 설정합니다.
    digitalWrite(buzzer, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);                               // buzzer에 0.5초간 HIGH를 출력합니다.
    pinMode(buzzer, INPUT);              // buzzer를 입력핀으로 설정합니다.
  }
    check = 0;
}

//10진수로 변환하는 함수
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
