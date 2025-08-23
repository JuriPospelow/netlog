# netlog
## Projektarbeit
### Kurs C++ Developer.Basic
#### Online-Schule Otus
# **Thema „Dienstprogramm zur Überwachung des Zustands von Computern im lokalen Netzwerk”**

netlog scannt Netzwerke, vergleicht das Scan-Ergebnis mit einer Liste bekannter Adressen und speichert das Vergleichsergebnis in einer CSV-Datei (*netlog.csv*).
  Das Scannen der Netzwerke erfolgt durch Aufruf des Dienstprogramms nmap. Die Aufrufparameter werden in der Datei *netlog.ini* festgelegt.
Die IP-Adressen der Geräte befinden sich in der ini-Datei, die beim Aufruf von netlog angegeben werden muss. Beispiel:
```
                      netlog home.ini
```
In dem Programm werden verwendet:
* boost.log
* boost.process
* boost.asio
* boost.property_tree
-----------------------------------------------------------------------
# netlog
## проектная работа
### курс C++ Developer.Basic
#### онлайн школа Отус
# **Тема «Утилита для мониторинга состояния компьютеров локальной сети»**

netlog сканирует сети, сравнивает результат сканирования со списком известных адрессов и сохраняет результат сравнения в csv-файле (*netlog.csv*).\
  Cканирование сетей происходит вызовом утилиты nmap. Парамметры вызова задаются в файле *netlog.ini*.
IP-Адресса устройств находятся в ini-файле, который надо сообщить при вызове netlog. Например:
```
                      netlog home.ini
```
В программе используются:
* boost.log
* boost.process
* boost.asio
* boost.property_tree
