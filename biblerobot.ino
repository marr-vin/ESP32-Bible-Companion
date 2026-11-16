
#define DEST_FS_USES_LITTLEFS

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LittleFS.h>
#include <ESP32-targz.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* books[] = {
  "1_corinthians",
  "1_john",
  "1_peter",
  "1_thessalonians",
  "1_timothy",
  "2_corinthians",
  "2_john",
  "2_peter",
  "2_thessalonians",
  "2_timothy",
  "3_john",
  "amos",
  "colossians",
  "ecclesiastes",
  "ephesians",
  "ezekiel",
  "galatians",
  "habakkuk",
  "haggai",
  "hebrews",
  "hosea",
  "isaiah",
  "james",
  "jeremiah",
  "job",
  "joel",
  "john",
  "jonah",
  "jude",
  "lamentations",
  "luke",
  "malachi",
  "mark",
  "matthew",
  "micah",
  "nahum",
  "obadiah",
  "philemon",
  "philippians",
  "proverbs",
  "psalms",
  "romans",
  "song_of_solomon",
  "titus",
  "zechariah",
  "zephaniah"
};

const char* bookNames[] = {
  "1 Corinthians",
  "1 John",
  "1 Peter",
  "1 Thessalonians",
  "1 Timothy",
  "2 Corinthians",
  "2 John",
  "2 Peter",
  "2 Thessalonians",
  "2 Timothy",
  "3 John",
  "Amos",
  "Colossians",
  "Ecclesiastes",
  "Ephesians",
  "Ezekiel",
  "Galatians",
  "Habakkuk",
  "Haggai",
  "Hebrews",
  "Hosea",
  "Isaiah",
  "James",
  "Jeremiah",
  "Job",
  "Joel",
  "John",
  "Jonah",
  "Jude",
  "Lamentations",
  "Luke",
  "Malachi",
  "Mark",
  "Matthew",
  "Micah",
  "Nahum",
  "Obadiah",
  "Philemon",
  "Philippians",
  "Proverbs",
  "Psalms",
  "Romans",
  "Song of Solomon",
  "Titus",
  "Zechariah",
  "Zephaniah"
};

const int bookCount = sizeof(books) / sizeof(books[0]);

int currentBook = -1;

String currentReference = "";
String currentVerse = "";

GzUnpacker GZUnpacker;

String cleanVerse(String text) {

  while (true) {

    int start = text.indexOf("\\+w ");

    if (start < 0)
      break;

    int end = text.indexOf("\\+w*", start);

    if (end < 0)
      break;

    String word = text.substring(start + 4, end);

    int strong = word.indexOf("strong=");

    if (strong >= 0)
      word = word.substring(0, strong);

    text = text.substring(0, start) + word + text.substring(end + 4);
  }

  text.replace("\\+w*", "");
  text.replace("\\add*", "");
  text.replace("\\add ", "");
  text.replace("\\nd*", "");
  text.replace("\\nd ", "");
  text.replace("\\wj*", "");
  text.replace("\\wj ", "");

  text.replace("  ", " ");

  text.trim();

  return text;
}

bool loadRandomVerse() {

  currentBook = random(bookCount);

  String gzPath = "/" + String(books[currentBook]) + ".gz";
  String txtPath = "/" + String(books[currentBook]) + ".txt";

  Serial.println();
  Serial.print("Selected: ");
  Serial.println(bookNames[currentBook]);

  if (LittleFS.exists(txtPath))
    LittleFS.remove(txtPath);

  GZUnpacker.haltOnError(false);

  GZUnpacker.setupFSCallbacks(targzTotalBytesFn, targzFreeBytesFn);

  GZUnpacker.setGzProgressCallback(BaseUnpacker::defaultProgressCallback);

  GZUnpacker.setLoggerCallback(BaseUnpacker::targzPrintLoggerCallback);

  Serial.println("Decompressing...");

  if (!GZUnpacker.gzExpander(
        LittleFS,
        gzPath.c_str(),
        LittleFS,
        txtPath.c_str()
      )) {

    Serial.print("Decompression failed: ");
    Serial.println(GZUnpacker.tarGzGetError());

    return false;
  }

  Serial.println("Decompression successful");

  File file = LittleFS.open(txtPath, "r");

  if (!file) {
    Serial.println("Could not open decompressed file");
    return false;
  }

  int totalLines = 0;

  while (file.available()) {
    file.readStringUntil('\n');
    totalLines++;
  }

  if (totalLines == 0) {
    file.close();
    LittleFS.remove(txtPath);
    return false;
  }

  int selectedLine = random(totalLines);

  file.seek(0);

  String line;

  for (int i = 0; i <= selectedLine; i++)
    line = file.readStringUntil('\n');

  file.close();

  line.trim();

  int firstBar = line.indexOf("|");
  int secondBar = line.indexOf("|", firstBar + 1);
  int thirdBar = line.indexOf("|", secondBar + 1);

  if (firstBar < 0 || secondBar < 0 || thirdBar < 0) {

    Serial.println("Invalid verse format");

    LittleFS.remove(txtPath);

    return false;
  }

  String chapter = line.substring(firstBar + 1, secondBar);
  String verseNumber = line.substring(secondBar + 1, thirdBar);
  String verseText = line.substring(thirdBar + 1);

  verseText = cleanVerse(verseText);

  currentReference = String(bookNames[currentBook]) + " " + chapter + ":" + verseNumber;

  currentVerse = verseText;

  Serial.println(currentReference);
  Serial.println(currentVerse);

  LittleFS.remove(txtPath);

  return true;
}

void showVerse() {

  lcd.clear();


  lcd.setCursor(0, 0);
  lcd.print(currentReference);

  String message = "                " + currentVerse + "                ";

  for (int i = 0; i <= message.length() - 16; i++) {

    lcd.setCursor(0, 1);
    lcd.print(message.substring(i, i + 16));

    delay(180);
  }

  delay(1500);

  lcd.clear();

  Serial.println();
  Serial.println("y = new quotation");
  Serial.println("r = repeat quotation");
}

void setup() {

  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();

  Serial.begin(115200);

  if (!LittleFS.begin()) {

    Serial.println("LittleFS ERROR");

    lcd.clear();
    lcd.print("FS ERROR");

    return;
  }

  randomSeed(analogRead(34));

  Serial.println("Bible Robot");
  Serial.println("LittleFS OK");

  if (loadRandomVerse())
    showVerse();
}

void loop() {

  if (Serial.available()) {

    char input = Serial.read();

    if (input == 'y' || input == 'Y') {

      if (loadRandomVerse())
        showVerse();
    }

    if (input == 'r' || input == 'R')
      showVerse(); 
  }
}

