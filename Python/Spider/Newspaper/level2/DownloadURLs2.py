#!/usr/bin/env python
# -*- coding:utf-8 -*-
import queue as Queue
import sys
import requests
import os
import threading
import time
import subprocess

class Worker(threading.Thread):  # ����������
  def __init__(self, workQueue, resultQueue, **kwds):
    threading.Thread.__init__(self, **kwds)
    self.setDaemon(True)
    self.workQueue = workQueue
    self.resultQueue = resultQueue


  def run(self):
    while 1:
      try:
        callable, args, kwds = self.workQueue.get(False)  # get task
        res = callable(*args, **kwds)
        self.resultQueue.put(res)  # put result
      except Queue.Empty:
        break

class WorkManager:  # �̳߳ع���,����
  def __init__(self, num_of_workers=10):
    self.workQueue = Queue.Queue()  # �������
    self.resultQueue = Queue.Queue()  # �������Ķ���
    self.workers = []
    self._recruitThreads(num_of_workers)

  def _recruitThreads(self, num_of_workers):
    for i in range(num_of_workers):
      worker = Worker(self.workQueue, self.resultQueue)  # ���������߳�
      self.workers.append(worker)  # ���뵽�̶߳���


  def start(self):
    for w in self.workers:
      w.start()

  def wait_for_complete(self):
    while len(self.workers):
      worker = self.workers.pop()  # �ӳ���ȡ��һ���̴߳�������
      worker.join()
      if worker.isAlive() and not self.workQueue.empty():
        self.workers.append(worker)  # ���¼����̳߳���
    print('All jobs were complete.')


  def add_job(self, callable, *args, **kwds):
    self.workQueue.put((callable, args, kwds))  # ���������м�������

  def get_result(self, *args, **kwds):
    return self.resultQueue.get(*args, **kwds)


def download_file(url):
    #print 'beg download', url
    # requests.get(url).text
    filename=url.replace('http://','').replace(':','_')
    path=filename.split('/')
    path='/'.join(path[0:-1])
    if not os.path.exists(path):
    # maybe neen a thread lock
        try:
            os.makedirs(path)
        except:
            print("exist")
    if os.path.exists(filename):return
    # GetImage(url,filename)
    # cmd = 'wget --header=\"accept-encoding:gzip\" '+url+' -O '+filename
    num = filename.split('/')[-2]
    # header = " --header=\"Referer: http://www.zngirls.com/g/" + num + "/index.html\" "
    cmd = 'wget -U \"\" '+ url + ' -O ' + filename
    # print(cmd)
    # cmd = 'curl --compressed -o '+filename+' '+url
    subprocess.call(cmd)
    # urllib.urlretrieve(url, filename, callbackfunc)




num_of_threads = 256
_st = time.time()
wm = WorkManager(num_of_threads)
print(num_of_threads)
# urls = ['http://www.baidu.com'] * 1000

f = open('items.txt','r')
urls = f.readlines()
f.close()

for i in urls:
    wm.add_job(download_file, i[:-1])
wm.start()
wm.wait_for_complete()
print(time.time() - _st)

# 15:10-2:44
# 122G 41730.37442469597Seconds
# Average Speed 2.92 MB/s