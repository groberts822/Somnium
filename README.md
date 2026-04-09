# Somnium
bedside dream image frame. you find an image online that looks like what you dreamed, open the web UI on your phone, upload it, and it shows up on the display. that's the whole thing.
i saw a project that used AI to generate dream imagery based on a description you speak into a mic and I liked the physical form factor, which is just a matte rounded box with a glowing display sitting on a nightstand, but i didn't want any of the AI stuff. finding an image that already looks right takes like 20 seconds. describing your dream well enough to get anything useful out of a model takes way longer and the result is usually off anyway.
so basically this is just a picture frame with wifi.

how it works
ESP32 connects to your wifi on boot and hosts a tiny web server. open the IP in your phone browser, pick a JPEG, hit send. the image gets written to flash and drawn on the display. next time it boots it reloads the last image automatically.
no app, cloud, account, or mic.

hardware
part, notes, approx cost
ESP32 dev board, any standard 30-pin and has wifi built in, $4
2.8" ILI9341 TFT320×240 SPI display, dead simple to wire, $8
USB power supply, 5V 1A plugged in permanently $5
3D printed enclosure, around 100g PLA or PETG, $3
2mm clear acrylic, small piece for display window, $2
M3 heat-set inserts ×4, for screwing the shells together, $1
jumper wires, general wires for connecting display to ESP32
total around $25

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
