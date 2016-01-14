Getting started
=====

### 1) Install MOOSE ###

Numbat is a MOOSE application. In order to run Numbat, you must first install MOOSE. See [http://www.mooseframework.com/](http://www.mooseframework.com) for installation instructions.

### 2) Fork Numbat ###

Once MOOSE has been installed and the tests run to verify that everything works as expected, the next step is to fork the Numbat repository to your local GitHub account.

Navigate to the [Numbat repository](https://github.com/cpgr/numbat.git) and press the *Fork* button in the top right corner of the page.

Now you should have a copy of Numbat in your personal account.

### 3) Clone Numbat ###

The next step is to clone your Numbat repository to your local machine.

In the following, it assumed that MOOSE was installed to the directory *~/projects*. If MOOSE was installed to a different directory, the following instructions must be modified accordingly.

To clone Numbat, use the following commands (where USERNAME is your GitHub username)

    cd ~/projects
    git clone https://github.com/USERNAME/numbat.git
    cd numbat
    git checkout master

### 4) Compile Numbat ###

Next, compile Numbat using

    make -jn

where *n* is the number of processing cores on the computer. If everything has gone well, Numbat should compile without error, resulting in a binary named *numbat-opt*.

### 5) Test Numbat ###

Finally, to test that the installation worked, the small test suite can be run using

    ./run_tests -jn

where *n* is the number of processing cores on the computer.
