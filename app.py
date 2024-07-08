import subprocess
import  os
from flask import Flask, request, render_template

app = Flask(__name__)

@app.after_request
def add_cors_headers(response):
    response.headers.add('Access-Control-Allow-Origin', '*')
    response.headers.add('Access-Control-Allow-Headers', 'Content-Type,Authorization')
    response.headers.add('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE,OPTIONS')
    return response

@app.route('/ortus', methods=['POST'])
def process_code():
    code = request.form.get('code')

    with open("test.ort", "w") as file:
        file.write(code)

    
    print("Text written to test.ort")

    os.system("./cmake-build-debug-wsl/ortus test.ort")
    result = subprocess.run(['./out'], capture_output=True, text=True)
    

    x=result.returncode


    response = f"{x}"

    command = ["./cmake-build-debug-wsl/ortus", "test.ort"]


    process = subprocess.Popen(command, stderr=subprocess.PIPE)


    stdout, stderr = process.communicate()

    if stderr:

        error_message = stderr.decode("utf-8")
        return error_message



    return response

if __name__ == '__main__':
    app.run(debug=True,host = '0.0.0.0')

