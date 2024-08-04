#include <Servo.h>

Servo gateServo; // Define a servo object for the gate
const int trigFrontPin = 2;
const int echoFrontPin = 3;
const int trigRearPin = 4;
const int echoRearPin = 5;
const int gateOpenAngle = 90;    // Angle to open the gate
const int gateClosedAngle = 0; // Angle to close the gate
const int numberOfSlots = 5;
int availableSlots = numberOfSlots;
const int ledPins[] = {6, 7, 8, 9, 10};
int carCount = 0; // Initialize car count

void setup()
{
  gateServo.attach(11); // Servo motor control pin
  pinMode(trigFrontPin, OUTPUT);
  pinMode(echoFrontPin, INPUT);
  pinMode(trigRearPin, OUTPUT);
  pinMode(echoRearPin, INPUT);
  gateServo.write(0);
  for (int i = 0; i < numberOfSlots; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
  updateLEDs();

  Serial.begin(9600);
}

void loop()
{
  long frontDistance = measureDistance(trigFrontPin, echoFrontPin);
  long rearDistance = measureDistance(trigRearPin, echoRearPin);

  // Check if a car is entering from the front
  if (frontDistance < 15)
  {
    if (availableSlots > 0)
    {
      openGate();
      availableSlots--;
      carCount++;
      updateLEDs();
      delay(2000); // Allow 3 seconds for a car to pass through
      closeGate();
    }
    else if (availableSlots == 0)
    {
      Serial.println("Slots are Full");
    }
  }

  // Check if a car is leaving from the rear
  if (rearDistance < 15)
  {
    if (availableSlots > -1 && availableSlots < 5)
    {
      availableSlots++;
      carCount--;
      updateLEDs();
      openGate();
      delay(3000);
      closeGate();
    } // Delay to prevent multiple counts for the same car
  }

  // Display information on Serial Monitor
  Serial.print("Front Distance: ");
  Serial.print(frontDistance);
  Serial.print(" cm | Rear Distance: ");
  Serial.print(rearDistance);
  Serial.print(" cm | Available Slots: ");
  Serial.print(availableSlots);
  Serial.print(" | Car Count: ");
  Serial.println(carCount);
}

long measureDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH) / 58.2; // Calculate distance in centimeters
}

void openGate()
{
  gateServo.write(gateOpenAngle);
}

void closeGate()
{
  gateServo.write(gateClosedAngle);
}

void updateLEDs()
{
  if (availableSlots == 0)
  {
    digitalWrite(ledPins[0], LOW);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[3], LOW);
    digitalWrite(ledPins[4], LOW);
  }
  if (availableSlots == 1)
  {
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[3], LOW);
    digitalWrite(ledPins[4], LOW);
  }
  if (availableSlots == 2)
  {
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[3], LOW);
    digitalWrite(ledPins[4], LOW);
  }
  if (availableSlots == 3)
  {
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], HIGH);
    digitalWrite(ledPins[3], LOW);
    digitalWrite(ledPins[4], LOW);
  }
  if (availableSlots == 4)
  {
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], HIGH);
    digitalWrite(ledPins[3], HIGH);
    digitalWrite(ledPins[4], LOW);
  }
  if (availableSlots == 5)
  {
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], HIGH);
    digitalWrite(ledPins[3], HIGH);
    digitalWrite(ledPins[4], HIGH);
  }
}




