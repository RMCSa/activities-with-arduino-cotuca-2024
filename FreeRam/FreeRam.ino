#include <MemoryUsage.h>

void setup()
{
    Serial.begin(115200);
    Serial.println(F("Starting state of the memory:"));
    Serial.println();
    Serial.println("Total de memoria do dispositivo");
    MEMORY_PRINT_TOTALSIZE
    Serial.println();
   
    MEMORY_PRINT_START
    MEMORY_PRINT_HEAPSTART
    MEMORY_PRINT_HEAPEND
    MEMORY_PRINT_STACKSTART
    MEMORY_PRINT_END
    MEMORY_PRINT_HEAPSIZE

    Serial.println();
    Serial.println();
   
    FREERAM_PRINT;

    doible valor = 100.0;
    Serial.println("Exemplo Float");
    Serial.println(valor);
    Serial.print("Tamanho da variavel valor ");
    Serial.println(sizeof(valor));
    byte* p = (byte*)(void*)&valor;
    Serial.println(*p++);

    Serial.println(*p++);
    Serial.println(*p++);
    Serial.println(*p++);

  
   
    //byte *p = new byte[3000];  
     
    //*p++ = 'A';
    //*p++ = 'A';
   
    Serial.println();
    Serial.println();
   
    Serial.println(F("Ending state of the memory:"));
    Serial.println();
   
    MEMORY_PRINT_START
    MEMORY_PRINT_HEAPSTART
    MEMORY_PRINT_HEAPEND
    MEMORY_PRINT_STACKSTART
    MEMORY_PRINT_END
    MEMORY_PRINT_HEAPSIZE
   
    Serial.println();
    Serial.println();
   
    FREERAM_PRINT;
}

void loop()
{

}