CXX = g++					
CXXFLAGS = -g -Wall -MMD -Werror=vla	

OBJECTS = main.o
DEPENDS = ${OBJECTS:.o=.d}			
EXEC = a.out					

.PHONY : clean					

${EXEC} : ${OBJECTS}				
	${CXX} ${CXXFLAGS} $^ -o $@

-include ${DEPENDS}				

clean :						
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
