import subprocess
import  os
from flask import Flask, request, render_template

app = Flask(__name__)

@app.route('/ortus', methods=['POST'])
def process_code():
    # Get the code from the form submission
    code = request.form.get('code')

    with open("test.ort", "w") as file:
    # Write text to the file
        file.write(code)

    # The 'with' statement automatically closes the file
    print("Text written to test.ort")

    os.system("./cmake-build-debug-wsl/ortus test.ort")
    result = subprocess.run(['./out'], capture_output=True, text=True)
    # Print the output

    x=result.returncode

    # You can process the code here (e.g., evaluate, analyze)
    # This is a simple example that just returns the code
    response = f"{x}"

    command = ["./cmake-build-debug-wsl/ortus", "test.ort"]

# Capture standard error using PIPE
    process = subprocess.Popen(command, stderr=subprocess.PIPE)

    # Communicate with the process to get standard output and error
    stdout, stderr = process.communicate()

    # Check for errors
    if stderr:
    # Decode the error message from bytes (assuming UTF-8 encoding)
        error_message = stderr.decode("utf-8")
        return error_message

    # Render a template with the response
    return response

if __name__ == '__main__':
    app.run(debug=True,host = '0.0.0.0')

# sudo docker login -u "frontkick11" -p "Soumya@7378" docker.io
# sudo docker push frontkick11/flask:0.0.1