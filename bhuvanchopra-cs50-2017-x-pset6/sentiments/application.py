from flask import Flask, redirect, render_template, request, url_for

import helpers
import os,sys
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name,count=100)
    l=[]
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    b=Analyzer(positives,negatives)
    positive=0
    negative=0
    neutral=0
    
    for text in tweets:
        l.append(b.analyze(text))
        if b.analyze(text)>0:
            positive+=1
        elif b.analyze(text)<0:
            negative+=1
        else:
            neutral+=1
    
    #positive, negative, neutral = 0.0, 0.0, 100.0

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
