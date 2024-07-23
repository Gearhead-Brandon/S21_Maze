EXECUTE = Maze
CMAKE_BUILD = build
DIR_INSTALL = out

all: install

install: clean uninstall
	@mkdir -p ./out
	cd $(CMAKE_BUILD) && cmake .. && make && mv $(EXECUTE) ../${DIR_INSTALL}/
	@make run

run:
	@cd $(DIR_INSTALL) && ./${EXECUTE}

uninstall:
	@rm -rf $(DIR_INSTALL)

clean:
	@rm -rf $(CMAKE_BUILD)/*

rebuild: clean install