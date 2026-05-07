src-dir:=./src
src:=tree -Ffina --noreport\ 
	$(src-dir) |\ 
 	grep -v /$ |\ 
	 tr '\n' ' '

header-dir:=./"include"

headers:=tree -Ffina --noreport\ 
	$(header-dir) |\ 
 	grep -v /$ |\ 
	 tr '\n' ' '

out:=./build/check-disk-usage

flags:=-s -Wl,-emain -Os

build: $(out) $(src) $(headers) $(flags)
	-o $(out)\ 
	$(src)\ 
	$(headers)\ 
	$(flags)

run: $(out)
	exec $(out)

all: build run