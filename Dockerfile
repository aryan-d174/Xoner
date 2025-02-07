# Use a base image with g++ and CMake
FROM debian:latest

# Install dependencies
RUN apt update && apt install -y g++ cmake curl libcurl4-openssl-dev

# Set working directory
WORKDIR /app

# Copy project files
COPY . .

# Compile the C++ program
RUN cmake . && make

# Expose port 8080
EXPOSE 8080

# Run the compiled backend
CMD ["./backend"]
