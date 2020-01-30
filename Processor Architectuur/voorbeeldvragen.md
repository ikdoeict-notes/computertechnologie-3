# Voorbeeldvragen Processor architectuur

- Waar in de pipeline van moderne GPU's worden programmeerbare shaders gebruikt (2 juiste antwoorden)?

  - __Vertex Processing__: Geometry shader
  - __Fragment Processing__: Fragment shader

- Welk van volgende aspecten zijn typische nadelen van een VLIW-processor (2 juiste antwoorden)?

  - Moeilijkere compilers
  - __Code Bloating__: Wanneer geen combinatie mogelijk is in 1 VLIW komen er NOPs bij -> minder efficiënt
  - verandering aan hardware -> verandering aan compiler

- Welke uitspraken zijn correct in verband met een 'Very Long Word Instruction (VLIW)'-processor (2 juiste antwoorden)?

  - VLIW hebben lange instructiecodes
  - De compiler zoekt instructies die tegelijk uitgevoerd kunnen worden.
  - De instructies zijn fixed length

- Welke uitspraken zijn correct betreffende multicore processoren (2 juiste antwoorden)?

  - Implementatie van meerdere cores in 1 processor
  - Verdeling van rekenwerk tussen verschillende threads die onafhankelijk van mekaar kunnen werken.

- Welke uitspraken zijn juist in verband met de Cell-processor (2 juiste antwoorden):

  - ontworpen door IBM
  - elke core: back to basics (zeer performant)
  - PPC General purpose core (L1 en L2 cache)

- Welke processor heeft de beste IPC-waarde (=Instructions per clockcycle).

  - (voorlopig antwoord) Een processor met lage clock-speed

- Bij welke processor is een 'stall' in de pipeline het meest nadelig?

  - __Intel Pentium 4__; kan tot 126 instructies in flight hebben -> enorme stagnatie
  - __RISC processor__

- Duidt aan welke uitspraken van toepassing zijn bij een processor met een decoder op basis van microcode (2 juiste antwoorden).

  - gemakkelijker om nieuwe instructies toe te voegen (Control Store Uitbreiden)
  - Interne hardware kan gewijzigd worden zonder de instruction set architecture aan te moeten passen
  - mogelijk verschillende processoren te ontwerpen die toch compatibel zijn (microcode van alle processoren die zelfde macrocode ondersteunen)

- Wat zijn typische eigenschappen van een RISC-processor (2 juiste antwoorden)?

  - hardware decoder
  - elementaire instructies (moet voor HW-D)
  - vaste instructielengte (HW-D & efficiëntie)
  - enkel register-bewerkingen (Load/Store architectuur)
  - dus veel registers (aantal Loads/Store beperkingen)

- Wat is 'in order issuing' van instructies?

  - Het verwerken van instructies uitgevoerd in een instructie cycle die bestaat uit:
    1. fetch instructie
    2. als input nodig is -> als niet beschikbaar -> stall
    3. Execute
    4. Write back

- Wat wordt bedoeld met de 'dispatch' van een instructie in een superscalaire processor?

  - Eerst meerdere instructies fetchen uit instruction cache (Registry Renaming waar nuttig). Wanneer klaar voor verwerking: instructie klaarzetten(__Dispatch__) in een wachtrij (Reserving station). Bij beschikbaarheid EX unit -> instructieverwerking starten (issuing).

- GPGPU processing (code uitvoeren op grafische kaarten) is interessant voor 'High Performance Computing' (HPC) omdat...

  - Thread level parallelisme wordt intens ingezet

- Welke van volgende uitspraken is een juiste omschrijving van de forwarding-techniek in een processor?

  -  van zodra het resultaat (van een fetch/Exec) bestaat op de processor, het beschikbaar is voor volgende instructies die dit resultaat gebruiken, zelf als is het resultaat nog niet wegegeschreven in het registerbestand. forwarding kan gebeuren vanuit de output van de executetrap of vanuit de output van de geheugentrap

- De maximale klokfrequentie van een pipelined processor wordt bepaald door ...

  - De traagste stage van de pipeline

- Welke uitspraak geeft op een correcte manier het verband tussen de klokfrequentie van een processor en het aantal 'stages' in de pipeline daarvan.

  - Hoe meer stages in de pipline, hoe hoger de klokfrequentie

- Welke van volgende toepassingen zijn het best geschikt voor verwerking op een grafische kaart via GPGPU processing? (2 juiste antwoorden)

  -

- Wat betekent de term 'Dynamic Voltage Scaling' in een processor

  - CPU is zelf in staat om core spanning en frequency aan te passen . dat gebeurt dynamisch tijdens de werking op basis van actuele omstandigheden en behoeften

- Welke uitspraken zijn correct betreffende de SSE-instructie-uitbreiding (2 juiste antwoorden)?

  -

- In welke van volgende categoriën vallen de SSE-instructies bij de Intel-processoren?

  -

- Welke van volgende afhankelijkheden kan niet opgelost worden met behulp van 'register renaming'?

  - __RAW__ (Read after write)
  - __RAR__ (read after read)

- Wat zijn de 5 stages van een pipelined RISC architectuur?

  1. __Instruction fetch (IF)__: Ophalen van een instructie uit geheugen en aanpassen PC voor colgende instructie
  2. __Instruction decode (ID)__: Decoderen van de instructie en uitlezen van de operanden uit het registerbestand voor de ALU bewerking
  3. __Execute (EX)__: Uitvoeren van de relevante berekening in de ALU
  4. __Memory (MEM)__: Indien de instructie een geheugenoperatie vereist, wordt deze stap uitgevoerd.
  5. __Write back (WB)__: Terugschrijven van het resultaat van de berekening of memory-operatie naar het registerbestand.

- Wat betekent de term 'Code morphing' bij de Transmeta Crusoë processor.

  - dynamische vertaling van externe opgeslagen x86 instructies naar native VLIW instructies.

- Welke uitspraken zijn correct over de 'execution trace cache' (ETR) bij de Pentium IV processor?

  -

- GPGPU processing (berekeningen uitvoeren op de grafische kaart) is niet altijd zo gemakkelijk. Welke van volgende aspecten zijn specifieke voor GPGPU een probleem of beperking? (3 juiste antwoorden)

  - Slechts één programmeermodel
  - aantal vertex/shaders ligt vast per model

- Wat betekent de term 'ACPI' bij computerhardware

  - Advanced Configuration & Power Interface
  - Industriestandaard voor configuratie van power states = interface tussen OS en Hardware

- Wat zijn typische kenmerken van GPGPU processing (berekeningen in de grafische kaart). (2 juiste antwoorden).

  - Hoge densiteit, goede power efficienty
  - Vooral efficient voor specifieke problemen (streaming)
  - Moeilijk programmeerbaar
  - Complexe geheugenarchitectuur
  - High Latency (geen probleem bij streaming)

- Wat zijn gevolgen van het gebruik van 'out of order execution' (2 juiste antwoorden)?

  -

- Welke van volgende technieken zijn een absolute vereiste om een IPC (= instructions per clockcycle) die groter is dan 1 mogelijk te maken (2 juiste antwoorden)?

  - extra vormen parallelisme

- Welke van volgende afhankelijkheden kan opgelost worden door de forwarding' techniek?

  - RAW(read after write)

- Welke van volgende technieken worden gebruikt om een 'pipeline stall' te vermijden in het geval van een controle-hazard (2 juiste antwoorden)?

  - delayed branch
  - branch prediction

- Wat betekent de term 'Power Gating' bij een processor?

  - Power gating: Delen van de CPU uitschakelen (klok en/of spanning)

- Welk van volgende aspecten zijn specifieke problemen van 'Exascale' (of algemener 'High Performance') Computing? (3 juiste antwoorden)

  - Code complexiteit
  - Lokalisatie van gegevens & architectuur van het geheugensysteem
  - complexe geheugenstructuren

- Wat zijn typische problemen bij een 'Symmetric multiprocessing (SMP)'-architectuur (2 juiste antwoorden)?

  - Bandbreedte van geheugen:van geheugen trager dan processoren -> processor moet regelmatig wachten (zeker bij meerdere processoren op één geheugen)
  - Cache-consistentie: Om traagheid te compenseren -> cache -> alle processoren moeten op de hoogte gebracht worden als cache van 1 processor naar geheugen wordt geschreven

- Welke omschrijving komt overeen met wel soort programmacode?

  - Geeft de programmeur top op niveau van de processorhardware controle over hoe de code uitgevoerd zal worden. -> Assembly language
  - 'High level' sourcecode wordt vertaald naar 'intermediate code' die dan uitgevoerd wordt door een interpreter of JIT compiler binnen een afgeschermde omgeving. -> Native (unmanaged) code
  - Technische aspecten als memory management moeten door de programmeur verzorgd worden. -> Native (Unmanaged) code
  - De source code wordt door de compiler omgezet naar machinetaal die door de processor rechtstreeks uitgevoerd kan worden. -> Managed code

- Wat is hyperthreading

  - hyperthreading is het verwerken van meerdere (2) threads door elkaar

- Welke omschrijving hoort bij welke processor ISA:

  - 32-bit CPU op basis van RISC-filosofie -> geoptimaliseerd voor mobile en low-power toepassingen
  - Eenvoudige 8-bit processor met 16-bit adresbus -> gebruikt in vroege microcomputers als de Apple II en Acorn BBC computer.
  - Klassieke 32-bit CISC processor -> met ondersteuning complexe adresseringsmethoden en bewerkingen in het geheugen.
  - Processor met geïntegreerde schakelingen voor aansturen van analoge en digitale hardware -> geschikt voor kleine 'Internet of Things (IOT) devices.

- Welke omschrijving hoort bij welke computerarchitectuur?

  - Programmacode en data worden in een gemeenschappelijke geheugenschakeling opgeslagen. -> Von Neuman architectuur
  - Laat toe gelijktijdig instructies en operanden(data) op te halen. -> Harvard architectuur
  - Is vooral geschikt voor microcontrollers omdat de complexere geheugenarchitectuur minder problematisch is binnen één chip dan in systemen met extern geheugen. -> Harvard architectuur
  - Wordt bijna uitsluitend gebruikt voor general purpose processoren -> Von Neuman architectuur
