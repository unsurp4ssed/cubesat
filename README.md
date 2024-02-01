# Get
```sh
git clone https://github.com/unsurp4ssed/cubesat
```

# Build
```sh
cmake .
make
```

# Run
## binarisation
```sh
./binar [source img path] [result img path]
```
## median filtering
```sh
./median [source img path] [result img path]
```
## closening-opening filter
```sh
./close-open [source img path] [result img path]
```

There're test images provided in the data/
### example:
```sh
./binar data/stars.bmp a.bmp
```
