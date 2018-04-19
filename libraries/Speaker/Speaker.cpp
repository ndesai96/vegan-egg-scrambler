#include <Speaker.h>

Speaker::Speaker(int digitalPin) {
  _digitalPin = digitalPin;
}

void Speaker::begin() {
  pinMode(_digitalPin, OUTPUT);
}

void Speaker::flatTone(int frequency, int duration) {
  tone(_digitalPin, frequency); // 1000 Hz
  delay(duration);
  noTone(_digitalPin);
}

void Speaker::texasFight(int tempo) {
  char notes[232] = {
  'f', 'b', 'f', 'b', 'd', 'b', 'd', 'F', ' ', 'e',
  'F', 'I', 'G', 'S', 'A', ' ', 'f', 'f', 'b', ' ',
  'f', 'b', 'd', ' ', 'b', 'a', 'g', 'b', 'g', 'b',
  'g', 'f', ' ', 'f', 'f', 'b', ' ', 'f', 'b', 'd',
  ' ', 'b', 'a', 'g', 'c', 'n', 'c', 'd', 'c', ' ',
  'b', 'd', 'F', 'd', 'b', 'f', ' ', 'b', 'a', 'g',
  'b', 'b', 'c', 's', 'd', ' ', 'f', 'g', 'a', 'b',
  'c', 's', 'd', ' ', 'd', ' ', 'b', 'c', 'b', 'f',
  'f', 'i', 'g', 'b', 'g', 'b', 'c', 'b', ' ', 'f',
  'd', 'd', 'd', 'b', 'd', 'F', 'F', 'F', 'F', 'F',
  'F', 'G', 'F', 'd', 'c', 'b', 'd', 'd', 'd', 'b',
  'd', 'F', 'F', 'F', 'F', 'G', 'F', 'd', 'c', 'b',
  ' ', 'f', 'd', 'd', 'd', 'b', 'd', 'F', 'F', 'F',
  'F', 'F', 'F', 'G', 'F', 'd', 'c', 'b', 'd', 'd',
  'd', 'b', 'd', 'F', 'F', 'F', 'F', 'F', 'F', 'G',
  'A', 'B', ' ', 'f', 'b', 'f', 'b', 'f', 'b', 'c',
  'd', 'b', 'j', 'j', 'b', 'c', 'd', ' ', 'f', 'b',
  'f', 'b', 'f', 'b', 'c', 'd', 'b', 'd', 'd', 'd',
  'c', 'n', 'c', 'd', 'c', ' ', 'b', 'd', 'F', 'd',
  'b', 'f', ' ', 'b', 'a', 'g', 'b', 'b', 'c', 's',
  'd', ' ', 'f', 'g', 'a', 'b', 'c', 's', 'd', ' ',
  'd', ' ', 'b', 'c', 'b', 'f', 'f', 'i', 'g', 'b',
  'g', 'b', 'c', 'b', 'c', 'd', 'e', 'F', 'G', 'A',
  'B', ' '};

  int beats[232] = {
  6, 6, 3, 3, 6, 3, 3, 12, 6, 6, 6, 6, 6, 6, 6, 6,
  9, 3, 24, 12, 9, 3, 24, 12, 9, 3, 6, 12, 6, 12,
  12, 24, 12, 9, 3, 24, 12, 9, 3, 24, 12, 9, 3, 6,
  12, 6, 12, 12, 24, 12, 9, 3, 24, 12, 12, 24, 12,
  9, 3, 6, 12, 6, 12, 12, 24, 6, 3, 3, 3, 3, 3, 3,
  12, 12, 12, 6, 6, 12, 12, 12, 9, 3, 6, 12, 6, 12,
  12, 24, 12, 12, 8, 4, 4, 4, 4, 8, 4, 12, 8, 4, 4,
  4, 4, 8, 4, 12, 8, 4, 4, 4, 4, 8, 4, 12, 4, 4, 4,
  8, 4, 6 , 6, 12, 8, 4, 4, 4, 4, 8, 4, 12, 8, 4, 4,
  4, 4, 8, 4, 12, 8, 4, 4, 4, 4, 8, 4, 12, 4, 4, 4,
  8, 4, 6, 6, 12, 18, 6, 6, 6, 6, 6, 24, 24, 18, 6,
  12, 12, 24, 12, 12, 18, 6, 6, 6, 6, 6, 24, 12, 9,
  3, 6, 12, 6, 12, 12, 24, 12, 9, 3, 24, 12, 12, 24,
  12, 9, 3, 6, 12, 6, 12, 12, 24, 6, 3, 3, 3, 3, 3, 3,
  12, 12, 12, 6, 6, 12, 12, 12, 9, 3, 6, 12, 6, 12, 12,
  6, 3, 3, 3, 3, 3, 6, 2};


  for (int i = 0; i < 232; i++) {
    int duration = beats[i] * tempo;
    if (notes[i] == ' ') {
      delay(duration);
    }
    else {
      tone(_digitalPin, frequency(notes[i]), duration);
      delay(duration);
    }
    delay(tempo / 10);
  }
  noTone(_digitalPin);
}

int Speaker::frequency(char note) {
  const int numNotes = 17;
  char names[numNotes] = {
    'f', 'i', 'g', 'a', 'b', 'n', 'c', 's', 'd', 'j', 'e', 'F','I', 'G','S','A', 'B'};
  int frequencies[numNotes] = {
    311, 330, 349, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831};

  for (int i = 0; i < numNotes; i++)
  {
    if (names[i] == note)
    {
      return(frequencies[i]);
    }
  }
  return(0);
}
