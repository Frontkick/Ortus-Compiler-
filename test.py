import subprocess

# Define the command to run (replace with your actual C++ program path and arguments)
command = ["./cmake-build-debug-wsl/ortus", "test.ort"]

# Capture standard error using PIPE
process = subprocess.Popen(command, stderr=subprocess.PIPE)

# Communicate with the process to get standard output and error
stdout, stderr = process.communicate()

# Check for errors
if stderr:
  # Decode the error message from bytes (assuming UTF-8 encoding)
  error_message = stderr.decode("utf-8")
  print("Error occurred:", error_message)
  # Handle the error (e.g., log it, raise an exception)
else:
  print(stdout.decode("utf-8"))

# ... rest of your Python code
