# Les 4 & 5

door Lode Allaert

1. Welk geheugen is ideaal om instellingen te bewaren?

    EEPROM

2. Welke signaalversterker kan geen grote stromen aan?

    Optocoupler

3. Wat is het verschil tussen I²C en SPI?

    Beide zijn een protocol voor de communicatie tussen 2 IC’s.

    SPI staat voor Serial Peripheral Interface en is ontwikkelt voor korte afstanden. Hierbij zijn geen adressen nodig. Wel extra pinnen (pin per slave). Bij I²C moet elke slave een uniek adres hebben.

4. In welk deel van het geheugen worden globale en statische variabelen opgeslagen?

    SRAM in de static data

5. In welk geheugen wordt de code bewaard?

    Flash

6. In welk geheugen worden de variabelen opgeslagen?

    SRAM

7. In welk deel van het geheugen wordt dynamisch gealloceerde data opgeslagen?

    SRAM in de Heap

8. Wat is een probleem bij wrapping?

    Je kan naar een adres schrijven hoger van 1023 bv. adres 1024 zal schrijven naar adres 0

9. In welk deel van het geheugen worden functies of interrupts aangeroepen?

    SRAM in de Stack

10. Welke signaalversterker laat WEL ompooling to

    H-Brug

11. Wat is een beperking van EEPROM?

    De standaard lees- en schrijffuncties laten enkel bytes toe, andere datatypes zijn mogelijk met externe bibliotheken

12. Wat zijn de 2 mogelijkheden van ADC’s in AVR controllers?

    1. Single ended (ingangsspanning wordt vergeleken met GND)

    2. Differential (2 ingangswaarden worden van elkaar afgetrokken)

13. Wat is een Gain Error?

    Er kunnen in een schakeling offset error ontstaan, na de offsetcompensatie uit te voeren kan er een afwijking zijn van de maximum waarde. Dit is een Gain Error

14. Welke signaalversterker kan gebruikt worden om DC-netwerken van elkaar te scheiden?

    Optocoupler

15. Wat zijn de 2 data lijnen van de I²C bus?

    1. SCL-lijn (Serial Clock)

    2. SDA-lijn (Serial Data)

16. Wat zijn de 2 datalijnen van een SPI bus?

    1. MISO: Master in slave out (master lezen)

    2. MOSI: Master out slave in (master schrijven)

17. Wat is de waarde van de R/W bit bij het lezen en schrijven bij het I²C protocol?

    Schrijven: R/W bit op 0

    Lezen: R/W bit op 1

18. Welke signaalversterker kan gebruikt worden voor DC motoren

    H-Brug

19. Welke 2 signaalversterkers zijn galvanisch gescheiden?

    Relais, Optocoupler

20. Welke signaalversterker is de traagste van de 4
    1. Transistor

    2. Relais

    3. H-Brug

    4. Optocoupler
