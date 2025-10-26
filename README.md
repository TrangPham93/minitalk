# minitalk

minitalk is a simple client-server communication program using UNIX signals (`SIGUSR1` and `SIGUSR2`).

## Features:

There are 2 programs:

- Server → receives messages:
  - Server needs to print its PID so client knows where to send the signals.
  - Wait for incoming signal using `sigaction()`.
  - When it receives a complete byte (8 bits) then it prints the character.
- Client → sends messages:
  - Client takes 2 arguments: server ID and string to send. 
  - The client converts each character to bits and sends signal one by one.
  - Add null character at the end to indicate end of message. 
- Signal encoding:
  - `SIGUSR1` → represents binary 0
  - `SIGUSR2` → represents binary 1

## How To Run:

### Requirements:
Linux OS

### Installment:
#### 1. Clone the Repository

```bash
git clone https://github.com/TrangPham93/minitalk.git minitalk
cd minitalk
```

#### 2. Compile the Project

```bash
make
```

#### 3. Run the project

Open 2 or more terminals.
On the 1st terminal, run the `server` first, server will return a process ID immediately.
```bash
./server 
```

On the other terminals, run the `client` and connect to the `server`. 
```
./client PID [messages]
```
#### 4. Examples

<img width="1500" height="300" alt="image" src="https://github.com/user-attachments/assets/e881c66f-1730-44a9-9f7f-6c6338d52912" />


