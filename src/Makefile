EXECUTE = Maze
APP_BUILD = build
DIR_INSTALL = out

DIR_TEST = unit_tests
TEST_BUILD = unit_tests/build
TEST_EXECUTE = Tests

DIR_REPORT = report
HTML_REPORT = REPORT.html
EXCLUDE_FILES = "unit_tests/*" "App/Common/Structures/*" "App/Model/S21Matrix"\
                "App/Model/Maze/PathFinder/PathFinder.h"\
				"App/Model/Maze/PathFinder/Components/QActions.h"\
				"App/Model/Maze/FileReader/*"		
EXCLUDE_REPORT = $(foreach file, $(EXCLUDE_FILES), --exclude $(file)) 

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

gcov_report: tests
	@mkdir -p $(DIR_REPORT)
	@find ./$(TEST_BUILD)/CMakeFiles \( -name "*.gcno" -o -name "*.gcda"  \) -exec mv {} $(DIR_REPORT)/ \;
	~/.local/bin/gcovr $(DIR_REPORT)/ $(EXCLUDE_REPORT) --html --html-details -o $(HTML_REPORT)
	@make move_report

move_report:
	@mv *.html *.css $(DIR_REPORT)

peer: gcov_report
	@open $(DIR_REPORT)/$(HTML_REPORT)

clean: rm_build
	@rm -rf ./$(DIR_TEST)/$(TEST_EXECUTE)
	@rm -rf ./$(DIR_TEST)/generatedMazes
	@rm -rf ./$(DIR_REPORT)

rm_build:
	@rm -rf $(APP_BUILD)
	@rm -rf $(TEST_BUILD)

rebuild: clean install