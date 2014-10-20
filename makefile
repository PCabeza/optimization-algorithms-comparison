# Makefile to build the a tester to test insert,search and delete for BST
# file: makefile
# author: Pablo Cabeza García

define MSG
How should be used: 
	make <COMMAND> 

<COMMAND>
	help	  :: show this message
	build 	  :: compile project in realese mode
	rebuild   :: clean and compile project again
	debug 	  :: compile project for debugging
	redebug   :: clean and compile for debugging
	clean 	  :: clean all generated files except libraries

endef
export MSG


CXX=g++
MKDIR=mkdir -p
CD=cd
MAKE=make
RM=rm -rf
SRCEXT=cpp

INCLUDE-DIRS=$(SRC) include-armadillo
INCLUDE=$(addprefix -I,$(INCLUDE-DIRS))

# add to CXXFLAGS if error -Wno-error=unused-result
LDFLAGS=
CXXFLAGS=-c -std=c++11 -O2 -Wall -Werror -Wno-error=unused-result -pedantic $(INCLUDE)

SRC=src
OBJ=obj
BIN=bin
DEP=dep
SLIBS= -llapack -lblas#-static -L$(SRC)/timer/lib -ltimer -lrt 

EXEC=pcg
SOURCES=$(wildcard $(SRC)/*.$(SRCEXT))
OBJECTS=$(patsubst %.$(SRCEXT),%.o,$(patsubst $(SRC)/%,$(OBJ)/%,$(SOURCES)))
DEPENDENCIES=$(patsubst %.$(SRCEXT),%.d,$(patsubst $(SRC)/%,$(DEP)/%,$(SOURCES)))


.PHONY: help build rebuild clean debug fullclean
.PRECIOUS: $(DEP)/%.d

build:
help:
	@echo "$$MSG"

build: $(BIN)/$(EXEC)


rebuild: clean build


debug: CXXFLAGS+= -g -rdynamic -O0
debug: clean build


redebug: clean debug


$(BIN)/$(EXEC): $(OBJECTS) $(BIN)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@ $(SLIBS)

$(BIN) $(OBJ) $(DEP):
	@$(MKDIR) $@

$(OBJ)/%.o: $(SRC)/%.$(SRCEXT) $(DEP)/%.d $(OBJ)
	$(CXX) $(CXXFLAGS) $< -o $@

$(DEP)/%.d: $(SRC)/%.$(SRCEXT) $(DEP)
	$(CXX) $(CXXFLAGS) -MM -MF$@ -MT$@ -MT$(OBJ)/$*.o $<

-include $(DEPENDENCIES)



clean:
	@$(RM) $(OBJ) $(BIN) $(DEP)
