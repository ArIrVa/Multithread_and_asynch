# Get the GCC preinstalled image from Docker Hub
FROM gcc:latest

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . /home/irbis/Netology/homework/Multithread_and_asynch/hw_7.5/hw_07_05_task_1

# Specify the working directory
WORKDIR /home/irbis/Netology/homework/Multithread_and_asynch/hw_7.5/hw_07_05_task_1

# Use GCC to compile the Test.cpp source file
RUN g++ -o hw_07_05_1 hw_07_05_1.cpp
 
# Run the program output from the previous step
CMD ["./hw_07_05_1"]

LABEL Name=hw7_1 Version=0.0.1
