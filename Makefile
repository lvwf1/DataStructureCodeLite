.PHONY: clean All

All:
	@echo "----------Building project:[ Assignment10 - Debug ]----------"
	@cd "Assignment10" && "$(MAKE)" -f  "Assignment10.mk"
clean:
	@echo "----------Cleaning project:[ Assignment10 - Debug ]----------"
	@cd "Assignment10" && "$(MAKE)" -f  "Assignment10.mk" clean
