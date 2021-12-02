#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Nov  6 18:40:17 2019

@author: Carlos Alcantara and Michael P. McGarry
"""

import requests
from PIL import Image
import io
global MyInfo
#
# getMovie()
#
def getMovie(movieTitle):
    myKey = 'b0c115f8'
    # Setup the URL and two parameters for invocation
    url = f'http://www.omdbapi.com/?'
    params = {"apikey": myKey, 't': movieTitle}
    # Issue HTTP Get Request
    res = requests.get(url, params)
    print("\nJSON response form server\n")
    MyInfo=str(res.content.decode('utf-8'))
    print(res.content.decode('utf-8'))
    print("\n\n")
    # Return content of Response message decoded from JSON
    return res.json()
    

# Obtain movie data for The Lion King (STUDENTS: SELECT YOUR OWN MOVIE)
movieData = getMovie("Gladiator")

#
# Do something interesting with the data from OMDB (STUDENTS: REPLACE THE CODE BELOW WITH SOMETHING UNIQUE)
#
print("\n"+movieData['Director']+" was the director of Gladiator ("+str(movieData['Year'])+")")

#
# Get the movie poster image
#
def displayPoster(movieData, name):
    res = requests.get(movieData['Poster'])

    image = Image.open(io.BytesIO(res.content))
    image.show()
    image.save(name)

displayPoster(movieData, "MoviePicture.jpeg")
with open('MovieDetails.txt','w') as f:
    print("Title: " + movieData['Title'], file=f)
    print("Director: " + movieData['Director'], file=f)
    print("Actors: " + movieData['Actors'], file=f)
    print("Date Released: " + movieData['Released'], file=f)
    print("Language: " + movieData['Language'], file=f)
    print("Location of Film Capture: " + movieData['Country'], file=f)
    print("BoxOffice of: " + movieData['BoxOffice'], file=f)
    print("Awards: " + movieData['Awards'], file=f)
    print("Genre: " + movieData['Genre'], file=f)
    print("Description: " + movieData['Plot'], file=f)