
# Taskforge
Taskforge is a parcel delivery management system, aimed to help keep track of parcels that are to be delivered to customers. The system keeps track of the state of each parcel and allows retrieving parcels based on priority delivery.


## Authors

- [u24916031 - Jamie King](https://github.com/u24916031-Jamie)
- [u25089464 - Lushomo Mankomba](https://github.com/HesNot-Real)
- [u24984362 - Joelle Tsaku](https://github.com/Joelle-Tsaku)


## Run Locally

Clone the project

```bash
git clone https://github.com/HesNot-Real/Cos214Prac4
```

Go to the project directory

```bash
cd Cos214Prac4
```

Build Docker Image
```bash
docker build -t cos214pa4 .
```

Run Docker
```bash
docker run -it cos214pa4
```

Compile

```bash
make
```

Run

```bash
./taskforge
```

Run valgrind
```bash
valgrind ./taskforge
```


Run gdb
```bash
make test
make runtest
```