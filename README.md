# Shrips Bag
A bag full of tasty shrisps tools for easier automated system management!

## What is it?
Shrips Bag is a server management toolbox that aims for an easy and automated aproach. This means that the system admins should not be doing manual procedures for executing the monitoring and maintainment, if this toolbox is installed and setup properly.

## Why should I install this?
As we previously said, the systems with these tools installed are faster and easier to manage, resulting in more time for the admins to attend incidents on the same system or to develop future projects.

Also, this toolbox provides a human-readable way of reporting warnings and errors to a Zulip chat, to avoid mistakes related to a lack of communication.

This is an opensource project where you can read the code for better understanding of what the community and you are installing.

Finally, you can purpose what should we add, how do we implement it as a community. We will dedicate a file to give credits to all contributors and what did they implemented.

## SOURCE INSTALATION GUIDE
### Dependencies
#### Only needed for build
- Cargo
- Build Essential
- Rustup
- Rust Nightly

#### Runtime dependencies
- Curl

### Download
- You can download an specific source code from the releases or execute the follwing command for cloning the repository:
```
git clone https://github.com/rikusushado/Shrips-Bag.git
```

- **If You have downloaded the source code from a release**, you can execute the following command in the directory where the download is located:
```
mkdir Shrips-Bag && tar -xvzf Shrips-Bag-*.tar.gz -C Shrips-Bag
```

### Build and Install
Once the dependencies are met, and the source code is downloaded and extracted, you can execute the following commands for finishing the installation process:
```
cd Shrips-Bag
make all
make install
```

### Reinstalling and uninstalling
If you did a mistake in the installation process, you want to update, or simply you didn't like the toolbox. We provide the commands to reinstall and uninstall the toolbox easily, as we show below:

- Reinstall
```
make reinstall
```

- Uninstall
```
make uninstall
```

**(Remember that you must be inside the downloaded source code containing directory to execute those commands)**

## Miscelaneous
Thanks to [Lliure Tic](https://lliuretic.cat) for the idea and support to the project! 😁
