# Zabduino, ZBX in Arduino
[![CodeFactor](https://www.codefactor.io/repository/github/deb8v/zabduino/badge)](https://www.codefactor.io/repository/github/deb8v/zabduino)
This project can be used to create for simple integration of your own modules in Zabbix.
   

The project meets the standards:

- https://www.zabbix.com/documentation/3.2/manual/appendix/items/activepassive 
- https://zabbix.org/wiki/Docs/protocols/zabbix_agent/3.2 


Unresolved issues:
- [x] The answer for the queries
- [ ] Аutomatic detection (in Zabbix)
- [ ] Error correction
_I will be happy to add your suggestions in Master*_

# Usage  

```
$ zabbix_get -s 8.8.8.8 -k agent.ping
$ zabbix_get -s 8.8.8.8 -k sensors.temperature.0
$ zabbix_get -s 8.8.8.8 -k who
```  
![d](https://sun1-93.userapi.com/1C6f-ki8h6_c7smSv_-wQj4rj1Erqd6pbimGeQ/PG2b3x8dMe0.jpg)
