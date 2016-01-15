# Installation instructions

To install Numbat, follow these simple instructions.

### Install MOOSE
Numbat is based on the MOOSE framework, so the first step is to install
MOOSE. For detailed installation instructions depending on your hardware, see
[www.mooseframework.com](http://www.mooseframework.com).

### Fork Numbat
Once MOOSE has been installed and the tests run to verify that everything works as expected, the
next step is to fork the Numbat repository to your local GitHub account.

Navigate to the [Numbat repository](https://github.com/cpgr/numbat) and press the *Fork* button in the top right corner
of the page.

Now you should have a copy of Numbat in your personal account.

### Clone Numbat

The next step is to clone your Numbat repository to your local machine.

In the following, it is assumed that MOOSE was installed to the directory *~/projects.* If MOOSE was
installed to a different directory, the following instructions must be modified accordingly.

To clone Numbat, use the following commands (where *USERNAME* is your GitHub account name)

    cd ~/projects
    git clone https://github.com/USERNAME/numbat.git
    cd numbat
    git checkout master

### Compile Numbat

Next, compile Numbat using

    make -jn

where *n* is the number of processing cores on the computer. If everything has gone well, Numbat should
compile without error, producing a binary named *numbat-opt*.

### Test Numbat

Finally, to test that the installation worked, the test suite can be run using

    ./run_tests -jn

where *n* is the number of processing cores on the computer.
