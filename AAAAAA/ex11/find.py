import requests
import json

which_poke = input("Name of Pokemon: ")
res = requests.get('https://pokeapi.co/api/v2/pokemon/' + which_poke)
if (res.status_code != 200):
	print (which_poke + ' not found :(')
	exit(1)
data = json.loads(res.text)['abilities']
print('Name: ' + json.loads(res.text)['name'])
print('Abilities: ')
for i in data:
	print(' - ' + i['ability']['name'])