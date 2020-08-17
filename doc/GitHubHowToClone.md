# GitHubWiP
author: Chiara Bissolotti

This is a test file to check if the following procedure was successful. Tha aim of the procedure is to obtain a private repository (to become NangaParbatPrivate) that can communicate with the public NangaParbat to ``push`` and ``pull`` changes.

If this file arrives to the original NangaParbat repository through a pull request, then the procedure worked, at least for the ``push`` case.
- If this file arrives to the original NangaParbat repository through a pull request, then the procedure worked, at least for the ``push`` case.
The ``push`` procedure was successfully tested by doing what is reported in the previous line.
- The ``pull`` procedure described in the following was also tested and it works.
NangaParbatPrivate had fallen behind NangaParbat, as we worked on the public repository, and I brought NangaParbatPrivate up to speed with NangaParbat using the four lines of code under 'To pull new chages form the public repo' in the next section. There were few conflicts, highlighted by git during the pulling procedure, and I handled them as it is normally done in github repositories (``git checkout`` of the selected files).

## Procedure followed
From:  https://stackoverflow.com/questions/10065526/github-how-to-make-a-fork-of-public-repository-private or
https://medium.com/@bilalbayasut/github-how-to-make-a-fork-of-public-repository-private-6ee8cacaf9d3

Create a new repo (let’s call it private-repo) via the Github UI. Then:
```
git clone --bare https://github.com/exampleuser/public-repo.git
cd public-repo.git
git push --mirror https://github.com/yourname/private-repo.git
cd ..
rm -rf public-repo.git
```
Clone the private repo so you can work on it:

```
git clone https://github.com/yourname/private-repo.git
cd private-repo
make some changes
git commit
git push origin master
```
To pull new changes from the public repo:
```
cd private-repo
git remote add public https://github.com/exampleuser/public-repo.git
git pull public master # Creates a merge commit
git push origin master
```
Your private repo now has the latest code from the public repo plus your changes.

Finally, to create a pull request private repo -> public repo:

The only way to create a pull request is to have push access to the public repo. This is because you need to push to a branch there.
```
git clone https://github.com/exampleuser/public-repo.git
cd public-repo
git remote add private_repo_yourname https://github.com/yourname/private-repo.git
git checkout -b pull_request_yourname
git pull private_repo_yourname master
git push origin pull_request_yourname
```
Now simply create a pull request via the Github UI for public-repo, as described here.

Once project owners review your pull request, they can merge it.



# Appendix: useful info on GitHub
[https://stackoverflow.com/questions/3959924/whats-the-difference-between-git-clone-mirror-and-git-clone-bare]
Suppose origin has a few branches (master (HEAD), next, pu, and maint), some tags (v1, v2, v3), some remote branches (devA/master, devB/master), and some other refs (refs/foo/bar, refs/foo/baz, which might be notes, stashes, other devs' namespaces, who knows).

__git clone origin-url (non-bare)__: You will get all of the tags copied, a local branch master (HEAD) tracking a remote branch origin/master, and remote branches origin/next, origin/pu, and origin/maint. The tracking branches are set up so that if you do something like git fetch origin, they'll be fetched as you expect. Any remote branches (in the cloned remote) and other refs are completely ignored.

Copies contents of the repository.

__git clone --bare origin-url__: You will get all of the tags copied, local branches master (HEAD), next, pu, and maint, no remote tracking branches. That is, all branches are copied as is, and it's set up completely independent, with no expectation of fetching again. Any remote branches (in the cloned remote) and other refs are completely ignored.

Copies tags of the repository and the info about it, but no folders and stuff.

__git clone --mirror origin-url__: Every last one of those refs will be copied as-is. You'll get all the tags, local branches master (HEAD), next, pu, and maint, remote branches devA/master and devB/master, other refs refs/foo/bar and refs/foo/baz. Everything is exactly as it was in the cloned remote. Remote tracking is set up so that if you run git remote update all refs will be overwritten from origin, as if you'd just deleted the mirror and recloned it. As the docs originally said, it's a mirror. It's supposed to be a functionally identical copy, interchangeable with the original.

### git remote add
[https://stackoverflow.com/questions/5617211/what-is-git-remote-add-and-git-push-origin-master]
```
git remote add ...
```
As you probably know, git is a distributed version control system. Most operations are done locally. To communicate with the outside world, git uses what are called remotes. These are repositories other than the one on your local disk which you can push your changes into (so that other people can see them) or pull from (so that you can get others changes). The command git remote add origin git@github.com:peter/first_app.gitcreates a new remote called origin located at git@github.com:peter/first_app.git. Once you do this, in your push commands, you can push to origin instead of typing out the whole URL.

### git pull origin master
```
git pull PalmTree-FruIT_bissolotti master
```
This is a command that says "pull the commits from the remote named PalmTree-FruIT_bissolotti, from the branch named master" (I think).
### git push origin master
[https://stackoverflow.com/questions/5617211/what-is-git-remote-add-and-git-push-origin-master]
```
git push origin master
```

This is a command that says "push the commits in the local branch named master to the remote named origin". Once this is executed, all the stuff that you last synchronised with origin will be sent to the remote repository and other people will be able to see them there.

### git checkout -b
```
git checkout -b pull_request_yourname
```
Command line that has to be executed from inside the public repository into which you want to merge your new objects or changes from the private repository.
So, in this case:
```
cd NangaParbat
git checkout -b pull_request_yourname
```
this creates a new branch in NangaParbat, called ``pull_request_yourname``.

## About branches
We can view all existing branches by typing
```
git branch -a
```
into terminal, which tells git that we want to see ALL the branches in this project, even ones that are not in our local workspace.

We can also use the git checkout command to toggle back and forth between our two branches. Type
```
git checkout branchName
```
to switch to that branch. So, ``git checkout master`` takes you to ``master`` while ``git checkout hello_octo`` takes you back to ``hello_octo`` branch.

## About forks
[https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/about-forks]

A fork is a copy of a repository that you manage. Forks let you make changes to a project without affecting the original repository. You can fetch updates from or submit changes to the original repository with pull requests.

Any user or organization on GitHub can fork a repository. Forking a repository is similar to copying another repository, with two major differences:

1. You can use a pull request to suggest changes from your fork to the original repository, also known as the upstream repository.
2. You can bring changes from the upstream repository to your local fork by synchronizing your fork with the upstream repository.
