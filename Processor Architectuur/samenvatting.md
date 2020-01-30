# Processor architectuur

voorlopig enkel hoofdstuk 1 & 2 - feel free to add

## 1 Overzicht  werking processor

### 1.1 Uitvoeren van programmacode

In de processor worden instructies verwerkt waaruit het besturingssysteem en de toepassing zijn gebouwd. Dit zijn een beperkt aantal relatief eenvoudige instructies, deze staan als binaire informatie opgeslagen in het geheugen. De geschreven code moet hiernaar omgezet worden.

#### 1.1.1 Managed code (_java_, _C#_, ...)

__werking:__
Code -> compiler -> Tussencode -> Interpreter -> CPU en OS

__Gevolgen:__
 - Extra bescherming door interpreter, geheugenbeheer gebeurt automatisch (performatiewinst)
 - Source code en tussencode kunnen niet rechtstreeks op CPU runnen
 - Interpreter bestaat uit native processorinstructies
 - Elke instructie in een lus wordt opnieuw geïnterpreteerd (performantieverlies)
  - __oplossing:__ Just in time compilatie -> instructies uit tussencode worden opgeslagen.

__Conclusie:__
 - Weinig performatieverlies bij goede kwaliteit code
 - Productiever en minder kans op fouten dan bij native code
 - Betere beveiliging dan native code

#### 1.1.2 Native code (_C_, _C++_, ...)

__werking:__
High level language -> compiler -> Executable -> CPU en OS

__Gevolgen:__
 - toepassingscode draait rechtstreeks op CPU
 - Technische aspecten zijn verantwoordelijkheid programmeur
 - Kans op hogere performantie
 - Meer kans op fouten

__Conclusie:__
 - Veel minder controle van OS op fouten & kwaadwillige code
 - Slechte code kan oorzaak zijn van instabiel systeem

#### 1.1.3 Assembly language

__werking:__
Low level assembler code -> Assembler -> excluded -> CPU en OS

__Gevolgen:__
 - programmeur bepaald tot laatste detail wat processor doet
 - Specifiek per CPU familie
 - Erg technisch

__Conclusie:__
 - Vereist goede ervaren programmeur
 - Kan voor maximale performantie zorgen
 - Goed voor beperkte resources

### 1.2 Het formaat van een processorinstructie

__Native instructies__
Binair opgeslagen in het geheugen, bestaat uit Operation code en operanden.
Operation code = instructie
Operanden = variabelen

### 1.3 Verwerking van een instructie

__Fetch - Decode - Execute__
Eerst wordt de instructie uit het geheugen opgehaald, de instruction fetch. Daarna wordt de binaire waarde van de instructie opgeslagen in een het Instruction Register (buffergeheugen). Daarna zal de control unit van de processor de instructie ontleden in elementaire bewerkingen, de decodeerfase. De processor bepaalt dan of er nog operanden nodig zijn (registers, datapaden, ALU). Uiteindelijk zal in de execution-fase de control unit ervoor zorgen dat deze elementaire bewerkingen worden uitgevoerd (ophalen operanden, bewerking uitvoeren, stockeren resultaat) door de nodige controlesignalen te genereren. Na de instructie gebeurt deze cyclus opnieuw.

#### 1.3.1 De instruction fetch

De verbinding van de adres- en databus met het inwendige van de processor gebeurt via de AdresBusBuffer en de DataBusBuffer. Deze dienen om de externe signalen genoeg vermogen te geven en eventueel de spanningsniveaus aan te passen aan de externe elektronica. Om bij het ophalen van de instructies het juiste adres te kunnen genereren, bevat elke processor een telregister dat het adres bevat van de uit te voeren instructie, dit is de Program Counter of Instruction Pointer. Deze wordt bij elke instruction fetch automatisch verhoogd.

verloop instruction fetch:
 - inhoud PC wordt via ABB op adresbus gezet
 - CU maakt het externe Read-signaal actief zodat het geheugen actief wordt
 - Geheugen plaatst gevraagde instructie op de databus
 - CU vergrendelt de instructie-code via de DBB in het IR
 - PC verhoogd

#### 1.3.2 Von Neuman vs. Harvard architectuur

 | Von Neuman architectuur | Harvard architectuur |
 | :------------- | :------------- |
 | IO system <-> CPU <-> Code & data | IO system <-> CPU <-> Code memory <-> Data memory |
 | Bottleneck: geheugenbus | Complexe schakeling (bus, buffers, cache) |
 | zit in alle general purpose computers | Sommige microcontrollers (on chip memory) |

### 1.4 Instruction Set Architecture

#### 1.4.1 ISA omschrijving

__belangrijkste aspecten:__
 - Assemblerinstructies
 - Registers
 - GeheugenOrganisatie
 - I/O
 - beveiliging

#### 1.4.2 De 6502 architectuur

Zit in Apple II, Comodore 64, NES, Atari

##### 1.4.2.1 programmeermodel

  - 8-bit ALU en 16-bit adresbus
  - 64kiB geheugen (ROM, RAM, I/O)

##### 1.4.2.2 Registers

  - Accumulator: Algemeen 8-bit rekenregister (berekeningen en logische bewerkingen)
  - X, Y: Indexregisters (adresberekeningen)
  - Status Register: Statusvlaggen Zero – Carry – Overflow – Negative – Decimal – Interrupt
  - Program Counter: enige 16-bit register (volgende instructieadres)
  - Stack Pointer: 256 bytes groot, in RAM 0$100 - $01FF

##### 1.4.2.3 Instructies

  - Binaire bewerkingen (AND, OR, SHIFT, ROL)
  - Rekenkundige bewerkingen (geen vermenigvuldiging en deling)
  - Verplaatsen van of naar register
  - (Voorwaardelijke) spronginstructies
  - Gespecialiseerde instructies voor stack en statusvlaggen; In hardware enkel 8-bit integer bewerkingen.

##### 1.4.2.4 Adresseermethodes
  - __Implicit:__ De instructie legt impliciet de operand(en) vast.
  - __Immediate:__ De operand wordt rechtstreeks in de instructie gegeven.
  - __Absolute:__ In de instructie wordt het geheugenadres opgegeven van de operand.
  - __Indexed:__ Het opgegeven adres wordt verhoogd met de inhoud van het gebruikte reg.
  - __Indirect:__ Het te gebruiken geheugenadres wordt meegegeven. Indirecte adressering i.c.m.
  .Indexed addressing en enkel voor adressen in eerste 256 bytes v/h geheugen.

##### 1.4.2.5 Interrupts

  __Non Maskable Interrupt:__ Kan niet uitgeschakeld worden. Bij actief: lopende instructie afwerken, PC en SR op stack, springen naar adres op $FFFA. Op $FFFA en $FFFB moet dus het adres van de interrupt handler voor NMI staan
  __IRQ:__ Gelijkaardig aan NMI maar kan uitgeschakeld woorden door de I-vlag op 1 te zetten. Vector wordt gelezen op $FFFE en $FFFF
  __BRK:__ Software-interrupt. Zelfde effect als actieve IRQ.

#### 1.4.3 De Intel IA-32 architectuur (x86)

##### 1.4.3.1 Programmeermodel

  - Intel 4004 (4-bit), 8008 (8-bit), 8080 (8-bit)
  - 1976: Intel 8086 (16-bit, 20-bit adresbus -> 1MiB)
  - 1985: Intel 80386 (32-bit, 32-bit adresbus -> 4GiB)

  80386 was compatibel met 8086 (16-bit ‘real mode’), maar had eigen 32-bit ‘protected mode’. Prototype van de moderne processor met beveiligingsmechanismes in hardware. Later onder druk van AMD: 64-bit mode.

  __Typische kenmerken:__

  - Bij het inschakelen start de processor op in ‘real mode’. Na initialisatie wordt overgeschakeld naar ‘protected mode’, met volledige capaciteiten.
  - 32-bit ALU die ook 8-bit en 16-bit bewerkingen kan uitvoeren. De adresbus en externe databus zijn ook 32-bit (4GiB).
  - Randapparatuur met Isolated I/O (64KiB en aparte instructies)
  - Geheugenorganisatie in afzonderlijke segmenten met specifieke eigenschappen. Elk proces krijgt minstens een codesegment, datasegment en stacksegment. Deze zitten overal en kunnen overlappen. Er is ook virtueel geheugen voorzien (als theoretisch geheugen > fysiek geheugen).

##### 1.4.3.2 Registers

Algemene rekenregisters: EAX 32-bit, AX 16-bit, AH en AL 8-bit

  - __AX:__ Accumulator (E/H/L)
  - __BX:__ Base (E/H/L)
  - __CX:__ Count (E/H/L)
  - __DX:__ Data (E/H/L)

  Registers voor adresberekeningen: geen bewerkingen, 8-bit

  - __BP:__ Base Pointer
  - __SI:__ Source-Index
  - __DI:__ Destination-Index
  - __SP:__ Stack-Pointer

  Segmentregisters: Informatie over geheugen

  - __CS:__ Code Segment
  - __SS:__ Stack Segment
  - __DS:__ Data Segment
  - __EFGS:__ Extra Segment

  Adres van volgende uit te voeren instructie

  - __  IP:__ Instruction Pointer

  Statusvlaggen: Carry, Parity, Zero, Sign, Interrupt enable, Overflow...

  - __FLAGS__

##### 1.4.3.3 Instructies

Bewerkingen zowel rechtstreeks in het geheugen als in de rekenregisters.

  - Verplaatsingen
  - Berekeningen
  - Binaire logische bewerkingen
  - Voorwaardelijke spronginstructies
  - Sinds Intel 486 ook floating point
  - Later ook SSE-instructies

#####1.4.3.4 Adresseermethodes

  - Register
  - Immediate
  - Direct
  - Register Indirect
  - Register Relative
  - Base + index
  - Base Relative + Index
  - Scaled Indexed

Meer mogelijkheden dan 8-bit. Aantal adresseermethodes zijn speciaal voor arrays en velden in objecten.

##### 1.4.3.5 Interrupts en exceptions
256 Verschillende exceptionhandlers in de Interrupt Vector Table voor zowel externe als interne interrupts.

##### 1.4.3.6 Beveiliging
4 privilegeniveaus (in praktijk 0 en 3)
0: Operating System Kernel  complete controle
1 en 2: Operating System Services  Beperkte toegang
3: Application ‘User’ Mode  Beperkte toegang

#### 1.4.4 De ARM-architectuur
Acorn Risc Machines, kwam net tegelijkertijd met IBM-PC x86 dus andere afzetmarkt -> embedded control. Zeer geschikt voor taken met relatief hoge rekenkracht en laag energieverbruik. Deze bevat weinig transistoren dus goedkoop en klein. Deze architectuur werd niet geproduceerd als processor door de ontwerpers maar de architectuur werd verkocht met licenties, zo kon een fabrikant de architectuur gebruiken op zijn eigen hardware. Nu zit de ARM in 90% van de mobile devices.

##### 1.4.4.1 Programmeermodel

  - 32-bit processor, nadien ook 64-bit
  - Op basis van RISC-principes. Load/store architectuur (gegevens laden, bewerking in intern CPU-register, gegevens wegschrijven)
  - Minimaal 16 registers van 32/64 bit
  - Bijna alle instructies kunnen conditioneel uitgevoerd worden -> compact, efficiënt en goed voor pipeline
  - Alle instructies zijn 32-bit lang
  - Beperkt aantal instructies, maar worden in 1 klokcyclus uitgevoerd
  - Uitgebreide en zeer krachtige adresseermethodes
  - Beveiliging: ‘user mode’, ‘supervisor mode’, ‘system mode’
  - Bij goed geschreven code -> Zeer efficiënt

## 2 Basisarchitectuur van een processor

### 2.1 Interne architectuur van een processor
Bij 8-bit processoren -> gelijkaardige basisarchitectuur (nadruk op foutloos verwerken van instructies)
Later -> grote ontwikkelingen:

- Comfort van de programmeur verhogen door het krachtiger maken van de instructies en adresseermethodes. Minder instructies nodig -> productiever en minder fouten
- Performantie van processor verhogen door verhogen klokfrequentie en efficiëntie van interne architectuur verhogen (minder klokperiodes per instructie)
- Extra voorzieningen voor multitasking (elk proces isoleren)

### 2.2 Basisschema processor
__Belangrijkste elementen:__
  - Registers
  - Rekeneenheid (ALU)
  - Controle-unit (CU)
  - Interne bussen
  - Bus-buffers

  Interne controlesignalen sturen de werking van de verschillende componenten.

#### 2.2.1 Processorregister
Een processorregister is een kleine, snelle geheugenplaats (opgebouwd uit een aantal D-flipflops) waarin één geheugenwoord van 8, 16, 32, 64... bits opgeslagen kan worden. Elke processor heeft enkele gespecialiseerde registers:

  - __Program Counter/Instruction Pointer:__ Geheugenadres van de volgende instructie (wordt automatisch verhoogd naar het adres van de volgende instructie bij fetch)
  - __Instruction Register:__ Wanneer de operation code van een instructie bij een fetch ingelezen wordt van een extern geheugen, dan wordt deze hierin opgeslagen (van daar kan de CU de bits lezen bij het decoderen van de instructie)
  - __Status Register:__ Aantal vlaggen waarin de huidige toestand van de processor weergegeven
  wordt. Een paar standaardvlaggen:
    - __Zero vlag (Z):__ 1 als laatst berekende resultaat 0 was
    - __Carry vlag (C):__ Bevat eventueel een carry-bit na optelling/aftrekking
    - __Sign vlag (S, N):__ Bevat de hoogste bit van het laatst berekende resultaat. Als er gerekend wordt met 2’s complement dan zal de Sign-bit op 1 staan bij een negatief resultaat.
    - __Overflow vlag (O, V):__ Indien er gerekend wordt met 2’s complement en het resultaat kan niet in het register, dan zal de overflow vlag op 1 staan.

De statusvlaggen kunnen meestal gebruikt worden om te beslissen of een conditionele sprong uitgevoerd moet worden.

#### 2.2.2 Rekeneenheid (ALU)

Schakeling waarin de bewerkingen effectief uitgevoerd worden. Het gaat dan minimaal over optellingen, aftrekkingen van int en binaire bewerkingen (AND, OR, XOR, SHIFT, ROTATE). Afhankelijk van de processor komen daar ook nog vermenigvuldiging en deling bij, eventueel bewerkingen op BCD of floating point. Soms is er ook Multiply and Accumulate (meerdere bewerkingen in één stap).

#### 2.2.3 Control Unit (CU)

Deze coördineert de werking van de processor. Hij zorgt voor de nodige controlesignalen (intern en extern) voor het ophalen van een instructie, decodeert de instructie en zal op basis daarvan de nodige controlesignalen genereren voor het uitvoeren.

Naast de externe adres-, data- en controlebus zijn er ook intern bussen nodig. Om technische redenen zijn er buffers nodig tussen de interne en externe bussen:

- Intern lage spanningen (0,8V – 1,5V) -> extern hogere spanningen (1,3V – 1,5V)
- Intern weinig vermogen nodig -> extern veel vermogen nodig

### 2.3 Controle-Unit met hardware decoder

In allereerste processoren gebeurde decoderen na intstruction-fetch door hardware. De verwerking van een assembler-instructie gebeurt intern in aantal stappen. Deze gebeuren door aan- of uitschakelen van controlesignalen. Bij elke instructie dus een opeenvolging van controlesignalen. In de eerste microprocessoren werd dit gegenereerd door een hardwareschakeling:

De bits van de opcode zijn dus een input voor een digitale schakeling. Elke volgorde van bits heeft eigen uitgang -> de decoder is een soort sequencer voor digitale controle signalen. Het effect van de instructies is ingebakken in het ontwerp van de sequencer -> hardware decoder

Complexere instructies -> ontwerp hardware wordt moeilijker

__Voordeel:__

  - Snelle werking want hardware schakeling (enkel beperking door schakeltijd technologie)

__Nadeel:__

  - Zeer complexe schakeling
  - Moeilijk te ontwerpen of aan te passen
  - Vroeger geen systemen om complexe ontwerpen te testen (zoals CAD)

### 2.4 Microprogrammatie

Bij complexere 8-bit processoren en opkomst van 16-bit processoren  microprogrammatie (vanuit mainframewereld)

__Interne opbouw processor:__

  - Datapath: Deel van de processor waar data opgeslagen, verwerkt of verplaatst wordt (interne bussen, registers, ALU, buffers)
  - Control Unit: Stuurt in een aantal stappen de blokken van het datapath (via controlesignalen)

Bij hardware decoder -> voor elk controlesignaal een specifieke toestand aanleggen (H of L)

Dit kan ook via intern geheugenblok met opeenvolgende toestanden. Om instructie uit te voeren -> op juiste plaats in intern geheugen starten -> opeenvolgende geheugenplaatsen naar buiten brengen -> controlesignalen aansturen.

Elke locatie in geheugen wordt dan micro-instructie genoemd. Op deze manier kan een instructie van de programmeur opgesplitst worden in een opeenvolging van een aantal micro-instructies.

In plaats van hardware decoder dus een intern geheugen (Control Store) waarin voor elke macro- instructie een opeenvolging van micro-instructies staat. Bij ophalen macro-instructie -> micro-instructies -> controlelijnen aansturen

__Gevolgen:__

  - Gemakkelijker om nieuwe instructies toe te voegen (Control Store uitbreiden)
  - Interne hardware kan gewijzigd worden zonder de Instruction Set Architecture aan te moeten passen
  - Fouten kunnen gemakkelijk verholpen worden door microcode te herschrijven. Bijvoorbeeld de interne microcode van ROM vervangen door een bug-vrije microcode (veel goedkoper)
  - Processorontwerp wordt een kwestie van software makkelijker testen en ontwikkelen
  - Mogelijk om verschillende processoren te ontwerpen die toch compatibel zijn (microcode van alle processoren moet dezelfde macrocode ondersteunen)
  - Bij gelijke klokfrequentie: decoder op basis van microcode trager dan hardware decoder

Tegenwoordig gebruiken alle processoren een combinatie van de twee:

 - Eenvoudige instructies -> hardware
 - Complexe instructies -> microcode

### 2.5 Complex Instruction Set Computers (CISC)

Aantal instructies van een processor is sterk opgevoerd, instructies zelf warden complexer en krachtiger -> makkelijker voor programmeur en eenvoudiger ontwerp compiler.

-> Complex Instruction Set Computer

Niet noodzakelijk efficiënter: groot aantal instructies en adresseermethodes -> grote hoeveelheid microcode (sommige amper gebruikt) en complexe instructies zijn vrij traag door groot aantal micro-instructies.

### 2.6 Reduces Instruction Set Computers (RISC)

CISC heeft zware beperkingen bij het zoeken naar hoge performantie. Er kwamen steeds meer gespecialiseerde instructies en adresseermethodes  meer microcode  complexer ontwerp maar niet
altijd sneller.

RISC -> processor zonder microcode met hardware decoder. Om de decoder snel te houden: beperkt aantal elementaire instructies en adresseermethodes (snel en efficiënt).

Redenering: veel kleine instructies is sneller dan enkele complexe.

Het is dus belangrijk om zo efficiënt mogelijk instructies uit te voeren -> gemiddeld aantal instructies per klokcyclus (IPC)

Typische kenmerken RISC:
 - Beperkte, eenvoudige instructieset
 - Vaste instructielengte (32 bits)
 - Veel processorregisters (geen bewerkingen in extern geheugen)
 - Doel is IPC van 1

Gevolg:
 - Meer code voor hetzelfde werk maar hogere snelheid
 - Gemiddelde instructielengte RISC > CISC -> programma op RISC zal groter zijn

Tegenwoordig aspecten van CISC en RISC in processor.
