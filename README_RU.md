# Zabduino ZBX для Arduino

Это решение может быть использовано для интеграции ваших модулей в единую систему Zabbix для упрощения жизни.
  
Для повышения качества ваших работ рекомендую прочитать документацию:
https://www.zabbix.com/documentation/3.2/manual/appendix/items/activepassive
https://zabbix.org/wiki/Docs/protocols/zabbix_agent/3.2

# Usage  

```
$ zabbix_get -s 8.8.8.8 -k agent.ping
$ zabbix_get -s 8.8.8.8 -k sensors.temperature.0
$ zabbix_get -s 8.8.8.8 -k who
```  
