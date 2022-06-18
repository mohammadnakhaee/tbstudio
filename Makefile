.PHONY: clean All

All:
	@echo "----------Building project:[ GUI - Release ]----------"
	@cd "GUI" && "$(MAKE)" -f  "GUI.mk" && "$(MAKE)" -f  "GUI.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ GUI - Release ]----------"
	@cd "GUI" && "$(MAKE)" -f  "GUI.mk" clean
