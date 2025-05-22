# Use a base image with GCC C++ compiler
FROM gcc:latest

# Set the working directory in the container
WORKDIR /app

# Copy the C++ source files into the container at /app
COPY Calc.h Calc.cpp main.cpp ./

# Compile the C++ application
# -std=c++11 for C++11 features
# -o calculator specifies the output file name
# -lm links the math library
RUN g++ -std=c++11 main.cpp Calc.cpp -o calculator -lm

# Set the default command to run when the container starts
CMD ["./calculator"]
