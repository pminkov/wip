import math
import datetime
import urllib2
import time
import traceback

from flask import Flask
from multiprocessing import Process

import threading

app = Flask(__name__)

@app.route('/cpu')
def cpu():
  sum = 0
  for i in range(0, 1000):
    sum += int(math.sqrt(i)) % 100
  
  return 'Sum = %d' % sum


@app.route('/network')
def network():
  goog = urllib2.urlopen("http://www.google.com").read()

  return '[%d][%s]' % (len(goog), goog[:20])

@app.route('/disk')
def disk():
  with open("test.txt", "a") as myfile:
    myfile.write("hello there")

  return 'hi there'

qps = 1 

@app.route('/qps/<int:new_value>')
def set_qps(new_value):
  global qps
  qps = new_value
  return 'QPS is now: %d' % qps

@app.route('/inc')
def inc():
  global qps
  qps += 1
  return '%d' % qps
  

@app.route('/dec')
def dec():
  global qps
  qps -= 1
  return '%d' % qps
  
def run_cpu():
  cpu = urllib2.urlopen("http://localhost:5000/cpu").read()
  print cpu
  

def loop():
  global qps
  while True:
    print datetime.datetime.now()
    for i in range(0, qps):
      print 'Hi there %d' % i
      #p = threading.Thread(target=run_cpu)
      p = Process(target=run_cpu)
      p.start()
      time.sleep(1.0 / qps)


if __name__ == '__main__':
  p = threading.Thread(target=loop)
  p.daemon = True
  p.start()
  app.run()
