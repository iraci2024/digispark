import serial
import requests
import time
import serial.tools.list_ports

# Listar portas seriais disponíveis
ports = serial.tools.list_ports.comports()
for port in ports:
    print(f"Porta disponível: {port.device}")


# URL do formulário que receberá os dados
url = 'http://108.165.179.123:5000/submit'  # Substitua <seu_ip> pelo IP do seu servidor

# Configuração da porta serial (verifique qual porta seu ATtiny85 está conectado)
ports = serial.tools.list_ports.comports()
if not ports:
    print("Nenhuma porta serial disponível.")
    exit()

print("Portas seriais disponíveis:")
for i, port in enumerate(ports):
    print(f"{i}: {port.device}")

port_index = int(input("Selecione o índice da porta serial: "))
ser = serial.Serial(ports[port_index].device, 9600)

while True:
    try:
        line = ser.readline().decode('utf-8').strip()  # Lê a linha da porta serial
        if line:
            print(f"Capturado: {line}")  # Exibe no console
            # Envia os dados para o servidor
            data = {'input_data': line}  # Mapeia a chave para os dados capturados
            response = requests.post(url, data=data)  # Envia dados via POST
            print(f"Resposta do servidor: {response.status_code}")  # Exibe status da resposta
    except serial.SerialException:
        print("Erro na comunicação com o dispositivo serial.")
        break
    except requests.exceptions.RequestException as e:
        print(f"Erro ao enviar dados: {e}")
    time.sleep(1)  # Espera 1 segundo antes de ler novamente
