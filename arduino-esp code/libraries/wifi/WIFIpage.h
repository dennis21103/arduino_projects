String webPage()
{
  String web; 
  
  web+="<!doctype html><html lang=\"ru\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /><meta charset=\"utf-8\" /><title>ESP 8266</title><link rel=\"stylesheet\" href=\"style.css\" /><style> button.socketoff {color: green; padding: 10px 27px;} button.socketon {color: red; padding: 10px 27px;}</style></head>";

  web+="<body><h1 style=\"text-align: center;font-family: Open sans;font-weight: 800;font-size: 24px;\">ESP8266 Web Server</h1><div>";
  
  web+="<h2 style=\"text-align: center;font-family: Open sans;font-weight: 600;font-size: 20px;\">Temperature: ";
  web+=t;
  web+=" &#176;C</h2>";
  web+="<h2 style=\"text-align: center;font-family: Open sans;font-weight: 600;font-size: 20px;\">Humidity: ";
  web+=h;
  web+=" %</h2>";
  web+="<h2 style=\"text-align: center;font-family: Open sans;font-weight: 600;font-size: 20px;\">Average 1-min temperature: ";
  web+=Tavg1;
  web+=" &#176;C</h2>";
  web+="<h2 style=\"text-align: center;font-family: Open sans;font-weight: 600;font-size: 20px;\">Average 1-min Humidity: ";
  web+=Havg1;
  web+=" %</h2>";
  web+="<h2 style=\"text-align: center;font-family: Open sans;font-weight: 600;font-size: 20px;\">Average 5-min temperature: ";
  web+=Tavg5;
  web+=" &#176;C</h2>";
  web+="<h2 style=\"text-align: center;font-family: Open sans;font-weight: 600;font-size: 20px;\">Average 5-min Humidity: ";
  web+=Havg5;
  web+=" %</h2>";
   
  web+="<h2 style=\"text-align: center;font-family: Open sans;font-weight: 600;font-size: 20px;\">CO2 ppm: ";
  web+=buffer1;
  web+=" ppm</h2>";
  web+="<h2 style=\"text-align: center;font-family: Open sans;font-weight: 600;font-size: 20px;\">CO2 Volts: ";
    web+=buffer;
  web+=" V</h2>";
  
  web+="<h2 style=\"text-align: center;font-family: Open sans;font-weight: 600;font-size: 20px;\">220V State: ";
   if (digitalRead(PIN_RELAY) == 1){
  web+="<span style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #ec1212;margin: 0 auto;\">OFF</span>";}
   else {
  web+="<span style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #12ec41;margin: 0 auto;\">ON</span> </h2>";
   }
   
  web+="<p style=\"text-align: center;font-family: Open sans;font-weight: 100;font-size: 18px;\">=============REFRESH=============</p><div style=\"text-align:center;margin-top: 20px;\"><a href=\"/\"><button style=\"width:158px;\">REFRESH DATA</button></a></div><p style=\"text-align: center;font-family: Open sans;font-weight: 100;font-size: 18px;\">=============REFRESH=============</p><p style=\"text-align: center;font-family: Open sans;font-weight: 100;font-size: 18px;\">==========Socket control============</p>";
	if (digitalRead(PIN_RELAY) == 0){
	web+="<div style=\"text-align: center; width: 98px; color: white; padding: 10px 30px; background-color: #12ec41; margin: 0 auto;\">ON</div>";}
	else {
	web+="<div style=\"text-align: center; width: 98px; color: white; padding: 10px 30px; background-color: #ec1212; margin: 0 auto;\">OFF</div>";
		}
  web+="<div style=\"text-align: center; margin: 5px 0px;\">";
    if (digitalRead(PIN_RELAY) == 0){  
	web+="<a href=\"socket1Off\"><button class=\"socketon\">OFF</button></a>";}
	else {
	web+="<a href=\"socket1On\"><button class=\"socketoff\">ON</button></a>";
	}
  web+="</div>";
	
  web+="<p style=\"text-align: center;font-family: Open sans;font-weight: 100;font-size: 18px;\">==========Socket control============</p></div></body></html>";
   return(web);
}