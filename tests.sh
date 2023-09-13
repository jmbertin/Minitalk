#!/bin/bash

# Function to print messages in color
print_color () {
    COLOR=$1
    TEXT=$2
    printf "\e[${COLOR}m${TEXT}\e[0m\n"
}

print_color 34 "Serveur display:"
# Start the server in the background and save its PID
./server &
SERVER_PID=$!

# Allow the server to initialize
sleep 1

# Define an array of test messages
MESSAGES=(
  "Hello, world!"
  "Minitalk is great."
  "UNIX signals are fun!"
)

# Loop over the test messages and send each one to the server
for MESSAGE in "${MESSAGES[@]}"; do
  # Announce the message being sent
  echo "------------------------------------------------------------"
  print_color 36 "Client: Sending message '$MESSAGE'"
  print_color 34 "Serveur display:"

  # Send the message to the server and capture the output
  OUTPUT=$(./client $SERVER_PID "$MESSAGE")

  # Sleep for a short period to allow the server to process the message
  sleep 1

  # Check the output to see if the server confirmed receipt of the message
  if [[ $OUTPUT == *"Server confirmed reception of the message."* ]]; then
    echo ""
    print_color 32 "Client: Server confirmed reception of the message."
  else
    print_color 31 "Server: Failed to receive message"
  fi
done

# Kill the server process
kill $SERVER_PID
