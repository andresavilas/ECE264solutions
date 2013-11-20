GCC = gcc
CFLAGS = -g -Wall -Wshadow
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

pa06: pa07.o answer07.o
	$(GCC) $(CFLAGS) pa07.o answer07.o -o ./pa07

pa06.o: pa07.c answer07.c
	$(GCC) $(CFLAGS) -c pa07.c

answer06.o: pa07.c answer07.c
	$(GCC) $(CFLAGS) -c answer07.c 

clean: 
	@rm *.o pa07

testall: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11

test1: pa07
	./pa07 inputs/input0_A inputs/input0_B > outputs/output0 
	$(VALGRIND) --log-file=valgrindlog1 ./pa07 inputs/input0_A inputs/input0_B 
	diff outputs/output0 expected/expected0

test2: pa07
	./pa07 inputs/input10_A inputs/input10_B > outputs/output1 
	$(VALGRIND) --log-file=valgrindlog2 ./pa07 inputs/input10_A inputs/input10_B
	diff outputs/output1 expected/expected10

test3: pa07
	./pa07 inputs/input2_A inputs/input2_B > outputs/output2  
	$(VALGRIND) --log-file=valgrindlog3 ./pa07 inputs/input2_A inputs/input2_B 
	diff outputs/output2 expected/expected2

test4: pa07
	./pa07 inputs/input3_A inputs/input3_B > outputs/output3
	$(VALGRIND) --log-file=valgrindlog4 ./pa07 inputs/input3_A inputs/input3_B 
	diff outputs/output3 expected/expected3

test5: pa07
	./pa07 inputs/input1_A inputs/input1_B > outputs/output4
	$(VALGRIND) --log-file=valgrindlog5 ./pa07 inputs/input1_A inputs/input1_B
	diff outputs/output4 expected/expected1

test6: pa07
	./pa07 inputs/input4_A inputs/input4_B > outputs/output5
	$(VALGRIND) --log-file=valgrindlog6 ./pa07 inputs/input4_A inputs/input4_B 
	diff outputs/output5 expected/expected4

test7: pa07
	./pa07 inputs/input5_A inputs/input5_B > outputs/output6
	$(VALGRIND) --log-file=valgrindlog7 ./pa07 inputs/input5_A inputs/input5_B 
	diff outputs/output6 expected/expected5

test8: pa07
	./pa07 inputs/input6_A inputs/input6_B > outputs/output7
	$(VALGRIND) --log-file=valgrindlog8 ./pa07 inputs/input6_A inputs/input6_B 
	diff outputs/output7 expected/expected6

test9: pa07
	./pa07 inputs/input7_A inputs/input7_B > outputs/output8
	$(VALGRIND) --log-file=valgrindlog9 ./pa07 inputs/input7_A inputs/input7_B 
	diff outputs/output8 expected/expected7

test10: pa07
	./pa07 inputs/input8_A inputs/input8_B > outputs/output9
	$(VALGRIND) --log-file=valgrindlog10 ./pa07 inputs/input8_A inputs/input8_B 
	diff outputs/output9 expected/expected8

test11: pa07
	./pa07 inputs/input9_A inputs/input9_B > outputs/output10
	$(VALGRIND) --log-file=valgrindlog11 ./pa07 inputs/input9_A inputs/input9_B 
	diff outputs/output10 expected/expected9
