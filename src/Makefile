EXECUTE = Maze
APP_BUILD = build
DIR_INSTALL = out

DIR_TEST = unit_tests
TEST_BUILD = unit_tests/build
TEST_EXECUTE = Tests

all: install

install: clean uninstall
	@mkdir -p ./out
	@mkdir -p ./build
	cd $(APP_BUILD) && cmake .. && make && mv $(EXECUTE) ../${DIR_INSTALL}/
	@make rm_build
	@make run

run:
	@cd $(DIR_INSTALL) && ./${EXECUTE}

uninstall:
	@rm -rf $(DIR_INSTALL)

tests: clean
	@mkdir -p ./unit_tests/build
	cd $(TEST_BUILD) && cmake .. && make && mv $(TEST_EXECUTE) ..
	@cd $(DIR_TEST) && ./${TEST_EXECUTE}

clean: rm_build
	@rm -rf ./$(DIR_TEST)/$(TEST_EXECUTE)

rm_build:
	@rm -rf $(APP_BUILD)
	@rm -rf $(TEST_BUILD)

rebuild: clean install