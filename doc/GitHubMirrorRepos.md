# GitHub - Mirror repository, how to pull and push to/from parent public repo
author: Chiara Bissolotti

## Table of Contents
- [GitHub - Mirror repository, how to pull and push to/from parent public repo](#github---mirror-repository-how-to-pull-and-push-tofrom-parent-public-repo)
  - [Table of Contents](#table-of-contents)
  - [How to set up a private copy (mirror) of a public repository](#how-to-set-up-a-private-copy-mirror-of-a-public-repository)
  - [To pull new changes from the public repo](#to-pull-new-changes-from-the-public-repo)
  - [To create a pull request private repo -\> public repo](#to-create-a-pull-request-private-repo---public-repo)
    - [NangaParbat-Beta to NangaParbat](#nangaparbat-beta-to-nangaparbat)
    - [To solve conflicts](#to-solve-conflicts)
  - [To overwrite the branch master of the public repo with the branch master of the private repo.](#to-overwrite-the-branch-master-of-the-public-repo-with-the-branch-master-of-the-private-repo)
  - [Manage Repositories](#manage-repositories)
    - [add a remote](#add-a-remote)
    - [pull from the remotes](#pull-from-the-remotes)
    - [push to the remote](#push-to-the-remote)
- [Appendix: useful info on GitHub](#appendix-useful-info-on-github)
    - [git checkout -b](#git-checkout--b)
  - [About branches](#about-branches)
  - [About forks](#about-forks)
  - [Reset](#reset)
  
## How to set up a private copy (mirror) of a public repository

The aim of the procedure described here is to obtain a private repository (to become NangaParbatPrivate) that can ``push`` and ``pull`` changes to and from the public NangaParbat.

From:  https://stackoverflow.com/questions/10065526/github-how-to-make-a-fork-of-public-repository-private or
https://medium.com/@bilalbayasut/github-how-to-make-a-fork-of-public-repository-private-6ee8cacaf9d3

Create a new repo (let’s call it private-repo) via the Github UI.
Then:
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

## To pull new changes from the public repo
```
cd private-repo
git remote add public https://github.com/exampleuser/public-repo.git
git pull public master # Creates a merge commit
git push origin master
```
Your private repo now has the latest code from the public repo plus your changes.

## To create a pull request private repo -> public repo

The only way to create a pull request is to have push access to the public repo. This is because you need to push to a branch there.
To create a pull request, you need to create a new branch in your private repo, push that branch to your public repo, and then create the pull request. 
These are the steps to follow in order to get to the point where it's possibile to create a pull request from the private repo to the public: 
```
git clone https://github.com/exampleuser/public-repo.git
cd public-repo
git remote add private_repo_yourname https://github.com/yourname/private-repo.git
git checkout -b pull_request_yourname
git pull private_repo_yourname master

```
``git checkout -b pull_request_yourname`` creates a new branch in the public repository, called ``pull_request_yourname``. This is the branch that will be used to create the pull request.
``git pull private_repo_yourname master`` pulls the changes from the private repository into the public one. This is necessary because the pull request will be created from the public repository, so it has to contain the changes from the private one.
If no warning or git error is issued after ``git pull private_repo_yourname master``, one can proceed with the pull request. 
```
git push origin pull_request_yourname
```
Now simply create a pull request via the Github UI for public-repo.
Otherwise, one has to solve the conflicts and then proceed with the pull request. __If the automatic merge does not complete successfully__, and you have to do it manually, try using:
``git mergetool`` or `VSCode` (preferred) (https://code.visualstudio.com/docs/editor/versioncontrol#_merge-conflicts).
Look also at https://stackoverflow.com/questions/161813/how-to-resolve-merge-conflicts-in-git.

### NangaParbat-Beta to NangaParbat
```
cd NangaParbat
git remote add NangaParbat-Beta git@github.com:MapCollaboration/NangaParbat-Beta.git
git checkout -b pull_beta_to_nangaparbat_public
git pull NangaParbat-Beta master
```
At this point, if there is no warning or error, all good. Otherwhise, the output might be similar to:
```terminal
From github.com:MapCollaboration/NangaParbat-Beta
 * branch              master     -> FETCH_HEAD
 * [new branch]        master     -> check_pull_request/master
hint: You have divergent branches and need to specify how to reconcile them.
hint: You can do so by running one of the following commands sometime before
hint: your next pull:
hint: 
hint:   git config pull.rebase false  # merge
hint:   git config pull.rebase true   # rebase
hint:   git config pull.ff only       # fast-forward only
hint: 
hint: You can replace "git config" with "git config --global" to set a default
hint: preference for all repositories. You can also pass --rebase, --no-rebase,
hint: or --ff-only on the command line to override the configured default per
hint: invocation.
fatal: Need to specify how to reconcile divergent branches.
```
If this is the case, proceed with the following. The following assumes that we want to keep the changes from the private repository, and discard the changes from the public one. The master branch of the public will be a copy of the master branch of the private repo.

Here's how you can proceed after you've encountered the divergence message:

1. **Ensure you're on the correct branch where you want to merge the changes (pull_beta_to_nangaparbat_public in your case)**.
   ```bash
   git checkout pull_beta_to_nangaparbat_public
    ```
2. **Use the ``git fetch`` command to update your local copy of the remote branches without merging**:
   ```bash
   git fetch NangaParbat-Beta master
   ```
3. **Reset your local branch to exactly match the state of the private repository's master branch, effectively prioritizing its content**. 
   This step can potentially discard local changes on your current branch, so ensure that's your intended outcome.
   ```bash
   git reset --hard NangaParbat-Beta/master
   ```
   This command resets the ``pull_beta_to_nangaparbat_public`` branch to exactly match the state of NangaParbat-Beta's ``master`` branch, effectively discarding any divergent changes that were present in the ``pull_beta_to_nangaparbat_public branch``.

4. **Finally, if you wish to update the public repository (NangaParbat) with the changes, you would push this branch and create a pull request against the master branch of the NangaParbat repository**.
    Since you've reset your branch to match the private repo, this will effectively apply all the changes from NangaParbat-Beta onto NangaParbat.
   ```bash
   git push origin pull_beta_to_nangaparbat_public --force
   ```
Remember, using ``--hard`` and ``--force`` are powerful commands that rewrite history and can result in lost work if not used carefully. Always make sure you have backups of your repositories and are certain of the changes you want to apply.

Now, we can create the ``pull request`` on GitHUb using the web interface. The new branch, ``pull_beta_to_nangaparbat_public``, should show up among the branches of the ``NangaParbat`` repo. Use this branch to create the pull request.
Chances are that, once created the pull request, there are too many conflicts and Git HUb can't perform an authomatic merge. In this case, the conflicts have to be solved manually. See the next section.

### To solve conflicts
If the automatic merge does not complete successfully, and you have to do it manually, try using `VSCode`(https://code.visualstudio.com/docs/editor/versioncontrol#_merge-conflicts). Otherwise, one can proceed with the command line approach (see following)

If you want to keep only the private repository's history and files and replace the master branch of the public repository (NangaParbat) with the state of the branch you've created from the private repository (pull_beta_to_nangaparbat_public), you will need to perform a force push. However, since you have opened a pull request, it's usually best to handle this via the pull request by resolving the conflicts in favor of the private repository. Since there are many files and the GitHub web interface suggests using the command line, here are the steps you can follow:

1. **Make sure you have the latest version of both the public repository's master branch and your branch pull_beta_to_nangaparbat_public**:

   ```bash
   git fetch origin master
   git checkout pull_beta_to_nangaparbat_public
   git rebase origin/master
   ```
2. **During the rebase, you'll encounter conflicts. You can resolve all conflicts in favor of the private repository's version by using the following command**:

   ```bash
   git checkout --theirs path/to/conflicting/file
   ```
   You'll have to do this for each file that has a conflict. However, if there are many files and you want to automate this process to choose the private repo's changes for all conflicts, you can use the following command:

   ```bash
   git checkout --theirs .
   git add .
   ```
   This will check out the private repo's version for all files and then stage them for commit.

3. **After resolving all conflicts, continue the rebase**:

   ```bash
   git rebase --continue
   ```
__IMPORTANT:__ You may have to resolve conflicts and continue the rebase multiple times if there are many conflicting files.

1. **Once the rebase is completed without any more conflicts, you can force push your branch to update the pull request**:

   ```bash
   git push origin pull_beta_to_nangaparbat_public --force
   ```
Go to the pull request on GitHub. The pull request should now be able to be merged without conflicts because it will reflect the state of your ``pull_beta_to_nangaparbat_public`` branch, which has been rebased onto the public repo's master branch.

You can now merge the pull request on GitHub, and it should replace the ``master`` branch of NangaParbat with the changes from ``pull_beta_to_nangaparbat_public``, effectively making it the same as your private repo's master branch.

Remember, these operations can rewrite the history of your branches and could potentially lead to lost work for others if they have based their work on the previous state of the master branch. Make sure all collaborators are aware of this operation, and it's agreed upon. This method will preserve the private repo's history in the pull request, and you'll have a record of this operation within the pull request itself.



## To overwrite the branch master of the public repo with the branch master of the private repo. 
To completely overwrite the `master` branch of your public repo (`NangaParbat`) with the `master` branch from your private repo (`NangaParbat-Beta`), follow these steps:

1. **Fetch the latest changes from your private repo**:
   ```bash
   git fetch NangaParbat-Beta master
   ```
2. **Check out the master branch of your public repo**:
   ```bash
   git checkout master
   ```
3. **Reset your public repo's master branch to match the private repo's master**:
   ```bash
   git reset --hard NangaParbat-Beta/master
   ```
   This command will reset the master branch of your local copy to match the master branch of the NangaParbat-Beta repository.

4. **Force push to overwrite the master branch on your public repo**:
   ```bash
   git push origin master --force
   ```
   This operation is destructive and cannot be undone. It will overwrite the history on the master branch of the NangaParbat repository with the history from the master branch of the NangaParbat-Beta repository. Ensure that this is what you want to do before you execute the --force push, as it will erase the current state of the master branch on the remote and replace it with the state of your private repo's master branch.

__Warning__: Force-pushing will overwrite history and can cause problems for anyone else who has cloned or forked the repository. They will have to handle the rewritten history in their own clones/forks, which can be a complex process. Always communicate with your team before performing such actions, especially on a public repository.



## Manage Repositories
To see what the differences between two local git repositories are:
```
cd first_repo
git --work-tree=path_to_second_repo diff
```
from https://stackoverflow.com/questions/30771920/how-to-diff-two-local-repositories .

---
As you probably know, Git is a distributed version control system. Most operations are done locally. To communicate with the outside world, git uses what are called remotes. These are repositories other than the one on your local disk which you can push your changes into (so that other people can see them) or pull from (so that you can get others changes).

See https://git-scm.com/book/en/v2/Git-Basics-Working-with-Remotes

### add a remote
from https://stackoverflow.com/questions/5617211/what-is-git-remote-add-and-git-push-origin-master
The command
```
git remote add origin https://github.com/ChiaBis/NangaParbatPrivate.git
```
creates a new remote called ``origin`` located at ``https://github.com/ChiaBis/NangaParbatPrivate.git``. Once you do this, in your push commands, you can push to ``origin`` instead of typing out the whole URL.
``git pull origin master``
The name ``origin`` is just the name of the remote, any name can be chosen.

To see __what are the remotes__ of a repository:
```
git remote -v
```

### pull from the remotes
from https://stackoverflow.com/questions/5617211/what-is-git-remote-add-and-git-push-origin-master
```
git pull PalmTree-FruIT master
```
This is a command that says "pull the commits from the remote named PalmTree-FruIT, from the branch named master" (I think).

### push to the remote
[https://stackoverflow.com/questions/5617211/what-is-git-remote-add-and-git-push-origin-master]
```
git push origin master
```
This is a command that says "push the commits in the local branch named master to the remote named origin". Once this is executed, all the stuff that you last synchronised with origin will be sent to the remote repository and other people will be able to see them there.

# Appendix: useful info on GitHub
[https://stackoverflow.com/questions/3959924/whats-the-difference-between-git-clone-mirror-and-git-clone-bare]
Suppose origin has a few branches (master (HEAD), next, pu, and maint), some tags (v1, v2, v3), some remote branches (devA/master, devB/master), and some other refs (refs/foo/bar, refs/foo/baz, which might be notes, stashes, other devs' namespaces, who knows).

__git clone origin-url (non-bare)__: You will get all of the tags copied, a local branch master (HEAD) tracking a remote branch origin/master, and remote branches origin/next, origin/pu, and origin/maint. The tracking branches are set up so that if you do something like git fetch origin, they'll be fetched as you expect. Any remote branches (in the cloned remote) and other refs are completely ignored.

Copies contents of the repository.

__git clone --bare origin-url__: You will get all of the tags copied, local branches master (HEAD), next, pu, and maint, no remote tracking branches. That is, all branches are copied as is, and it's set up completely independent, with no expectation of fetching again. Any remote branches (in the cloned remote) and other refs are completely ignored.

Copies tags of the repository and the info about it, but no folders and stuff.

__git clone --mirror origin-url__: Every last one of those refs will be copied as-is. You'll get all the tags, local branches master (HEAD), next, pu, and maint, remote branches devA/master and devB/master, other refs refs/foo/bar and refs/foo/baz. Everything is exactly as it was in the cloned remote. Remote tracking is set up so that if you run git remote update all refs will be overwritten from origin, as if you'd just deleted the mirror and recloned it. As the docs originally said, it's a mirror. It's supposed to be a functionally identical copy, interchangeable with the original.

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

## Reset
To reset to a particular point in time:
```
git reset --hard master@{"10 minutes ago"}
```


[def]: #nang