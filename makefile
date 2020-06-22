# Makefile

make_file: 
	cd src && make && mv libssandbox.a ..

.PHONY clean:
	rm -rf *.a && cd src && make clean
