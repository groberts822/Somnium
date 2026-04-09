# Somnium
bedside dream image frame. you find an image online that looks like what you dreamed, open the web UI on your phone, upload it, and it shows up on the display. that's the whole thing.
i saw a project that used AI to generate dream imagery based on a description you speak into a mic and I liked the physical form factor, which is just a matte rounded box with a glowing display sitting on a nightstand, but i didn't want any of the AI stuff. finding an image that already looks right takes like 20 seconds. describing your dream well enough to get anything useful out of a model takes way longer and the result is usually off anyway.
so basically this is just a picture frame with wifi.

how it works
ESP32 connects to your wifi on boot and hosts a tiny web server. open the IP in your phone browser, pick a JPEG, hit send. the image gets written to flash and drawn on the display. next time it boots it reloads the last image automatically.
no app, cloud, account, or mic.

Part,Notes,Qty, Cost USD, link
ESP32 dev board (any 30-pin),Handles WiFi + drives display over SPI,1,$5.45,https://www.aliexpress.us/item/3256808584827377.html?spm=a2g0o.productlist.main.56.6768eRc2eRc2kj&algo_pvid=0320d764-ae5c-465f-81b8-878eb552397c&algo_exp_id=0320d764-ae5c-465f-81b8-878eb552397c-55&pdp_ext_f=%7B"order"%3A"647"%2C"eval"%3A"1"%2C"fromPage"%3A"search"%7D&pdp_npi=6%40dis%21USD%213.09%213.08%21%21%2121.00%2120.91%21%402101e81117756986183275534e0075%2112000046602507590%21sea%21US%217425461850%21X%211%210%21n_tag%3A-29913%3Bd%3A2f50d3e6%3Bm03_new_user%3A-29895&curPageLogUid=Y5nI70lgqV0x&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005008771142129%7C_p_origin_prod%3A&_gl=1*198imkq*_gcl_aw*R0NMLjE3NjkwMzU1NzEuRUFJYUlRb2JDaE1JdDY3dHF0cWRrZ01WbW1oSEFSMG93UWdMRUFRWUFpQUJFZ0tiV19EX0J3RQ..*_gcl_dc*R0NMLjE3NjkwMzU1NzEuRUFJYUlRb2JDaE1JdDY3dHF0cWRrZ01WbW1oSEFSMG93UWdMRUFRWUFpQUJFZ0tiV19EX0J3RQ..*_gcl_au*OTExMzQxMzAyLjE3NzM2MTUyNjg.*_ga*MTY2NjQwMzk4OC4xNzczNjE1MjY4*_ga_VED1YSGNC7*czE3NzU2OTg2MDQkbzckZzEkdDE3NzU2OTg2MjgkajM2JGwwJGgw 
2.8" ILI9341 TFT display,320x240 SPI,1,$12.98,https://www.aliexpress.us/item/3256808428950922.html?spm=a2g0o.productlist.main.2.2ca3smZpsmZpQg&algo_pvid=bbb42281-5179-4926-bbda-a14ba8aa49b7&algo_exp_id=bbb42281-5179-4926-bbda-a14ba8aa49b7-1&pdp_ext_f=%7B"order"%3A"39"%2C"eval"%3A"1"%2C"fromPage"%3A"search"%7D&pdp_npi=6%40dis%21USD%2112.98%218.70%21%21%2112.98%218.70%21%40210328c017756986766474334ebc63%2112000045959827813%21sea%21US%217425461850%21X%211%210%21n_tag%3A-29913%3Bd%3Abcfded55%3Bm03_new_user%3A-29895&curPageLogUid=Kei7A2R8Dbuz&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005008615265674%7C_p_origin_prod%3A
2mm clear acrylic sheet,Display window,1,$4.22,https://www.aliexpress.us/item/3256811802454241.html?spm=a2g0o.productlist.main.1.5eb5sgl3sgl3Xb&algo_pvid=e07722ce-5c64-4bfd-a23e-820d65afd5c7&algo_exp_id=e07722ce-5c64-4bfd-a23e-820d65afd5c7-0&pdp_ext_f=%7B"order"%3A"-1"%2C"eval"%3A"1"%2C"fromPage"%3A"search"%7D&pdp_npi=6%40dis%21USD%214.22%213.00%21%21%214.22%213.00%21%402101eee917756987623393711e7a89%2112000057206937412%21sea%21US%217425461850%21X%211%210%21n_tag%3A-29913%3Bd%3Abcfded55%3Bm03_new_user%3A-29895&curPageLogUid=gEe688W88iRe&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005011988768993%7C_p_origin_prod%3A
M3 heat-set inserts x4,For enclosure assembly (M3(OD4.5mm) & Length 4mm),4,$2.66,https://www.aliexpress.us/item/3256803396040989.html?spm=a2g0o.productlist.main.1.410b29ba3XAy5U&algo_pvid=3faa41a0-430e-4215-a1e0-63894394da96&algo_exp_id=3faa41a0-430e-4215-a1e0-63894394da96-0&pdp_ext_f=%7B"order"%3A"70266"%2C"eval"%3A"1"%2C"fromPage"%3A"search"%7D&pdp_npi=6%40dis%21USD%212.28%212.28%21%21%2115.53%2115.53%21%402101dedf17756989576537476e71a5%2112000026370649753%21sea%21US%217425461850%21X%211%210%21n_tag%3A-29913%3Bd%3Abcfded55%3Bm03_new_user%3A-29895&curPageLogUid=u2e9fOh4BqV5&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005003582355741%7C_p_origin_prod%3A
M3 screws x4, For enclosure assembly (M3 & 4mm),4,$1.65,https://www.aliexpress.us/item/2255800794906149.html?spm=a2g0o.productlist.main.55.b3bd48abRXSzOx&algo_pvid=2dd3ac37-7aa1-478f-adae-4bc1f17e6b0f&algo_exp_id=2dd3ac37-7aa1-478f-adae-4bc1f17e6b0f-54&pdp_ext_f=%7B"order"%3A"8797"%2C"eval"%3A"1"%2C"fromPage"%3A"search"%7D&pdp_npi=6%40dis%21USD%211.42%211.42%21%21%211.42%211.42%21%402101e83017756991041264918e4ab1%2110000013188303771%21sea%21US%217425461850%21X%211%210%21n_tag%3A-29913%3Bd%3Abcfded55%3Bm03_new_user%3A-29895&curPageLogUid=8rfIbm1sL74t&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A4000981220901%7C_p_origin_prod%3A
Dupont wires / jumper wires,Connecting display to ESP32,,,self-supplied/have extras
Total,,,~$27

wiring
TFT pin, ESP32 pin
VCC, 3.3V
GND, GND
CS, GPIO 15
RESET, GPIO 4
DC, GPIO 2
MOSI, GPIO 23
SCK, GPIO 18
LED, 3.3V (or PWM pin for brightness control)

dependencies
install these via Arduino library manager:

TFT_eSPI by Bodmer
JPEGDecoder by Bodmer
WebServer (built into ESP32 Arduino core)
SPIFFS (built into ESP32 Arduino core)

also make sure to install the ESP32 board package:
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

setup
open somnium.ino in Arduino IDE
change YOUR_SSID and YOUR_PASSWORD at the top to your wifi credentials
in Tools → Board, select "ESP32 Dev Module" (or whatever matches yours)
in Tools → Partition Scheme, pick "Default with SPIFFS" or "Huge APP (3MB No OTA/1MB SPIFFS)" — you need SPIFFS enabled
upload
open Serial Monitor at 115200 baud, wait for it to print the IP address
type that IP into your phone browser on the same wifi network
upload a JPEG

enclosure
rounded rectangle box, two shells, display window on top. the display sits behind a piece of clear acrylic glued into a recessed pocket so the surface is flush. button or switch on the back for power if you want one — or just leave it plugged in.
STLs not included yet, still designing. rough dimensions are 110×70×30mm.

just some notes
images need to be JPEG. if you're pulling something off Google Images it's probably already JPEG. if not, any free online converter works
the display is 320×240. images don't need to match that exactly, the firmware centers them and fills the rest with black
SPIFFS only stores one image at a time — uploading a new one overwrites the old one. could add a gallery later but keeping it simple for now
the device stores the last image in flash so if you unplug it overnight and plug it back in the morning, the image comes back automatically
