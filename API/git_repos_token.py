import json
import requests
from pprint import pprint
from github import Github

#Github Token, better be placed in Ansible Vault
api_token = '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'

headers = {'Content-Type': 'application/json',
           'Authorization': 'Bearer {0}'.format(api_token)}
username = "falcon169"
repo=username+'/jsm'

def get_account_info():
    url_base = f"https://api.github.com/users/{username}"
    response = requests.get(url_base, headers=headers)

    if response.status_code == 200:
        return json.loads(response.content.decode('utf-8'))
    else:
        return None

def get_from_token(token, repo):
    g = Github(token)
    repo = g.get_repo('falcon169/jsm')
    print("Name of repository is ", repo.name)

def get_repos(username):
    g = Github()
    user = g.get_user(username)
    for repo in user.get_repos():
        pprint("Repo name is {} " .format(repo))

#Get commit ID's
def get_commits(username, reponame):
    g = Github()
    user = g.get_user(username)
    print("User is {}".format(user))
    commits = g.search_commits(reponame)
    print(commits.get_page(1))
    print(commits.total_count)

account_info = get_account_info()
if account_info is not None:
    pprint(account_info)
else:
    pprint('[!] Request Failed')

get_from_token(api_token, repo)
get_repos(username)
#get_commits(username, 'falcon/jsm')
