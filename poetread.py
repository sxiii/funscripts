#!/usr/bin/python
import requests, bs4, subprocess, os, sys

def get_poet():
    response = requests.get(str(sys.argv[1]))
    soup = bs4.BeautifulSoup(response.text)
    for a1 in soup.select('p'):
        print a1.text.encode('utf-8')
get_poet()
