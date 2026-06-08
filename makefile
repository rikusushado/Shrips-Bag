all: prepare-build-env shrips cli-tools

shrips: disk-usage

disk-usage:
	RUSTFLAGS="-Z unstable-options -Zfmt-debug=none -Zlocation-detail=none -Ctarget-feature=-crt-static" \
	cargo +nightly build --target x86_64-unknown-linux-musl \
	-Z build-std=std,panic_abort \
	-Z build-std-features="optimize_for_size" \
	--release --manifest-path ./shrips/disk_usage/Cargo.toml
	rm -rf ./build
	mkdir -p ./build/bin
	mkdir -p ./build/config/disk-usage
	mkdir -p ./build/lang/disk-usage
	yes | cp -rf ./shrips/disk_usage/resources/config/* ./build/config/disk-usage
	yes | cp -rf ./shrips/disk_usage/resources/lang/* ./build/lang/disk-usage
	yes | cp -rf ./shrips/disk_usage/target/x86_64-unknown-linux-musl/release/disk_usage ./build/bin/disk-usage


prepare-build-env:
	mkdir -p ./build/config
	mkdir -p ./build/lang


cli-tools:
	yes | cp -rf ./cli_tools/* ./build/bin


install:
	sudo mkdir -p /opt/shrips-bag
	sudo cp -r ./build/* /opt/shrips-bag
	sudo chmod +x -R /opt/shrips-bag/bin
	sudo ln -s /opt/shrips-bag/bin/wrapper.sh /usr/local/bin/shrips-bag

reinstall:
	sudo mkdir -p /opt/shrips-bag
	sudo chmod +x -R /opt/shrips-bag/bin
	yes | sudo cp -rf ./build/* /opt/shrips-bag

uninstall:
	sudo rm /usr/local/bin/shrips-bag
	sudo rm -r /opt/shrips-bag
