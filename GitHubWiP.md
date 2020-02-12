# GitHubWiP

This is a test file to check if the following procedure was successful. Tha aim of the procedure is to obtain a private repository (now temporarily called PalmTree-FruIT but to become NangaParbatWiP maybe in the future) that can communicate with the public NangaParbat to ``push`` and ``pull`` changes.

If this file arrives to the original NangaParbat repository through a pull request, then the procedure worked, at least for the ``push`` case.

## Procedure followed
From:  https://stackoverflow.com/questions/10065526/github-how-to-make-a-fork-of-public-repository-private

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
To pull new hotness from the public repo:
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
