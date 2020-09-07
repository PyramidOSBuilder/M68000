# M68000 Assembler

* type make to build m68.

## Usage: 
```bash
	./m68 [INFILE] [OUTFILE]
```

## Utils
* hwrite - Program for writing bytes by hand to output file
* hex	 - Program for dumping bin files to stdout in hex
### Usage
```bash
	cd utils
	make
	./hwrite > [BINFILE]
	make testbin bin=[BINFILE]
	./hex [BINFILE] 
```
 
## Useful Docs

* [Motorola 68k ISA doc](https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf)


