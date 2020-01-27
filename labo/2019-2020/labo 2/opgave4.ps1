clear
$port.Close()
$test = 1

Write-output "Choose a COM port"
$portName = Read-Host
$port= new-Object System.IO.Ports.SerialPort $portName,9600,none,8,2
$port.open()
clear

while($test -eq 1){
    Write-Output "Toets de letter in van uw keuze:"
    Write-Output "a. alle LED’s aan"
    Write-output "b. alle LED’s uit"
    Write-output "c. individuele LED aansturen"

    $keuze = Read-Host

    if ($keuze -eq "exit"){
        $test = 2
        $port.close()
    }

    $port.Write($keuze)
    clear
}
