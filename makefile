all: build-all


##########################
## DEFALT VALS SECTION  ##
##########################
mode = 'debug'
mode_file = /tmp/build.dat


##########################
## MODE SWITCH SECTION  ##
##########################
set_debug: $(mode_file)
	echo -e "\x01" > $(mode_file)

set_release: $(mode_file)
	echo -e "\x02" > $(mode_file)

set_packed: $(mode_file)
	echo -e "\x03" > $(mode_file)

set_compressed: $(mode_file)
	echo -e "\x04" > $(mode_file)

set_tiny: $(mode_file)
	echo -e "\x05" > $(mode_file)

get_mode: $(mode_file)
	mode_code := $(xdd "$mode_file")
	@case $(mode_code) in\
		echo -e "\x01") mode = 'debug'
		echo -e "\x02") mode = 'release'
		echo -e "\x03") mode = 'packed'
		echo -e "\x04") mode = 'compressed'
		echo -e "\x05") mode = 'tiny'
		?) mode = 'debug'

##########################
## SCRIPT PATH SECTION  ##
##########################
build-script-dir = ./py/build
build-all-script = $(build-script-dir)/all.py
update-wp-script = $(build-script-dir)/update-wp.py


##########################
## SCRIPT CALL SECTION  ##
##########################
build-all: $(build-all-script) $(mode)
	python3 $(build-all-script) $(mode)

update-wp: $(update-wp-script) $(mode)
	python3 $(update-wp-script) $(mode)

disk-usage: $(update-wp-script) $(mode)
	python3 $(update-wp-script) $(mode)