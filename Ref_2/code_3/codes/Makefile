CC := g++
MK_DIR = mkdir -p
OUT_DIR = outputs/

all: ${OUT_DIR} tb.out

${OUT_DIR}:
	${MK_DIR} ${OUT_DIR}

tb.out: avgFinder_TB.o  utilityFunctions.o classVectorPrimitives.o avgFinder_DP.o avgFinder_CU.o avgFinder_TOP.o
	$(CC) ${OUT_DIR}avgFinder_TB.o ${OUT_DIR}utilityFunctions.o ${OUT_DIR}classVectorPrimitives.o ${OUT_DIR}avgFinder_TOP.o ${OUT_DIR}avgFinder_DP.o ${OUT_DIR}avgFinder_CU.o -o tb.out

avgFinder_TB.o: avgFinder_TB.cpp 
	$(CC) -c avgFinder_TB.cpp -o ${OUT_DIR}avgFinder_TB.o

# extraClassPrimitives.o: extraClassPrimitives.hpp extraClassPrimitives.cpp
# 	$(CC) -c extraClassPrimitives.cpp -o ${OUT_DIR}extraClassPrimitives.o

utilityFunctions.o: utilityFunctions.cpp
	$(CC) -c utilityFunctions.cpp -o ${OUT_DIR}utilityFunctions.o

classVectorPrimitives.o: classVectorPrimitives.cpp
	$(CC) -c classVectorPrimitives.cpp -o ${OUT_DIR}classVectorPrimitives.o

avgFinder_DP.o: avgFinder_DP.h avgFinder_DP.cpp
	$(CC) -c avgFinder_DP.cpp -o ${OUT_DIR}avgFinder_DP.o

avgFinder_CU.o: avgFinder_CU.h avgFinder_CU.cpp
	$(CC) -c avgFinder_CU.cpp -o ${OUT_DIR}avgFinder_CU.o

avgFinder_TOP.o: avgFinder_TOP.h avgFinder_TOP.cpp
	$(CC) -c avgFinder_TOP.cpp -o ${OUT_DIR}avgFinder_TOP.o

clean:
	rm -r ${OUT_DIR}
	rm tb.out
	rm Assignment.vcd
