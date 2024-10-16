from flask import Flask, request, render_template
import os

app = Flask(__name__)

# Rota principal que exibe o formulário
@app.route('/')
def index():
    return render_template('index.html')

# Rota para receber os dados enviados
@app.route('/submit', methods=['POST'])
def submit():
    input_data = request.form['input_data']
    # Armazena os dados em um arquivo ou processa conforme necessário
    with open('captured_data.txt', 'a') as f:
        f.write(input_data + '\n')  # Salva os dados em um arquivo
    print(f'Dados recebidos: {input_data}')  # Imprime no console do servidor
    return 'Dados recebidos com sucesso!', 200

@app.route('/captured')
def captured():
    with open('captured_data.txt', 'r') as f:
        data = f.read()  # Lê os dados do arquivo
    return data

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')  # Escuta em todas as interfaces
