#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <TFT_eSPI.h>
#include <JPEGDecoder.h>

// WiFi credentials 
const char* SSID     = "MYWIFI";
const char* PASSWORD = "MYPASSWORD";

// Hardware 
TFT_eSPI tft = TFT_eSPI(); 
WebServer server(80);

// Globals
String currentImage = "";  

// HTML served at /
// Minimal single-page upload form, no frameworks
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Somnium</title>
<style>
  body { font-family: sans-serif; max-width: 420px; margin: 40px auto; padding: 0 16px; background:#111; color:#eee; }
  h2 { font-size:18px; margin-bottom:8px; }
  p  { font-size:13px; color:#888; margin:0 0 20px; }
  input[type=file] { display:block; margin-bottom:14px; }
  button { background:#5c4fff; color:#fff; border:none; padding:10px 22px; border-radius:6px; cursor:pointer; font-size:14px; }
  button:active { opacity:0.8; }
  #status { margin-top:14px; font-size:13px; color:#5eead4; }
</style>
</head>
<body>
<h2>Somnium</h2>
<p>Pick a JPEG from your phone and it shows up on the display.</p>
<input type="file" id="f" accept="image/jpeg">
<button onclick="upload()">Send to display</button>
<div id="status"></div>
<script>
function upload() {
  const file = document.getElementById('f').files[0];
  if (!file) { document.getElementById('status').innerText = 'pick a file first'; return; }
  const fd = new FormData();
  fd.append('image', file);
  document.getElementById('status').innerText = 'uploading...';
  fetch('/upload', { method:'POST', body:fd })
    .then(r => r.text())
    .then(t => { document.getElementById('status').innerText = t; })
    .catch(() => { document.getElementById('status').innerText = 'error'; });
}
</script>
</body>
</html>
)rawliteral";

// Draw JPEG
void drawJpeg(const char* path) {
  fs::File f = SPIFFS.open(path, "r");
  if (!f) { Serial.println("file open failed"); return; }

  // load raw bytes
  size_t size = f.size();
  uint8_t* buf = (uint8_t*)malloc(size);
  if (!buf) { f.close(); Serial.println("malloc failed"); return; }
  f.read(buf, size);
  f.close();

  JpegDec.decodeArray(buf, size);
  free(buf);

  // center on screen
  int offX = (tft.width()  - JpegDec.width)  / 2;
  int offY = (tft.height() - JpegDec.height) / 2;
  if (offX < 0) offX = 0;
  if (offY < 0) offY = 0;

  tft.fillScreen(TFT_BLACK);

  while (JpegDec.read()) {
    uint16_t* pImg  = JpegDec.pImage;
    int mcuX = JpegDec.MCUx * JpegDec.MCUWidth  + offX;
    int mcuY = JpegDec.MCUy * JpegDec.MCUHeight + offY;
    int mcuW = JpegDec.MCUWidth;
    int mcuH = JpegDec.MCUHeight;
    tft.pushImage(mcuX, mcuY, mcuW, mcuH, pImg);
  }
}

// HTTP handler
void handleRoot() {
  server.send_P(200, "text/html", INDEX_HTML);
}

void handleUpload() {
  // multipart upload — file lands via HTTPUpload
  HTTPUpload& upload = server.upload();

  static fs::File uploadFile;
  static const char* SAVE_PATH = "/dream.jpg";

  if (upload.status == UPLOAD_FILE_START) {
    Serial.printf("upload start: %s\n", upload.filename.c_str());
    SPIFFS.remove(SAVE_PATH);
    uploadFile = SPIFFS.open(SAVE_PATH, "w");
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (uploadFile) uploadFile.write(upload.buf, upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    if (uploadFile) {
      uploadFile.close();
      Serial.printf("upload done: %u bytes\n", upload.totalSize);
      currentImage = SAVE_PATH;
      drawJpeg(SAVE_PATH);
      server.send(200, "text/plain", "done — check your display");
    } else {
      server.send(500, "text/plain", "write failed");
    }
  }
}

void handleNotFound() {
  server.send(404, "text/plain", "not found");
}

void setup() {
  Serial.begin(115200);

  // display
  tft.init();
  tft.setRotation(1);   // landscape — adjust 0-3 to match your enclosure
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(1);
  tft.drawString("connecting...", 4, 4);

  // SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS mount failed");
    tft.drawString("SPIFFS error", 4, 20);
    while (1) delay(1000);
  }

  // redraw last image if one exists
  if (SPIFFS.exists("/dream.jpg")) {
    drawJpeg("/dream.jpg");
  }

  // wifi
  WiFi.begin(SSID, PASSWORD);
  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 30) {
    delay(500);
    Serial.print(".");
    tries++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    tft.fillScreen(TFT_BLACK);
    tft.drawString("wifi failed", 4, 4);
    Serial.println("\nwifi failed");
    return;
  }

  Serial.printf("\nIP: %s\n", WiFi.localIP().toString().c_str());

  // show IP on display if no image loaded
  if (currentImage == "") {
    tft.fillScreen(TFT_BLACK);
    tft.drawString(WiFi.localIP().toString().c_str(), 4, 4);
    tft.drawString("open in browser to upload", 4, 20);
  }

  // routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/upload", HTTP_POST, []() {}, handleUpload);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("server up");
}

// loop
void loop() {
  server.handleClient();
}
