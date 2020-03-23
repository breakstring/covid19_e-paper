# covid19_e-paper
A wearable e-paper device to track the covid19 status

# Hardware
 - Waveshare [E-Paper_ESP32_Driver_Board](http://www.waveshare.net/wiki/E-Paper_ESP32_Driver_Board): Which is an ESP32 dev board with FFC slot.
 ![ESP32 Driver Board](/images/board.jpg)
 - Waveshare [2.9inch e-Paper Module (B)](http://www.waveshare.net/wiki/2.9inch_e-Paper_Module_(B)): 3 colors (white, black, red) 
 ![2.9inch 3 colors e-Paper module](/images/module.jpg)
 - Waveshare [2.9inch e-Paper case](http://www.waveshare.net/shop/2.9inch-e-Paper-Case.htm)
 ![e-Paper case](/images/case.jpg)
 
# Depend on
 - Diplay render: [GxEPD2](https://github.com/ZinggJM/GxEPD2)
 - [Data source](https://covid19.mathdro.id/): [API source code](https://github.com/mathdroid/covid-19-api)


# Connect
Just connect the driver board with your e-paper module, and deploy the code to the board. (Do not forgot to change the WiFi SSID and password). It will get the confirmed/recovered/deaths data of global, China, Italy, Spain, USA and Germany, and show the data with circle. If you want more, just add logo data of the country and also the related API endpoints. 

# Sample pictures
![All](/images/ALL.jpg "Global")
![China](/images/CN.jpg "China")
![Italy](/images/IT.jpg "Italy")
![Spain](/images/ES.jpg "Spain")
![USA](/images/USA.jpg "USA")
![Germany](/images/DE.jpg "Germany")

# Next
I just stick the e-paper case on my respirator, 3M 6502QL with 7093 P100 particulate box. Share with my mobile device's hotspot and charged with a power banck.
![1](/images/1.jpg)
![2](/images/2.jpg)
