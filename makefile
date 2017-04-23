pipeline:clean
	g++ -std=c++14 -o pipeline *.cpp
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
