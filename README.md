# Zabduino, ZBX in Arduino

This project can be used to create for simple integration of your own modules in Zabbix.
   

The project meets the standards:
https://www.zabbix.com/documentation/3.2/manual/appendix/items/activepassive 
https://zabbix.org/wiki/Docs/protocols/zabbix_agent/3.2 


  

# Usage  

```
$ zabbix_get -s 8.8.8.8 -k agent.ping
$ zabbix_get -s 8.8.8.8 -k sensors.temperature.0
$ zabbix_get -s 8.8.8.8 -k who
```  
