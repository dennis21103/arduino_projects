# front server data graph folder
Что делает данный код:
- Html страница, которая рисует график зависимости температуры\влажности\CO2 от времени.
Откуда приходит информация:
- Данные для построения графика собираются с помощью датчиков на ESP8266(wemos), затем агрегируются с помощью python скрипта раз в 5 минут, и складываются в папку для веб-сервера
Что происходит при запуске кода из данной папки:
- html файл + скрипт для рисования графиков + данных для рисования отдаются веб-сервером клиенту. Клиент фильтрует данные и отрисовывает у себя график.

Для построения гарфика используются 5 минутные показания датчиков.

Формат данных на входе:
Time;Date;temp;Temp_Value;hum;Humidity_Value;temp1avg:1_Min_Average_Temp_Value;hum1avg;1_Min_Humidity_Average_Value;temp5avg;15_Min_Average_Temp_Value;hum5avg;5_Min_Humidity_Average_Value;co2ppm;Co2_ppm_Value;co2V;Co2_Voltage_Value\n
example: 17:55:01;02-05-22;temp;31.3;hum;14.7;temp1avg;30.75;hum1avg;14.67;temp5avg;30.74;hum5avg;14.69;co2ppm;4553.3;co2V;0.94

