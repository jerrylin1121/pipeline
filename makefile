pipeline:clean simulator.o InstructionDecode.o memory.o regfile.o InstructionFetch.o
	g++ -std=c++0x -g -o pipeline simulator.o InstructionDecode.o memory.o regfile.o InstructionFetch.o
	rm -f *.o
InstructionFetch.o:
	g++ -std=c++0x -c InstructionFetch.cpp -o InstructionFetch.o
error.o:error.cpp
	g++ -std=c++0x -c error.cpp -o error.o
regfile.o:regfile.cpp
	g++ -std=c++0x -c regfile.cpp -o regfile.o
memory.o:memory.cpp
	g++ -std=c++0x -c memory.cpp -o memory.o
InstructionDecode.o:InstructionDecode.cpp
	g++ -std=c++0x -c InstructionDecode.cpp -o InstructionDecode.o
simulator.o:simulator.cpp
	g++ -std=c++0x -c simulator.cpp -o simulator.o
clean:
	rm -f *.o *.rpt pipeline
clean_test:
	rm -f *.rpt makefile result
my:
	~/Archi2017_Project2/pipeline/simulator/pipeline
goldon:
	~/Archi2017_Project2/archiTA/simulator/pipeline
diff_snap:
	diff ./snapshot.rpt ./_snapshot.rpt
diff_error:
	diff ./error_dump.rpt ./_error_dump.rpt
