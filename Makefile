CXX = g++					
CXXFLAGS = -g -Wall -MMD -Werror=vla	

OBJECTS = resourceEnum.o colorEnum.o residenceEnum.o tile.o component.o player.o controller.o dice.o main.o# CHANGE HERE
DEPENDS = ${OBJECTS:.o=.d}			
EXEC = a.out					# executable name

.PHONY : clean					

${EXEC} : ${OBJECTS}				
	${CXX} ${CXXFLAGS} $^ -o $@

-include ${DEPENDS}				

clean :						
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
