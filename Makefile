CXX = g++					
CXXFLAGS = -g -Wall -MMD -Werror=vla	

OBJECTS = resourceEnum.o tile.o color.o component.o main.o player.o # CHANGE HERE
DEPENDS = ${OBJECTS:.o=.d}			
EXEC = a.out					# executable name

.PHONY : clean					

${EXEC} : ${OBJECTS}				
	${CXX} ${CXXFLAGS} $^ -o $@

-include ${DEPENDS}				

clean :						
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
