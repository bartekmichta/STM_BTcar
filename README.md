STM_BTRobot

Projekt samochodziku sterowanego za pomocą aplikacji na telefon, komunikującej się poprzez  moduł bluetooth z płytką STM. Dzieki aplikacji
możemy wysyłać poszczególne znaki na płytkę STM która za pomocą sygnału PWM odpowiednio steruje silniczkami. Do kounikacji wykorzystywany jest 
szeregowy interfejs komunikacyjny USART.

Sprzęt:</br>

STM32F4 Discovery</br>
Moduł Bluetooth HC-06</br>
Podwozie 2WD Robot Car</br>
Do zasilania silników oraz płytki wykorzystano powerbank o natężeniu 1A</br>
Moduł podwójny sterownik silnika L9110</br>

Podłączenie urządzeń

HC-06

VCC -> 5V</br>
GND -> GND</br>
TxD -> PA3</br>
RxD -> PA2</br>

Sterownik silnika L9110

VCC -> 5V</br>
GND -> GND</br>
A-1A -> PB6</br>
A-1B -> PB8</br>
B-1A -> PB7</br>
B-2A -> PB9</br>

Autorzy:</br>
Bartosz Michta</br>
Emilian Ossowski
