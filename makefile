all: build-all


##########################
## DEFALT VALS SECTION  ##
##########################
mode = 'debug'
mode_file = /tmp/build.dat

##########################
## SCRIPT PATH SECTION  ##
##########################
build-script-dir = ./py/build
build-all-script = $(build-script-dir)/all.py
update-wp-script = $(build-script-dir)/update-wp.py


##########################
## SCRIPT CALL SECTION  ##
##########################
build-all: $(build-all-script)
	python3 $(build-all-script)

update-wp: $(update-wp-script)
	python3 $(update-wp-script)

disk-usage: $(update-wp-script)
	python3 $(update-wp-script)
