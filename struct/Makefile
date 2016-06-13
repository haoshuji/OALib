CXX = g++
CFLAGS = -g -Wall 
all: SOAL
OBJS = Start.o Data.o Experiment.o Parameter.o Result.o Vector.o\
	Model.o ModelAROW.o ModelAROWC.o ModelAROWCD.o ModelAROWD.o ModelPA.o \
	ModelPE.o ModelSOP.o ModelSOPD.o

SOAL: $(OBJS)	
	$(CXX) $(CFLAGS) -o SOAL $(OBJS) 
	# -O1 -larmadillo

AOS_main.o: Start.cpp
	$(CXX) $(CFLAGS) -c Start.cpp

Data.o: Data.h
	$(CXX) $(CFLAGS) -c Data.h Data.cpp

Experiment.o: Experiment.h Experiment.cpp
	$(CXX) $(CFLAGS) -c Experiment.h Experiment.cpp

Parameter.o: Parameter.h Parameter.cpp
	$(CXX) $(CFLAGS) -c Parameter.h Parameter.cpp

Result.o: Result.h Result.cpp
	$(CXX) $(CFLAGS) -c Result.h Result.cpp	

Model.o: Model.h Model.cpp
	$(CXX) $(CFLAGS) -c Model.h Model.cpp
	
Vector.o: Vector.h Vector.cpp
	$(CXX) $(CFLAGS) -c Vector.h Vector.cpp

ModelAROW.o: ModelAROW.h ModelAROW.cpp
	$(CXX) $(CFLAGS) -c ModelAROW.h ModelAROW.cpp

ModelAROWD.o: ModelAROWD.h ModelAROWD.cpp
	$(CXX) $(CFLAGS) -c ModelAROWD.h ModelAROWD.cpp

ModelAROWC.o: ModelAROWC.h ModelAROWC.cpp
	$(CXX) $(CFLAGS) -c ModelAROWC.h ModelAROWC.cpp

ModelAROWCD.o: ModelAROWCD.h ModelAROWCD.cpp
	$(CXX) $(CFLAGS) -c ModelAROWCD.h ModelAROWCD.cpp

ModelPA.o: ModelPA.h ModelPA.cpp
	$(CXX) $(CFLAGS) -c ModelPA.h ModelPA.cpp

ModelPE.o: ModelPE.h ModelPE.cpp
	$(CXX) $(CFLAGS) -c ModelPE.h ModelPE.cpp

ModelSOP.o: ModelSOP.h ModelSOP.cpp
	$(CXX) $(CFLAGS) -c ModelSOP.h ModelSOP.cpp

ModelSOPD.o: ModelSOPD.h ModelSOPD.cpp
	$(CXX) $(CFLAGS) -c ModelSOPD.h ModelSOPD.cpp

clean:
	rm -rf *o *gch
