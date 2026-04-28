py-file:=./CheckDiskUsage.py
test: $(py-file)
	python3 $(py-file)

ifile:=./dist/CheckDiskUsage
ofile:=./dist/check-disk-usage
build: $(py-file) $(ifile) $(ofile)
	pyinstaller --onefile $(py-file)
	mv $(ifile) $(ofile)
	chmod +x $(ofile)

run: $(ofile)
	exec $(ofile)

debug: build run