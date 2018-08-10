# Contributing

Numbat is an open-source application built using the [MOOSE] framework. It is developed on [GitHub](https://github.com/cpgr/numbat), and is written using C++. We welcome new contributions to the code base, which can be submitted using the workflow outlined below.

This guide is based on the MOOSE [contributing guide](framework_development/contributing.md), where you can find lots of information about the [code standards](framework_development/code_standards.md) and workflow.

## Fork numbat

The first step is to create your own [fork](https://help.github.com/articles/fork-a-repo/) of Numbat where you can commit your set of changes.

- Navigate to [https://github.com/cpgr/numbat](https://github.com/cpgr/numbat)

- Click the "Fork" button in the upper right corner

- Clone your fork to your local machine (replace "username" with your GitHub username).

+Note:+ We recommend that you use SSH URLs instead of HTTPS. Generally you will have fewer problems with
firewalls and authentication this way. It does however require an additional step of setting up keys.
Please follow the instructions provided by Github to setup your [SSH keys](https://help.github.com/articles/connecting-to-github-with-ssh/).

```bash
git clone git@github.com:username/numbat.git
```

## Add the `upstream` Remote:

Add the main Numbat repository as a remote named "upstream":

```bash
cd moose
git remote add upstream git@github.com:cpgr/numbat.git
```

## Make Modifications

Create a branch for your work:

```bash
git checkout -b branch_name upstream/master
```

Make your modifications and commit them to a branch (be sure to reference an issue number in your commit messages).

```bash
git add your_file.h your_file.C
git commit -m "A message about the commit

closes #12345"
```

See [`git add`](http://git-scm.com/docs/git-add) and [`git commit`](http://git-scm.com/docs/git-commit) for more assistance on these commands.

Before contributing your changes you should rebase them on top of the current set of patches in the master branch in the main Numbat repository:

```bash
git fetch upstream
git rebase upstream/master
```

## Push Modifications Back to GitHub

Push your branch back into your fork on GitHub:

```bash
git push origin branch_name
```

## Create a Pull Request

GitHub uses Pull Requests (PRs) to allow you to submit changes stored in your Fork back to the main Numbat repository.  If you are generally interested in how PRs work, see the [official GitHub documentation](https://help.github.com/articles/using-pull-requests).
