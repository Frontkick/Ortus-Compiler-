# Use a base image with package management
FROM ubuntu:latest

# Copy your project files
COPY . /usr/src/Ortus

# Set working directory
WORKDIR /usr/src/Ortus

# Install build dependencies
RUN apt-get update && apt-get install -y g++ cmake nasm python3 python3-flask
RUN apt install -y gunicorn

EXPOSE 5000

# Define the command to run

CMD ["gunicorn", "--bind", "0.0.0.0:5000", "app:app"]
