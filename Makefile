.PHONY: clean All

All:
	@echo "----------Building project:[ GUI - Debug ]----------"
	@cd "GUI" && "$(MAKE)" -f  "GUI.mk" && "$(MAKE)" -f  "GUI.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ GUI - Debug ]----------"
	@cd "GUI" && "$(MAKE)" -f  "GUI.mk" clean
