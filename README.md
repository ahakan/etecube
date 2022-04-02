
## Installation

### *Installing Prerequisites: CMake*

Please install cmake.

### *Step 1: Clone this project*

```sh
git clone https://github.com/ahakan/etecube.git   
```

### *Step 2.2: Build this project with CMake*
```sh
cd without_rsa
mkdir build && cd build
cmake .. 
make

./client/client 8080 
```

## Usage

```sh
cd server           
./server 8080       
```
and
```sh
cd client           
./client 8080    
``` 
