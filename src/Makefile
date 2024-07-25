EXECUTE = Maze
CMAKE_BUILD = build
DIR_INSTALL = out

all: install

install: clean uninstall
	@mkdir -p ./out
	@mkdir -p ./build
	cd $(CMAKE_BUILD) && cmake .. && make && mv $(EXECUTE) ../${DIR_INSTALL}/
	@make rm_build
	@make run

run:
	@cd $(DIR_INSTALL) && ./${EXECUTE}

uninstall:
	@rm -rf $(DIR_INSTALL)

rm_build:
	@rm -rf $(CMAKE_BUILD)

clean: rm_build

rebuild: clean install