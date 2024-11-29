// Interrupção - Interna e externa
//

#define led 4
#define external_int_Pin 3

volatile byte estado_led = LOW;
volatile byte estado_prescaler;

using ISR_callback = void(*)();

volatile ISR_callback ISR_function;

ISR(TIMER1_OVF_vect){
  ISR_function();
  pisca_led();
}

void Event_handler(ISR_callback callback, byte Freq){
  cli(); //desliga as interrupções para que não ocorram 
  		//quando do processamento dessa função
  ISR_function = callback;
  
  estado_prescaler = Freq;
  
  TCCRIA = 0b00000000; // modo normal
  
  TCCRIB = Freq & 0x07;

  TMISK1 = 0x01; // hablita a interrupção de overflow do timer
  
  sei(); // habilita as interupções
}

void pisca_led(){
  digitalWrite(led, estado_led);
  estado_led = !estado_led;
}

void setup()
{
  pinMode(led, OUTPUT);
  
  Event_handler(pisca_led, 0x00000100);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}