###
### Makefile for Gerp Project
###
### Author:  YOUR NAME HERE

## 
## Build up your Makefile in a similar manner as for Zap. Feel free 
## to use that Makefile to guide you! Note, you do NOT need rules for
## FSTree.o and DirNode.o as those (pre-compiled) object files are 
## provided to you.
## 
## At the end, you can delete this comment!
## 

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

##
## Here is a special rule that removes all .o files besides the provided ones 
## (DirNode.o and FSTree.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##

gerp: main.o wordTable.o gerp.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) $^ -o gerp

unit_test: unit_test_driver.o DirNode.o FSTree.o processing.o
	${CXX} ${CXXFLAGS} $^

wordTable.o: wordTable.cpp wordTable.h
	${CXX} ${CXXFLAGS} -c wordTable.cpp

gerp.o: gerp.cpp gerp.h wordTable.h FSTree.h DirNode.h
	${CXX} ${CXXFLAGS} -c gerp.cpp

processing.o: processing.cpp processing.h FSTree.h DirNode.h
	${CXX} ${CXXFLAGS} -c processing.cpp

clean:
	@find . -type f \( \
		-name '*.o' ! -name 'FSTree.o' ! -name 'DirNode.o' \
		\) -exec rm -f {} \;
	@rm -f *~ a.out

